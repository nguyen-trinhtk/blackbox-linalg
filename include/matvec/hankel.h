#pragma once
#include <NTL/ZZ_p.h>
#include <NTL/mat_ZZ_p.h>
#include <vector>

namespace matvec {
	inline NTL::mat_ZZ_p hankel_matrix(std::size_t n, long p, const std::vector<NTL::ZZ_p>* coeffs = nullptr) {
		NTL::ZZ_p::init(NTL::ZZ(p));
		std::vector<NTL::ZZ_p> c;
		if (coeffs && coeffs->size() == 2 * n - 1) {
			c = *coeffs;
		} else {
			c.resize(2 * n - 1);
			for (std::size_t i = 0; i < c.size(); ++i)
				c[i] = NTL::random_ZZ_p();
		}
		NTL::mat_ZZ_p M;
		M.SetDims(n, n);
		for (std::size_t i = 0; i < n; ++i)
			for (std::size_t j = 0; j < n; ++j)
				M[i][j] = c[i + j];
		return M;
	}
}
