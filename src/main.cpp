#include <getopt.h>
#include <string>
#include <iostream>
#include "file_manager.h"

int main(int argc, char** argv) {
    bool doC=false, doD=false, doE=false, doU=false;
    std::string compAlg="huffman", encAlg="vigenere";
    std::string inPath, outPath, key;

    static struct option long_opts[] = {
        {"comp-alg", required_argument, 0, 1},
        {"enc-alg",  required_argument, 0, 2},
        {0,0,0,0}
    };
    int opt, idx;
    while ((opt = getopt_long(argc, argv, "cdeui:o:k:", long_opts, &idx)) != -1) {
        switch (opt) {
            case 'c': doC = true; break;
            case 'd': doD = true; break;
            case 'e': doE = true; break;
            case 'u': doU = true; break;
            case 'i': inPath = optarg; break;
            case 'o': outPath = optarg; break;
            case 'k': key = optarg; break;
            case 1:   compAlg = optarg; break; // --comp-alg
            case 2:   encAlg  = optarg; break; // --enc-alg
            default:
                std::cerr << "Uso: -c|-d|-e|-u [--comp-alg ...] [--enc-alg ...] -i in -o out [-k key]\n";
                return 1;
        }
    }

    // Validaciones básicas
    if (!(doC||doD||doE||doU)) { std::cerr<<"Error: especifique una operación.\n"; return 1; }
    if (inPath.empty() || outPath.empty()) { std::cerr<<"Error: -i y -o son obligatorios.\n"; return 1; }
    if ((doE||doU) && key.empty()) { std::cerr<<"Error: -k requerido para -e/-u.\n"; return 1; }
    if (doE && doC) { /* ok: -ce */ }
    if (doE && doC && compAlg!="huffman") { std::cerr<<"Solo huffman implementado.\n"; }
    if (doE && doD) { std::cerr<<"Combinación inválida.\n"; return 1; }
    if (doE && doC == false && doD == false && doU == false) { /* solo cifrar */ }
    if (doE && doC == false) { /* adv: comprimir después de cifrar no recomendado */ }

    return run_cli(doC, doD, doE, doU, compAlg, encAlg, inPath, outPath, key);
}
