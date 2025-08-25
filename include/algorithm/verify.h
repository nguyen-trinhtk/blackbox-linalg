// Minimal polynomial verification for matrix A and polynomial f over GF(p)
#include <NTL/ZZ_pXFactoring.h>
#include <NTL/mat_ZZ_p.h>
#include <NTL/vec_ZZ_p.h>

namespace verify {
	NTL::mat_ZZ_p evaluate_poly_matrix(const NTL::ZZ_pX& f, const NTL::mat_ZZ_p& A) {
		long n = A.NumRows();
		NTL::mat_ZZ_p result;
		NTL::ident(result, n); // result = I
		result *= NTL::coeff(f, NTL::deg(f));
		for (long i = NTL::deg(f) - 1; i >= 0; --i) {
			result = A * result;
			NTL::mat_ZZ_p term;
			NTL::ident(term, n);
			term *= NTL::coeff(f, i);
			result += term;
		}
		return result;
	}

	bool is_min_poly(const NTL::mat_ZZ_p& A, const NTL::ZZ_pX& f) {
	NTL::mat_ZZ_p eval = evaluate_poly_matrix(f, A);
		if (!IsZero(eval)) return false;

		NTL::vec_pair_ZZ_pX_long factors;
		NTL::CanZass(factors, f);

		for (long i = 0; i < factors.length(); ++i) {
			NTL::ZZ_pX factor = factors[i].a;
			// long exp = factors[i].b;
			NTL::ZZ_pX q = f / factor;
			NTL::mat_ZZ_p eval_q = evaluate_poly_matrix(q, A);
			if (IsZero(eval_q)) return false;
		}
		return true;
	}
}
