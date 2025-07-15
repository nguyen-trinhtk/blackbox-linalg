// ==========================================================================
// Copyright(c)'2016 by The Givaro group
// This file is part of Givaro.
// Givaro is governed by the CeCILL-B license under French law
// and abiding by the rules of distribution of free software.
// see the COPYRIGHT file for more details.
// Authors: J.-G. Dumas

#ifndef __GIVARO_random_integer_iterator_H
#define __GIVARO_random_integer_iterator_H

#include "gmp++/gmp++.h"

namespace Givaro
{

    template <class Element> class ZRing;

    /*!@brief Random Integer Iterator.
     * @ingroup integers
     * @ingroup randiter
     *
     * Generates integers of specified length.
     * @tparam _Unsigned if \c true, then only non negative integers
     * are generated, if \c false, their sign is random.
     * @tparam _Exact_Size if \c true, then random integers have
     * exactly the number of required bits, if \c false, they have
     * less than the required number of bits
     * WARNING, the seed is *** global ***
     * WARNING: i.e. sets the seed for all Givaro Integer 
     */
    template<bool _Unsigned=true, bool _Exact_Size=false>
    class RandomIntegerIterator {
      typedef typename
      std::integral_constant<bool,_Exact_Size>::type _Exact_Size_t;

    public:
        typedef Givaro::Integer Integer_Type ;
        typedef Givaro::Integer Element ;
        typedef Givaro::Integer Residu_t ;
        typedef Givaro::ZRing<Integer> Integer_Domain ;

    private:
        void initialize(uint64_t seed, const size_t bits)
        {
            if (! bits) _bits = 30u;
            GIVARO_ASSERT( _bits>0u, "[RandomIntegerIterator] bad bit size");
            int64_t s=seed;
            while (!s)
                s = static_cast<uint64_t>(BaseTimer::seed());
            setSeed (s);
            this->operator++();
        }

    public:
        /*! Constructor.
         * @param seed if \c 0 a seed will be generated, otherwise, the
         * provided seed will be used, *** globally ***
         * Default bit size (30) can be changed with method 'setBitsize'
         */
        RandomIntegerIterator(const Integer_Domain& D, uint64_t seed = 0) :
            _bits(30u), _integer(), _ring(D)
        {
            initialize(seed,_bits);
        }

        /*! Constructor.
         * @param seed if \c 0 a seed will be generated, otherwise, the
         * provided seed will be used, *** globally ***
         * @param samplesize is number ofpossible random values
         */
        RandomIntegerIterator(const Integer_Domain& D, uint64_t seed, const Integer& samplesize) : _bits(samplesize.bitsize()), _integer(), _ring(D)
        {
            initialize(seed,_bits);
        }

        /// copy constructor.
        /// @param R random iterator to be copied.
        RandomIntegerIterator (const RandomIntegerIterator &R) :
            _bits(R._bits), _integer(R._integer), _ring(R._ring)
        {}

        /// copy.
        /// @param R random iterator to be copied.
        RandomIntegerIterator &operator=(const RandomIntegerIterator &R)
        {
            if (this != &R) {
                _bits = R._bits;
                _integer = R._integer;
            }
            return *this;
        }


        /** @brief operator++()
         *  creates a new random integer.
         */
        inline RandomIntegerIterator &operator ++ ()
        {
            this->nextRandom(_Exact_Size_t(), _integer);
            return *this;
        }

        /** @brief get the random integer.
         *  returns the actual integer.
         */
        const Integer_Type &operator *  () const
        {
            return _integer;
        }

        /** @brief get the random integer.
         *  returns the actual integer.
         *  @warning a new integer is not generated.
         */
        const Integer_Type & randomInteger() const
        {
            return _integer;
        }

        Integer_Type & random (Integer_Type & a) const
        {
            return this->nextRandom(_Exact_Size_t(), a);
        }

        Element& operator() (Element& a) const {
            return this->random(a);
        }

        Element operator() () const{
            Element a; this->random(a); return a;
        }
        Element random () const {
            return this->operator()();
        }

        /** @brief Sets the seed *** globally ***
         *  WARNING: i.e. sets the seed for all Givaro Integer 
         *  Set the random seed to be \p ul.
         *  @param ul the new seed.
         */
        void static setSeed(uint64_t ul)
        {
            Givaro::Integer::seeding(ul);
        }

        void setBitsize (size_t  bits)
        {
            _bits = bits;
            this->operator++(); // next random value must depend on new bitsize
        }

        size_t getBitsize () const
        {
            return _bits ;
        }

        const Integer_Domain& ring() const
        {
            return _ring;
        }



    protected:
        inline Integer_Type& nextRandom(std::true_type,  Integer_Type & a) const {
            return Givaro::Integer::random_exact<_Unsigned>(a,_bits);
        }
        inline Integer_Type& nextRandom(std::false_type, Integer_Type & a) const {
            return Givaro::Integer::random_lessthan<_Unsigned>(a,_bits);
        }

        size_t				_bits;	//!< common length of all integers
        Integer_Type			_integer;	//!< the generated integer.
        const Integer_Domain&	_ring;

    private:
        /*! DEPRECATED Constructor.
         * This behavior can be now reproduced by calling:
         * 1/ Constructor with 2 args, D and seed ...
         * 2/ ... then object.setBitsize(bits).
         */
        RandomIntegerIterator(const Integer_Domain&, uint64_t, size_t); // DEPRECATED Constructor. Instead, call constructor with 2 args then object.setBitsize(bits)


    };

}

#endif //__GIVARO_random_integer_iterator_H
/* -*- mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
// vim:sts=4:sw=4:ts=4:et:sr:cino=>s,f0,{0,g0,(0,\:0,t0,+0,=s
