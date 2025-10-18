# LinBox Installation Guides

NOTE: $ROOT is path to current working directory

### 1. GMP
- Grab & extract zip file: `wget https://gmplib.org/download/gmp/gmp-6.3.0.tar.xz && tar -xvf gmp-6.3.0.tar.xz`
- Configure: `cd gmp-6.3.0 && ./configure --prefix=$ROOT/gmp-6.3.0 --enable-cxx`
- Make: `make && make check`
- Install: `make install`
- Update environment variables:
```
export PATH=$ROOT/gmp-6.3.0/bin:$PATH
export LD_LIBRARY_PATH=$ROOT/gmp-6.3.0/lib:$LD_LIBRARY_PATH
export PKG_CONFIG_PATH=$ROOT/gmp-6.3.0/lib/pkgconfig:$PKG_CONFIG_PATH
export CPPFLAGS="-I$ROOT/gmp-6.3.0/include"
export LDFLAGS="-L$ROOT/gmp-6.3.0/lib"
```

### 2. Givaro (requires GMP)
- Grab & extract zip file: `wget https://github.com/linbox-team/givaro/releases/download/v4.2.1/givaro-4.2.1.tar.gz && tar -xvzf givaro-4.2.1.tar.gz`
- Configure: `cd givaro-4.2.1 && ./configure --prefix=$ROOT/givaro-4.2.1`
- Make: `make && make check`
- Install: `make install`
- Export environment variables: 
```
export PATH=$ROOT/givaro-4.2.1/bin:$PATH
export LD_LIBRARY_PATH=$ROOT/givaro-4.2.1/lib:$LD_LIBRARY_PATH
export PKG_CONFIG_PATH=$ROOT/givaro-4.2.1/lib/pkgconfig:$PKG_CONFIG_PATH
export CPPFLAGS="$CPPFLAGS -I$ROOT/givaro-4.2.1/include"
export LDFLAGS="$LDFLAGS -L$ROOT/givaro-4.2.1/lib"
```

### 3. OpenBLAS
- Grab & extract zip file: `wget https://github.com/OpenMathLib/OpenBLAS/releases/download/v0.3.30/OpenBLAS-0.3.30.tar.gz && tar -xvzf OpenBLAS-0.3.30.tar.gz`
- Make: `cd OpenBLAS-0.3.30 && make`
- Install: `make PREFIX=$ROOT/OpenBLAS-0.3.30 install`
- Export variables: 
```
export PATH=$ROOT/OpenBLAS-0.3.30/bin:$PATH 
export LD_LIBRARY_PATH=$ROOT/OpenBLAS-0.3.30/lib:$LD_LIBRARY_PATH 
export PKG_CONFIG_PATH=$ROOT/OpenBLAS-0.3.30/lib/pkgconfig:$PKG_CONFIG_PATH
export CPPFLAGS="$CPPFLAGS -I$ROOT/OpenBLAS-0.3.30/include" 
export LDFLAGS="$LDFLAGS -L$ROOT/OpenBLAS-0.3.30/lib"
export DYLD_LIBRARY_PATH=$ROOT/OpenBLAS-0.3.30/lib:$DYLD_LIBRARY_PATH
```

### 4. FFLAS-FFPACK
- Grab & extract zip file: `wget https://github.com/linbox-team/fflas-ffpack/releases/download/v2.5.0/fflas-ffpack-2.5.0.tar.gz && tar -xvzf fflas-ffpack-2.5.0.tar.gz`
- Configure: `cd fflas-ffpack-2.5.0 && ./configure --prefix=$ROOT/fflas-ffpack-2.5.0 --with-blas-libs="-L$ROOT/OpenBLAS-0.3.30/lib -lopenblas" --with-blas-cflags="-I$ROOT/OpenBLAS-0.3.30/include"`
- Make: `make && make autotune`
- Install: `make install && make check`
- Export variables: 
```
export PATH=$ROOT/fflas-ffpack-2.5.0/bin:$PATH 
export LD_LIBRARY_PATH=$ROOT/fflas-ffpack-2.5.0/lib:$LD_LIBRARY_PATH 
export PKG_CONFIG_PATH=$ROOT/fflas-ffpack-2.5.0/lib/pkgconfig:$PKG_CONFIG_PATH
export CPPFLAGS="$CPPFLAGS -I$ROOT/fflas-ffpack-2.5.0/include" 
export LDFLAGS="$LDFLAGS -L$ROOT/fflas-ffpack-2.5.0/lib"
export DYLD_LIBRARY_PATH=$ROOT/fflas-ffpack-2.5.0/lib:$DYLD_LIBRARY_PATH
```
### Install LINBOX
- Grab & extract zip file: `wget https://github.com/linbox-team/linbox/releases/download/v1.7.1/linbox-1.7.1.tar.gz && tar -xvzf linbox-1.7.1.tar.gz`
- Configure: `cd linbox-1.7.1 && ./configure --prefix=$ROOT/linbox --with-givaro=$ROOT/givaro-4.2.1 --with-fflas-ffpack=$ROOT/fflas-ffpack-2.5.0`
- Make: `make`
- Install: `make install && make check`
- Export variables: 
```
```
export PATH=$ROOT/linbox-1.7.1/bin:$PATH 
export LD_LIBRARY_PATH=$ROOT/linbox-1.7.1/lib:$LD_LIBRARY_PATH 
export PKG_CONFIG_PATH=$ROOT/linbox-1.7.1/lib/pkgconfig:$PKG_CONFIG_PATH
export CPPFLAGS="$CPPFLAGS -I$ROOT/linbox-1.7.1/include" 
export LDFLAGS="$LDFLAGS -L$ROOT/linbox-1.7.1/lib"
export DYLD_LIBRARY_PATH=$ROOT/linbox-1.7.1/lib:$DYLD_LIBRARY_PATH
```