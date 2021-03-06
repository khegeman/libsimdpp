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

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_ALIGN_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_ALIGN_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/bit_or.h>
#include <simdpp/core/move_l.h>
#include <simdpp/core/move_r.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {
namespace insn {


// base 8x16 implementation
template<unsigned shift>
uint8x16 i_align16(uint8x16 lower, uint8x16 upper)
{
#if SIMDPP_USE_NULL
    uint8x16 r;
    //use int to disable warnings wrt. comparison result always being true/false
    for (int i = 0; i < (int)(16-shift); i++) {
        r.el(i) = lower.el(i + shift);
    }
    for (unsigned i = 16-shift; i < 16; i++) {
        r.el(i) = upper.el(i - 16 + shift);
    }
    return r;
#elif SIMDPP_USE_SSSE3
    return _mm_alignr_epi8(upper, lower, shift);
#elif SIMDPP_USE_SSE2
    uint8x16 a;
    lower = move16_l<shift>(lower);
    upper = move16_r<16-shift>(upper);
    a = bit_or(upper, lower);
    return a;
#elif SIMDPP_USE_NEON
    return vextq_u8(lower, upper, shift);
#elif SIMDPP_USE_ALTIVEC
    return vec_sld((__vector uint8_t)lower, (__vector uint8_t)upper, (unsigned)shift);
#endif
}

#if SIMDPP_USE_AVX2
template<unsigned shift>
uint8x32 i_align16(uint8x32 lower, uint8x32 upper)
{
    return _mm256_alignr_epi8(upper, lower, shift);
}
#endif

template<unsigned shift, unsigned N>
uint8<N> i_align16(uint8<N> lower, uint8<N> upper)
{
    SIMDPP_VEC_ARRAY_IMPL2(uint8<N>, i_align16<shift>, lower, upper);
}

// generic implementations

template<unsigned shift, unsigned N>
uint16<N> i_align8(uint16<N> lower, uint16<N> upper)
{
    return uint16<N>(i_align16<shift*2>(uint8<N*2>(lower),
                                        uint8<N*2>(upper)));
}

template<unsigned shift, unsigned N>
uint32<N> i_align4(uint32<N> lower, uint32<N> upper)
{
    return uint32<N>(i_align16<shift*4>(uint8<N*4>(lower),
                                        uint8<N*4>(upper)));
}

template<unsigned shift, unsigned N>
uint64<N> i_align2(uint64<N> lower, uint64<N> upper)
{
    return uint64<N>(i_align16<shift*8>(uint8<N*8>(lower),
                                        uint8<N*8>(upper)));
}

template<unsigned shift, unsigned N>
float32<N> i_align4(float32<N> lower, float32<N> upper)
{
    return float32<N>(i_align4<shift>(uint32<N>(lower),
                                      uint32<N>(upper)));
}

template<unsigned shift, unsigned N>
float64<N> i_align2(float64<N> lower, float64<N> upper)
{
    return float64<N>(i_align2<shift>(uint64<N>(lower),
                                      uint64<N>(upper)));
}

} // namespace insn
} // namespace detail
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

