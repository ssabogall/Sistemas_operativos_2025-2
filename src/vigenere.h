// src/vigenere.h
#pragma once
#include <string>
#include <cstdint>

int vigenere_stream(int ifd, int ofd, const std::string& key, bool decrypt);
void vigenere_inplace(uint8_t* buf, size_t n, const std::string& key, bool decrypt);
