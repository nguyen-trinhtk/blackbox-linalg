# ===== Makefile for LinBox examples (minpoly + echelon) =====

ROOT := $(abspath ..)

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

# Targets
TARGETS := minpoly echelon
MINPOLY_SRC := minpoly.C
ECHELON_SRC := echelon.C

.PHONY: all clean

all: $(TARGETS)

# Build minpoly
minpoly: $(MINPOLY_SRC)
	@if [ -z "$(PKGFLAGS)" ]; then \
	    echo "Error: pkg-config could not find linbox.pc."; \
	    echo "Try manually running:"; \
	    echo "  export PKG_CONFIG_PATH=$(PKG_CONFIG_PATH)"; \
	    echo "  pkg-config --cflags --libs linbox"; \
	    exit 1; \
	fi
	@echo "Building minpoly with flags: $(PKGFLAGS)"
	$(CXX) $(CXXFLAGS) $(MINPOLY_SRC) -o $@ $(PKGFLAGS) $(LDFLAGS)

# Build echelon
echelon: $(ECHELON_SRC)
	@if [ -z "$(PKGFLAGS)" ]; then \
	    echo "Error: pkg-config could not find linbox.pc."; \
	    echo "Try manually running:"; \
	    echo "  export PKG_CONFIG_PATH=$(PKG_CONFIG_PATH)"; \
	    echo "  pkg-config --cflags --libs linbox"; \
	    exit 1; \
	fi
	@echo "Building echelon with flags: $(PKGFLAGS)"
	$(CXX) $(CXXFLAGS) $(ECHELON_SRC) -o $@ $(PKGFLAGS) $(LDFLAGS)

clean:
	rm -f $(TARGETS)
