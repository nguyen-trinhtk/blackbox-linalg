# Archived: Wiedemann Linear System Solver using NTL

This is a deprecated C++ implementation of Wiedemann algorithm for solving linear systems, with exact arithmetic via NTL and GMP libraries.

<!-- ## Structure

- `include/` — C++ headers (algorithms, matrix/vector types)
- `tests/` — Test programs and Makefile
- `external/` — External libraries (NTL, GMP)
- `docs/` — Project documentation
- `theoretical-notes/` — Linear algebra notes
- `scratch/` — Research scripts and notebooks -->

## Build & Run

```sh
cd tests
make
./main        # Run main test
./matvec      # Run matvec test
./bm          # Run Berlekamp-Massey test
./wiedemann   # Run Wiedemann test
```

## Docker

Build and run tests in Docker:

```sh
docker build -t wiedemann-analyzer .
docker run wiedemann-analyzer
```

## Requirements

- NTL
- GMP
- g++ (C++17+)
