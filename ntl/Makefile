CXX = g++
CXXFLAGS = -std=c++11 -Wall -O2

INCLUDES = -I$(PWD)/build/ntl-11.5.1/include -I$(PWD)/build/gmp-install/include
LIBS = $(PWD)/build/ntl-11.5.1/src/ntl.a -L$(PWD)/build/gmp-install/lib -lgmp

all: main

main: main.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $< $(LIBS)

clean:
	rm -f main *.o

run: main
	./main

debug: CXXFLAGS += -g -DDEBUG
debug: main

rebuild: clean all

.PHONY: all clean run debug rebuild