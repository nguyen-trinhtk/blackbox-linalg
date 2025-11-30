ROOT := $(abspath ../..)

GMP_DIR          := $(ROOT)/external/gmp-6.3.0
GIVARO_DIR       := $(ROOT)/external/givaro-4.2.1
OPENBLAS_DIR     := $(ROOT)/external/OpenBLAS-0.3.30
FFLAS_FFPACK_DIR := $(ROOT)/external/fflas-ffpack-2.5.0
LINBOX_DIR       := $(ROOT)/external/linbox-1.7.1

PKG_CONFIG_PATH := \
    $(LINBOX_DIR)/lib/pkgconfig:\
    $(FFLAS_FFPACK_DIR)/lib/pkgconfig:\
    $(GIVARO_DIR)/lib/pkgconfig:\
    $(OPENBLAS_DIR)/lib/pkgconfig

CXX := clang++
CXXFLAGS := -std=c++17 -O3 -w -I$(GMP_DIR)/include

PKGFLAGS := $(shell PKG_CONFIG_PATH=$(PKG_CONFIG_PATH) pkg-config --cflags --libs linbox)

LDFLAGS := \
    -L$(GMP_DIR)/lib -lgmp -lgmpxx \
    -L$(OPENBLAS_DIR)/lib -lopenblas

SRC = main.cpp
TARGET = main

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $@ $(PKGFLAGS) $(LDFLAGS)

clean:
	rm -rf build
