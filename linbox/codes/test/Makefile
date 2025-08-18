CXX = g++
CXXFLAGS = -std=c++11 -Wall -O2

INCLUDES = -I../linboxbuild/linbox-install/include \
           -I../linboxbuild/givaro-install/include \
           -I../linboxbuild/gmp-install/include \
           -I../linboxbuild/ff-install/include \
           -I../linboxbuild/open-blas-install/include

LIBDIRS = -L../linboxbuild/linbox-install/lib \
          -L../linboxbuild/givaro-install/lib \
          -L../linboxbuild/gmp-install/lib \
          -L../linboxbuild/ff-install/lib \
          -L../linboxbuild/open-blas-install/lib

LIBS = -llinbox -lgivaro -lgmp -lopenblas

all: test_linbox_sparse

test_linbox_sparse: test_linbox.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(LIBDIRS) -o $@ $< $(LIBS)

clean:
	rm -f test_linbox_sparse test_linbox_dense *.o

run: test_linbox_sparse
	./test_linbox_sparse

debug: CXXFLAGS += -g -DDEBUG
debug: test_linbox_sparse

rebuild: clean all

.PHONY: all clean run debug rebuild
