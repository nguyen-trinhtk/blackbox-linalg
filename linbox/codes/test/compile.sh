INCLUDES="-I../linboxbuild/linbox-install/include -I../linboxbuild/givaro-install/include -I../linboxbuild/gmp-install/include -I../linboxbuild/ff-install/include -I../linboxbuild/open-blas-install/include"
LIBDIRS="-L../linboxbuild/linbox-install/lib -L../linboxbuild/givaro-install/lib -L../linboxbuild/gmp-install/lib -L../linboxbuild/ff-install/lib -L../linboxbuild/open-blas-install/lib"
LIBS="-llinbox -lgivaro -lgmp -lopenblas"

g++ -std=c++11 $INCLUDES $LIBDIRS -o test_linbox_sparse test_linbox.cpp $LIBS

if [ $? -eq 0 ]; then
    echo "Compilation successful!"
    if [ "$1" = "run" ]; then
        echo "Running program..."
        ./test_linbox_sparse
    fi
else
    echo "Compilation failed!"
    exit 1
fi
