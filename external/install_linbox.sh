#!/bin/bash
set -e

ROOT=$PWD

# 1. GMP
wget https://gmplib.org/download/gmp/gmp-6.3.0.tar.xz
tar -xvf gmp-6.3.0.tar.xz
rm gmp-6.3.0.tar.xz
cd gmp-6.3.0
./configure --prefix=$ROOT/gmp-6.3.0 --enable-cxx
make && make install
cd ..

# Export GMP env
export PATH="$ROOT/gmp-6.3.0/bin:$PATH"
export LD_LIBRARY_PATH="$ROOT/gmp-6.3.0/lib:$LD_LIBRARY_PATH"
export PKG_CONFIG_PATH="$ROOT/gmp-6.3.0/lib/pkgconfig:$PKG_CONFIG_PATH"
export CPPFLAGS="-I$ROOT/gmp-6.3.0/include"
export LDFLAGS="-L$ROOT/gmp-6.3.0/lib"
export DYLD_LIBRARY_PATH=$LD_LIBRARY_PATH


# 2. Givaro
wget https://github.com/linbox-team/givaro/releases/download/v4.2.1/givaro-4.2.1.tar.gz
tar -xvzf givaro-4.2.1.tar.gz
rm givaro-4.2.1.tar.gz
cd givaro-4.2.1
./configure --prefix=$ROOT/givaro-4.2.1 --with-gmp-prefix=$ROOT/gmp-6.3.0
make && make install
cd ..

# Export Givaro env
export PATH="$ROOT/givaro-4.2.1/bin:$PATH"
export LD_LIBRARY_PATH="$ROOT/givaro-4.2.1/lib:$LD_LIBRARY_PATH"
export PKG_CONFIG_PATH="$ROOT/givaro-4.2.1/lib/pkgconfig:$PKG_CONFIG_PATH"
export CPPFLAGS="$CPPFLAGS -I$ROOT/givaro-4.2.1/include"
export LDFLAGS="$LDFLAGS -L$ROOT/givaro-4.2.1/lib"


# 3. OpenBLAS
wget https://github.com/OpenMathLib/OpenBLAS/releases/download/v0.3.30/OpenBLAS-0.3.30.tar.gz
tar -xvzf OpenBLAS-0.3.30.tar.gz
rm OpenBLAS-0.3.30.tar.gz
cd OpenBLAS-0.3.30
make && make PREFIX=$ROOT/OpenBLAS-0.3.30 install
cd ..

# Export OpenBLAS env
export PATH="$ROOT/OpenBLAS-0.3.30/bin:$PATH"
export LD_LIBRARY_PATH="$ROOT/OpenBLAS-0.3.30/lib:$LD_LIBRARY_PATH"
export PKG_CONFIG_PATH="$ROOT/OpenBLAS-0.3.30/lib/pkgconfig:$PKG_CONFIG_PATH"
export CPPFLAGS="$CPPFLAGS -I$ROOT/OpenBLAS-0.3.30/include"
export LDFLAGS="$LDFLAGS -L$ROOT/OpenBLAS-0.3.30/lib"


# 4. FFLAS-FFPACK
wget https://github.com/linbox-team/fflas-ffpack/releases/download/v2.5.0/fflas-ffpack-2.5.0.tar.gz
tar -xvzf fflas-ffpack-2.5.0.tar.gz
rm fflas-ffpack-2.5.0.tar.gz
cd fflas-ffpack-2.5.0
./configure --prefix=$ROOT/fflas-ffpack-2.5.0 \
    --with-blas-libs="-L$ROOT/OpenBLAS-0.3.30/lib -lopenblas" \
    --with-blas-cflags="-I$ROOT/OpenBLAS-0.3.30/include"
make && make autotune && make install
cd ..

# Export FFLAS-FFPACK env
export PATH="$ROOT/fflas-ffpack-2.5.0/bin:$PATH"
export LD_LIBRARY_PATH="$ROOT/fflas-ffpack-2.5.0/lib:$LD_LIBRARY_PATH"
export PKG_CONFIG_PATH="$ROOT/fflas-ffpack-2.5.0/lib/pkgconfig:$PKG_CONFIG_PATH"
export CPPFLAGS="$CPPFLAGS -I$ROOT/fflas-ffpack-2.5.0/include"
export LDFLAGS="$LDFLAGS -L$ROOT/fflas-ffpack-2.5.0/lib"

# 5. LinBox
wget https://github.com/linbox-team/linbox/releases/download/v1.7.1/linbox-1.7.1.tar.gz
tar -xvzf linbox-1.7.1.tar.gz
rm linbox-1.7.1.tar.gz
cd linbox-1.7.1
./configure --prefix="$ROOT/linbox-1.7.1" \
    --with-givaro="$ROOT/givaro-4.2.1" \
    --with-fflas-ffpack="$ROOT/fflas-ffpack-2.5.0" \
    --with-blas-libs="-L$ROOT/OpenBLAS-0.3.30/lib -lopenblas" \
    --with-blas-cflags="-I$ROOT/OpenBLAS-0.3.30/include"
make && make check && make install
cd ..

# Export LinBox env
export PATH="$ROOT/linbox-1.7.1/bin:$PATH"
export LD_LIBRARY_PATH="$ROOT/linbox-1.7.1/lib:$LD_LIBRARY_PATH"
export PKG_CONFIG_PATH="$ROOT/linbox-1.7.1/lib/pkgconfig:$PKG_CONFIG_PATH"
export CPPFLAGS="$CPPFLAGS -I$ROOT/linbox-1.7.1/include"
export LDFLAGS="$LDFLAGS -L$ROOT/linbox-1.7.1/lib"

echo "" >> ~/.bashrc
echo "# >>> LinBox environment setup >>>" >> ~/.bashrc
echo "export PATH=\"$PATH\"" >> ~/.bashrc
echo "export LD_LIBRARY_PATH=\"$LD_LIBRARY_PATH\"" >> ~/.bashrc
echo "export PKG_CONFIG_PATH=\"$PKG_CONFIG_PATH\"" >> ~/.bashrc
echo "export CPPFLAGS=\"$CPPFLAGS\"" >> ~/.bashrc
echo "export LDFLAGS=\"$LDFLAGS\"" >> ~/.bashrc

echo "Installation complete, reload your shell or run: source ~/.bashrc"
