
### 1. Matrix Definitions & Constructions
#### a. Definitions: 
- $n \times m$ matrix: rectangular table with $n$ rows, $m$ columns
- **Dimension:** $n \times m$
- $A_{i, j}$: **entry** of $A$ in row $i$ and column $j$
#### b. Special Matrices: 
- **Square matrix:** $A_{n \times n}$
- **Diagonal matrix:** square matrix with off-diagonal entries = 0
- **Identity:** $I_n: n \times n$ matrix where 
$$
I_{i, j} = \left\{
\begin{aligned}
  & 1 : i = j \\
  & 0 : i = i
\end{aligned}
\right.
$$
  (i.e. diagonal matrix with diagonal entries = 0)
- **Triangular matrix:**
    - Upper (right): $R_{i, j} = 0$ for all $i > j$
    - Lower (left): $L_{i, j} = 0$ for all $i < j$
- **Orthogonal matrix:** square matrix with orthonormal columns (or rows) $\rightarrow Q^TQ = I$ or $Q^T = Q^{-1}$
- **Permutation matrix:** square matrix with only $0$ and $1$, such that every row/column has exactly one $1$
- **Elementary matrix:** $E = I - \alpha u v^T$
  (where $\alpha$ is a scalar, $u, v$ is vector with $dim(u) = dim(v)$
### 2. Matrix Operations
#### a. Basic Operations & Properties
##### i. Addition: 
$C = A + B \to C_{i, j} = A_{i, j} + B_{i, j}$
##### ii. Multiplication: 
- **Definition:** Given $A_{m \times n}$
	- **With $n$-vector $x$:** $(A_x)_i = \sum^{n}_{j=1} A_{i, j} x_j$
	- **With $B_{n \times p}$:**  $(AB_{i, j})= \sum^{n}_{k = 1} A_{i, k} B_{k, j}$
			- $(AB_{i, j}) = A_{i, 1}B_{1, j} + A_{i, 2}B_{2, j} + ... + A_{i, m}B_{m, j}$
			- $AB = (row_iA \cdot col_j B)$
			- $row_i(AB) = row_iA \cdot B$
			- $col_j (AB) = A \cdot col_jB$
- **Matrix powers:** For square matrix $A$, $A^x = AAA...A$ ($x$ times)
##### iii. Properties:
- Commutativity of addition: $A + B = B + A$
- Associativity of addition: $A + (B + C) = (A + B) + C$
- Scalar distributivity over addition: $\lambda (A + B) = \lambda A + \lambda B$
- Scalar associativity and distributivity: 
	  - $\lambda (\mu A) = (\lambda \mu) A$
	  - $(\lambda + \mu) A = \lambda A + \mu A$
- Multiplicative identity of scalars: $1A = A$
- Left distributivity of multiplication: $A(B + C) = AB + AC$
- Right distributivity of multiplication: $(A + B)C = AC + BC$
- Scalar multiplication and matrix product compatibility: $\lambda (AB) = (\lambda A)B = A(\lambda B)$
- Associativity of multiplication: $A(BC) = (AB)C$
#### b. Matrix Transposition
- **Definition:** The transpose of $n \times m$ matrix $A$ is the $m \times n$ matrix $(A_{j, i})_{1 \le i \le m, 1 \le j \le n}$
- **Notation**: $A^T$
- **Transpose of a matrix product:** $(AB)^T = B^T A^T$
### 3. Gaussian Elimination
#### a. Gaussian Row Operations
	1. Swap
	2. Scaling
	3. Row Combinations
- Gaussian operations preserve solutions, (R)REF
- **Leading variable:** first nonzero variable in a row; otherwise free variable
- **Augmented matrix $(B | v)$:** matrix $B$ and vector $v \to$ represent linear systems
#### b.(Reduced) Row Echelon Form
- **Row EF:** Each leading var is to the right of the leading var in preceding row, all zero rows at bottom
- **Reduced Row EF:** EF, and each lead entry is the **one and only** nonzero in the column
#### c. Pivot
- Pivot position: location (index) of leading non-zero entry of row-vector
- Pivot column: column containing pivot position
- Use pivot element to eliminate entries below it
### 4. Singular/Nonsingular, Inverse
- Checks (non)singularity only for square matrices
#### a. Nonsingular Matrices
- **Definition:** square matrix $A_{n\times n}$ with linearly independent columns
- Nonsingular matrix $A$ is **invertible**
- Inverse of $A$: $A^{-1}$ such that $A^{-1}A = I$
- **Properties:**
    - Column space spans $\mathbb{R}^n$; null space (of itself & its tranpose): $\{0\}$
    - $Ax = 0 \Rightarrow x = 0$ ($A$ matrix, $x$ vector); $Ax = b$ has unique solution
    - $A, B$ nonsingular $\to (AB)$ nonsingular, $(AB)^{-1} = B^{-1}A^{-1}$
    - $A^T$ also nonsingular, $(A^T)^{-1} = (A^{-1})^T$
#### b. Singular Matrices
- **Definition:** matrices with linearly dependent columns
- **Properties:**
    - No inverse
    - There exists $x \neq 0$ such that $Ax = 0$
    - If $Ax = b$ has a solution, it has infinitely many solutions
### 5. Determinant, Adjugate, Laplace Expansion, Determinant of Matrix Product, Cauchy-Binet Expansion
#### a. Determinants
- For $1 \times 1$ matrices: $det(a) = a$
- For $2 \times 2$ matrices: $det(\begin{smallmatrix}a & b\\c & d\\ \end{smallmatrix}) = ad - bc$
- **Definition:** Determinants is a function $det: M_{n \times n} \rightarrow \mathbb{R}$ with the following properties:
$$ 
\begin{align*}
&\det(I) = 1 \\
&A \xrightarrow{\text{switch rows}} B \quad \Rightarrow \quad \det(B) = -\det(A) \\
&A \xrightarrow{\text{scale one row by } \lambda} B \quad \Rightarrow \quad \det(B) = \lambda \cdot \det(A) \\
&A \xrightarrow{\text{add } \lambda \cdot \text{(one row) to another}} B \quad \Rightarrow \quad \det(B) = \det(A)
\end{align*}
$$
- Determinant is unique function for every $n$
- Notation: $\det(A) = |A|$
- If $A$ has a zero (row/column) or has two identical (row/column), then $\det(A) = 0$
- $A$ is invertible $\Rightarrow \det(A) \neq 0$
- For any triangular (L/U) matrix $D$, $\det(D) =$ product of diag. entries
#### b. Adjugate
Given $A_{n \times n}$, let $A_{ \sim j, \sim i}$ be the $(n - 1) \times (n - 1)$ matrix resulted from removing $i^{th}$ row and $j^{th}$ column of $A$
- $(i, j)$ **cofactor** of $A$: $A_{ij} = (-1)^{i + j} \det(A_{\sim j, \sim i})$
- **Adjugate** of A: $adj A_{n \times n} = ((-1)^{i + j}\det(A_{\sim j, \sim i})$ (matrix of cofactors) $\rightarrow A \cdot adj A = adj A \cdot A = \det(A) \cdot I_n$
#### c. Laplace Expansion
- **Along $p^{th}$ row:** $\det(A) = \sum_{q=1}^{n} (-1)^{p+j} A_{pq} \cdot \det(A_{\sim p, \sim q})$
- **Along $q^{th}$ row:** $\det(A) = \sum_{p=1}^{n} (-1)^{i+q} A_{pq} \cdot \det(A_{\sim p, \sim q})$

#### d. Determinant of a Matrix Product
- **Product of square matrices:** $\det(AB) = \det(A) \cdot \det(B)$ ($A, B$ square matrices)
- **Properties:** Let $A$ be an $n \times n$ matrix; $\lambda \in \mathbb{R}$; $S$ be an invertible matrix
	- $\det(AB) = \det(BA)$
    - $\det(\lambda A) = \lambda^n \cdot \det(A)$
    - $\det(S^{-1} = \frac{1}{\det(S)}$
    - $\det(SAS^{-1}) = \det(A)$
#### e. Cauchy-Binet Formula
Let:
- $A$ be an $m \times n$ matrix and $B$ an $n \times m$ matrix
- $[n] = \{1, \dots, n\}$: set of indices
- ${\tbinom{[n]}{m}}$: set of $m$-combinations of $[n]$ (subsets of size $m$)
- For $S \in {\tbinom{[n]}{m}}$
    - $A_{[m],S}$: $m \times m$ matrix formed by the columns of $A$ indexed by $S$
    - $B_{S,[m]}$: $m \times m$ matrix formed by the rows of $B$ indexed by $S$.
Then
$$\det(AB) = \sum_{S \in {\tbinom{[n]}{m}}} \det(A_{[m],S}) \det(B_{S,[m]})$$
### 6. Matrix Decomposition (Incomplete)

#### a. QR Decomposition
- Any (real) square matrix $A$ can be decomposed as $A = QR$
    - $Q$ is an orthogonal matrix
    - $R$ is a right (upper) triangular matrix
- 2 methods to compute: Gram-Schmidt and Householder reflection