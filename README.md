# Wiedemann solver & analyzer for efficient exact linear algebra

### Installing LinBox

This project heavily relies on LinBox - a template library for exact, high performance linear algebra. LinBox 1.7.1 (lastest version) depends on Givaro (requires GMP) and FFLAS-FFPACK (requires OpenBLAS/ATLAS). Currently, we are using GMP 6.3.0, Givaro 4.2.1, OpenBLAS 0.3.30, and FFLAS-FFPACK 2.5.0. All those third-party dependencies are placed in `external`. 

For one-step installation, please run the `install_linbox.sh` in `external`. Note that the root working directory should be passed to `$ROOT` before running. Alternatively, a detailed step-by-step LinBox installation instructions is further specified in `installation_guides.md`.