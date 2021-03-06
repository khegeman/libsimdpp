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

#ifndef LIBSIMDPP_SIMDPP_CORE_ALIGN_H
#define LIBSIMDPP_SIMDPP_CORE_ALIGN_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/insn/align.h>
#include <simdpp/detail/get_expr.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif


/** Extracts a int8x16 vector from two concatenated int8x16 vectors

    @code
    shift:  pos:| 0   1    .  14  15  |
     0      r = [ l0  l1   .  l14 l15 ]
     1      r = [ l1  l2   .  l15 u0  ]
     2      r = [ l2  l3   .  u0  l1  ]
      ...    ..   .. ..  ... .. ..
     15     r = [ l15 u0   .  u13 u14 ]
     16     r = [ u0  u1   .  u14 u15 ]
    @endcode

    @par 128-bit version:
    @icost{SSE2-SSE3, 3}

    @par 256-bit version:
    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{SSE2-SSE3, 6}
    @icost{SSSE3-AVX, NEON, ALTIVEC, 2}
*/
template<unsigned shift, unsigned N, class V1, class V2>
typename detail::get_expr2_nomask<V1, V2, void>::empty
    align16(const any_vec8<N,V1>& lower,
            const any_vec8<N,V2>& upper)
{
    static_assert(shift <= 16, "Shift out of bounds");
    if (shift == 0) return lower.vec().eval();
    if (shift == 16) return upper.vec().eval();

    typename detail::get_expr2_nomask_nosign<V1, V2, void>::type qlower, qupper;
    qlower = lower.vec().eval();
    qupper = upper.vec().eval();
    return detail::insn::i_align16<shift>(qlower, qupper);
}

/** Extracts a int16x8 vector from two concatenated int16x8 vectors

    @code
    shift:  pos:| 0  1    .  6  7  |
     0      r = [ l0 l1   .  l6 l7 ]
     1      r = [ l1 l2   .  l7 u0 ]
     2      r = [ l2 l3   .  u0 l1 ]
      ...    ..   .. ..  ... .. ..
     7      r = [ l3 u0   .  u5 u6 ]
     8      r = [ u0 u1   .  u6 u7 ]
    @endcode

    @par 128-bit version:
    @icost{SSE2-SSE3, 3}

    @par 256-bit version:
    @icost{SSE2-SSE3, 6}
    @icost{SSSE3-AVX, NEON, ALTIVEC, 2}

    The all 128-bit sub-vectors are processed as if 128-bit instruction
    was applied to each of them separately.

*/
template<unsigned shift, unsigned N, class V1, class V2>
typename detail::get_expr2_nomask<V1, V2, void>::empty
    align8(const any_vec16<N,V1>& lower,
           const any_vec16<N,V2>& upper)
{
    static_assert(shift <= 8, "Shift out of bounds");
    if (shift == 0) return lower.vec().eval();
    if (shift == 8) return upper.vec().eval();

    typename detail::get_expr2_nomask_nosign<V1, V2, void>::type qlower, qupper;
    qlower = lower.vec().eval();
    qupper = upper.vec().eval();
    return detail::insn::i_align8<shift>(qlower, qupper);
}

/** Extracts a int32x4 vector from two concatenated int32x4 vectors

    @code
    shift:  pos:| 0  1  2  3  |
     0      r = [ l0 l1 l2 l3 ]
     1      r = [ l1 l2 l3 u0 ]
     2      r = [ l2 l3 u0 u1 ]
     3      r = [ l3 u0 u1 u2 ]
     4      r = [ u0 u1 u2 u3 ]
    @endcode

    @par int32

    @par 128-bit version:
    @icost{SSE2-SSE3, 3}

    @par 256-bit version:
    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{SSE2-SSE3, 6}
    @icost{SSSE3-AVX, NEON, ALTIVEC, 2}

    @par float32

    @par 128-bit version:
    @icost{SSE2-SSE3, 3}

    @par 256-bit version:
    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{SSE2-SSE3, 6}
    @icost{SSSE3-SSE4.1 NEON, ALTIVEC, 2}
*/
template<unsigned shift, unsigned N, class V1, class V2>
typename detail::get_expr2_nomask<V1, V2, void>::empty
    align4(const any_vec32<N,V1>& lower,
           const any_vec32<N,V2>& upper)
{
    static_assert(shift <= 4, "Shift out of bounds");
    if (shift == 0) return lower.vec().eval();
    if (shift == 4) return upper.vec().eval();

    typename detail::get_expr2_nomask_nosign<V1, V2, void>::type qlower, qupper;
    qlower = lower.vec().eval();
    qupper = upper.vec().eval();
    return detail::insn::i_align4<shift>(qlower, qupper);
}

/** Extracts a int64x2 vector from two concatenated int64x2 vectors

    @code
    shift:  pos:| 0  1  |
     0      r = [ l0 l1 ]
     1      r = [ l1 u0 ]
     2      r = [ u0 u1 ]
    @endcode

    @par int64

    @par 128-bit version:
    @icost{SSE2-SSE3, 3}

    @par 256-bit version:
    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{SSE2-SSE3, 6}
    @icost{SSSE3-AVX, NEON, ALTIVEC, 2}

    @par float64

    @par 128-bit version:
    @icost{SSE2-SSE3, 3}

    @par 256-bit version:
    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{SSE2-SSE3, 6}
    @icost{SSSE3-SSE4.1 NEON, ALTIVEC, 2}
*/
template<unsigned shift, unsigned N, class V1, class V2>
typename detail::get_expr2_nomask<V1, V2, void>::empty
    align2(const any_vec64<N,V1>& lower,
           const any_vec64<N,V2>& upper)
{
    static_assert(shift <= 2, "Shift out of bounds");
    if (shift == 0) return lower.vec().eval();
    if (shift == 2) return upper.vec().eval();

    typename detail::get_expr2_nomask_nosign<V1, V2, void>::type qlower, qupper;
    qlower = lower.vec().eval();
    qupper = upper.vec().eval();
    return detail::insn::i_align2<shift>(qlower, qupper);
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

