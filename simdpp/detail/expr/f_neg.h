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

#ifndef LIBSIMDPP_SIMDPP_DETAIL_EXPR_F_NEG_H
#define LIBSIMDPP_SIMDPP_DETAIL_EXPR_F_NEG_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/bit_xor.h>
#include <simdpp/null/math.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {

template<class E>
float32<4> expr_eval(expr_neg<float32<4,E>> q)
{
    float32<4> a = q.a.eval();
#if SIMDPP_USE_NULL || (SIMDPP_USE_NEON && !SIMDPP_USE_NEON_FLT_SP)
    return null::neg(a);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    // reversion of the sign bit required even for NaNs and zeros
    int32x4 zero = make_int(0x80000000);
    return bit_xor(a, zero);
#elif SIMDPP_USE_NEON_FLT_SP
    return vnegq_f32(a);
#endif
}

#if SIMDPP_USE_AVX
template<class E>
float32<8> expr_eval(expr_neg<float32<8,E>> q)
{
    float32<8> a = q.a.eval();
    int32x8 zero = make_int(0x80000000);
    return bit_xor(a, zero);
}
#endif

template<unsigned N, class E>
float32<N> expr_eval(expr_neg<float32<N,E>> q)
{
    float32<N> a = q.a.eval();
    SIMDPP_VEC_ARRAY_IMPL1(float32<N>, neg, a);
}

// -----------------------------------------------------------------------------

template<class E>
float64x2 expr_eval(expr_neg<float64<2,E>> q)
{
    float64x2 a = q.a.eval();
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    return null::neg(a);
#elif SIMDPP_USE_SSE2
    int64x2 zero = make_int(0x8000000000000000);
    return bit_xor(a, zero);
#endif
}

#if SIMDPP_USE_AVX
template<class E>
float64x4 expr_eval(expr_neg<float64<4,E>> q)
{
    float64x4 a = q.a.eval();
    int64x4 zero = make_int(0x8000000000000000);
    return bit_xor(a, zero);
}
#endif

template<unsigned N, class E>
float64<N> expr_eval(expr_neg<float64<N,E>> q)
{
    float64<N> a = q.a.eval();
    SIMDPP_VEC_ARRAY_IMPL1(float64<N>, neg, a);
}

} // namespace detail
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

