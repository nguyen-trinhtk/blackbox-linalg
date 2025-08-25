#pragma once
#include <NTL/ZZ_p.h>
#include <NTL/mat_ZZ_p.h>
#include <vector>

// Companion nxn matrix over GF(p) (optional: polynomial coefficients)
namespace matvec {
	inline NTL::mat_ZZ_p companion_matrix(std::size_t n, long p, const std::vector<NTL::ZZ_p>* coeffs = nullptr) {
		NTL::ZZ_p::init(NTL::ZZ(p));
		std::vector<NTL::ZZ_p> c;
		if (coeffs && coeffs->size() == n) {
			c = *coeffs;
		} else {
			c.resize(n);
			for (std::size_t i = 0; i < n; ++i)
				c[i] = NTL::random_ZZ_p();
		}
		NTL::mat_ZZ_p M;
		M.SetDims(n, n);
		for (std::size_t i = 0; i < n; ++i) {
			for (std::size_t j = 0; j < n; ++j) {
				if (i == j + 1)
					M[i][j] = NTL::ZZ_p(1); // subdiagonal
				else if (j == n - 1)
					M[i][j] = -c[i]; // last column
				else
					M[i][j] = NTL::ZZ_p(0);
			}
		}
		return M;
	}
}
