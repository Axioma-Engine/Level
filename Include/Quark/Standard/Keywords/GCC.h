#ifndef ATOM_QRK_STANDARD_KEYWORDS_GCC_H
#define ATOM_QRK_STANDARD_KEYWORDS_GCC_H

/**
 * @file GCC.h
 * @brief GCC/Clang-specific implementations of C++ keyword shims.
 *
 * Maps standard keywords and language features to GCC/Clang-compatible
 * equivalents or attributes when available.
 */

#include "../../Features.h"
#include "../../System/Cpp.h" // IWYU pragma: keep
#include "../../Utils.h"

#if ATOM_HAS_CXX11
#    define ATOM_ALIGNAS(x) alignas(x)
#    define ATOM_ALIGNOF(x) alignof(x)
#elif ATOM_HAS_ATTRIBUTE(aligned)
#    define ATOM_ALIGNAS(x) __attribute__((aligned(x)))
#    define ATOM_ALIGNOF(x) __alignof__(x)
#else
#    include <stddef.h>
#    define ATOM_ALIGNAS(x)
#    define ATOM_ALIGNOF(T)                                                                        \
        (offsetof(                                                                                 \
            struct {                                                                               \
                char c;                                                                            \
                T    member;                                                                       \
            },                                                                                     \
            member))
#endif

#if ATOM_HAS_CXX11
#    define ATOM_CONSTEXPR constexpr
#else
#    define ATOM_CONSTEXPR
#endif

#if ATOM_HAS_CXX17
#    define ATOM_CONSTEXPR17 constexpr
#else
#    define ATOM_CONSTEXPR17
#endif

#if ATOM_HAS_CXX11
#    define ATOM_NOEXCEPT(x) x noexcept
#elif ATOM_HAS_ATTRIBUTE(nothrow)
#    define ATOM_NOEXCEPT(x) __attribute__((nothrow)) x
#else
#    define ATOM_NOEXCEPT(x) x
#endif

#if ATOM_HAS_CXX11
#    define ATOM_NULLPTR nullptr
#else
namespace Quark {
    class Nullptr {
      public:
        template <class T>
        operator T*() const {
            return 0;
        }

        template <class C, class T>
        operator T C::*() const {
            return 0;
        }

      private:
        void operator&() const;
    };
    const Nullptr NULLPTR = {};
}
#    define ATOM_NULLPTR NULLPTR
#endif

#if ATOM_HAS_CXX11
#    define ATOM_STATIC_ASSERT(expr, msg) static_assert(expr, msg)
#else
template <bool B>
struct AtomStaticAssert;
template <>
struct AtomStaticAssert<true> {};
#    define ATOM_STATIC_ASSERT(expr, msg) AtomStaticAssert<expr> ATOM_UNIQUE_NAME(Success);
#endif

#if ATOM_HAS_CXX11
#    define ATOM_THREAD_LOCAL thread_local
#else
#    define ATOM_THREAD_LOCAL __thread
#endif

#if ATOM_HAS_CXX20
#    define ATOM_CONSTEVAL consteval
#else
#    define ATOM_CONSTEVAL ATOM_CONSTEXPR
#endif

#if defined(ATOM_STATIC_BUILD)
#    define ATOM_EXPORT
#elif defined(ATOM_SHARED_BUILD)
#    define ATOM_EXPORT __attribute__((visibility("default")))
#else
#    define ATOM_EXPORT __attribute__((visibility("default")))
#endif

#endif

