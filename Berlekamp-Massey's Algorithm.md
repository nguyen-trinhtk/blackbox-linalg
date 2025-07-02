- **Problem:** 
	Given $s = \{s_0, ..., s_{2n}\} \subset \mathbb{F}$
	find $C(x) = 1 + c_1x + ... + c_Lx^L$ with min degree $L$
	such that $s_i + c_1s_{i - 1} + ... + c_Ls_{i - L} = 0 \quad \forall i \ge L$ 
- **Input:** linearly recurrent sequence $s = \{s_0, ..., s_{2n}\} \subset \mathbb{F}$
- **Algorithm:**
	**Initialize:** 
	- $C(x) = 1$, $L = 0$
	-  $B(x) = 1$: last $C(x)$ since $L$ is updated
	-  $b = 1$: last $d$ since $L$ is updated
	-  $m = 1$: number of iterations since $B(x), b, L$ is updated
	**Iterate $k$ from $0$ to $2n$**
	- Compute discrepancy: $d = s_k + c_1s_{k-1} + ... + c_Ls_{k-L}$ (if $k - i$ is negative, set $s_{k - i} = 0$)
	- If $d = 0$: $C(x), L$ currently fits the sequence $\to$ $m \leftarrow m + 1$ and continue to next $k$
	- If $d \neq 0$: 
		- If $2L \le k$: (significant $d \to$ updates $L$ )
			- $B(x) \leftarrow C(x), b \leftarrow d$ (store copies)
			- $L \leftarrow k + 1 - L$
			- $m \leftarrow 1$: reset $m$
		- Else: 
			- Adjust $C(x) = C(x) - \frac{d}{b}x^mB(x)$ $b \to$ recalculated $d = 0$
			- $m \leftarrow m + 1$: increment $m$
- **Output:** $C(x)$, min poly of sequence $\{s_i\}$