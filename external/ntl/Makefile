CXX = g++
CXXFLAGS = -std=c++11 -Wall -O2

INCLUDES = -I$(PWD)/ntl-build/ntl-11.5.1/include -I$(PWD)/ntl-build/gmp-install/include
LIBS = $(PWD)/ntl-build/ntl-11.5.1/src/ntl.a -L$(PWD)/ntl-build/gmp-install/lib -lgmp

all: main

main: main.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $< $(LIBS)

clean:
	rm -f main *.o

run: main
	./main

debug: CXXFLAGS += -g -DDEBUG
debug: main

rentl-build: clean all

.PHONY: all clean run debug rentl-build