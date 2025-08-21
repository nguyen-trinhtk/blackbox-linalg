/* linbox/algorithms/doubledet.h
 * Copyright (C) LinBox
 *
 *  Written by Clement Pernet <clement.pernet@gmail.com>
 *
 *
 * ========LICENCE========
 * This file is part of the library LinBox.
 *
 * LinBox is free software: you can redistribute it and/or modify
 * it under the terms of the  GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 * ========LICENCE========
 *.
 */

#ifndef __LINBOX_doubledet_H
#define __LINBOX_doubledet_H

#include "fflas-ffpack/ffpack/ffpack.h"
#include "linbox/algorithms/matrix-hom.h"
#include "linbox/algorithms/cra-domain.h"
#include "linbox/algorithms/cra-builder-full-multip.h"
#include "linbox/algorithms/cra-builder-early-multip.h"
#include "linbox/randiter/random-prime.h"
#include "linbox/solutions/solve.h"
#include "linbox/solutions/methods.h"
#include "linbox/solutions/hadamard-bound.h"

namespace LinBox
{

	/* Given a (n-1) x n full rank matrix A and 2 vectors b,c mod p,
	 * compute
	 * d1 = det( [ A ] ) mod p and d2 = det ( [ A ]) mod p
	 *           [ b ]                        [ c ]
	 *
	 *
	 * A, b, c will be overwritten.
	 */
	template <class Field>
	void doubleDetModp (const Field& F, const size_t N,
			    typename Field::Element& d1,
			    typename Field::Element& d2,
			    typename Field::Element* A, const size_t lda,
			    typename Field::Element* b, const size_t incb,
			    typename Field::Element* c, const size_t incc)
	{

		size_t* P = new size_t[N];
		size_t* Qt = new size_t[N-1];

		FFPACK::LUdivine (F, FFLAS::FflasUnit, FFLAS::FflasNoTrans, N-1, N,
				  A, lda, P, Qt);
		typename Field::Element d;

		// Multiplying all (N-1) first pivots)
		F.assign(d, F.one);
		for (size_t i=0; i<N-1; ++i)
			F.mulin (d, *(A + i*(lda+1)));

		bool count = false;
		for (size_t i=0;i<N-1;++i)
			if (P[i] != i) count = !count;
		if (count)
			F.negin(d);

		// Trick: instead of Right-Trans, do Left-NoTrans in order to use inc*
		FFPACK::applyP (F, FFLAS::FflasLeft, FFLAS::FflasNoTrans,
				1, 0,(int) N-1, b, incb, P);
		FFPACK::applyP (F, FFLAS::FflasLeft, FFLAS::FflasNoTrans,
				1, 0,(int) N-1, c, incc, P);
		FFLAS::ftrsv (F, FFLAS::FflasUpper, FFLAS::FflasTrans,
			      FFLAS::FflasUnit,
			      N, A, lda, b, (int)incb);
		FFLAS::ftrsv (F, FFLAS::FflasUpper, FFLAS::FflasTrans,
			      FFLAS::FflasUnit,
			      N, A, lda, c, (int)incc);


		F.mul (d1, d, *(b + (N-1) * incb));
		F.mul (d2, d, *(c + (N-1) * incc));

		delete[] P;
		delete[] Qt;
	}

	// Iteration class for the Chinese remaindering phase
	template <class BlackBox>
	struct IntegerDoubleDetIteration{

		const BlackBox& _matA;
		const typename BlackBox::Field::Element _s1;
		const typename BlackBox::Field::Element _s2;
		IntegerDoubleDetIteration(const BlackBox& A,
					  const typename BlackBox::Field::Element& s1,
					  const typename BlackBox::Field::Element& s2) :
			_matA(A), _s1(s1), _s2(s2)
		{}

		template<class Field>
		IterationResult
		operator () (BlasVector<Field>& dd,
			     const Field& F) const
		{

			typedef typename BlackBox::template rebind<Field>::other FBlackbox;
			typename Field::Element s1p, s2p;
			dd.resize(2);
			F.init(s1p, _s1);
			F.init(s2p, _s2);
			FBlackbox Ap(_matA, F);
			const size_t N = _matA.coldim();
			//Timer tim;
			//tim.clear();
			//tim.start();
			doubleDetModp (F,  N, dd[0], dd[1],
				       Ap.getPointer(), Ap.getStride(),
				       Ap.getPointer() + (N-1) * Ap.getStride(), 1,
				       Ap.getPointer() + N * Ap.getStride(), 1);

			F.divin (dd[0], s1p);
			F.divin (dd[1], s2p);
			//tim.stop();
			//std::cerr<<"doubleDetModp took "<<tim.usertime()<<std::endl;
			return IterationResult::CONTINUE;
		}
	};

