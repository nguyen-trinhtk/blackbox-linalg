- How many times min poly of uTAib is min poly of uTAib
- How many times it correctly solves
- Chances factor appear ...
---
- Theoretical time complexity vs practical performance (plot time vs n)
- Varying sparsity
- Performance differences fot various matrix-vector multiplication methods (dense, sparse, custom blackbox)
- How many iterations needed to determine rank, det, etc. 
- Wiedemann vs Lanczos
- Scalability on Multithreading/Parallel Environments
    Goal: Explore whether matrix-vector multiplications or minimal polynomial steps can be parallelized.
    Tasks:
    Profile code (e.g., with gprof or valgrind) to identify bottlenecks.
    Implement or simulate multithreaded matrix-vector product (e.g., using OpenMP).
    Measure speedup with increasing threads.
    Deliverable:
    Speedup vs. threads graph, with Amdahl’s law interpretation.
---
TDD: 
- if $A*A^{-1} = 1 mod p$ 
- matrix-vector mult, compare sparse vs dense result
- krylov sequence
- min poly
- Check if $A*x = b$ is valid/satisfied
- Edge cases
---
Data analysis: 
- Runtime vs matrix size: plot
- Convergence rate (iteration count): histogram
- Runtime vs sparsity: heatmap/bar chart
- Randomness effect	(Success rate vs. trials): Boxplot
- Preconditioning (Speedup vs. baseline) Bar chart
-> Export C++ results, then do data analysis w matplotlib, pandas