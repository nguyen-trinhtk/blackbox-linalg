#include <iostream>
#include <NTL/mat_ZZ_p.h>
#include <NTL/ZZ.h>
#include "matrix/all.h"

using namespace std;
using namespace NTL;
int main() {
    long p;
    // Prime check
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
    mat_ZZ_p C = matrix::companion_matrix(n, p);
    cout << "Companion matrix:\n" << C << "\n";
    mat_ZZ_p D = matrix::diagonal_matrix(n, p);
    cout << "Diagonal matrix:\n" << D << "\n";
    mat_ZZ_p H = matrix::hankel_matrix(n, p);
    cout << "Hankel matrix:\n" << H << "\n";
    mat_ZZ_p J = matrix::jordan_matrix(n, p);
    cout << "Jordan matrix:\n" << J << "\n";
    mat_ZZ_p R = matrix::random_matrix(n, p);
    cout << "Random matrix:\n" << R << "\n";
    mat_ZZ_p S = matrix::sparse_matrix(n, p);
    cout << "Sparse matrix:\n" << S << "\n";
    mat_ZZ_p T = matrix::toeplitz_matrix(n, p);
    cout << "Toeplitz matrix:\n" << T << "\n";
    return 0;
}