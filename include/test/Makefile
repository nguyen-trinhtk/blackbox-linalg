CXX = g++
CXXFLAGS = -std=c++11 -Wall -O2

# Include paths for matrix/random-matrix.h, NTL, and GMP
INCLUDES = -I$(PWD)/../../include \
           -I$(PWD)/../../external/ntl/ntl-build/ntl-11.5.1/include \
           -I$(PWD)/../../external/ntl/ntl-build/gmp-install/include

# Link NTL and GMP libraries
LIBS = $(PWD)/../../external/ntl/ntl-build/ntl-11.5.1/src/ntl.a -L$(PWD)/../../external/ntl/ntl-build/gmp-install/lib -lgmp

all: main test-matvec test-bm 
# test-wiedemann

main: main.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $< $(LIBS)

test-matvec: test-matvec.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $< $(LIBS)

test-bm: test-bm.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $< $(LIBS)

# test-wiedemann: test-wiedemann.cpp
# 	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $< $(LIBS)

clean:
	rm -f main test-matvec test-bm *.o
# test-wiedemann 

run: main
	DYLD_LIBRARY_PATH=$(PWD)/../../external/ntl/ntl-build/gmp-install/lib ./main

run-matvec: test-matvec
	DYLD_LIBRARY_PATH=$(PWD)/../../external/ntl/ntl-build/gmp-install/lib ./test-matvec

run-bm: test-bm
	DYLD_LIBRARY_PATH=$(PWD)/../../external/ntl/ntl-build/gmp-install/lib ./test-bm

# run-wiedemann: test-wiedemann
# 	DYLD_LIBRARY_PATH=$(PWD)/../../external/ntl/ntl-build/gmp-install/lib ./test-wiedemann

debug: CXXFLAGS += -g -DDEBUG
debug: main

rebuild: clean all

.PHONY: all clean run run-matvec run-bm debug rebuild
# run-wiedemann