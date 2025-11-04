
# Proyecto de Compresión y Encriptación de Archivos

## Descripción

Este proyecto implementa una utilidad de línea de comandos que permite comprimir, descomprimir, encriptar y desencriptar archivos y directorios completos de manera eficiente. La eficiencia se logra mediante el procesamiento concurrente de múltiples archivos, utilizando un enfoque de **concurrencia** en sistemas multinúcleo. 

Los algoritmos utilizados para compresión son **Huffman** y para encriptación **Vigenère**. Los algoritmos están implementados desde cero, sin hacer uso de librerías externas como `zlib`, `OpenSSL` o `Crypto++`.

## Funcionalidades

- **Compresión**: Utiliza el algoritmo de compresión **Huffman** para reducir el tamaño de los archivos.
- **Descompresión**: Descomprime archivos previamente comprimidos con Huffman.
- **Encriptación**: Utiliza el algoritmo **Vigenère** para encriptar los archivos.
- **Desencriptación**: Desencripta archivos previamente encriptados usando el mismo algoritmo de Vigenère.

## Requisitos

- **Sistema operativo**: Linux (aunque puede adaptarse a otros sistemas operativos con los cambios necesarios en las llamadas al sistema).
- **Compilador**: `g++` o cualquier compilador compatible con C++17.
- **Librerías**: Ninguna librería externa (todo implementado desde cero).

## Instalación

1. Clona el repositorio:

    ```bash
    git clone https://github.com/ssabogall/Sistemas_operativos_2025-2.git
    ```

2. Navega al directorio del proyecto:

    ```bash
    cd Sistemas_operativos_2025-2
    ```

3. Compila el proyecto:

    ```bash
    g++ -std=c++17 -O3 -march=native -pthread       src/main.cpp src/file_manager.cpp src/thread_pool.cpp       src/huffman.cpp src/vigenere.cpp       -o comp_enc_tool
    ```

    Esto generará el ejecutable `comp_enc_tool`.

## Uso

La utilidad se invoca desde la terminal con el siguiente formato de comando:

```bash
./comp_enc_tool -c/-d/-e/-u --comp-alg [algoritmo_compresion] --enc-alg [algoritmo_encriptacion] -i [ruta_entrada] -o [ruta_salida] -k [clave_secreta]
```

### Parámetros

- **Operación**:  
  - `-c`: Comprimir
  - `-d`: Descomprimir
  - `-e`: Encriptar
  - `-u`: Desencriptar  
  Se pueden combinar operaciones (ej. `-ce` para comprimir y luego encriptar).

- **Algoritmo de compresión**:  
  - `--comp-alg [huffman]`: Algoritmo de compresión, actualmente solo Huffman está implementado.

- **Algoritmo de encriptación**:  
  - `--enc-alg [vigenere]`: Algoritmo de encriptación, actualmente solo Vigenère está implementado.

- **Entrada**:  
  - `-i [ruta_archivo_o_directorio]`: Ruta del archivo o directorio de entrada.

- **Salida**:  
  - `-o [ruta_archivo_o_directorio_salida]`: Ruta de salida para los archivos procesados.

- **Clave (opcional)**:  
  - `-k [clave_secreta]`: Clave secreta para las operaciones de encriptación/desencriptación.

### Ejemplos de uso

1. **Comprimir un archivo**:

    ```bash
    ./comp_enc_tool -c --comp-alg huffman -i input_files/archivo.txt -o output_files/archivo_comprimido.huf
    ```

2. **Descomprimir un archivo**:

    ```bash
    ./comp_enc_tool -d --comp-alg huffman -i output_files/archivo_comprimido.huf -o output_files/archivo_recuperado.txt
    ```

3. **Comprimir y encriptar un archivo**:

    ```bash
    ./comp_enc_tool -ce --comp-alg huffman --enc-alg vigenere -k "MiClaveSecreta" -i input_files/archivo.txt -o output_files/archivo_comprimido_encriptado.huf.enc
    ```

4. **Desencriptar y descomprimir un archivo**:

    ```bash
    ./comp_enc_tool -du --comp-alg huffman --enc-alg vigenere -k "MiClaveSecreta" -i output_files/archivo_comprimido_encriptado.huf.enc -o output_files/archivo_recuperado.txt
    ```

5. **Procesar todo un directorio (comprimir todos los archivos)**:

    ```bash
    ./comp_enc_tool -c --comp-alg huffman -i input_files/ -o output_files/
    ```

### Notas

- Si la entrada es un **directorio**, el programa procesará todos los archivos dentro de él.
- El programa utilizará concurrencia para procesar múltiples archivos a la vez, mejorando el rendimiento en sistemas multinúcleo.
- La clave (`-k`) es **obligatoria** para las operaciones de encriptación (`-e`) y desencriptación (`-u`).

## Estructura del proyecto

- **src/main.cpp**: Contiene el punto de entrada del programa y la lógica principal para el manejo de parámetros.
- **src/file_manager.cpp / file_manager.h**: Implementa la gestión de archivos (lectura, escritura, verificación de directorios/archivos).
- **src/thread_pool.cpp / thread_pool.h**: Implementa el pool de hilos para procesar archivos de manera concurrente.
- **src/huffman.cpp / huffman.h**: Implementa el algoritmo de compresión Huffman.
- **src/vigenere.cpp / vigenere.h**: Implementa el algoritmo de encriptación/desencriptación Vigenère.
- **src/io_utils.h**: Funciones auxiliares para manejo seguro de lectura y escritura de archivos.

## Contribuciones

Las contribuciones al proyecto son bienvenidas. Si deseas colaborar, por favor sigue estos pasos:

1. Haz un **fork** del repositorio.
2. Crea una rama para tu funcionalidad o corrección (`git checkout -b mi-nueva-funcionalidad`).
3. Realiza tus cambios y haz un commit (`git commit -am 'Agrega nueva funcionalidad'`).
4. Haz un push a tu rama (`git push origin mi-nueva-funcionalidad`).
5. Abre un pull request con una descripción detallada de lo que has cambiado.

