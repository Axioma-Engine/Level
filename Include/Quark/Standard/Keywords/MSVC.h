#ifndef ATOM_QRK_STANDARD_KEYWORDS_MSVC_H
#define ATOM_QRK_STANDARD_KEYWORDS_MSVC_H

/**
 * @file MSVC.h
 * @brief MSVC-specific implementations of C++ keyword shims.
 *
 * Implements alignment, nullptr, noexcept and other language shims using
 * MSVC-compatible constructs when standard keywords are not available.
 */

#include "../../System/Cpp.h" // IWYU pragma: keep
#include "../../Utils.h"

#if ATOM_HAS_CXX11
#    define ATOM_ALIGNAS(x) alignas(x)
#    define ATOM_ALIGNOF(x) alignof(x)
#else
#    define ATOM_ALIGNAS(x) __declspec(align(x))
#    define ATOM_ALIGNOF(x) __alignof(x)
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
#    define ATOM_NOEXCEPT(x) __declspec(nothrow) x
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
#    define ATOM_THREAD_LOCAL __declspec(thread)
#endif

#if ATOM_HAS_CXX20
#    define ATOM_CONSTEVAL consteval
#else
#    define ATOM_CONSTEVAL ATOM_CONSTEXPR
#endif

#if defined(ATOM_STATIC_BUILD)
#    define ATOM_EXPORT
#elif defined(ATOM_SHARED_BUILD)
#    define ATOM_EXPORT __declspec(dllexport)
#else
#    define ATOM_EXPORT __declspec(dllimport)
#endif

#endif
