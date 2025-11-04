# Definición de variables
CC = g++
CFLAGS = -std=c++11 -pthread
SRC = src/main.cpp src/file_manager.cpp src/compression.cpp src/encryption.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = comp_enc_tool

# Regla principal para compilar el ejecutable
$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

# Regla para compilar los archivos .cpp
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Limpiar los archivos de compilación
clean:
	rm -f $(OBJ) $(EXEC)

# Regla para ejecutar el programa
run: $(EXEC)
	./$(EXEC) -c -i input_files/prueba.docx -o output_files/prueba.docx --comp-alg Huffman
