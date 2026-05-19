#ifndef ATOM_QRK_STANDARD_ATTRIBUTES_GCC_H
#define ATOM_QRK_STANDARD_ATTRIBUTES_GCC_H

/**
 * @file GCC.h
 * @brief Standard attribute mappings for GCC/Clang compilers.
 *
 * Exposes `[[...]]` attribute fallbacks and maps them to `__attribute__`
 * equivalents when appropriate. Provides unified macros like `ATOM_NORETURN`,
 * `ATOM_DEPRECATED`, `ATOM_FALLTHROUGH` and more.
 */

#include "../../Features.h"
#include "../../System/Cpp.h" // IWYU pragma: keep

#if ATOM_HAS_CPP_ATTRIBUTE(noreturn)
#    define ATOM_NORETURN [[noreturn]]
#elif ATOM_HAS_ATTRIBUTE(noreturn)
#    define ATOM_NORETURN __attribute__((noreturn))
#else
#    define ATOM_NORETURN
#endif

#if ATOM_HAS_CPP_ATTRIBUTE(carries_dependency)
#    define ATOM_CARRIES_DEPENDENCY [[carries_dependency]]
#elif ATOM_HAS_ATTRIBUTE(carries_dependency)
#    define ATOM_CARRIES_DEPENDENCY __attribute__((carries_dependency))
#else
#    define ATOM_CARRIES_DEPENDENCY
#endif

#if ATOM_HAS_CPP_ATTRIBUTE(deprecated)
#    define ATOM_DEPRECATED [[deprecated]]
#    if ATOM_HAS_CXX17
#        define ATOM_DEPRECATED_MSG(msg) [[deprecated(msg)]]
#    elif ATOM_HAS_ATTRIBUTE(deprecated)
#        define ATOM_DEPRECATED_MSG(msg) __attribute__((deprecated(msg)))
#    else
#        define ATOM_DEPRECATED_MSG(msg) [[deprecated]]
#    endif
#elif ATOM_HAS_ATTRIBUTE(deprecated)
#    define ATOM_DEPRECATED          __attribute__((deprecated))
#    define ATOM_DEPRECATED_MSG(msg) __attribute__((deprecated(msg)))
#else
#    define ATOM_DEPRECATED
#    define ATOM_DEPRECATED_MSG(msg)
#endif

#if ATOM_HAS_CPP_ATTRIBUTE(fallthrough)
#    define ATOM_FALLTHROUGH [[fallthrough]]
#elif ATOM_HAS_ATTRIBUTE(fallthrough)
#    define ATOM_FALLTHROUGH __attribute__((fallthrough))
#else
#    define ATOM_FALLTHROUGH
#endif

#if ATOM_HAS_CPP_ATTRIBUTE(maybe_unused)
#    define ATOM_MAYBE_UNUSED [[maybe_unused]]
#elif ATOM_HAS_ATTRIBUTE(unused)
#    define ATOM_MAYBE_UNUSED __attribute__((unused))
#else
#    define ATOM_MAYBE_UNUSED
#endif

#if ATOM_HAS_CPP_ATTRIBUTE(nodiscard)
#    define ATOM_NODISCARD [[nodiscard]]
#    if ATOM_HAS_CXX20
#        define ATOM_NODISCARD_MSG(msg) [[nodiscard(msg)]]
#    else
#        define ATOM_NODISCARD_MSG(msg) [[nodiscard]]
#    endif
#elif ATOM_HAS_ATTRIBUTE(warn_unused_result)
#    define ATOM_NODISCARD          __attribute__((warn_unused_result))
#    define ATOM_NODISCARD_MSG(msg) __attribute__((warn_unused_result))
#else
#    define ATOM_NODISCARD
#    define ATOM_NODISCARD_MSG(msg)
#endif

#if ATOM_HAS_CPP_ATTRIBUTE(likely)
#    define ATOM_LIKELY(x) (x) [[likely]]
#elif ATOM_HAS_BUILTIN(expect)
#    define ATOM_LIKELY(x) (__builtin_expect(!!(x), 1))
#else
#    define ATOM_LIKELY(x) (x)
#endif

#if ATOM_HAS_CPP_ATTRIBUTE(unlikely)
#    define ATOM_UNLIKELY(x) (x) [[unlikely]]
#elif ATOM_HAS_BUILTIN(expect)
#    define ATOM_UNLIKELY(x) (__builtin_expect(!!(x), 0))
#else
#    define ATOM_UNLIKELY(x) (x)
#endif

#if ATOM_HAS_CPP_ATTRIBUTE(no_unique_address)
#    define ATOM_NO_UNIQUE_ADDRESS [[no_unique_address]]
#else
#    define ATOM_NO_UNIQUE_ADDRESS
#endif

#if ATOM_HAS_CPP_ATTRIBUTE(assume)
#    define ATOM_ASSUME(x) [[assume(x)]]
#elif ATOM_HAS_BUILTIN(assume)
#    define ATOM_ASSUME(x) __builtin_assume(x)
#elif ATOM_HAS_BUILTIN(unreachable)
#    define ATOM_ASSUME(x)                                                                         \
        do {                                                                                       \
            if (!(x)) __builtin_unreachable();                                                     \
        } while (0)
#else
#    define ATOM_ASSUME(x)
#endif

#endif
