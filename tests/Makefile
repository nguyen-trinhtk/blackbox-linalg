CXX = g++
CXXFLAGS = -std=c++11 -Wall -O2

INCLUDES = -I$(PWD)/../include -I/usr/local/include
LIBS = -L/usr/local/lib -lntl -lgmp

all: main matvec bm wiedemann

main: main.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $< $(LIBS)

matvec: run-matvec.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $< $(LIBS)

bm: run-bm.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $< $(LIBS)

wiedemann: run-wiedemann.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $< $(LIBS)

run-main: main
	LD_LIBRARY_PATH=/usr/local/lib ./main

run-matvec: matvec
	LD_LIBRARY_PATH=/usr/local/lib ./matvec

run-bm: bm
	LD_LIBRARY_PATH=/usr/local/lib ./bm

run-wiedemann: wiedemann
	LD_LIBRARY_PATH=/usr/local/lib ./wiedemann

clean:
	rm -f main matvec bm wiedemann *.o

.PHONY: all clean run-main run-matvec run-bm run-wiedemann