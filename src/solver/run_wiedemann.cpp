#include <linbox/linbox-config.h>
#include <regex>
#include <iostream>
#include <fstream>
#include <linbox/ring/modular.h>
#include <linbox/matrix/sparse-matrix.h>
#include <linbox/polynomial/dense-polynomial.h>
#include <linbox/solutions/minpoly.h>

using namespace LinBox;
using namespace std;

int main(int argc, char **argv)
{
    if (argc != 2) {
        cerr << "Usage: run_wiedemann <matrix-file-in-SMS-format>" << endl;
        return -1;
    }
    std::string file_name = argv[1];

    ifstream input(file_name);
    if (!input) {
        cerr << "Error opening matrix file " << argv[1] << endl;
        return -1;
    }

    std::regex re("GF(\\d+)");
    std::smatch match;
    long q = 0;

    if (std::regex_search(file_name, match, re)) {
        q = std::stol(match[1].str());
        std::cout << "Extracted modulus q = " << q << std::endl;
    } else {
        std::cerr << "Could not find GF(q) in filename!" << std::endl;
        return -1;
    }
    Givaro::Modular<int> F(q);
    SparseMatrix<Givaro::Modular<int>> B(F);
    B.read(input);

    DensePolynomial<Givaro::Modular<int>> m_exact(F);
    DensePolynomial<Givaro::Modular<int>> m_wied(F);

    cout << "Matrix size: " << B.rowdim() << " x " << B.coldim()
         << " over GF(" << q << ")\n";

    // Compute exact minimal polynomial
    minpoly(m_exact, B, Method::Elimination());

    // Compute Wiedemann minimal polynomial
    minpoly(m_wied, B, Method::Wiedemann());

    // cout << "\nExact minimal polynomial:\n";
    // printPolynomial(cout, F, m_exact);

    // cout << "\nWiedemann minimal polynomial:\n";
    // printPolynomial(cout, F, m_wied);

    if (m_exact == m_wied)
        cout << "\nSAME minimal polynomial.\n";
    else
        cout << "\nDIFFERENT minimal polynomials!\n";

    return 0;
}
