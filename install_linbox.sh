#!/bin/bash
set -e

ROOT=${ROOT:-$PWD}

# GMP
wget https://gmplib.org/download/gmp/gmp-6.3.0.tar.xz
tar -xvf gmp-6.3.0.tar.xz
cd gmp-6.3.0
./configure --prefix=$ROOT/gmp-6.3.0 --enable-cxx
make -j$(nproc) && make install
cd ..

# Givaro
wget https://github.com/linbox-team/givaro/releases/download/v4.2.1/givaro-4.2.1.tar.gz
tar -xvzf givaro-4.2.1.tar.gz
cd givaro-4.2.1
./configure --prefix=$ROOT/givaro-4.2.1 --with-gmp-prefix=$ROOT/gmp-6.3.0
make -j$(nproc) && make install
cd ..

# OpenBLAS
wget https://github.com/OpenMathLib/OpenBLAS/releases/download/v0.3.30/OpenBLAS-0.3.30.tar.gz
tar -xvzf OpenBLAS-0.3.30.tar.gz
cd OpenBLAS-0.3.30
make -j$(nproc) && make PREFIX=$ROOT/OpenBLAS-0.3.30 install
cd ..

# FFLAS-FFPACK
wget https://github.com/linbox-team/fflas-ffpack/releases/download/v2.5.0/fflas-ffpack-2.5.0.tar.gz
tar -xvzf fflas-ffpack-2.5.0.tar.gz
cd fflas-ffpack-2.5.0
./configure --prefix=$ROOT/fflas-ffpack-2.5.0 \
            --with-blas-libs="-L$ROOT/OpenBLAS-0.3.30/lib -lopenblas" \
            --with-blas-cflags="-I$ROOT/OpenBLAS-0.3.30/include"
make -j$(nproc) && make autotune && make install
cd ..

# LinBox
wget https://github.com/linbox-team/linbox/releases/download/v1.7.1/linbox-1.7.1.tar.gz
tar -xvzf linbox-1.7.1.tar.gz
cd linbox-1.7.1
./configure --prefix=$ROOT/linbox \
            --with-givaro=$ROOT/givaro-4.2.1 \
            --with-fflas-ffpack=$ROOT/fflas-ffpack-2.5.0
make -j$(nproc) && make install
cd ..

# Pass environment variables to .bashrc
echo "export PATH=$ROOT/gmp-6.3.0/bin:$ROOT/givaro-4.2.1/bin:$ROOT/OpenBLAS-0.3.30/bin:$ROOT/fflas-ffpack-2.5.0/bin:$ROOT/linbox/bin:\$PATH" >> ~/.bashrc
echo "export LD_LIBRARY_PATH=$ROOT/gmp-6.3.0/lib:$ROOT/givaro-4.2.1/lib:$ROOT/OpenBLAS-0.3.30/lib:$ROOT/fflas-ffpack-2.5.0/lib:$ROOT/linbox/lib:\$LD_LIBRARY_PATH" >> ~/.bashrc
echo "export PKG_CONFIG_PATH=$ROOT/gmp-6.3.0/lib/pkgconfig:$ROOT/givaro-4.2.1/lib/pkgconfig:$ROOT/OpenBLAS-0.3.30/lib/pkgconfig:$ROOT/fflas-ffpack-2.5.0/lib/pkgconfig:$ROOT/linbox/lib/pkgconfig:\$PKG_CONFIG_PATH" >> ~/.bashrc
echo "export CPPFLAGS=\"-I$ROOT/gmp-6.3.0/include -I$ROOT/givaro-4.2.1/include -I$ROOT/OpenBLAS-0.3.30/include -I$ROOT/fflas-ffpack-2.5.0/include -I$ROOT/linbox/include\"" >> ~/.bashrc
echo "export LDFLAGS=\"-L$ROOT/gmp-6.3.0/lib -L$ROOT/givaro-4.2.1/lib -L$ROOT/OpenBLAS-0.3.30/lib -L$ROOT/fflas-ffpack-2.5.0/lib -L$ROOT/linbox/lib\"" >> ~/.bashrc

echo "Installation complete! Reload shell or run 'source ~/.bashrc'."
