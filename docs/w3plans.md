## Experimental Design by Question

### 1. Which \( u, v \) generate a "bad" minimal polynomial? Why?

**Goal**: Identify which choices of \( u, v \in \mathbb{F}^n \) lead to a Krylov sequence \( (uA^iv) \) whose minimal polynomial is not the true minimal polynomial of A, or whose degree is much lower than expected.

**Experiment Plan**:
- Fix matrix \( A \in \mathbb{F}_q^{n \times n} \).
- For 100–1000 random \( u, v \in \mathbb{F}_q^n \), generate the scalar Krylov sequence \( (uA^iv) \).
- Compute:
  - The minimal polynomial of the scalar sequence.
  - The minimal polynomial of \( A \) (ground truth).
- Record:
  - Degree of sequence min poly.
  - Whether it matches or divides matrix min poly.
  - Inner product correlation \( \langle u, A^iv \rangle \), sparsity in \( u, v \), etc.

**Analysis**:
- Are certain choices of sparse \( u \) or \( v \) worse?
- Is performance better when \( u, v \) are chosen uniformly at random?
- Plot histogram of min poly degrees vs. sparsity of \( u \), \( v \).

---

### 2. How often does the BM-generated min poly equal/divide the matrix min poly?

**Goal**: Measure empirical success rate of Wiedemann’s algorithm returning the full matrix min poly or one that divides it.

**Experiment Plan**:
- For each matrix \( A \in \mathbb{F}_q^{n \times n} \):
  - Repeat for \( N = 100 \) different random \( u, v \).
  - Compare:
    - \( \mu_{u,A,v}(x) \): BM-generated scalar min poly
    - \( \mu_A(x) \): true minimal polynomial of \( A \)
- Metrics:
  - % of times \( \mu_{u,A,v}(x) = \mu_A(x) \)
  - % of times \( \mu_{u,A,v}(x) \mid \mu_A(x) \)
  - Distribution of degrees of \( \mu_{u,A,v}(x) \)

**Varied Parameters**:
- Field sizes \( q = 2, 17, 65537 \)
- Matrix sizes \( n = 128, 256, 512 \)
- Sparsity

---

### 3. Is the first \( k < 2n \) entries of the Krylov sequence sufficient to get the min poly?

**Goal**: Investigate the minimum length of Krylov sequence needed for BM to recover the minimal polynomial.

**Experiment Plan**:
- For fixed \( A \), \( u, v \), generate scalar Krylov sequence of length \( 2n \).
- For \( k = n, n+1, ..., 2n \):
  - Run Berlekamp-Massey on prefix \( (uA^iv)_{i=0}^{k-1} \)
  - Check if output matches min poly from full sequence.
- Repeat across different \( u, v \) and matrix instances.

**Metric**:
- For each \( k \), % of trials where recovered poly = full-length BM poly

**Bonus**: Plot convergence curve: recovered poly degree vs. \( k \)

---

### 4. Relationship between dimension, field size, convergence rate, and runtime

**Goal**: Understand how convergence and runtime vary with:
- Matrix size \( n \)
- Field size \( q \)
- Sparsity and structure

**Experiment Plan**:
- Fix a problem size, then vary:
  - \( n = 128 \to 2048 \)
  - \( q = 2, 2^8, 65537 \)
- For each config:
  - Record time until BM completes (time per iteration)
  - Krylov sequence length required for min poly to converge
  - Number of restarts (if applicable)

**Plot**:
- Runtime vs. \( n \)
- Convergence length vs. field size
- Separate plots for structured (e.g. Toeplitz) vs. random sparse matrices

---

### 5. How often is a matrix non-derogatory? \( \mu_A = \chi_A \)

**Goal**: Estimate the probability that a random matrix is non-derogatory.

**Experiment Plan**:
- For random matrices over various fields and sizes:
  - Compute:
    - Characteristic polynomial \( \chi_A \)
    - Minimal polynomial \( \mu_A \)
  - Record whether \( \mu_A = \chi_A \)
- Repeat over 1000 matrices for each config:
  - Field sizes: \( \mathbb{F}_2, \mathbb{F}_{17}, \mathbb{F}_{65537} \)
  - Sizes: \( n = 32, 64, 128, 256 \)

**Plot**:
- Bar chart: % of non-derogatory matrices per field + size

---

### 6. Determinant recovery: How often does diagonal \( D = \text{diag}(y_1,\dots,y_n) \) succeed?

**Goal**: Empirically validate the random diagonal preconditioning method for determinant recovery.

**Experiment Plan**:
- Fix \( A \in \mathbb{F}_q^{n \times n} \)
- For each of \( N = 1000 \) random diagonal \( D \):
  - Form \( DAD^{-1} \)
  - Compute BM-based min poly
  - Check if it equals \( \chi_{DAD^{-1}} \)

**Metrics**:
- % of time min poly = char poly (→ determinant recoverable)
- Effect of field size

**Bonus**: Try structured vs. random \( A \) to compare

---

## Tools and Output

- Language: SageMath or Python (with NumPy + finite field libraries)
- Logging: Save matrix, seeds, and results to JSON/CSV for reproducibility
- Visualization: Use matplotlib or seaborn for:
  - Convergence plots
  - Success/failure histograms
  - Runtime trends
