/*  libsimdpp
    Copyright (C) 2012-2012  Povilas Kanapickas tir5c3@yahoo.co.uk
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

#ifndef LIBSIMDPP_SIMDPP_TYPES_INT32X8_INL
#define LIBSIMDPP_SIMDPP_TYPES_INT32X8_INL

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types/int32x8.h>
#include <simdpp/types/float32x8.h>
#include <simdpp/null/mask.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

#if SIMDPP_USE_AVX2

inline uint32<8>::uint32(const uint8x32& d) { *this = bit_cast<uint32x8>(d); }
inline uint32<8>::uint32(const uint16x16& d){ *this = bit_cast<uint32x8>(d); }
inline uint32<8>::uint32(const uint64x4& d) { *this = bit_cast<uint32x8>(d); }
inline uint32<8>& uint32<8>::operator=(const uint8x32& d) { *this = bit_cast<uint32x8>(d); return *this; }
inline uint32<8>& uint32<8>::operator=(const uint16x16& d){ *this = bit_cast<uint32x8>(d); return *this; }
inline uint32<8>& uint32<8>::operator=(const uint64x4& d) { *this = bit_cast<uint32x8>(d); return *this; }

inline int32<8>::int32(const uint8x32& d) : uint32x8(bit_cast<uint32x8>(d)) {}
inline int32<8>::int32(const uint16x16& d): uint32x8(bit_cast<uint32x8>(d)) {}
inline int32<8>::int32(const uint32x8& d) : uint32x8(d) {}
inline int32<8>::int32(const uint64x4& d) : uint32x8(bit_cast<uint32x8>(d)) {}
inline int32<8>& int32<8>::operator=(const uint8x32& d) { uint32x8::operator=(d); return *this; }
inline int32<8>& int32<8>::operator=(const uint16x16& d){ uint32x8::operator=(d); return *this; }
inline int32<8>& int32<8>::operator=(const uint32x8& d) { uint32x8::operator=(d); return *this; }
inline int32<8>& int32<8>::operator=(const uint64x4& d) { uint32x8::operator=(d); return *this; }

inline uint32<8>::uint32(const uint8x32& d) : uint32x8(bit_cast<uint32x8>(d)) {}
inline uint32<8>::uint32(const uint16x16& d): uint32x8(bit_cast<uint32x8>(d)) {}
inline uint32<8>::uint32(const uint32x8& d) : uint32x8(d) {}
inline uint32<8>::uint32(const uint64x4& d) : uint32x8(bit_cast<uint32x8>(d)) {}
inline uint32<8>& uint32<8>::operator=(const uint8x32& d) { uint32x8::operator=(d); return *this; }
inline uint32<8>& uint32<8>::operator=(const uint16x16& d){ uint32x8::operator=(d); return *this; }
inline uint32<8>& uint32<8>::operator=(const uint32x8& d) { uint32x8::operator=(d); return *this; }
inline uint32<8>& uint32<8>::operator=(const uint64x4& d) { uint32x8::operator=(d); return *this; }

inline uint32<8>::uint32(const float32x8& d)
{
    *this = bit_cast<uint32x8>(d);
}

inline uint32x8 uint32x8::zero()
{
    return (uint32<8>) make_uint(0);
}

inline uint32x8 uint32x8::ones()
{
    return (uint32<8>) make_uint(0xffffffff);
}

inline mask_int32x8::operator uint32x8() const
{
    return d_;
}

#endif // SIMDPP_USE_AVX2

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
