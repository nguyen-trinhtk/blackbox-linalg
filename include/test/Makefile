CXX = g++
CXXFLAGS = -std=c++11 -Wall -O2

# Include paths for matrix/random-matrix.h, NTL, and GMP
INCLUDES = -I$(PWD)/../../include \
           -I$(PWD)/../../external/ntl/ntl-build/ntl-11.5.1/include \
           -I$(PWD)/../../external/ntl/ntl-build/gmp-install/include

# Link NTL and GMP libraries
LIBS = $(PWD)/../../external/ntl/ntl-build/ntl-11.5.1/src/ntl.a -L$(PWD)/../../external/ntl/ntl-build/gmp-install/lib -lgmp

all: main

main: main.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $< $(LIBS)

clean:
	rm -f main *.o

run: main
	DYLD_LIBRARY_PATH=$(PWD)/../../external/ntl/ntl-build/gmp-install/lib ./main

debug: CXXFLAGS += -g -DDEBUG
debug: main

rebuild: clean all

.PHONY: all clean run debug rebuild