# On LINBOX's implementation of Wiedemann and preconditioning
```cpp
Method::Wiedemann method;
method.preconditioner = Preconditioner::Sparse;
```
- wiedemann.h has include timing
- wiedemann solver has return status: OK, FAILED, SINGULAR, INCONSISTENT, BAD_PRECONDITIONER
- useRandIter: false if uAb, true if uAv
- preconds are only for singular, if nonsingular + precond -> might broke
- somehow preconditioners for wiedemann does not include diag
```
WiedemannSolver<Field>::solveNonsingular (const Blackbox &A,
Vector &x,
const Vector &b,
bool useRandIter)
```
- Wiedemann (BM based): early-term threshold = 10
- trials before failure = 20
- Inspect source code in: `solutions/methods.h`, `algorithm/wiedemann.h`, `solutions/minpoly.h`, `solutions/constants.h`
- Obviously LinBox's implementation is optimized, which means it uses multi-iteration Wiedemann, early-terminated Berlekamp-Massey, preconditioner auto-selection
- Suggestion: replicate one-pass Wiedemann