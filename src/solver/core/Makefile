# Compiler settings
CC = gcc
CXX = g++
CFLAGS = -Wall -Wextra -O2 -std=c11
CXXFLAGS = -Wall -Wextra -O2 -std=c++17

# Directories
SRC_DIR = .
OBJ_DIR = ./build
BIN_DIR = ./bin

# Source files
C_SRCS = $(SRC_DIR)/matrix_gen.c $(SRC_DIR)/preconditioner.c
CXX_SRCS = $(SRC_DIR)/matrix_cli.cpp

# Object files
C_OBJS = $(OBJ_DIR)/matrix_gen.o $(OBJ_DIR)/preconditioner.o
CXX_OBJS = $(OBJ_DIR)/matrix_cli.o

# Executable
TARGET = $(BIN_DIR)/mat_precond

# Default target
all: $(TARGET)

# Link executable
$(TARGET): $(C_OBJS) $(CXX_OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile C sources
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile C++ sources
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean