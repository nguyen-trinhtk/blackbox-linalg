#!/bin/bash
set -euo pipefail

ROOT=$PWD

# Detect shell config file
SHELL_RC="$HOME/.bashrc"
if [[ "$SHELL" == *"zsh"* ]]; then
    SHELL_RC="$HOME/.zshrc"
fi

echo "Using shell config: $SHELL_RC"

# Helper function to append env vars to shell rc
append_env() {
    local var_name=$1
    local value=$2
    echo "export $var_name=\"$value\"" >> "$SHELL_RC"
}

# -------------------------
# 1. GMP
# -------------------------
curl -LO https://gmplib.org/download/gmp/gmp-6.3.0.tar.xz
tar -xvf gmp-6.3.0.tar.xz
rm gmp-6.3.0.tar.xz
cd gmp-6.3.0
./configure --prefix="$ROOT/gmp-6.3.0" --enable-cxx
make && make install
cd ..

# Export GMP env
export PATH="$ROOT/gmp-6.3.0/bin:$PATH"
export DYLD_LIBRARY_PATH="$ROOT/gmp-6.3.0/lib:${DYLD_LIBRARY_PATH:-}"
export PKG_CONFIG_PATH="$ROOT/gmp-6.3.0/lib/pkgconfig:${PKG_CONFIG_PATH:-}"
export CPPFLAGS="-I$ROOT/gmp-6.3.0/include ${CPPFLAGS:-}"
export LDFLAGS="-L$ROOT/gmp-6.3.0/lib ${LDFLAGS:-}"

# -------------------------
# 2. Givaro
# -------------------------
curl -LO https://github.com/linbox-team/givaro/releases/download/v4.2.1/givaro-4.2.1.tar.gz
tar -xvzf givaro-4.2.1.tar.gz
rm givaro-4.2.1.tar.gz
cd givaro-4.2.1
./configure --prefix="$ROOT/givaro-4.2.1" --with-gmp-prefix="$ROOT/gmp-6.3.0"
make && make install
cd ..

# Export Givaro env
export PATH="$ROOT/givaro-4.2.1/bin:$PATH"
export DYLD_LIBRARY_PATH="$ROOT/givaro-4.2.1/lib:$DYLD_LIBRARY_PATH"
export PKG_CONFIG_PATH="$ROOT/givaro-4.2.1/lib/pkgconfig:$PKG_CONFIG_PATH"
export CPPFLAGS="${CPPFLAGS:-} -I$ROOT/givaro-4.2.1/include"
export LDFLAGS="${LDFLAGS:-} -L$ROOT/givaro-4.2.1/lib"

# -------------------------
# 3. OpenBLAS
# -------------------------
curl -LO https://github.com/OpenMathLib/OpenBLAS/releases/download/v0.3.30/OpenBLAS-0.3.30.tar.gz
tar -xvzf OpenBLAS-0.3.30.tar.gz
rm OpenBLAS-0.3.30.tar.gz
cd OpenBLAS-0.3.30
make && make PREFIX="$ROOT/OpenBLAS-0.3.30" install
cd ..

# Export OpenBLAS env
export PATH="$ROOT/OpenBLAS-0.3.30/bin:$PATH"
export DYLD_LIBRARY_PATH="$ROOT/OpenBLAS-0.3.30/lib:$DYLD_LIBRARY_PATH"
export PKG_CONFIG_PATH="$ROOT/OpenBLAS-0.3.30/lib/pkgconfig:$PKG_CONFIG_PATH"
export CPPFLAGS="${CPPFLAGS:-} -I$ROOT/OpenBLAS-0.3.30/include"
export LDFLAGS="${LDFLAGS:-} -L$ROOT/OpenBLAS-0.3.30/lib"

# -------------------------
# 4. FFLAS-FFPACK
# -------------------------
curl -LO https://github.com/linbox-team/fflas-ffpack/releases/download/v2.5.0/fflas-ffpack-2.5.0.tar.gz
tar -xvzf fflas-ffpack-2.5.0.tar.gz
rm fflas-ffpack-2.5.0.tar.gz
cd fflas-ffpack-2.5.0
./configure --prefix="$ROOT/fflas-ffpack-2.5.0" \
    --with-blas-libs="-L$ROOT/OpenBLAS-0.3.30/lib -lopenblas" \
    --with-blas-cflags="-I$ROOT/OpenBLAS-0.3.30/include"
make && make autotune && make install
cd ..

# Export FFLAS-FFPACK env
export PATH="$ROOT/fflas-ffpack-2.5.0/bin:$PATH"
export DYLD_LIBRARY_PATH="$ROOT/fflas-ffpack-2.5.0/lib:$DYLD_LIBRARY_PATH"
export PKG_CONFIG_PATH="$ROOT/fflas-ffpack-2.5.0/lib/pkgconfig:$PKG_CONFIG_PATH"
export CPPFLAGS="${CPPFLAGS:-} -I$ROOT/fflas-ffpack-2.5.0/include"
export LDFLAGS="${LDFLAGS:-} -L$ROOT/fflas-ffpack-2.5.0/lib"

# -------------------------
# 5. LinBox
# -------------------------
curl -LO https://github.com/linbox-team/linbox/releases/download/v1.7.1/linbox-1.7.1.tar.gz
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
export DYLD_LIBRARY_PATH="$ROOT/linbox-1.7.1/lib:$DYLD_LIBRARY_PATH"
export PKG_CONFIG_PATH="$ROOT/linbox-1.7.1/lib/pkgconfig:$PKG_CONFIG_PATH"
export CPPFLAGS="${CPPFLAGS:-} -I$ROOT/linbox-1.7.1/include"
export LDFLAGS="${LDFLAGS:-} -L$ROOT/linbox-1.7.1/lib"

# -------------------------
# 6. Append env to shell rc
# -------------------------
{
    echo ""
    echo "# >>> LinBox environment setup >>>"
    echo "export PATH=\"$PATH\""
    echo "export DYLD_LIBRARY_PATH=\"$DYLD_LIBRARY_PATH\""
    echo "export PKG_CONFIG_PATH=\"$PKG_CONFIG_PATH\""
    echo "export CPPFLAGS=\"$CPPFLAGS\""
    echo "export LDFLAGS=\"$LDFLAGS\""
} >> "$SHELL_RC"

echo "Installation complete. Reload your shell or run: source $SHELL_RC"
