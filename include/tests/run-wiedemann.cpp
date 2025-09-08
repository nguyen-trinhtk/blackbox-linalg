#include <iostream>
#include <NTL/ZZ_p.h>
#include <NTL/mat_ZZ_p.h>
#include <NTL/vec_ZZ_p.h>
#include "algorithm/all.h"

using namespace std;
using namespace NTL;
// using namespace wiedemann;

int main() {
    long p = 17;
    cout << "Enter field modulus p: ";
    cin >> p;
    ZZ_p::init(ZZ(p));
    long n;
    cout << "Enter matrix size n: ";
    cin >> n;
    cout << "Enter matrix A (n x n, row-major, space separated): ";
    mat_ZZ_p A;
    A.SetDims(n, n);
    for (long i = 0; i < n; ++i) {
        for (long j = 0; j < n; ++j) {
            long val;
            cin >> val;
            A[i][j] = ZZ_p(val);
        }
    }
    cout << "Optionally, enter vector v (length n, space separated, or -1 to use random): ";
    vec_ZZ_p v;
    v.SetLength(n);
    bool use_random = false;
    for (long i = 0; i < n; ++i) {
        long val;
        cin >> val;
        if (val == -1) {
            use_random = true;
            break;
        }
        v[i] = ZZ_p(val);
    }
    cout << "Computing minimal polynomial using Wiedemann...\n";
    ZZ_pX minpoly;
    if (use_random) {
        minpoly = wiedemann::wiedemann(A);
    } else {
        minpoly = wiedemann::wiedemann(A, &v);
    }
    cout << "Minimal polynomial: " << minpoly << endl;
    return 0;
}
