# Large Linear System Solver with Black-box Linear Algebra

## Introduction
This repository serves as a personal log for my research on black-box linear algebra (with a strong emphasis on Wiedemann algorithm). Currently, I'm investigating preconditioners for solving large, sparse linear systems in finite fields. 

To support this work, I also include a solve and analysis tool designed to evaluate probabilistic nature of Monte Carlo algorithms and exploit structural characteristic of matrices that can possible influence that probability. Further details about the repository and the tool are provided below.

## Repo Structure
```
.
├── README.md
├── docs                       # Weekly notes, relevant research documents, or references
├── external                   # External C++ libraries
├── notebooks                  # Jupyter notebooks for demonstration and presentation
├── requirements.txt           # Python dependencies
├── src                        # Source code
│   ├── analyzer               # Python-based analysis tools
│   └── solver                 # C++ solver implemented with LinBox
├── results                    # Solver output (CSV files)
└── test                       # Tests for solver and other components
```

## Linear Solver & Analyzer
### 1. Installing dependencies
#### LinBox
This tool relies on LinBox 1.7.1 (lastest version), which depends on Givaro (requires GMP) and FFLAS-FFPACK (requires OpenBLAS/ATLAS). All those third-party dependencies are placed in `external`. 

For one-step installation, run the `install-fixed.sh` in `external`. Alternatively, a detailed step-by-step installation instructions is further specified in `docs/installation_guides.md`.

#### Python libraries
All Python dependencies have been specified in `requirements.txt`. Run `pip install requirements.txt` should install prerequisites for the tool.


### 2. Using the tool
Please find `src/README.md` for more details about the tool. Below is an example usage: 

```bash
# Build C/C++
 executables
make

# Run a batch experiment
./batch-run -v q -r 2-5 -t dense -a wiedemann -p diagonal -f 100
````

This:

1. Generates matrices and preconditioners via `gen_precond`.
2. Solves each with the chosen algorithm using `solve`.
3. Stores results and plots in `src/runs/<timestamp>/`.

## Development Notes
Automated testing, CI workflows, and containerization (Docker) are currently being implemented. Since this research primarily focuses on theoretical linear algebra rather than software implementation, these tools are not strictly required. However, running the solver with C++ LinBox has significantly reduced overhead compared to using Sage (via CLI or Jupyter Notebook) and has resulted in a more organized codebase.
