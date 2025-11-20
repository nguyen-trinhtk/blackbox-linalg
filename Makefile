# CXX = clang++
# CXXFLAGS = -Wall
ROOT := $(abspath .)

# Paths to external libraries
GMP_DIR          := $(ROOT)/external/gmp-6.3.0
GIVARO_DIR       := $(ROOT)/external/givaro-4.2.1
OPENBLAS_DIR     := $(ROOT)/external/OpenBLAS-0.3.30
FFLAS_FFPACK_DIR := $(ROOT)/external/fflas-ffpack-2.5.0
LINBOX_DIR       := $(ROOT)/external/linbox-1.7.1

PKG_CONFIG_PATH := $(LINBOX_DIR)/lib/pkgconfig:$(FFLAS_FFPACK_DIR)/lib/pkgconfig:$(GIVARO_DIR)/lib/pkgconfig:$(OPENBLAS_DIR)/lib/pkgconfig

CXX := clang++
CXXFLAGS := -std=c++17 -O3 -Wall -Wextra -I$(GMP_DIR)/include
PKGFLAGS := $(shell PKG_CONFIG_PATH=$(PKG_CONFIG_PATH) pkg-config --cflags --libs linbox 2>/dev/null)
LDFLAGS := -L$(GMP_DIR)/lib -lgmp -lgmpxx

GEN_SRC = src/solver/generate_matrix.cpp src/utils/utils.cpp
GEN_TARGET = build/solver/generate_matrix

PRECOND_SRC = src/solver/apply_precond.cpp src/utils/utils.cpp src/utils/sms_mult.cpp
PRECOND_TARGET = build/solver/apply_precond

SOLVE_SRC = src/solver/run_wiedemann.cpp
SOLVE_TARGET = build/solver/run_wiedemann

all: $(GEN_TARGET) $(PRECOND_TARGET) $(SOLVE_TARGET)

$(GEN_TARGET): $(GEN_SRC)
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(GEN_SRC) -o $@ $(PKGFLAGS) $(LDFLAGS)

$(PRECOND_TARGET): $(PRECOND_SRC)
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(PRECOND_SRC) -o $@ $(PKGFLAGS) $(LDFLAGS)

$(SOLVE_TARGET): $(SOLVE_SRC)
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(SOLVE_SRC) -o $@ $(PKGFLAGS) $(LDFLAGS)

clean:
	rm -rf build
