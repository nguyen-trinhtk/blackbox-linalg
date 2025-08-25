#pragma once
#include <NTL/ZZ_p.h>
#include <NTL/vec_ZZ_p.h>

// Return a random vector of size n over GF(p)
namespace matvec {
	inline NTL::vec_ZZ_p random_vector(std::size_t n, long p) {
		NTL::ZZ_p::init(NTL::ZZ(p));
		NTL::vec_ZZ_p v;
		v.SetLength(n);
		for (std::size_t i = 0; i < n; ++i)
			v[i] = NTL::random_ZZ_p();
		return v;
	}
}
