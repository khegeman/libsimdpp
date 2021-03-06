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

#ifndef LIBSIMDPP_SIMDPP_CORE_LOAD_PACKED4_H
#define LIBSIMDPP_SIMDPP_CORE_LOAD_PACKED4_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/insn/load_packed4.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif


/** Loads values packed in quartets, de-interleaves them and stores the result
    into four vectors.

    @code
    a = [ *(p),   *(p+4), *(p+8),  ... , *(p+M*4-4) ]
    b = [ *(p+1), *(p+5), *(p+9),  ... , *(p+M*4-3) ]
    c = [ *(p+2), *(p+6), *(p+10), ... , *(p+M*4-2) ]
    d = [ *(p+3), *(p+7), *(p+11), ... , *(p+M*4-1) ]
    @endcode

    Here M is the number of elements in the vector

    @a p must be aligned to the vector size in bytes
*/
template<unsigned N, class V>
void load_packed4(any_vec<N,V>& a, any_vec<N,V>& b,
                  any_vec<N,V>& c, any_vec<N,V>& d,
                  const void* p)
{
    static_assert(!is_mask<V>::value, "Mask types can not be loaded");
    typename detail::get_expr_nosign<V,void>::type ra, rb, rc, rd;
    detail::insn::i_load_packed4(ra, rb, rc, rd, reinterpret_cast<const char*>(p));
    a.vec() = ra;
    b.vec() = rb;
    c.vec() = rc;
    d.vec() = rd;
}


#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

