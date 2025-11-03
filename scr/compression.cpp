#include <iostream>
#include <getopt.h>
#include <string>

int main(int argc, char *argv[]) {
    int op;
    std::string compAlg = "Huffman";  // Valor por defecto
    std::string encAlg = "Vigenere";  // Valor por defecto
    std::string inputFile, outputFile, key;

    while ((op = getopt(argc, argv, "cdeu:i:o:k:")) != -1) {
        switch (op) {
            case 'c':
                std::cout << "Operación: Comprimir\n";
                break;
            case 'd':
                std::cout << "Operación: Descomprimir\n";
                break;
            case 'e':
                std::cout << "Operación: Encriptar\n";
                break;
            case 'u':
                std::cout << "Operación: Desencriptar\n";
                break;
            case 'i':
                inputFile = optarg;
                break;
            case 'o':
                outputFile = optarg;
                break;
            case 'k':
                key = optarg;
                break;
            case '?':
                // Si los argumentos son incorrectos o faltan
                std::cerr << "Error en los argumentos\n";
                return 1;
        }
    }

    // Aquí puedes seguir con la lógica de aplicar las operaciones
    return 0;
}
