ROOT := $(abspath .)

# Library prefixes
GMP_DIR          := $(ROOT)/external/gmp-6.3.0
GIVARO_DIR       := $(ROOT)/external/givaro-4.2.1
OPENBLAS_DIR     := $(ROOT)/external/OpenBLAS-0.3.30
FFLAS_FFPACK_DIR := $(ROOT)/external/fflas-ffpack-2.5.0
LINBOX_DIR       := $(ROOT)/external/linbox-1.7.1

CXX := clang++
CXXFLAGS := -std=c++17 -O3 -w \
    -I$(GMP_DIR)/include \
    -I$(GIVARO_DIR)/include \
    -I$(OPENBLAS_DIR)/include \
    -I$(FFLAS_FFPACK_DIR)/include \
    -I$(LINBOX_DIR)/include

# Use pkg-config only for LinBox headers if available
PKGFLAGS := $(shell PKG_CONFIG_PATH="$(LINBOX_DIR)/lib/pkgconfig" pkg-config --cflags --libs linbox 2>/dev/null)

# Statically link all libraries
LDFLAGS := \
    $(GMP_DIR)/lib/libgmp.a \
    $(GMP_DIR)/lib/libgmpxx.a \
    $(GIVARO_DIR)/lib/libgivaro.a \
    $(OPENBLAS_DIR)/lib/libopenblas.a \
    $(FFLAS_FFPACK_DIR)/lib/libfflas.a \
    $(LINBOX_DIR)/lib/liblinbox.a

# Build targets
GEN_SRC    = src/solver/generate_matrix.cpp src/utils/utils.cpp
GEN_TARGET = build/solver/generate_matrix

PRECOND_SRC    = src/solver/apply_precond.cpp src/utils/utils.cpp src/utils/sms_mult.cpp
PRECOND_TARGET = build/solver/apply_precond

SOLVE_SRC    = src/solver/run_wiedemann.cpp src/utils/utils.cpp
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
