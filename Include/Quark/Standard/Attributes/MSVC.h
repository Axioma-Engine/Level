#ifndef ATOM_QRK_STANDARD_ATTRIBUTES_MSVC_H
#define ATOM_QRK_STANDARD_ATTRIBUTES_MSVC_H

/**
 * @file MSVC.h
 * @brief Standard attribute mappings for MSVC compilers.
 *
 * Provides attribute macro aliases using MSVC-compatible forms, and
 * falls back to conservative defaults when attributes are unavailable.
 */

#include "../../Features.h"

#if ATOM_HAS_CPP_ATTRIBUTE(noreturn)
#    define ATOM_NORETURN [[noreturn]]
#else
#    define ATOM_NORETURN __declspec(noreturn)
#endif

#if ATOM_HAS_CPP_ATTRIBUTE(carries_dependency)
#    define ATOM_CARRIES_DEPENDENCY [[carries_dependency]]
#else
#    define ATOM_CARRIES_DEPENDENCY
#endif

#if ATOM_HAS_CPP_ATTRIBUTE(deprecated)
#    define ATOM_DEPRECATED [[deprecated]]
#    if ATOM_HAS_CXX17
#        define ATOM_DEPRECATED_MSG(msg) [[deprecated(msg)]]
#    else
#        define ATOM_DEPRECATED_MSG(msg) [[deprecated]]
#    endif
#else
#    define ATOM_DEPRECATED          __declspec(deprecated)
#    define ATOM_DEPRECATED_MSG(msg) __declspec(deprecated(msg))
#endif

#if ATOM_HAS_CPP_ATTRIBUTE(fallthrough)
#    define ATOM_FALLTHROUGH [[fallthrough]]
#else
#    define ATOM_FALLTHROUGH
#endif

#if ATOM_HAS_CPP_ATTRIBUTE(maybe_unused)
#    define ATOM_MAYBE_UNUSED [[maybe_unused]]
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
#elif (_MSC_VER >= 1700)
#    define ATOM_NODISCARD          _Check_return_
#    define ATOM_NODISCARD_MSG(msg) _Check_return_
#else
#    define ATOM_NODISCARD
#    define ATOM_NODISCARD_MSG(msg)
#endif

#if ATOM_HAS_CPP_ATTRIBUTE(likely)
#    define ATOM_LIKELY(x) (x) [[likely]]
#else
#    define ATOM_LIKELY(x) (x)
#endif

#if ATOM_HAS_CPP_ATTRIBUTE(unlikely)
#    define ATOM_UNLIKELY(x) (x) [[unlikely]]
#else
#    define ATOM_UNLIKELY(x) (x)
#endif

#if ATOM_HAS_CPP_ATTRIBUTE(no_unique_address)
#    define ATOM_NO_UNIQUE_ADDRESS [[no_unique_address]]
#elif ATOM_HAS_CPP_ATTRIBUTE(msvc::no_unique_address)
#    define ATOM_NO_UNIQUE_ADDRESS [[msvc::no_unique_address]]
#else
#    define ATOM_NO_UNIQUE_ADDRESS
#endif

#if ATOM_HAS_CPP_ATTRIBUTE(assume)
#    define ATOM_ASSUME(x) [[assume(x)]]
#else
#    define ATOM_ASSUME(x) __assume(x)
#endif

#endif