	/* Given a (N+1) x N full rank matrix
	 * [ A ]
	 * [ b ]
	 * [ c ]
	 * where b and c are the last 2 rows,
	 * and given s1 and s2, respectively divisors of d1 and d2 defined as
	 * d1 = det ([ A ])
	 *          ([ b ])
	 * and
	 * d2 = det ([ A ])
	 *          ([ c ]),
	 * compute d1 and d2.
	 * Assumes d1 and d2 are non zero.
	 * Result is probablistic if proof=true
	 */
	template <class BlackBox>
	void doubleDetGivenDivisors (const BlackBox& A,
				     typename BlackBox::Field::Element& d1,
				     typename BlackBox::Field::Element& d2,
				     const typename BlackBox::Field::Element& s1,
				     const typename BlackBox::Field::Element& s2,
				     const bool proof)
	{

		typename BlackBox::Field F = A.field();
		IntegerDoubleDetIteration<BlackBox> iteration(A, s1, s2);
		// 0.7213475205 is an upper approximation of 1/(2log(2))
                typedef Givaro::ModularBalanced<double> Field;
                PrimeIterator<IteratorCategories::HeuristicTag> genprime(FieldTraits<Field>::bestBitSize(A.coldim()));

		BlasVector<typename BlackBox::Field> dd(A.field());
		if (proof) {
			double logbound;
			//Timer t_hd,t_cra;
			//t_hd.clear();
			//t_hd.start();
			size_t bound = HadamardBound(A);
			logbound = (bound - logtwo (MIN(abs(s1),abs(s2))));
			//t_hd.stop();
			//std::cerr<<"Hadamard bound = : "<<logbound<<" in "<<t_hd.usertime()<<"s"<<std::endl;

			ChineseRemainder <CRABuilderFullMultip <Givaro::Modular <double> > > cra(logbound);

			//t_hd.clear();
			//t_cra.start();
			cra (dd, iteration, genprime);
			//t_cra.stop();
			//std::cerr<<"CRA : "<<t_cra.usertime()<<"s"<<std::endl;

		}
		else {
			ChineseRemainder <CRABuilderEarlyMultip <Field> >  cra(LINBOX_DEFAULT_EARLY_TERMINATION_THRESHOLD);
			cra (dd, iteration, genprime);
		}
		F.mul (d1, dd[0], s1);
		F.mul (d2, dd[1], s2);
	}

	/* Given a (n + 1) x n full rank matrix
	 * A = [ B ]
	 *     [ b ]
	 *     [ c ]
	 * over Z, compute
	 * d1 = det( [ A ] ) and d2 = det ( [ A ])
	 *           [ b ]                  [ c ]
	 */

	template <class BlackBox>
	void doubleDet (typename BlackBox::Field::Element& d1,
			typename BlackBox::Field::Element& d2,
			const BlackBox& A,
			//const vector<typename BlackBox::Field::Element>& b,
			//const vector<typename BlackBox::Field::Element>& c,
			bool proof)
	{

		linbox_check (A.coldim() == A.rowdim()+1);

		const size_t N = A.coldim();
		BlasMatrix<typename BlackBox::Field> B (A.field(),N,N);
		typename BlackBox::Field::Element den1, den2;
		BlasVector<typename BlackBox::Field> x1(A.field(),N);
		for (size_t i=0; i<N; ++i){
			x1[i] = 0;
			for (size_t j=0; j<N; ++j)
				B.setEntry(j,i, A.getEntry(i,j));
		}
		// 		for (size_t i=0; i<N; ++i)
		// 			B.setEntry (i, N-1, b[i]);

		BlasVector<typename BlackBox::Field> c(A.field(),N);
		for (size_t i=0; i<N; ++i)
			c[i] = A.getEntry (N, i);
		//Timer tim;
		//tim.clear();
		//tim.start();
		solve (x1, den1, B, c);
		//tim.stop();
		//std::cerr<<"Solve took "<<tim.usertime()<<std::endl;

		// den1 = den1;
		// Should work:
		// den (y[n]) = den (-den1/x[n]) = x[n]
		den2 = -x1[N-1];
		//tim.clear();
		//tim.start();
		doubleDetGivenDivisors (A, d1, d2, den1, den2, proof);
		//tim.stop();
		//std::cerr<<"CRA "<<(proof?"Determinist":"Probablistic")
		//	 <<" took "<<tim.usertime()<<std::endl;
	}
}


#endif // __LINBOX_doubledet_H

// Local Variables:
// mode: C++
// tab-width: 4
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim:sts=4:sw=4:ts=4:et:sr:cino=>s,f0,{0,g0,(0,\:0,t0,+0,=s
