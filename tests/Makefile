CXX = g++
CXXFLAGS = -std=c++11 -Wall -O2

# Include paths for matrix/random-matrix.h, NTL, and GMP
INCLUDES = -I$(PWD)/../include \
           -I$(PWD)/../external/ntl/ntl-build/ntl-11.5.1/include \
           -I$(PWD)/../external/ntl/ntl-build/gmp-install/include

# Link NTL and GMP libraries
LIBS = $(PWD)/../external/ntl/ntl-build/ntl-11.5.1/src/ntl.a -L$(PWD)/../external/ntl/ntl-build/gmp-install/lib -lgmp

all: main matvec bm wiedemann

main: main.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $< $(LIBS)

matvec: run-matvec.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $< $(LIBS)

bm: run-bm.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $< $(LIBS)

wiedemann: run-wiedemann.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $< $(LIBS)

run-matvec: matvec
	DYLD_LIBRARY_PATH=$(PWD)/../../external/ntl/ntl-build/gmp-install/lib ./matvec

run-bm: bm
	DYLD_LIBRARY_PATH=$(PWD)/../../external/ntl/ntl-build/gmp-install/lib ./bm

run-wiedemann: wiedemann
	DYLD_LIBRARY_PATH=$(PWD)/../../external/ntl/ntl-build/gmp-install/lib ./wiedemann

clean:
	rm -f main matvec bm wiedemann *.o

.PHONY: all clean run-matvec run-bm run-wiedemann