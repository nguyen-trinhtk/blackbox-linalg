
#include <iostream>
#include <NTL/ZZ_p.h>
#include <NTL/ZZ_pX.h>
#include <vector>
#include "algorithm/all.h"

using namespace std;
using namespace NTL;
using namespace wiedemann;

int main() {
	long p = 17;
	cout << "Enter field modulus p: ";
	cin >> p;
	ZZ_p::init(ZZ(p));
	long n;
	cout << "Enter n: ";
	cin >> n;
	cout << "Enter sequence of length " << 2 * n << " (space separated): ";
	std::vector<ZZ_p> sequence(2 * n);
	for (long i = 0; i < 2 * n; ++i) {
		long val;
		cin >> val;
		sequence[i] = ZZ_p(val);
	}

	auto early_result = early_berlekamp_massey(sequence, n);
	ZZ_pX minpoly = early_result.first;
	long stop = early_result.second;

	cout << "Early minimal polynomial: " << minpoly << endl;
	cout << "Early stop value: " << stop << endl;

    ZZ_pX result = berlekamp_massey(sequence);
    cout << "Final minimal polynomial: " << result << endl;
	cout << eval(result, ZZ_p(2)) << endl;
	return 0;
}