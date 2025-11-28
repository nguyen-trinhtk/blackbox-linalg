#!/bin/bash
set -euo pipefail

ROOT="$PWD"

# Helper function to append env vars (for CI we don't append to shell rc)
append_env() {
    local var_name=$1
    local value=$2
    export "$var_name"="$value"
}

echo "Starting Linux external libraries installation in $ROOT"

# -------------------------
# 1. GMP
# -------------------------
curl -LO https://gmplib.org/download/gmp/gmp-6.3.0.tar.xz
tar -xf gmp-6.3.0.tar.xz
rm gmp-6.3.0.tar.xz
cd gmp-6.3.0
./configure --prefix="$ROOT/gmp-6.3.0" --enable-cxx
make -j$(nproc) && make install
cd ..

append_env PATH "$ROOT/gmp-6.3.0/bin:$PATH"
append_env LD_LIBRARY_PATH "$ROOT/gmp-6.3.0/lib:${LD_LIBRARY_PATH:-}"
append_env PKG_CONFIG_PATH "$ROOT/gmp-6.3.0/lib/pkgconfig:${PKG_CONFIG_PATH:-}"
append_env CPPFLAGS "-I$ROOT/gmp-6.3.0/include ${CPPFLAGS:-}"
append_env LDFLAGS "-L$ROOT/gmp-6.3.0/lib ${LDFLAGS:-}"

# -------------------------
# 2. Givaro
# -------------------------
curl -LO https://github.com/linbox-team/givaro/releases/download/v4.2.1/givaro-4.2.1.tar.gz
tar -xzf givaro-4.2.1.tar.gz
rm givaro-4.2.1.tar.gz
cd givaro-4.2.1
./configure --prefix="$ROOT/givaro-4.2.1" --with-gmp-prefix="$ROOT/gmp-6.3.0"
make -j$(nproc) && make install
cd ..

append_env PATH "$ROOT/givaro-4.2.1/bin:$PATH"
append_env LD_LIBRARY_PATH "$ROOT/givaro-4.2.1/lib:$LD_LIBRARY_PATH"
append_env PKG_CONFIG_PATH "$ROOT/givaro-4.2.1/lib/pkgconfig:$PKG_CONFIG_PATH"
append_env CPPFLAGS "${CPPFLAGS:-} -I$ROOT/givaro-4.2.1/include"
append_env LDFLAGS "${LDFLAGS:-} -L$ROOT/givaro-4.2.1/lib"

# -------------------------
# 3. OpenBLAS
# -------------------------
curl -L -o OpenBLAS-0.3.30.tar.gz \
  https://github.com/xianyi/OpenBLAS/archive/refs/tags/v0.3.30.tar.gz

tar -xzf OpenBLAS-0.3.30.tar.gz
rm OpenBLAS-0.3.30.tar.gz
cd OpenBLAS-0.3.30
make -j$(nproc)
make PREFIX="$ROOT/OpenBLAS-0.3.30" install
cd ..

append_env PATH "$ROOT/OpenBLAS-0.3.30/bin:$PATH"
append_env LD_LIBRARY_PATH "$ROOT/OpenBLAS-0.3.30/lib:$LD_LIBRARY_PATH"
append_env PKG_CONFIG_PATH "$ROOT/OpenBLAS-0.3.30/lib/pkgconfig:$PKG_CONFIG_PATH"
append_env CPPFLAGS "${CPPFLAGS:-} -I$ROOT/OpenBLAS-0.3.30/include"
append_env LDFLAGS "${LDFLAGS:-} -L$ROOT/OpenBLAS-0.3.30/lib"

# -------------------------
# 4. FFLAS-FFPACK
# -------------------------
curl -LO https://github.com/linbox-team/fflas-ffpack/releases/download/v2.5.0/fflas-ffpack-2.5.0.tar.gz
tar -xzf fflas-ffpack-2.5.0.tar.gz
rm fflas-ffpack-2.5.0.tar.gz
cd fflas-ffpack-2.5.0
./configure --prefix="$ROOT/fflas-ffpack-2.5.0" \
    --with-blas-libs="-L$ROOT/OpenBLAS-0.3.30/lib -lopenblas" \
    --with-blas-cflags="-I$ROOT/OpenBLAS-0.3.30/include"
make -j$(nproc) && make autotune && make install
cd ..

append_env PATH "$ROOT/fflas-ffpack-2.5.0/bin:$PATH"
append_env LD_LIBRARY_PATH "$ROOT/fflas-ffpack-2.5.0/lib:$LD_LIBRARY_PATH"
append_env PKG_CONFIG_PATH "$ROOT/fflas-ffpack-2.5.0/lib/pkgconfig:$PKG_CONFIG_PATH"
append_env CPPFLAGS "${CPPFLAGS:-} -I$ROOT/fflas-ffpack-2.5.0/include"
append_env LDFLAGS "${LDFLAGS:-} -L$ROOT/fflas-ffpack-2.5.0/lib"

# -------------------------
# 5. LinBox
# -------------------------
curl -LO https://github.com/linbox-team/linbox/releases/download/v1.7.1/linbox-1.7.1.tar.gz
tar -xzf linbox-1.7.1.tar.gz
rm linbox-1.7.1.tar.gz
cd linbox-1.7.1
./configure --prefix="$ROOT/linbox-1.7.1" \
    --with-givaro="$ROOT/givaro-4.2.1" \
    --with-fflas-ffpack="$ROOT/fflas-ffpack-2.5.0" \
    --with-blas-libs="-L$ROOT/OpenBLAS-0.3.30/lib -lopenblas" \
    --with-blas-cflags="-I$ROOT/OpenBLAS-0.3.30/include"
make -j$(nproc) && make check && make install
cd ..

append_env PATH "$ROOT/linbox-1.7.1/bin:$PATH"
append_env LD_LIBRARY_PATH "$ROOT/linbox-1.7.1/lib:$LD_LIBRARY_PATH"
append_env PKG_CONFIG_PATH "$ROOT/linbox-1.7.1/lib/pkgconfig:$PKG_CONFIG_PATH"
append_env CPPFLAGS "${CPPFLAGS:-} -I$ROOT/linbox-1.7.1/include"
append_env LDFLAGS "${LDFLAGS:-} -L$ROOT/linbox-1.7.1/lib"

echo "Linux external libraries installation complete."
echo "LD_LIBRARY_PATH=$LD_LIBRARY_PATH"
echo "PKG_CONFIG_PATH=$PKG_CONFIG_PATH"
