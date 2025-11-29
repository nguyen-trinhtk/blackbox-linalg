# #!/usr/bin/env bash
# set -e

# ROOT=$(pwd)
# EXT="$ROOT/external"

# echo "=== Building external dependencies into $EXT ==="

# cd external

# # ================================================================
# # GMP
# # ================================================================
# if [ ! -d gmp-6.3.0 ]; then
#     tar xf gmp-6.3.0.tar.xz
# fi

# cd gmp-6.3.0
# ./configure \
#   --disable-shared \
#   --enable-static \
#   --enable-cxx \
#   --with-pic \
#   --prefix="$EXT/gmp-6.3.0"

# make -j$(nproc)
# make install
# cd ..

# # ================================================================
# # GIVARO
# # ================================================================
# if [ ! -d givaro-4.2.1 ]; then
#     tar xf givaro-4.2.1.tar.gz
# fi

# cd givaro-4.2.1

# CPPFLAGS="-I$EXT/gmp-6.3.0/include" \
# LDFLAGS="-L$EXT/gmp-6.3.0/lib" \
# LIBS="-lgmp -lgmpxx" \
# ./configure \
#   --disable-shared \
#   --enable-static \
#   --with-pic \
#   --with-gmp="$EXT/gmp-6.3.0" \
#   --prefix="$EXT/givaro-4.2.1"

# make -j$(nproc)
# make install
# cd ..

# # ================================================================
# # OPENBLAS
# # ================================================================
# if [ ! -d OpenBLAS-0.3.30 ]; then
#     tar xf OpenBLAS-0.3.30.tar.gz
# fi

# cd OpenBLAS-0.3.30
# make -j$(nproc) NO_SHARED=1
# make PREFIX="$EXT/OpenBLAS-0.3.30" install
# cd ..

# # ================================================================
# # FFLAS-FFPACK
# # ================================================================
# if [ ! -d fflas-ffpack-2.5.0 ]; then
#     tar xf fflas-ffpack-2.5.0.tar.gz
# fi

# cd fflas-ffpack-2.5.0

# CPPFLAGS="-I$EXT/gmp-6.3.0/include -I$EXT/givaro-4.2.1/include" \
# LDFLAGS="-L$EXT/gmp-6.3.0/lib -L$EXT/givaro-4.2.1/lib -L$EXT/OpenBLAS-0.3.30/lib" \
# LIBS="-lgmp -lgmpxx -lgivaro -lopenblas" \
# ./configure \
#   --disable-shared \
#   --enable-static \
#   --with-pic \
#   --with-blas="$EXT/OpenBLAS-0.3.30" \
#   --with-givaro="$EXT/givaro-4.2.1" \
#   --with-gmp="$EXT/gmp-6.3.0" \
#   --prefix="$EXT/fflas-ffpack-2.5.0"

# make -j$(nproc)
# make install
# cd ..

# # ================================================================
# # LINBOX
# # ================================================================
# if [ ! -d linbox-1.7.1 ]; then
#     tar xf linbox-1.7.1.tar.gz
# fi

# cd linbox-1.7.1

# CPPFLAGS="-I$EXT/gmp-6.3.0/include -I$EXT/givaro-4.2.1/include -I$EXT/fflas-ffpack-2.5.0/include" \
# LDFLAGS="-L$EXT/gmp-6.3.0/lib -L$EXT/givaro-4.2.1/lib -L$EXT/fflas-ffpack-2.5.0/lib -L$EXT/OpenBLAS-0.3.30/lib" \
# LIBS="-lgmp -lgmpxx -lgivaro -lfflas -lopenblas" \
# ./configure \
#   --disable-shared \
#   --enable-static \
#   --with-pic \
#   --with-givaro="$EXT/givaro-4.2.1" \
#   --with-gmp="$EXT/gmp-6.3.0" \
#   --with-fflas-ffpack="$EXT/fflas-ffpack-2.5.0" \
#   --prefix="$EXT/linbox-1.7.1"

# make -j$(nproc)
# make install
# cd ..

# echo "=== All external libraries built successfully ==="
