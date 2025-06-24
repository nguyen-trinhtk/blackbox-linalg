### 1. Basics
#### a. Inner Product / Dot Product
- **Definition:** For $x, y \in \mathbb{R}^n$,
  $$
  x \cdot y = \sum_{i=1}^n x_i y_i = x^T y
  $$
- **Geometric meaning:** $x \cdot y = \|x\| \cdot \|y\| \cdot \cos(\theta)$
- **Orthogonality:** $x \cdot y = 0 \iff x \perp y$
#### b. Length ($l_2$-norm)
- **Definition:** $\|x\| = \sqrt{x^T \cdot x}$
- **Normalizing vector:** $\hat{x} = \frac{x}{\|x\|} \to$ unit vector
#### c. Triangle Inequality
$$
\|x + y\| \le \|x\| + \|y\|
$$

#### d. Cauchy-Schwarz Inequality
$$
|x \cdot y| \le \|x\| \cdot \|y\|
$$
### 2. Linear Combinations & Independence
#### a. Linear Combination
- A vector $v$ is a linear combination of $\{v_1, ..., v_k\}$ if:
  $$
  v = \lambda_1 v_1 + \lambda_2 v_2 + \dots + \lambda_k v_k
  $$
#### b. Linear Independence
- Vectors $\{v_1, ..., v_k\}$ are **linearly independent** if:
  $$
  \lambda_1 v_1 + \dots + \lambda_k v_k = 0 \Rightarrow \lambda_1 = \dots = \lambda_k = 0
  $$
- Otherwise: **linearly dependent** (some $v_i$ can be expressed as a combo of the others)
#### c. Pivot Connection
- Pivot columns in REF $\leftrightarrow$ linearly independent columns
- Each pivot reveals a "new direction" in column space
### 3. Vector Spaces & Subspaces
#### a. Vector Space
- A set $V$ with operations $+$ and scalar $\cdot$ satisfying:
  1. Closure (addition & scalar mult.)
  2. Associativity & commutativity (of +)
  3. Additive identity (0)
  4. Additive inverse ($-v$)
  5. Distributivity: $\lambda(v + w) = \lambda v + \lambda w$
  6. Scalar associativity: $(\lambda \mu)v = \lambda(\mu v)$
#### b. Subspace of $\mathbb{R}^n$
- A subset $W \subseteq \mathbb{R}^n$ is a **subspace** if:
  1. $0 \in W$
  2. Closed under vector addition
  3. Closed under scalar multiplication
### 4. Basis, Span, Dimension
#### a. Span
- $\text{span}(v_1, ..., v_k) = \{ \lambda_1 v_1 + \dots + \lambda_k v_k \}$
#### b. Basis
- A set of vectors in $V$ that is:
  - **Linearly independent**
  - **Spans** $V$
#### c. Dimension
- Number of vectors in a basis for $V$
- Denoted $\dim(V)$
### 5. Fundamental Subspaces
#### a. Column Space ($\text{Col}(A)$)
- Set of all linear combinations of columns of $A$
- Subspace of $\mathbb{R}^m$ (if $A$ is $m \times n$)
- $\text{dim(Col A)}$ = number of **pivot columns** = **rank**
#### b. Row Space ($\text{Row}(A)$)
- Set of all linear combinations of rows of $A$
- Subspace of $\mathbb{R}^n$
- $\text{Row}(A) = \text{Col}(A^T)$
#### c. Null Space ($\text{Nul}(A)$)
- Set of all $x$ such that $Ax = 0$
- Subspace of $\mathbb{R}^n$
- Contains all solutions to homogeneous system
- $\text{dim(Nul A)}$ = number of **free variables**
### 6. Rank-Nullity Theorem

Let $A$ be an $m \times n$ matrix.
$$
\text{rank}(A) + \text{nullity}(A) = n
$$
- $\text{rank}(A)$ = $\dim(\text{Col}(A))$
- $\text{nullity}(A)$ = $\dim(\text{Nul}(A))$
### 7. Krylov Subspace
Given $A \in \mathbb{R}^{n \times n}$ and $b \in \mathbb{R}^n$, the order-$r$ **Krylov subspace** is:
$$
\mathcal{K}_r(A, b) = \text{span}\{b, Ab, A^2b, \dots, A^{r-1}b\}
$$
**Properties:**
-  $\mathcal{K}_r(A, b), A\mathcal{K}_r(A, b) \subset \mathcal{K}{r + 1}(A, b)$
- Let $r_0 = dim([\{b, Ab, ...\}])$, then $\{b, Ab, ..., A^{r -1}b\}$ linearly independent if $r \le r_0$
	$\to r_0$ is the maximal dimension of $\mathcal{K}_r(A, b)$
- Maximal dimension satisfies: $r_0 \le 1 + \text{rank}A$ and $r_0\le n$
- Let $deg(p(A)) = dim([{I, A, A^2}])$ (where $p(A)$ is the minimal poly. of $A$), then $r_0 \le deg(p(A))$. 
- For any $A$, exists $b$ such that $r_0 = deg(p(A))$