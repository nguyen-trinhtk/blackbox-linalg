# STAR 2025

### Abstract
This project explores Wiedemann’s algorithm for
solving large sparse linear systems over a finite
field. Wiedemann’s method (1986) probabilistically
computes the minimal polynomial over finite fields
using the Berlekamp–Massey (BM) algorithm to find
the recurrence of Krylov sequences.
Eberly (2003) proposed an early termination
criterion for BM: For matrix size n and field order q , if
a recurrence holds for c * log_q(n) consecutive terms
without change, the algorithm may stop early. This
can significantly reduce runtime, but may fail.
This project studies the empirical success rate of
early-terminated BM across matrix types, sizes, and
field orders. For c = 3 , results show >98% success
across test cases. Diagonal and sparse matrices
terminate the earliest, while Toeplitz, Jordan, and
companion matrices typically require full BM.
Thus, early-terminated BM can be combined with
Wiedemann with high confidence, and specific
success rates for each matrix type can guide
combination strategies to ensure fast and precise
solutions in large, sparse linear system

### Poster