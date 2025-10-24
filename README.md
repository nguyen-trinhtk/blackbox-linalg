# Black-box Linear Algebra (Wiedemann Algorithm)

### Introduction
This repository serves as a personal log for my research on black-box linear algebra (with a strong emphasis on Wiedemann algorithm). Currently, I'm investigating preconditioners for solving large, sparse linear systems in finite fields. 

To support this work, I also include a solve and analysis tool designed to evaluate probabilistic nature of Monte Carlo algorithms and exploit structural characteristic of matrices that can possible influence that probability. Further details about the repository and the tool are provided below.

### Repo Structure

### Linear Solver & Analyzer Tool
##### 1. Installing dependencies
###### LinBox
This tool relies on LinBox 1.7.1 (lastest version), which depends on Givaro (requires GMP) and FFLAS-FFPACK (requires OpenBLAS/ATLAS). All those third-party dependencies are placed in `external`. 

For one-step installation, run the `install_linbox.sh` in `automation`. Alternatively, a detailed step-by-step installation instructions is further specified in `installation_guides.md`.

##### Python libraries
All Python dependencies have been specified in `requirements.txt`. Run `pip install requirements.txt` should install prerequisites for the tool.

### Using the tool

### Research notes
