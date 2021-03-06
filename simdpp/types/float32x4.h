/*  libsimdpp
    Copyright (C) 2011  Povilas Kanapickas tir5c3@yahoo.co.uk
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

#ifndef LIBSIMDPP_SIMDPP_TYPES_FLOAT32X4_H
#define LIBSIMDPP_SIMDPP_TYPES_FLOAT32X4_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/setup_arch.h>
#include <simdpp/types/fwd.h>
#include <simdpp/types/any.h>
#include <simdpp/types/int32x4.h>
#include <simdpp/core/cast.h>
#include <simdpp/detail/construct_eval.h>
#include <simdpp/detail/array.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/// @defgroup simd_vec_fp Types: floating-point vectors
/// @{

/// Class representing float32x4 vector
template<>
class float32<4, void> : public any_float32<4, float32<4,void>> {
public:
    static const unsigned type_tag = SIMDPP_TAG_FLOAT;
    using base_vector_type = float32<4,void>;
    using expr_type = void;

#if SIMDPP_USE_SSE2
    using native_type = __m128;
#elif SIMDPP_USE_NEON && !SIMDPP_USE_NEON_FLT_SP
    using native_type = float32x4_t;
#elif SIMDPP_USE_ALTIVEC
    using native_type = __vector float;
#else // NULL
    using native_type = detail::array<float, 4>;
#endif

    float32<4>() = default;
    float32<4>(const float32<4> &) = default;
    float32<4> &operator=(const float32<4> &) = default;

    template<class E> float32<4>(const float32<4,E>& d) { *this = d.eval(); }
    template<class V> explicit float32<4>(const any_vec<16,V>& d)
    {
        *this = bit_cast<float32<4>>(d.vec().eval());
    }
    template<class V> float32<4>& operator=(const any_vec<16,V>& d)
    {
        *this = bit_cast<float32<4>>(d.vec().eval()); return *this;
    }

    /// @{
    /// Construct from the underlying vector type
    float32<4>(const native_type& d) : d_(d) {}
    float32<4>& operator=(const native_type& d) { d_ = d; return *this; }
    /// @}

    /// Convert to the underlying vector type
    operator native_type() const { return d_; }

#if SIMDPP_USE_NULL && !DOXYGEN_SHOULD_SKIP_THIS
    float& el(unsigned id) { return d_[id]; }
    const float& el(unsigned id) const { return d_[id]; }
#endif

#ifndef DOXYGEN_SHOULD_SKIP_THIS
    template<class E> float32<4>(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr());
    }
    template<class E> float32<4>& operator=(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr()); return *this;
    }
#endif

    /// @{
    /// Access base vectors
    const float32<4>& operator[](unsigned) const { return *this; }
          float32<4>& operator[](unsigned)       { return *this; }
    /// @}

    float32<4> eval() const { return *this; }

    /** Creates a float32x4 vector with the contents set to zero

        @code
        r0 = 0.0f
        r1 = 0.0f
        r2 = 0.0f
        r3 = 0.0f
        @endcode
    */
    static float32x4 zero();

private:
    native_type d_;
};

/// Class representing possibly optimized mask data for 4x 32-bit floating-point
/// vector
template<>
class mask_float32<4, void> : public any_float32<4, mask_float32<4,void>> {
public:
    static const unsigned type_tag = SIMDPP_TAG_MASK_FLOAT;
    using base_vector_type = mask_float32<4,void>;
    using expr_type = void;

#if SIMDPP_USE_SSE2
    using native_type = __m128;
#elif SIMDPP_USE_NEON && !SIMDPP_USE_NEON_FLT_SP
    using native_type = float32x4_t;
#elif SIMDPP_USE_ALTIVEC
    using native_type = __vector float;
#else // NULL
    using native_type = detail::array<bool, 4>;
#endif
    mask_float32<4>() = default;
    mask_float32<4>(const mask_float32<4> &) = default;
    mask_float32<4> &operator=(const mask_float32<4> &) = default;

    mask_float32<4>(const native_type& d) : d_(d) {}

#if SIMDPP_USE_SSE2
    mask_float32<4>(const float32<4>& d) : d_(d) {}
#endif

    /// Access the underlying type
    float32<4> unmask() const;

#if SIMDPP_USE_NULL && !DOXYGEN_SHOULD_SKIP_THIS
    bool& el(unsigned id) { return d_[id]; }
    const bool& el(unsigned id) const { return d_[id]; }
#endif

    const mask_float32<4>& operator[](unsigned) const { return *this; }
          mask_float32<4>& operator[](unsigned)       { return *this; }

    mask_float32<4> eval() const { return *this; }

private:
    native_type d_;
};

/// @} -- end defgroup

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
