#include <linbox/linbox-config.h>
#include <sstream>
#include <string>
#include <iostream>
#include <linbox/polynomial/dense-polynomial.h>
#include <linbox/ring/modular.h>
#include "wrappers.h"

using namespace LinBox;
using namespace std;

bool testPolyPrint(const string &testName, DensePolynomial<Givaro::Modular<int>> &P, 
                         Givaro::Modular<int> &F, const string &expected)
{
    stringstream ss;
    polyPrint(ss, F, P);
    string result = ss.str();

    if (result == expected) {
        cout << "[PASS] " << testName << endl;
        return true;
    } else {
        cout << "[FAIL] " << testName << endl;
        cout << "  Expected: " << expected << endl;
        cout << "  Got:      " << result << endl;
        return false;
    }
}

int main()
{
    typedef Givaro::Modular<int> Mod7;
    Mod7 F(7);

    // Test 1: 3x^3 + 0x^2 + 2x + 1
    DensePolynomial<Mod7> P1(F);
    P1.resize(4);
    P1[0] = 1;
    P1[1] = 2;
    P1[2] = 0;
    P1[3] = 3;
    testPolyPrint("Test 1", P1, F, "3 x^3 + 0 x^2 + 2 x^1 + 1 x^0");

    // Test 2: 0x^2 + 5x + 6
    DensePolynomial<Mod7> P2(F);
    P2.resize(3);
    P2[0] = 6;
    P2[1] = 5;
    P2[2] = 0;
    testPolyPrint("Test 2", P2, F, "0 x^2 + 5 x^1 + 6 x^0");

    // Test 3: constant polynomial 4
    DensePolynomial<Mod7> P3(F);
    P3.resize(1);
    P3[0] = 4;
    testPolyPrint("Test 3", P3, F, "4 x^0");

    return 0;
}