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

#ifndef LIBSIMDPP_SIMDPP_TYPES_FLOAT64_H
#define LIBSIMDPP_SIMDPP_TYPES_FLOAT64_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/setup_arch.h>
#include <simdpp/types/fwd.h>
#include <simdpp/types/any.h>
#include <simdpp/core/cast.h>
#include <simdpp/types/float64x2.h>
#include <simdpp/types/float64x4.h>
#include <simdpp/detail/construct_eval.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/// @ingroup simd_vec_fp
/// @{

/** Class representing a @a float64 vector of arbitrary length. The vector
    always contains at least one native vector.
*/
template<unsigned N>
class float64<N, void> : public any_float64<N, float64<N,void>> {
public:
    static const unsigned type_tag = SIMDPP_TAG_FLOAT;
    using element_type = double;
    using base_vector_type = float64v;
    using expr_type = void;

    float64<N>() = default;
    float64<N>(const float64<N>&) = default;
    float64<N>& operator=(const float64<N>&) = default;

    template<class E> float64<N>(const float64<N,E>& d) { *this = d.eval(); }
    template<class V> explicit float64<N>(const any_vec<N*8,V>& d)
    {
        *this = bit_cast<float64<N>>(d.vec().eval());
    }
    template<class V> float64<N>& operator=(const any_vec<N*8,V>& d)
    {
        *this = bit_cast<float64<N>>(d.vec().eval()); return *this;
    }

#ifndef DOXYGEN_SHOULD_SKIP_THIS
    template<class E> float64<N>(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr());
    }
    template<class E> float64<N>& operator=(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr()); return *this;
    }
#endif

    const float64v& operator[](unsigned i) const { return d_[i]; }
    float64v& operator[](unsigned i)             { return d_[i]; }

    float64<N> eval() const { return *this; }

    /** Creates a float64 vector with the contents set to zero

        @code
        r0 = 0.0f
        ...
        rN = 0.0f
        @endcode
    */
    static float64<N> zero()
    {
        return set_vec(float64v::zero());
    }

private:
    /** Creates a float vector from a native vector

        @code
        r0 = v0
        ...
        rN = v0
        @endcode
    */
    static float64<N> set_vec(float64v v0)
    {
        float64<N> r;
        for (unsigned i = 0; i < r.vec_length; i++) r[i] = v0;
        return r;
    }

    float64v d_[float64::vec_length];
};

/// Class representing possibly optimized mask data for 2x 64-bit floating point
/// vector
template<unsigned N>
class mask_float64<N, void> : public any_float64<N, mask_float64<N,void>> {
public:
    static const unsigned type_tag = SIMDPP_TAG_MASK_FLOAT;
    using base_vector_type = mask_float64v;
    using expr_type = void;

    mask_float64<N>() = default;
    mask_float64<N>(const mask_float64<N> &) = default;
    mask_float64<N> &operator=(const mask_float64<N> &) = default;

    /// Access the underlying type
    float64<N> unmask() const
    {
        float64<N> r;
        for (unsigned i = 0; i < mask_float64::vec_length; ++i) {
            r[i] = d_[i].unmask();
        }
        return r;
    }

    const mask_float64v& operator[](unsigned i) const { return d_[i]; }
          mask_float64v& operator[](unsigned i)       { return d_[i]; }

    mask_float64<N> eval() const { return *this; }

private:
    mask_float64v d_[mask_float64::vec_length];
};

/// @} -- end ingroup

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
