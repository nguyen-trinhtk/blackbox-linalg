CXX = g++
CXXFLAGS = -Wall -O2
SRC = src/solver/generate_matrix.cpp
TARGET = build/solver/generate_matrix

all: $(TARGET)

$(TARGET): $(SRC)
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -rf build
