#include <iostream>
#include <NTL/mat_ZZ_p.h>
#include <NTL/ZZ.h>
#include "matvec/all.h"

using namespace std;
using namespace NTL;
using namespace matvec;
int main() {
    long p;
    while (true)
    {
        cout << "Enter p: ";
        cin >> p;
        if (ProbPrime(p)) {
            break;
        } else {
            cout << "p is not prime. " << endl;
        }
    }
    long n;
    cout << "Enter n: ";
    cin >> n;
    mat_ZZ_p C = companion_matrix(n, p);
    cout << "Companion matrix:\n" << C << "\n";
    mat_ZZ_p D = diagonal_matrix(n, p);
    cout << "Diagonal matrix:\n" << D << "\n";
    mat_ZZ_p H = hankel_matrix(n, p);
    cout << "Hankel matrix:\n" << H << "\n";
    mat_ZZ_p J = jordan_matrix(n, p);
    cout << "Jordan matrix:\n" << J << "\n";
    mat_ZZ_p R = random_matrix(n, p);
    cout << "Random matrix:\n" << R << "\n";
    mat_ZZ_p S = sparse_matrix(n, p);
    cout << "Sparse matrix:\n" << S << "\n";
    mat_ZZ_p T = toeplitz_matrix(n, p);
    cout << "Toeplitz matrix:\n" << T << "\n";
    vector<mat_ZZ_p> blocks = {C, D, H, J, R, S, T};
    mat_ZZ_p B = block_diagonal(blocks);
    cout << "Block diagonal matrix:\n" << B << "\n";
    return 0;
}