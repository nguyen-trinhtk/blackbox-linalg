ROOT := $(abspath .)

# External library paths (local fallback)
LOCAL_PKG_CONFIG_PATH = \
    $(ROOT)/external/linbox-1.7.1/lib/pkgconfig: \
    $(ROOT)/external/fflas-ffpack-2.5.0/lib/pkgconfig: \
    $(ROOT)/external/givaro-4.2.1/lib/pkgconfig: \
    $(ROOT)/external/OpenBLAS-0.3.30/lib/pkgconfig

# If PKG_CONFIG_PATH not provided by environment, use local fallback
PKG_CONFIG_PATH := $(if $(PKG_CONFIG_PATH),$(PKG_CONFIG_PATH),$(LOCAL_PKG_CONFIG_PATH))

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

# Use pkg-config cleanly
PKGFLAGS := $(shell PKG_CONFIG_PATH="$(PKG_CONFIG_PATH)" pkg-config --cflags --libs linbox)

LDFLAGS := \
    -L$(GMP_DIR)/lib -lgmp -lgmpxx

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
	PKG_CONFIG_PATH="$(PKG_CONFIG_PATH)" \
	$(CXX) $(CXXFLAGS) $(GEN_SRC) -o $@ $(PKGFLAGS) $(LDFLAGS)

$(PRECOND_TARGET): $(PRECOND_SRC)
	mkdir -p $(dir $@)
	PKG_CONFIG_PATH="$(PKG_CONFIG_PATH)" \
	$(CXX) $(CXXFLAGS) $(PRECOND_SRC) -o $@ $(PKGFLAGS) $(LDFLAGS)

$(SOLVE_TARGET): $(SOLVE_SRC)
	mkdir -p $(dir $@)
	PKG_CONFIG_PATH="$(PKG_CONFIG_PATH)" \
	$(CXX) $(CXXFLAGS) $(SOLVE_SRC) -o $@ $(PKGFLAGS) $(LDFLAGS)

clean:
	rm -rf build
