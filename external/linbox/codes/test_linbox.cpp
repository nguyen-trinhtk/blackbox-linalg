#include <linbox/linbox-config.h>
#include <linbox/matrix/dense-matrix.h>
#include <givaro/gfq.h>
#include <givaro/gfq.h>
#include <iostream>
#include <vector>
#include <random>

using namespace std;

typedef Givaro::GFqDom<int> Field;
typedef LinBox::DenseMatrix<Field> Matrix;

// Pretty-print a LinBox matrix in row/column format
template<typename Field>
void print_matrix(const LinBox::DenseMatrix<Field>& M) {
    size_t nrows = M.rowdim();
    size_t ncols = M.coldim();
    for (size_t i = 0; i < nrows; ++i) {
        for (size_t j = 0; j < ncols; ++j) {
            std::cout << M[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

std::vector<Matrix> mat_gen(int q, int n) {
    Field F(q);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, q-1);

    // Diagonal
    Matrix D(F, n, n);
    for (int i = 0; i < n; ++i)
        F.init(D[(size_t)i][(size_t)i], dis(gen));

    // Identity
    Matrix I(F, n, n);
    for (int i = 0; i < n; ++i)
        F.init(I[(size_t)i][(size_t)i], F.one);

    // Toeplitz
    Matrix T(F, n, n);
    std::vector<int> first_col(n), first_row(n);
    for (int i = 0; i < n; ++i) first_col[i] = dis(gen);
    for (int i = 0; i < n; ++i) first_row[i] = dis(gen);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            F.init(T[(size_t)i][(size_t)j], (i >= j) ? first_col[i-j] : first_row[j-i]);

    // Jordan block (eigenvalue random in [2, q])
    Matrix J(F, n, n);
    int eigen = 2 + dis(gen) % (q-1);
    for (int i = 0; i < n; ++i)
        F.init(J[(size_t)i][(size_t)i], eigen);
    for (int i = 0; i < n-1; ++i)
        F.init(J[(size_t)i][(size_t)i+1], 1);

    // Sparse random
    Matrix S(F, n, n);
    double density = 0.1;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (dis(gen) < q * density)
                F.init(S[(size_t)i][(size_t)j], dis(gen));

    // Companion matrix
    Matrix C(F, n, n);
    std::vector<int> coeffs(n);
    for (int i = 0; i < n; ++i) coeffs[i] = dis(gen);
    // x^n + sum(coeffs[i] * x^i)
    for (int i = 0; i < n-1; ++i)
        F.init(C[(size_t)i+1][(size_t)i], 1); // subdiagonal
    for (int i = 0; i < n; ++i)
        F.init(C[(size_t)0][(size_t)i], -coeffs[i]); // first row: negative coefficients

    return {D, I, T, J, S, C};
}

// Example usage in main
int main() {
    int n, q;
    std::cout << "Enter matrix size n: ";
    std::cin >> n;
    std::cout << "Enter field cardinality q: ";
    std::cin >> q;

    auto matrices = mat_gen(q, n);

    // Output matrices
    std::vector<std::string> names = {"Diagonal", "Identity", "Toeplitz", "Jordan", "Sparse", "Companion"};
    for (size_t i = 0; i < matrices.size(); ++i) {
        std::cout << names[i] << " =\n";
        print_matrix(matrices[i]);
        std::cout << "-------------------\n";
    }

    return 0;
}