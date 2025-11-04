#pragma once
#include <string>
#include "huffman.h"
#include "vigenere.h"

int run_cli(bool doC, bool doD, bool doE, bool doU,
            const std::string& compAlg, const std::string& encAlg,
            const std::string& inPath, const std::string& outPath,
            const std::string& key);
