### 1. Nonsingular Square Case
$$Ax = b$$
- **$A$ is nonsingular, square $\to x = A^{-1}b$**
- **Ideas:** 
	- From min poly of $A^ib$, can compute $A^{-1}$
	-  $\{A^ib\}$ is a sequence in $\mathbb{F}^n \to$ try to convert to a linearly recurrent sequence in $\mathbb{F}$
	- Given random vector $u \in \mathbb{F}^n$, sequences $\{A^ib\}_{i=0}^{\infty}$ ($\in \mathbb{F}^n$) and $\{u^TA^ib\}_{i=0}^{\infty}$ ($\in \mathbb{F}$) have the same min poly with high probability (if $\mathbb{F}$ has enough elements) 
	$\to$ check if generated min poly of $\{u^TA^ib\}$ is also min poly of $\{A^ib\}$
- **Algorithm:** 
	1. **Choose a random vector** $u \in \mathbb{F}_q^n$  
	2. **Generate & project Krylov:** $\{s_i\} = \{u^T \cdot A^i b\}$ for $i = 0, \dots, 2n - 1$  
	$\to$ linearly recursive
	3. **Find min poly:** Run Berlekamp-Massey on $\{s_i\}$: $m(z) = z^d + m_{d-1}z^{d-1} + \dots + m_1z + m_0$
	4. **Let** $h(z) = - \dfrac{m(z) - m_0}{m_0 z}$  
	- **Compute** $x = h(A) \cdot b \quad (= A^{-1} \cdot b)$ using **Horner’s rule**. If error, repeat. ($m(A)$ is  an annihilating poly of $A$ w. high prob. $\to$ $h(A)$ possibly accounts for $A^{-1}$)
### 2. Computing Determinants
- Let $m_A$ be min poly generated from Wiedemann's alg, $c_A$ for char poly
- By definition: $c_A(x) = det(xI - A) \to \det(A) = (-1)^n c_A(0)$ (normalizing leading coef to $1$)
- If $A$ is non-derogatory (no repeated $\lambda$): $c_A = m_A \to$ can compute $det(A)$
- If $A$ is derogatory ($c_A \neq m_A$): 
	- Let 
		$D = diag(y_1,..., y_n)$ (random $y_i$) 
		$B = A \cdot D$ $\to$ high prob that $B$ is non-derogatory
	- Then: $det(B) = det(A \cdot D) = det(A) \cdot det(D)$, $det(D) = y_1 \cdot ... \cdot y_n$ 
	- Basically breaking the symmetries with random entries
	$\to det(A) = \frac{det(B)}{y_1 \cdot ... \cdot y_n}$ ; $det(B)$ can be computed from its min poly ==(reapply W?)==
- 