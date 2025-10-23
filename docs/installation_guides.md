# LinBox Installation Guides
This tool is heavily dependent on LinBox, which is a template library for exact, high-performance linear algebra computations. Currently, we are using GMP 6.3.0, Givaro 4.2.1, OpenBLAS 0.3.30, and FFLAS-FFPACK 2.5.0. 


NOTE: $ROOT is path to current working directory

### I. Installing dependencies
##### 1. GMP
```shell
wget https://gmplib.org/download/gmp/gmp-6.3.0.tar.xz
tar -xvf gmp-6.3.0.tar.xz
cd gmp-6.3.0
./configure --prefix=$ROOT/gmp-6.3.0 --enable-cxx
make
make install
cd ..
```

##### 2. Givaro
```shell
wget https://github.com/linbox-team/givaro/releases/download/v4.2.1/givaro-4.2.1.tar.gz
tar -xvzf givaro-4.2.1.tar.gz
cd givaro-4.2.1
./configure --prefix=$ROOT/givaro-4.2.1
make        # Optional: make check
make install
cd ..
```

##### 3. OpenBLAS
```shell
wget https://github.com/OpenMathLib/OpenBLAS/releases/download/v0.3.30/OpenBLAS-0.3.30.tar.gz
tar -xvzf OpenBLAS-0.3.30.tar.gz
cd OpenBLAS-0.3.30
make
make PREFIX=$ROOT/OpenBLAS-0.3.30 install
cd ..
```

##### 4. FFLAS-FFPACK
```shell
wget https://github.com/linbox-team/fflas-ffpack/releases/download/v2.5.0/fflas-ffpack-2.5.0.tar.gz
tar -xvzf fflas-ffpack-2.5.0.tar.gz
cd fflas-ffpack-2.5.0
./configure --prefix=$ROOT/fflas-ffpack-2.5.0 \
            --with-blas-libs="-L$ROOT/OpenBLAS-0.3.30/lib -lopenblas" \
            --with-blas-cflags="-I$ROOT/OpenBLAS-0.3.30/include"
make
make autotune   # Optional
make install
cd ..
```

### II. Installing LinBox
```shell
wget https://github.com/linbox-team/linbox/releases/download/v1.7.1/linbox-1.7.1.tar.gz
tar -xvzf linbox-1.7.1.tar.gz
cd linbox-1.7.1
./configure --prefix=$ROOT/linbox \
            --with-givaro=$ROOT/givaro-4.2.1 \
            --with-fflas-ffpack=$ROOT/fflas-ffpack-2.5.0
make
make install
cd ..
```

### III. Export environment variables
Add these to `.bashrc`: 
```shell
export PATH=$ROOT/gmp-6.3.0/bin:$ROOT/givaro-4.2.1/bin:$ROOT/OpenBLAS-0.3.30/bin:$ROOT/fflas-ffpack-2.5.0/bin:$ROOT/linbox-1.7.1/bin:$PATH

export LD_LIBRARY_PATH=$ROOT/gmp-6.3.0/lib:$ROOT/givaro-4.2.1/lib:$ROOT/OpenBLAS-0.3.30/lib:$ROOT/fflas-ffpack-2.5.0/lib:$ROOT/linbox-1.7.1/lib:$LD_LIBRARY_PATH

export PKG_CONFIG_PATH=$ROOT/gmp-6.3.0/lib/pkgconfig:$ROOT/givaro-4.2.1/lib/pkgconfig:$ROOT/OpenBLAS-0.3.30/lib/pkgconfig:$ROOT/fflas-ffpack-2.5.0/lib/pkgconfig:$ROOT/linbox-1.7.1/lib/pkgconfig:$PKG_CONFIG_PATH

export CPPFLAGS="-I$ROOT/gmp-6.3.0/include -I$ROOT/givaro-4.2.1/include -I$ROOT/OpenBLAS-0.3.30/include -I$ROOT/fflas-ffpack-2.5.0/include -I$ROOT/linbox-1.7.1/include"

export LDFLAGS="-L$ROOT/gmp-6.3.0/lib -L$ROOT/givaro-4.2.1/lib -L$ROOT/OpenBLAS-0.3.30/lib -L$ROOT/fflas-ffpack-2.5.0/lib -L$ROOT/linbox-1.7.1/lib"

# For macOS
export DYLD_LIBRARY_PATH=$LD_LIBRARY_PATH
```