FROM ubuntu:22.04

# Install build tools
RUN apt-get update && \
    apt-get install -y build-essential g++ wget m4

RUN rm -rf /usr/lib/libgmp* /usr/lib64/libgmp* /lib/libgmp* /usr/include/gmp.h

# Build and install GMP
WORKDIR /tmp
RUN wget https://gmplib.org/download/gmp/gmp-6.3.0.tar.xz && \
    tar xf gmp-6.3.0.tar.xz && \
    cd gmp-6.3.0 && \
    ./configure --prefix=/usr/local && make && make install && ldconfig

# Check GMP install location
RUN ls -l /usr/local/lib/libgmp* && ls -l /usr/local/include/gmp.h && ldconfig -p | grep gmp

# Build and install NTL (shared and static)
RUN wget https://libntl.org/ntl-11.5.1.tar.gz && \
    tar xzf ntl-11.5.1.tar.gz && \
    cd ntl-11.5.1/src && \
    LD_LIBRARY_PATH=/usr/local/lib ./configure NTL_GMP_LIP=on GMP_PREFIX=/usr/local SHARED=on PREFIX=/usr/local && \
    LD_LIBRARY_PATH=/usr/local/lib make && \
    LD_LIBRARY_PATH=/usr/local/lib make install

COPY . /app
WORKDIR /app/tests
RUN make && make run-main