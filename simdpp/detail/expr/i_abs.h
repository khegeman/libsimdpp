/*  libsimdpp
    Copyright (C) 2013  Povilas Kanapickas povilas@radix.lt
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice,
      this list of conditions and the following disclaimer.

    * Redistributions in binary form must reproduce the above copyright notice,
      this list of conditions and the following disclaimer in the documentation
      and/or other materials provided with the distribution.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
    ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
    LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
    CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
    SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
    INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
    CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
    ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
    POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_EXPR_I_ABS_H
#define LIBSIMDPP_SIMDPP_DETAIL_EXPR_I_ABS_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/bit_xor.h>
#include <simdpp/core/cmp_lt.h>
#include <simdpp/core/cmp_neq.h>
#include <simdpp/core/i_shift_r.h>
#include <simdpp/core/i_sub.h>
#include <simdpp/null/math.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {

template<class E>
uint8<16> expr_eval(expr_abs<int8<16,E>> q)
{
    int8<16> a = q.a.eval();
#if SIMDPP_USE_NULL
    return null::abs(a);
#elif SIMDPP_USE_SSSE3
    return _mm_abs_epi8(a);
#elif SIMDPP_USE_SSE2
    int8x16 t;
    t = cmp_lt(a, int8x16::zero());
    a = bit_xor(a, t);
    a = sub(a, t);
    return a;
#elif SIMDPP_USE_NEON
    return int8x16(vabsq_s8(a));
#elif SIMDPP_USE_ALTIVEC
    // expands to 3 instructions
    return (__vector uint8_t) vec_abs((__vector int8_t)a);
#endif
}

#if SIMDPP_USE_AVX2
template<class E>
uint8<32> expr_eval(expr_abs<int8<32,E>> q)
{
    int8<32> a = q.a.eval();
    return _mm256_abs_epi8(a);
}
#endif

template<unsigned N, class E>
uint8<N> expr_eval(expr_abs<int8<N,E>> q)
{
    int8<N> a = q.a.eval();
    SIMDPP_VEC_ARRAY_IMPL1(uint8<N>, abs, a);
}

// -----------------------------------------------------------------------------

template<class E>
uint16<8> expr_eval(expr_abs<int16<8,E>> q)
{
    int16<8> a = q.a.eval();
#if SIMDPP_USE_NULL
    return null::abs(a);
#elif SIMDPP_USE_SSSE3
    return _mm_abs_epi16(a);
#elif SIMDPP_USE_SSE2
    int16x8 t;
    t = cmp_lt(a, int16x8::zero());
    a = bit_xor(a, t);
    a = sub(a, t);
    return a;
#elif SIMDPP_USE_NEON
    return int16x8(vabsq_s16(a));
#elif SIMDPP_USE_ALTIVEC
    // expands to 3 instructions
    return (__vector uint16_t) vec_abs((__vector int16_t)a);
#endif
}

#if SIMDPP_USE_AVX2
template<class E>
uint16<16> expr_eval(expr_abs<int16<16,E>> q)
{
    int16<16> a = q.a.eval();
    return _mm256_abs_epi16(a);
}
#endif

template<unsigned N, class E>
uint16<N> expr_eval(expr_abs<int16<N,E>> q)
{
    int16<N> a = q.a.eval();
    SIMDPP_VEC_ARRAY_IMPL1(uint16<N>, abs, a);
}

// -----------------------------------------------------------------------------

template<class E>
uint32<4> expr_eval(expr_abs<int32<4,E>> q)
{
    int32<4> a = q.a.eval();
#if SIMDPP_USE_NULL
    return null::abs(a);
#elif SIMDPP_USE_SSSE3
    return _mm_abs_epi32(a);
#elif SIMDPP_USE_SSE2
    int32x4 t;
    t = cmp_lt(a, int32x4::zero());
    a = bit_xor(a, t);
    a = sub(a, t);
    return a;
#elif SIMDPP_USE_NEON
    return int32x4(vabsq_s32(a));
#elif SIMDPP_USE_ALTIVEC
    // expands to 3 instructions
    return (__vector uint32_t) vec_abs((__vector int32_t)a);
#endif
}

#if SIMDPP_USE_AVX2
template<class E>
uint32<8> expr_eval(expr_abs<int32<8,E>> q)
{
    int32<8> a = q.a.eval();
    return _mm256_abs_epi32(a);
}
#endif

template<unsigned N, class E>
uint32<N> expr_eval(expr_abs<int32<N,E>> q)
{
    int32<N> a = q.a.eval();
    SIMDPP_VEC_ARRAY_IMPL1(uint32<N>, abs, a);
}

// -----------------------------------------------------------------------------

template<class E>
uint64<2> expr_eval(expr_abs<int64<2,E>> q)
{
    int64<2> a = q.a.eval();
#if SIMDPP_USE_NULL || SIMDPP_USE_ALTIVEC
    return null::abs(a);
#elif SIMDPP_USE_SSE2
    float64x2 ta;
    int64x2 t;
    ta = float64x2(shift_r<63>(uint64x2(a)));
    t = cmp_neq(ta, float64x2::zero());
    a = bit_xor(a, t);
    a = sub(a, t);
    return a;
#elif SIMDPP_USE_NEON
    int32x4 z = shift_r<63>(uint64x2(a));
    z = cmp_eq(z, int32x4::zero());
    z = permute4<0,0,2,2>(z);
    z = bit_not(z);
    int64x2 t = z;
    a = bit_xor(a, t);
    a = sub(a, t);
    return a;
#endif
}

#if SIMDPP_USE_AVX2
template<class E>
uint64<4> expr_eval(expr_abs<int64<4,E>> q)
{
    int64<4> a = q.a.eval();
    int64x4 t;
    t = _mm256_cmpgt_epi64(int64x4::zero(), a);
    a = bit_xor(a, t);
    a = sub(a, t);
    return a;
}
#endif

template<unsigned N, class E>
uint64<N> expr_eval(expr_abs<int64<N,E>> q)
{
    int64<N> a = q.a.eval();
    SIMDPP_VEC_ARRAY_IMPL1(uint64<N>, abs, a);
}

} // namespace detail
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

