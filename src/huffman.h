// src/huffman.h
#pragma once
#include <string>

int huf_compress_then_optional_vigenere(int ifd, int ofd,
                                        const std::string& key,
                                        bool applyVigenere);

int huf_decompress_then_optional_vigenere(int ifd, int ofd,
                                          const std::string& key,
                                          bool undoVigenere);
