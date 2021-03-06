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

#ifndef LIBSIMDPP_SIMDPP_TYPES_INT16X8_H
#define LIBSIMDPP_SIMDPP_TYPES_INT16X8_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/setup_arch.h>
#include <simdpp/types/fwd.h>
#include <simdpp/types/any.h>
#include <simdpp/core/cast.h>
#include <simdpp/detail/construct_eval.h>
#include <simdpp/detail/array.h>
#include <cstdint>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/// @ingroup simd_vec_int
/// @{

/** Class representing 8x 16-bit signed integer vector
*/
template<>
class int16<8, void> : public any_int16<8, int16<8,void>> {
public:
    static const unsigned type_tag = SIMDPP_TAG_INT;
    using element_type = int16_t;
    using base_vector_type = int16<8>;
    using expr_type = void;

#if SIMDPP_USE_SSE2
    using native_type = __m128i;
#elif SIMDPP_USE_NEON
    using native_type = int16x8_t;
#elif SIMDPP_USE_ALTIVEC
    using native_type = __vector int16_t;
#else
    using native_type = detail::array<int16_t, 8>;
#endif

    int16<8>() = default;
    int16<8>(const int16<8> &) = default;
    int16<8> &operator=(const int16<8> &) = default;

    template<class E> int16<8>(const int16<8,E>& d) { *this = d.eval(); }
    template<class E> int16<8>(const uint16<8,E>& d) { *this = d.eval(); }
    template<class V> explicit int16<8>(const any_vec<16,V>& d)
    {
        *this = bit_cast<int16<8>>(d.vec().eval());
    }
    template<class V> int16<8>& operator=(const any_vec<16,V>& d)
    {
        *this = bit_cast<int16<8>>(d.vec().eval()); return *this;
    }

    /// @{
    /// Construct from the underlying vector type
    int16<8>(const native_type& d) : d_(d) {}
    int16<8>& operator=(const native_type& d) { d_ = d; return *this; }
    /// @}

    /// Convert to the underlying vector type
    operator native_type() const { return d_; }

#ifndef DOXYGEN_SHOULD_SKIP_THIS
    template<class E> int16<8>(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr());
    }
    template<class E> int16<8>& operator=(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr()); return *this;
    }
#endif

    /// @{
    /// Access base vectors
    const int16<8>& operator[](unsigned) const { return *this; }
          int16<8>& operator[](unsigned)       { return *this; }
    /// @}

    int16<8> eval() const { return *this; }

#if SIMDPP_USE_NULL && !DOXYGEN_SHOULD_SKIP_THIS
    /// For internal use only
    const int16_t& el(unsigned i) const  { return d_[i]; }
          int16_t& el(unsigned i)        { return d_[i]; }
#endif

    static int16<8> zero();
    static int16<8> ones();

private:
    native_type d_;
};

/** Class representing 8x 16-bit unsigned integer vector
*/
template<>
class uint16<8, void> : public any_int16<8, uint16<8,void>> {
public:
    static const unsigned type_tag = SIMDPP_TAG_UINT;
    using element_type = uint16_t;
    using base_vector_type = uint16<8,void>;
    using expr_type = void;

#if SIMDPP_USE_SSE2
    using native_type = __m128i;
#elif SIMDPP_USE_NEON
    using native_type = uint16x8_t;
#elif SIMDPP_USE_ALTIVEC
    using native_type = __vector uint16_t;
#else
    using native_type = detail::array<uint16_t, 8>;
#endif

    uint16<8>() = default;
    uint16<8>(const uint16<8> &) = default;
    uint16<8> &operator=(const uint16<8> &) = default;

    template<class E> uint16<8>(const uint16<8,E>& d) { *this = d.eval(); }
    template<class E> uint16<8>(const int16<8,E>& d) { *this = d.eval(); }
    template<class V> explicit uint16<8>(const any_vec<16,V>& d)
    {
        *this = bit_cast<uint16<8>>(d.vec().eval());
    }
    template<class V> uint16<8>& operator=(const any_vec<16,V>& d)
    {
        *this = bit_cast<uint16<8>>(d.vec().eval()); return *this;
    }

    /// @{
    /// Construct from the underlying vector type
    uint16<8>(const native_type& d) : d_(d) {}
    uint16<8>& operator=(const native_type& d) { d_ = d; return *this; }
    /// @}

    /// Convert to the underlying vector type
    operator native_type() const { return d_; }

#ifndef DOXYGEN_SHOULD_SKIP_THIS
    template<class E> uint16<8>(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr());
    }
    template<class E> uint16<8>& operator=(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr()); return *this;
    }
#endif

    /// @{
    /// Access base vectors
    const uint16<8>& operator[](unsigned) const { return *this; }
          uint16<8>& operator[](unsigned)       { return *this; }
    /// @}

    uint16<8> eval() const { return *this; }

#if SIMDPP_USE_NULL && !DOXYGEN_SHOULD_SKIP_THIS
    /// For uinternal use only
    const uint16_t& el(unsigned i) const  { return d_[i]; }
          uint16_t& el(unsigned i)        { return d_[i]; }
#endif

    static uint16<8> zero();
    static uint16<8> ones();

private:
    native_type d_;
};

/// Class representing possibly optimized mask data for 8x 16-bit integer
/// vector
template<>
class mask_int16<8, void> : public any_int16<8, mask_int16<8,void>> {
public:
    static const unsigned type_tag = SIMDPP_TAG_MASK_INT;
    using base_vector_type = mask_int16<8, void>;
    using expr_type = void;

#if SIMDPP_USE_SSE2
    using native_type = __m128i;
#elif SIMDPP_USE_NEON
    using native_type = uint16x8_t;
#elif SIMDPP_USE_ALTIVEC
    using native_type = __vector uint16_t;
#else
    using native_type = detail::array<bool, 8>;
#endif

    mask_int16<8>() = default;
    mask_int16<8>(const mask_int16<8> &) = default;
    mask_int16<8> &operator=(const mask_int16<8> &) = default;

    mask_int16<8>(const native_type& d) : d_(d) {}

    /// Access the underlying type
    uint16<8> unmask() const;

#if SIMDPP_USE_NULL && !DOXYGEN_SHOULD_SKIP_THIS
    bool& el(unsigned id) { return d_[id]; }
    const bool& el(unsigned id) const { return d_[id]; }
#endif

    const mask_int16<8>& operator[](unsigned) const { return *this; }
          mask_int16<8>& operator[](unsigned)       { return *this; }

    mask_int16<8> eval() const { return *this; }

private:
    native_type d_;
};

/// @} -- end ingroup

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
