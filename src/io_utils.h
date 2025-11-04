#pragma once
#include <unistd.h>
#include <cerrno>
#include <cstdint>
#include <sys/stat.h>

inline ssize_t safe_read(int fd, void* buf, size_t n) {
    for (;;) {
        ssize_t r = ::read(fd, buf, n);
        if (r >= 0) return r;
        if (errno == EINTR) continue;
        return -1;
    }
}
inline bool write_all(int fd, const void* buf, size_t n) {
    const uint8_t* p = static_cast<const uint8_t*>(buf);
    size_t left = n;
    while (left) {
        ssize_t w = ::write(fd, p, left);
        if (w < 0 && errno == EINTR) continue;
        if (w <= 0) return false;
        p += w; left -= w;
    }
    return true;
}
inline bool is_regular_file(const std::string& path) {
    struct stat st{};
    if (::stat(path.c_str(), &st) != 0) return false;
    return S_ISREG(st.st_mode);
}
inline bool is_directory(const std::string& path) {
    struct stat st{};
    if (::stat(path.c_str(), &st) != 0) return false;
    return S_ISDIR(st.st_mode);
}
