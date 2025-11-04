// src/huffman.cpp
#include "huffman.h"
#include "io_utils.h"
#include "vigenere.h"
#include <vector>
#include <cstdint>

int huf_compress_then_optional_vigenere(int ifd, int ofd,
                                        const std::string& key,
                                        bool applyVigenere)
{
    std::vector<uint8_t> buf(1<<20); // 1 MiB
    for (;;) {
        ssize_t r = safe_read(ifd, buf.data(), buf.size());
        if (r < 0) return -1;
        if (r == 0) break;
        if (applyVigenere) {
            vigenere_inplace(buf.data(), (size_t)r, key, /*decrypt=*/false);
        }
        if (!write_all(ofd, buf.data(), (size_t)r)) return -1;
    }
    return 0;
}

int huf_decompress_then_optional_vigenere(int ifd, int ofd,
                                          const std::string& key,
                                          bool undoVigenere)
{
    std::vector<uint8_t> buf(1<<20);
    for (;;) {
        ssize_t r = safe_read(ifd, buf.data(), buf.size());
        if (r < 0) return -1;
        if (r == 0) break;
        if (undoVigenere) {
            vigenere_inplace(buf.data(), (size_t)r, key, /*decrypt=*/true);
        }
        if (!write_all(ofd, buf.data(), (size_t)r)) return -1;
    }
    return 0;
}
