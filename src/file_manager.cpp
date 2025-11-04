#include "file_manager.h"
#include "io_utils.h"
#include "thread_pool.h"
#include "huffman.h"
#include "vigenere.h"
#include <dirent.h>
#include <fcntl.h>
#include <vector>
#include <string>
#include <iostream>
#include <errno.h>
#include "huffman.h"
#include "vigenere.h"


static int process_one_file(const std::string& in, const std::string& out,
                            bool doC, bool doD, bool doE, bool doU,
                            const std::string& compAlg,
                            const std::string& encAlg,
                            const std::string& key)
{
    // open input
    int ifd = ::open(in.c_str(), O_RDONLY | O_CLOEXEC | O_NOFOLLOW);
    if (ifd < 0) { perror(("open "+in).c_str()); return -1; }

    // crear salida temporal (para atomicidad)
    std::string outTmp = out + ".tmp";
    int ofd = ::open(outTmp.c_str(), O_WRONLY|O_CLOEXEC|O_CREAT|O_TRUNC, 0644);
    if (ofd < 0) { perror(("open "+outTmp).c_str()); ::close(ifd); return -1; }

    int ret = 0;
    if (doC && !doD && !doU) {
        ret = huf_compress_then_optional_vigenere(ifd, ofd, key, doE); // pipeline -c(-e)
    } else if (doD && !doC && !doE) {
        ret = huf_decompress_then_optional_vigenere(ifd, ofd, key, doU); // pipeline -d(-u)
    } else if (doE && !doC && !doD) {
        ret = vigenere_stream(ifd, ofd, key, /*decrypt=*/false);
    } else if (doU && !doC && !doD) {
        ret = vigenere_stream(ifd, ofd, key, /*decrypt=*/true);
    } else if (doC && doE && !doD && !doU) {
        ret = huf_compress_then_optional_vigenere(ifd, ofd, key, /*applyVig=*/true);
    } else {
        std::cerr << "Combinación no soportada aún.\n"; ret = -1;
    }

    int e1 = ::close(ifd);
    int e2 = ::close(ofd);
    if (ret==0 && e1==0 && e2==0) {
        if (::rename(outTmp.c_str(), out.c_str()) != 0) { perror("rename"); ret=-1; }
    } else {
        ::unlink(outTmp.c_str());
    }
    return ret;
}

int run_cli(bool doC, bool doD, bool doE, bool doU,
            const std::string& compAlg, const std::string& encAlg,
            const std::string& inPath, const std::string& outPath,
            const std::string& key)
{
    if (is_regular_file(inPath)) {
        // Si outPath es carpeta, crea nombre destino derivado
        std::string out = outPath;
        if (is_directory(outPath)) {
            // simple: añade sufijo
            out = outPath + "/output.bin";
        }
        return process_one_file(inPath, out, doC,doD,doE,doU, compAlg, encAlg, key);
    }

    if (is_directory(inPath)) {
        // recorrer y usar pool de hilos
        ThreadPool pool(std::max(1u, std::thread::hardware_concurrency()));
        DIR* dir = ::opendir(inPath.c_str());
        if (!dir) { perror(("opendir "+inPath).c_str()); return -1; }
        struct dirent* ent;
        while ((ent = ::readdir(dir)) != nullptr) {
            if (ent->d_type != DT_REG) continue; // solo archivos regulares
            std::string file = inPath + "/" + ent->d_name;
            std::string out = outPath + "/" + std::string(ent->d_name) + ".out";
            pool.submit([=]{
                (void)process_one_file(file, out, doC,doD,doE,doU, compAlg, encAlg, key);
            });
        }
        ::closedir(dir);
        pool.close();
        return 0;
    }

    std::cerr << "Ruta de entrada inválida.\n";
    return -1;
}
