CXX = g++
CXXFLAGS = -Wall

GEN_SRC = src/solver/generate_matrix.cpp src/utils/utils.cpp
GEN_TARGET = build/solver/generate_matrix

PRECOND_SRC = src/solver/apply_precond.cpp src/utils/utils.cpp
PRECOND_TARGET = build/solver/apply_precond

all: $(GEN_TARGET) $(PRECOND_TARGET)

$(GEN_TARGET): $(GEN_SRC)
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(PRECOND_TARGET): $(PRECOND_SRC)
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -rf build
