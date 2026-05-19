#ifndef ATOM_QRK_STANDARD_KEYWORDS_UNKNOWN_H
#define ATOM_QRK_STANDARD_KEYWORDS_UNKNOWN_H

/**
 * @file Unknown.h
 * @brief Portable fallbacks for C++ keyword shims on unknown compilers.
 *
 * Provides alternatives for alignment, constexpr, noexcept, nullptr and
 * static_assert when the compiler does not expose standard language support.
 */

#include "../../System/Cpp.h" // IWYU pragma: keep
#include "../../Utils.h"

#if ATOM_HAS_CXX11
#    define ATOM_ALIGNAS(x) alignas(x)
#    define ATOM_ALIGNOF(x) alignof(x)
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
#    define ATOM_THREAD_LOCAL
#endif

#if ATOM_HAS_CXX20
#    define ATOM_CONSTEVAL consteval
#else
#    define ATOM_CONSTEVAL ATOM_CONSTEXPR
#endif

#define ATOM_EXPORT

#endif
