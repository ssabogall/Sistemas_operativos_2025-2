#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include <vector>

void processFile(const std::string &path) {
    int fd = open(path.c_str(), O_RDONLY);
    if (fd == -1) {
        std::cerr << "Error al abrir el archivo: " << path << std::endl;
        return;
    }

    // Leer y procesar el archivo
    char buffer[1024];
    ssize_t bytesRead;
    while ((bytesRead = read(fd, buffer, sizeof(buffer))) > 0) {
        // Llamar a funciones de compresión/encriptación
    }

    close(fd);
}

void processDirectory(const std::string &dirPath) {
    DIR *dir = opendir(dirPath.c_str());
    if (!dir) {
        std::cerr << "Error al abrir el directorio: " << dirPath << std::endl;
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != nullptr) {
        if (entry->d_type == DT_REG) {  // Si es archivo regular
            processFile(dirPath + "/" + entry->d_name);
        }
    }

    closedir(dir);
}
