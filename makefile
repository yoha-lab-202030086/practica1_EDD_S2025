# Nombre del ejecutable
TARGET = timbiriche

# Directorios
SRC_DIR = src
INC_DIR = include

# Archivos fuente
SRC = $(SRC_DIR)/main.cpp $(SRC_DIR)/Jugador.cpp

# Compilador y flags
CXX = g++
CXXFLAGS = -Wall -I$(INC_DIR)

# Regla principal
all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Ejecutar el programa
run: $(TARGET)
	./$(TARGET)

# Limpiar ejecutable
clean:
	rm -f $(TARGET)
