/*  libsimdpp
    Copyright (C) 2014  Povilas Kanapickas <povilas@radix.lt>
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

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_SET_SPLAT_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_SET_SPLAT_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {

template<class V>
struct is_expr_vec_set_splat { static const bool value = false; };
template<class VE>
struct is_expr_vec_set_splat<expr_vec_set_splat<VE>> { static const bool value = true; };

namespace insn {

inline void i_set_splat(uint32x4&, uint32_t);

inline void i_set_splat(uint8x16& v, uint8_t v0)
{
#if SIMDPP_USE_NULL
    v = null::make_vec<uint8x16>(v0);
#elif SIMDPP_USE_SSE2
    uint32_t u0;
    u0 = v0 * 0x01010101;
    uint32x4 u;
    i_set_splat(u, u0);
    v = u;
#elif SIMDPP_USE_NEON
    v = vdupq_n_u8(v0);
#elif SIMDPP_USE_ALTIVEC
    union {
        uint8_t rv[16];
        uint8x16 align;
    };
    rv[0] = v0;
    v = altivec::load1(v, rv);
    v = splat<0>(v);
#endif
}

#if SIMDPP_USE_AVX2
inline void i_set_splat(uint8x32& v, uint8_t v0)
{
    uint8x16 a = _mm_cvtsi32_si128(v0);
    v = _mm256_broadcastb_epi8(a);
}
#endif

template<unsigned N>
void i_set_splat(uint8<N>& v, uint8_t v0)
{
    uint8v tv;
    i_set_splat(tv, v0);
    for (unsigned i = 0; i < v.vec_length; ++i) {
        v[i] = tv;
    }
}

// -----------------------------------------------------------------------------

inline void i_set_splat(uint16x8& v, uint16_t v0)
{
#if SIMDPP_USE_NULL
    v = null::make_vec<uint16x8>(v0);
#elif SIMDPP_USE_SSE2
    uint32_t u0;
    u0 = v0 | v0 << 16;
    uint32x4 u;
    i_set_splat(u, u0);
    v = u;
#elif SIMDPP_USE_NEON
    v = vdupq_n_u16(v0);
#elif SIMDPP_USE_ALTIVEC
    union {
        uint16_t rv[8];
        uint16x8 align;
    };
    rv[0] = v0;
    v = altivec::load1(v, rv);
    v = splat<0>(v);
#endif
}

#if SIMDPP_USE_AVX2
inline void i_set_splat(uint16x16& v, uint16_t v0)
{
    uint16x8 a = _mm_cvtsi32_si128(v0);
    v = _mm256_broadcastw_epi16(a);
}
#endif

template<unsigned N>
void i_set_splat(uint16<N>& v, uint16_t v0)
{
    uint16v tv;
    i_set_splat(tv, v0);
    for (unsigned i = 0; i < v.vec_length; ++i) {
        v[i] = tv;
    }
}

// -----------------------------------------------------------------------------

inline void i_set_splat(uint32x4& v, uint32_t v0)
{
#if SIMDPP_USE_NULL
    v = null::make_vec<uint32x4>(v0);
#elif SIMDPP_USE_SSE2
    v = _mm_cvtsi32_si128(v0);
    v = permute4<0,0,0,0>(v);
#elif SIMDPP_USE_NEON
    v = vdupq_n_u32(v0);
#elif SIMDPP_USE_ALTIVEC
    union {
        uint32_t rv[4];
        uint32x4 align;
    };
    rv[0] = v0;
    v = altivec::load1(v, rv);
    v = splat<0>(v);
#endif
}

#if SIMDPP_USE_AVX2
inline void i_set_splat(uint32x8& v, uint32_t v0)
{
    uint32x4 a = _mm_cvtsi32_si128(v0);
    v = _mm256_broadcastd_epi32(a);
}
#endif

template<unsigned N>
void i_set_splat(uint32<N>& v, uint32_t v0)
{
    uint32v tv;
    i_set_splat(tv, v0);
    for (unsigned i = 0; i < v.vec_length; ++i) {
        v[i] = tv;
    }
}

// -----------------------------------------------------------------------------

inline void i_set_splat(uint64x2& v, uint64_t v0)
{
#if SIMDPP_USE_NULL
    v = null::make_vec<uint64x2>(v0);
#elif SIMDPP_USE_SSE2
#if SIMDPP_SSE_32_BITS
    uint32x4 va = _mm_cvtsi32_si128(uint32_t(v0));
    uint32x4 vb = _mm_cvtsi32_si128(uint32_t(v0 >> 32));
    v = zip4_lo(va, vb);
    v = permute2<0,0>(v);
#else
    v = _mm_cvtsi64_si128(v0);
    v = permute2<0,0>(v);
#endif
#elif SIMDPP_USE_NEON
    v = vdupq_n_u64(v0);
#elif SIMDPP_USE_ALTIVEC
    union {
        uint64_t rv[2];
        uint64x2 align;
    };
    rv[0] = v0;
    v = load(v, rv);
    v = splat<0>(v);
#endif
}

#if SIMDPP_USE_AVX2
inline void i_set_splat(uint64x4& v, uint64_t v0)
{
    uint64x2 a = _mm_cvtsi64_si128(v0);
    v = _mm256_broadcastq_epi64(a);
}
#endif

template<unsigned N>
void i_set_splat(uint64<N>& v, uint64_t v0)
{
    uint64v tv;
    i_set_splat(tv, v0);
    for (unsigned i = 0; i < v.vec_length; ++i) {
        v[i] = tv;
    }
}

// -----------------------------------------------------------------------------

inline void i_set_splat(float32x4& v, float v0)
{
#if SIMDPP_USE_NULL
    v = null::make_vec<float32x4>(v0);
#elif SIMDPP_USE_SSE2
    v = _mm_set1_ps(v0);        // likely in a SSE register anyway
#elif SIMDPP_USE_NEON
    v = vsetq_lane_f32(v0, v, 0);
    v = splat<0>(v);
#elif SIMDPP_USE_ALTIVEC
    union {
        float rv[4];
        float32x4 align;
    };
    rv[0] = v0;
    v = altivec::load1(v, rv);
    v = splat<0>(v);
#endif
}

#if SIMDPP_USE_AVX2
inline void i_set_splat(float32x8& v, float v0)
{
    v = _mm256_broadcast_ss(&v0);
}
#endif

template<unsigned N>
void i_set_splat(float32<N>& v, float v0)
{
    float32v tv;
    i_set_splat(tv, v0);
    for (unsigned i = 0; i < v.vec_length; ++i) {
        v[i] = tv;
    }
}

// -----------------------------------------------------------------------------

inline void i_set_splat(float64x2& v, double v0)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    v = null::make_vec<float64x2>(v0);
#elif SIMDPP_USE_SSE2
    v = _mm_set1_pd(v0);            // likely in a SSE register anyway
#endif
}

#if SIMDPP_USE_AVX2
inline void i_set_splat(float64x4& v, double v0)
{
    v = _mm256_broadcast_sd(&v0);
}
#endif

template<unsigned N>
void i_set_splat(float64<N>& v, double v0)
{
    float64v tv;
    i_set_splat(tv, v0);
    for (unsigned i = 0; i < v.vec_length; ++i) {
        v[i] = tv;
    }
}

// -----------------------------------------------------------------------------

template<class V>
struct i_set_splat_dispatch
{
    template<class VE>
    static V run(VE v)
    {
        V r;
        i_set_splat(r, static_cast<typename V::element_type>(v));
        return r;
    }
};

template<class VE>
struct i_set_splat_dispatch<expr_vec_set_splat<VE>>
{
    static expr_vec_set_splat<VE> run(VE v)
    {
        expr_vec_set_splat<VE> r;
        r.a = v;
        return r;
    }
};

} // namespace insn

template<class V, class VE>
void construct_eval(V& v, const expr_vec_set_splat<VE>& e)
{
    typename detail::remove_sign<V>::type r;
    insn::i_set_splat(r, e.a);
    v = r;
}

} // namespace detail
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

