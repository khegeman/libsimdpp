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

#ifndef LIBSIMDPP_SIMDPP_TYPES_FLOAT64X2_H
#define LIBSIMDPP_SIMDPP_TYPES_FLOAT64X2_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/setup_arch.h>
#include <simdpp/types/fwd.h>
#include <simdpp/types/any.h>
#include <simdpp/types/int64x2.h>
#include <simdpp/core/cast.h>
#include <simdpp/detail/construct_eval.h>
#include <simdpp/detail/array.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/// @ingroup simd_vec_fp
/// @{

/// Class representing float64x2 vector
template<>
class float64<2, void> : public any_float64<2, float64<2,void>> {
public:
    static const unsigned type_tag = SIMDPP_TAG_FLOAT;
    using element_type = double;
    using base_vector_type = float64<2,void>;
    using expr_type = void;

#if SIMDPP_USE_SSE2
    using native_type = __m128d;
#else
    using native_type = detail::array<double, 2>;
#endif

    float64<2>() = default;
    float64<2>(const float64<2> &) = default;
    float64<2> &operator=(const float64<2> &) = default;

    template<class E> float64<2>(const float64<2,E>& d) { *this = d.eval(); }
    template<class V> explicit float64<2>(const any_vec<16,V>& d)
    {
        *this = bit_cast<float64<2>>(d.vec().eval());
    }
    template<class V> float64<2>& operator=(const any_vec<16,V>& d)
    {
        *this = bit_cast<float64<2>>(d.vec().eval()); return *this;
    }

    /// @{
    /// Construct from the underlying vector type
    float64<2>(const native_type& d) : d_(d) {}
    float64<2>& operator=(const native_type& d) { d_ = d; return *this; }
    /// @}

    /// Convert to the underlying vector type
    operator native_type() const { return d_; }

#ifndef DOXYGEN_SHOULD_SKIP_THIS
    template<class E> float64<2>(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr());
    }
    template<class E> float64<2>& operator=(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr()); return *this;
    }
#endif

    /// @{
    /// Access base vectors
    const float64x2& operator[](unsigned) const { return *this; }
          float64x2& operator[](unsigned)       { return *this; }
    /// @}

    float64<2> eval() const { return *this; }

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    /// For internal use only
    const double& el(unsigned i) const { return d_[i]; }
          double& el(unsigned i)       { return d_[i]; }
#endif
#endif

    /** Creates a float64x2 vector with the contens set to zero

        @code
        r0 = 0.0
        r1 = 0.0
        @endcode
    */
    static float64x2 zero();

private:
    native_type d_;
};


/// Class representing possibly optimized mask data for 2x 64-bit floating point
/// vector
template<>
class mask_float64<2, void> : public any_float64<2, mask_float64<2,void>> {
public:
    static const unsigned type_tag = SIMDPP_TAG_MASK_FLOAT;
    using base_vector_type = mask_float64<2,void>;
    using expr_type = void;

#if SIMDPP_USE_SSE2
    using native_type = __m128d;
#else // NULL, NEON, ALTIVEC
    using native_type = detail::array<bool, 2>;
#endif

    mask_float64<2>() = default;
    mask_float64<2>(const mask_float64<2> &) = default;
    mask_float64<2> &operator=(const mask_float64<2> &) = default;

    mask_float64<2>(const native_type& d) : d_(d) {}

    /// Access the underlying type
    float64<2> unmask() const;

#if !SIMDPP_USE_SSE2 && !DOXYGEN_SHOULD_SKIP_THIS
    bool& el(unsigned id) { return d_[id]; }
    const bool& el(unsigned id) const { return d_[id]; }
#endif

    const mask_float64<2>& operator[](unsigned) const { return *this; }
          mask_float64<2>& operator[](unsigned)       { return *this; }

    mask_float64<2> eval() const { return *this; }

private:
    native_type d_;
};
/// @} -- end ingroup

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
