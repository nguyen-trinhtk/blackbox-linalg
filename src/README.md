Excellent — now that you have the working `batch-run` script, `gen_precond.cpp`, `solve.cpp`, and a LinBox-compatible `Makefile`, we can produce two versions of your documentation:

1. 🧱 **Detailed version** (for `src/runs/README.md` or inside the subproject folder) — a full technical guide explaining the architecture, directory structure, and code interactions.
2. ⚡ **Brief version** (for your project’s main `README.md`) — a short user-facing overview focusing on quick usage and workflow.

---

## 🧱 Detailed README (`src/runs/README.md`)

````markdown
# Wiedemann Batch Solver & Analyzer

This tool automates matrix generation, preconditioning, algorithm execution, and result analysis for Wiedemann-based solvers.

It consists of:
- A master Bash script: **`batch-run`**
- Two C++ executables: **`gen_precond`** and **`solve`**
- A Python analyzer: **`analyzer/plot.py`**

---

## 1. Command Format

```bash
batch-run -v {varying} -r {start-stop} -t {mattype} -a {algorithm} -p {precond} -f {fixed} [options]
````

### Required Flags

| Flag | Meaning                                                                        | Example        |
| ---- | ------------------------------------------------------------------------------ | -------------- |
| `-v` | Parameter to vary: `q` (field size) or `n` (matrix dimension)                  | `-v q`         |
| `-r` | Range of varying parameter (inclusive)                                         | `-r 2-5`       |
| `-t` | Matrix type (`dense`, `sparse`, `diagonal`, `toeplitz`, `companion`, `jordan`) | `-t dense`     |
| `-a` | Algorithm (`wiedemann` or `lcm_wiedemann`)                                     | `-a wiedemann` |
| `-p` | Preconditioner type (currently supports `diagonal`)                            | `-p diagonal`  |
| `-f` | Fixed value of the non-varying parameter                                       | `-f 100`       |

### Optional Flags

| Flag | Meaning                   | Default                    |
| ---- | ------------------------- | -------------------------- |
| `-d` | Directory for run results | `$(projectroot)/src/runs`  |
| `-n` | Test name                 | Auto-generated description |

If `-n` is not provided, a default name is generated automatically:

```
"{alg_type} on varying {v} over {maybe nxn or GF(q)} {mat_type} matrices using {precond} preconditioners"
```

---

## 2. Workflow Overview

### Step 1: Setup

For each run, the script:

1. Creates a timestamped directory in `src/runs/`, e.g. `241030_153422/`.
2. Inside that directory, it generates:

   * `metadata.txt` — stores run configuration (fixed/varying params, range, types, timestamp, etc.)
   * Subdirectories for intermediate data and outputs.

**Directory layout:**

```
yymmdd_hhmmss/
├─ matrix/            # Original matrices A
├─ precond/           # Preconditioners D
├─ precond_matrix/    # Preconditioned matrices D*A
├─ metadata.txt       # Run metadata
├─ results.csv        # Solver results
```

---

### Step 2: Matrix Generation & Preconditioning

The script calls:

```bash
./gen_precond <q_list> <n_list> <run_dir> <mattype> <precond_type>
```

**Responsibilities of `gen_precond.cpp`:**

1. For each combination of `(q, n)`:

   * Generate matrix `A`:

     ```
     mat_gen(n, q, mattype, "<run_dir>/matrix")
     → <run_dir>/matrix/q_nxn_<mattype>.sms
     ```
   * Generate preconditioner `D`:

     ```
     mat_gen(n, q, precond_type, "<run_dir>/precond")
     → <run_dir>/precond/q_nxn_<precond_type>.sms
     ```
   * Compute the preconditioned matrix:

     ```
     multiply_precond(D_file, A_file, q, "<run_dir>/precond_matrix")
     → <run_dir>/precond_matrix/q_nxn_<mattype>_precond.sms
     ```

**Includes:**

```cpp
#include "./solver/core/all.h"
```

---

### Step 3: Solving

The script then calls:

```bash
./solve <run_dir> <algorithm>
```

**Responsibilities of `solve.cpp`:**

* Iterate over all matrices in `<run_dir>/precond_matrix/`
* For each, run the selected algorithm:

  ```cpp
  wiedemann(matrix_file, q);
  // or
  lcm_wiedemann(matrix_file, q);
  ```
* Append results to a CSV file:

```
q,n,res
2,100,0.00123
3,100,0.00145
...
```

**Includes:**

```cpp
#include "./solver/algorithms/all.h"
```

---

### Step 4: Analysis

Finally, `batch-run` invokes:

```bash
python3 analyzer/plot.py <csv_path>[,<csv_path>...] x y [label1,label2,...]
```

For example:

```bash
python3 analyzer/plot.py src/runs/241030_153422/results.csv q res "Wiedemann dense"
```

* **x** → varying parameter (`q` or `n`)
* **y** → result metric (default: `res`)
* **label** → optional plot labels

---

## 3. Build Instructions

All executables are compiled with LinBox and its dependencies.

A `Makefile` is provided:

```bash
make             # builds gen_precond and solve
make clean       # removes binaries
```

It automatically pulls flags using:

```
pkg-config --cflags --libs linbox
```

Dependencies must exist under `$(ROOT)/external/`:

* GMP
* Givaro
* OpenBLAS
* FFLAS-FFPACK
* LinBox

---

## 4. Example Run

```bash
./batch-run -v q -r 2-5 -t dense -a wiedemann -p diagonal -f 100
```

Produces:

```
src/runs/241030_153422/
├─ matrix/
├─ precond/
├─ precond_matrix/
├─ metadata.txt
├─ results.csv
```

---

## 5. Notes

* Both `gen_precond` and `solve` are linked against LinBox, Givaro, and GMP.
* You can override the base run directory with `-d`.
* Analyzer is optional but recommended for visualization.

````

---