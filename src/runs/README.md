# Wiedemann Batch Solver & Analyzer

This guide explains how to use the `batch-run` script to generate matrices, precondition them, run algorithms, and analyze results.

---

## Command Format

```
batch-run -v {varying} -r {start-stop} -t {mattype} -a {algorithm type} -p {precond} [options]
```

### Required Flags

* `-v` : The parameter to vary (`q` or `n`).
* `-r` : Range of values for the varying parameter (inclusive), e.g., `1-5`.
* `-t` : Matrix type, one of: `dense`, `sparse`, `diagonal`, `toeplitz`, `companion`, `jordan`.
* `-a` : Algorithm type, one of: `wiedemann`, `lcm_wiedemann`.
* `-p` : Preconditioner type, currently `diagonal` (more types will be added).
* `-f` : Fixed value for the non-varying parameter.

  * Example: if varying `q`, pass `-f 100` to fix `n=100`.

### Optional Flags

* `-d` : Directory to execute in (default: current working directory).
* `-n` : Name of the test. If not provided, a default name is generated:

  ```
  "{alg_type} on varying {v} over {maybe nxn or GF(q)} {mat_type} matrices using {precond} preconditioners"
  ```

---

## Workflow

### 1. Setup

For each run:

1. Create a timestamped directory: `yymmdd_hhmmss` & navigate inside that directory.
2. Create a metadata file storing:

   * `datetime`: YYMMDD_HHMMSS
   * `fixed` and `varied` values
   * `start` and `stop` of range
   * `matrix_type`, `algorithm_type`
   * `left_precond_type`, `right_precond_type`
   * `name` of the test

---

### 2. Preconditioning

Inside the timestamped directory, create three child directories:

```
matrix/          # Original matrices A
precond/         # Preconditioners D
precond_matrix/  # Preconditioned matrices D*A
```
pass the list of q and n into the next c++ program. even if it's 1 element (fixed), still pass the list
also pass the timestamp directory down to the next c++ pg

Remember to include ./solver/core/all.h
Write C++ code, name `gen_precond.cpp` that takes (list_of_q, list_of_n, directory): 
For each q:
For each n:
1. Generate the matrix using and store it in `dir/matrix/` as: q_nxn_{mattype}.sms. This can be done by calling mat_gen(n, q, {mattype}, 'dir/matrix')
2. Generate the preconditioner using and store it in `dir/precond/` as: q_nxn_{pctype}.sms. Similarly, call mat_gen(n, q, {pctype}, 'dir/matrix')
3. Compute `P*A` by calling multiply_precond(`dir/precond/q_nxn_whatevertherestis`, `dir/matrix/q_nxn_whatevertherestis`, q, `dir/precond_matrix`)

---

### 3. Solve
Write a C++ file, named `solve.cpp`
Input: timestamped directory (ill call dir), alg_type (as passed in -a before)
Output: None
Remember to include ./solver/algorithms/all.h
For each file in `dir/precond_matrix/` with filename: q_nxn_{whatevertherestis}

1. Run the algorithm:

   ```
   {alg_type}(matrix_file,q)
   ```
2. Log these to a CSV file in `dir` called `results.csv`
   (q:...,n:...,res:...)

---

### 4. Analyze

Use the plotting script:

```
python3 plot.py path1.csv[,path2.csv,...] x y [label1,label2,...]
```

* `x` : the varying parameter (`q` or `n`)
* `y` : the result (`res`)
* `label` : a label for each dataset (default: the varying parameter name)

---

### Summary of Directory Structure

```
yymmdd_hhmmss/
├─ matrix/            # Original matrices A
├─ precond/           # Preconditioners D
├─ precond_matrix/    # Preconditioned matrices D*A
├─ metadata.txt       # Run info (datetime, parameters, test name)
├─ results.csv        # Algorithm results
```