 /*  libsimdpp
    Copyright (C) 2013  Povilas Kanapickas tir5c3@yahoo.co.uk
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

#ifndef LIBSIMDPP_CORE_ALIGNED_ALLOCATOR_H
#define LIBSIMDPP_CORE_ALIGNED_ALLOCATOR_H

#include <memory>
#include <cstddef>
#include <cstdint>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/** An allocator that allocates memory with stricter alignment requirements than
    the defaults. @a A must be a power of two.
*/
template<class T, std::size_t A>
class aligned_allocator {
private:

    static_assert(!(A & (A - 1)), "A is not a power of two");

public:
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;

    aligned_allocator() = default;
    aligned_allocator(const aligned_allocator&) = default;

    template<class U>
    aligned_allocator(const aligned_allocator<U,A>&) {}

    ~aligned_allocator() = default;

    aligned_allocator& operator=(const aligned_allocator&) = delete;

    template<class U>
    struct rebind {
        using other = aligned_allocator<U,A>;
    };

    T* address(T& x) const
    {
        return &x;
    }

    std::size_t max_size() const
    {
        return (static_cast<std::size_t>(0) - static_cast<std::size_t>(1)) / sizeof(T);
    }

    // stateless
    bool operator!=(const aligned_allocator& other) const { return false; }
    bool operator==(const aligned_allocator& other) const { return true; }

    void construct(T* p, const T& t) const
    {
        void* pv = static_cast<void*>(p);
        new (pv) T(t);
    }

    void destroy(T* p) const
    {
        p->~T();
    }

    T* allocate(std::size_t n) const
    {
        if (n == 0) {
            return nullptr;
        }

        if (n > max_size()) {
            throw std::length_error("aligned_allocator<T,A>::allocate() - Integer overflow.");
        }


        /* We align the storage by adding @a alignment bytes and truncating the
            pointer. The pointer to the original location returned by @a new is
            stored just before the location the returned pointer refers to.
            To ensure that there is always at least @a sizeof(void*) space
            there, @a alignment is at least 2*sizoef(void*)
        */
        std::size_t al = A < 2*sizeof(void*) ? 2*sizeof(void*) : A;

        char* pv = new char[n*sizeof(T) + al];
        std::uintptr_t upv = reinterpret_cast<std::uintptr_t>(pv);
        upv = (upv + al) & ~(al - 1);
        char** aligned_pv = reinterpret_cast<char**>(upv);

        *(aligned_pv-1) = pv; // original pointer

        return reinterpret_cast<T*>(aligned_pv);
    }

    void deallocate(T* p, std::size_t n) const
    {
        (void) n;
        if (!p) {
            return;
        }
        char** pptr = reinterpret_cast<char**>(p);
        delete[](*(pptr - 1));
    }

    template<class U>
    T * allocate(std::size_t n, const U* hint) const
    {
        (void) hint;
        return allocate(n);
    }
};

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
