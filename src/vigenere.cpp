#include "vigenere.h"
#include "io_utils.h"
#include <vector>
#include <cstdint>

void vigenere_inplace(uint8_t* buf, size_t n, const std::string& key, bool decrypt) {
    const size_t m = key.size();
    if (m==0) return;
    for (size_t i=0; i<n; ++i) {
        uint8_t k = static_cast<uint8_t>(key[i % m]);
        buf[i] = decrypt ? static_cast<uint8_t>(buf[i] - k)
                         : static_cast<uint8_t>(buf[i] + k);
    }
}
int vigenere_stream(int ifd, int ofd, const std::string& key, bool decrypt) {
    std::vector<uint8_t> buf(1<<20); // 1 MiB
    for (;;) {
        ssize_t r = safe_read(ifd, buf.data(), buf.size());
        if (r < 0) return -1;
        if (r == 0) break;
        vigenere_inplace(buf.data(), (size_t)r, key, decrypt);
        if (!write_all(ofd, buf.data(), (size_t)r)) return -1;
    }
    return 0;
}