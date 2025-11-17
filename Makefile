# ===== Fixed Makefile for gen_precond and solve =====

ROOT := $(abspath .)

# Paths to external libraries
GMP_DIR      := $(ROOT)/external/gmp-6.3.0
OPENBLAS_DIR := $(ROOT)/external/OpenBLAS-0.3.30
LINBOX_DIR   := $(ROOT)/external/linbox-1.7.1

# PKG_CONFIG search path
PKG_CONFIG_PATH := $(LINBOX_DIR)/lib/pkgconfig:$(GMP_DIR)/lib/pkgconfig:$(OPENBLAS_DIR)/lib/pkgconfig
export PKG_CONFIG_PATH

CXX := clang++
CXXFLAGS := -std=c++17 -stdlib=libc++ -O3 -w -DDISABLE_COMMENTATOR \
            -I$(GMP_DIR)/include \
            -I$(GMP_DIR)/include/gmp \
            -I$(ROOT)/core

LDFLAGS  := -L$(GMP_DIR)/lib -lgmp -lgmpxx -L$(OPENBLAS_DIR)/lib -lopenblas -stdlib=libc++

PKGFLAGS := $(shell pkg-config --cflags --libs linbox 2>/dev/null)

TARGETS := gen_precond run_solve

.PHONY: all clean

all: $(TARGETS)

# ===== Build gen_precond =====
GEN_PRECOND_SRCS := ./src/solver/gen_precond.cpp ./src/solver/core/matrix_gen.cpp ./src/solver/core/preconditioner.cpp

gen_precond: $(GEN_PRECOND_SRCS)
	@if [ -z "$(PKGFLAGS)" ]; then \
	    echo "Error: pkg-config could not find linbox.pc"; \
	    echo "Export PKG_CONFIG_PATH and try again:"; \
	    exit 1; \
	fi
	@echo "Building gen_precond..."
	$(CXX) $(CXXFLAGS) $(GEN_PRECOND_SRCS) -o $@ $(PKGFLAGS) $(LDFLAGS) -std=c++17 -stdlib=libc++

# ===== Build solve =====
RUN_SOLVE_SRCS := ./src/solver/run_solve.cpp \
              ./src/solver/algorithms/wiedemann.cpp \
              ./src/solver/algorithms/lcm_wiedemann.cpp

run_solve: $(RUN_SOLVE_SRCS)
	@if [ -z "$(PKGFLAGS)" ]; then \
	    echo "Error: pkg-config could not find linbox.pc"; \
	    echo "Export PKG_CONFIG_PATH and try again:"; \
	    exit 1; \
	fi
	@echo "Building run_solve..."
	$(CXX) $(CXXFLAGS) $(RUN_SOLVE_SRCS) -o $@ $(PKGFLAGS) $(LDFLAGS) -std=c++17 -stdlib=libc++

clean:
	rm -f $(TARGETS)
