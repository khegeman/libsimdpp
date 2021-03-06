/*  libsimdpp
    Copyright (C) 2012  Povilas Kanapickas tir5c3@yahoo.co.uk
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

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_SHUFFLE128_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_SHUFFLE128_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {
namespace insn {

/// @{
/** Shuffles 128 bit parts within the vectors.

@code
    switch(s0):
        case 0: r[0..127] = a[0..127]
        case 1: r[0..127] = a[128..255]
        case 2: r[0..127] = b[0..127]
        case 3: r[0..127] = b[128..255]

    switch(s1):
        case 0: r[128..255] = a[0..127]
        case 1: r[128..255] = a[128..255]
        case 2: r[128..255] = b[0..127]
        case 3: r[128..255] = b[128..255]
@endcode
*/
template<unsigned s0, unsigned s1>
uint8x32 shuffle128(uint8x32 a, uint8x32 b)
{
    static_assert(s0 < 4 && s1 < 4, "Selector out of range");
#if SIMDPP_USE_AVX2
    return _mm256_permute2x128_si256(a, b, s1*0x10 + s0);
#else
    uint8x32 r;
    r[0] = a[s0];
    r[1] = b[s1];
    return r;
#endif
}
template<unsigned s0, unsigned s1>
uint16x16 shuffle128(uint16x16 a, uint16x16 b) { return (uint16x16)shuffle128<s0,s1>(uint8x32(a), uint8x32(b)); }
template<unsigned s0, unsigned s1>
uint32x8 shuffle128(uint32x8 a, uint32x8 b) { return (uint32x8)shuffle128<s0,s1>(uint8x32(a), uint8x32(b)); }
template<unsigned s0, unsigned s1>
uint64x4 shuffle128(uint64x4 a, uint64x4 b) { return (uint64x4)shuffle128<s0,s1>(uint8x32(a), uint8x32(b)); }

template<unsigned s0, unsigned s1>
float32x8 shuffle128(float32x8 a, float32x8 b)
{
    static_assert(s0 < 4 && s1 < 4, "Selector out of range");
#if SIMDPP_USE_AVX
    return _mm256_permute2f128_ps(a, b, s1*0x10 + s0);
#else
    float32x8 r;
    r[0] = a[s0];
    r[1] = b[s1];
    return r;
#endif
}
template<unsigned s0, unsigned s1>
float64x4 shuffle128(float64x4 a, float64x4 b)
{
    static_assert(s0 < 4 && s1 < 4, "Selector out of range");
#if SIMDPP_USE_AVX
    return _mm256_permute2f128_pd(a, b, s1*0x10 + s0);
#else
    float64x4 r;
    r[0] = a[s0];
    r[1] = b[s1];
    return r;
#endif
}
/// @}

} // namespace insn
} // namespace detail
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

