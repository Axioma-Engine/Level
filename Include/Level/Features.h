/**
 * @file Features.h
 * @brief Compiler feature-probing helpers (portable __has_* / availability wrappers).
 *
 * This header centralizes queries for compiler capabilities so higher-level
 * code can use short, consistent macros when selecting attributes, builtins,
 * or other compiler-specific features.
 *
 * Exposed macros (behavior summary):
 * - AXM_HAS_ATTRIBUTE(x)
 *   - True if the compiler exposes __has_attribute and the queried attribute is supported.
 *   - Falls back to 0 when __has_attribute is not available.
 *
 * - AXM_HAS_BUILTIN(x)
 *   - True if __has_builtin is available and reports the builtin, or when targeting
 *     a compiler known to provide common builtins (GCC family fallback).
 *   - Falls back to 0 otherwise.
 *
 * - AXM_HAS_FEATURE(x)
 *   - Uses __has_feature when present (Clang) to detect language/feature support.
 *   - Falls back to 0 when not present.
 *
 * - AXM_HAS_EXTENSION(x)
 *   - Uses __has_extension when present, otherwise mirrors AXM_HAS_FEATURE(x).
 *
 * - AXM_HAS_CPP_ATTRIBUTE(x)
 *   - Uses __has_cpp_attribute when present to query standard C++ attributes.
 *   - Compares availability against AXM_CXX_STANDARD where applicable to avoid
 *     treating future attributes as present on older language modes.
 *   - Falls back to 0 when __has_cpp_attribute is not available.
 *
 * - AXM_HAS_INCLUDE(x)
 *   - Uses __has_include to detect header availability; falls back to 0 otherwise.
 *
 * - AXM_HAS_DECLSPEC(x)
 *   - Uses __has_declspec_attribute if provided by the compiler; falls back to 0.
 *
 * Implementation notes:
 * - Where direct feature-query intrinsics are not available, conservative defaults
 *   (0) are used so that callers will choose portable fallbacks.
 * - Consumers should include System/Cpp.h before relying on AXM_HAS_CPP_ATTRIBUTE so
 *   that AXM_CXX_STANDARD is defined for attribute-version comparisons.
 */
#ifndef AXM_LVL_FEATURES_H
#define AXM_LVL_FEATURES_H

#include "System/Cpp.h"

/** Check for compiler attribute support (e.g., __noreturn__). */
#if defined(__has_attribute)
#    define AXM_HAS_ATTRIBUTE(x) __has_attribute(x)
#else
#    define AXM_HAS_ATTRIBUTE(x) 0
#endif

/** Check for compiler builtin support (e.g., __builtin_expect). */
#if defined(__has_builtin)
#    define AXM_HAS_BUILTIN(x) __has_builtin(x)
#elif AXM_COMPILER_GCC
#    define AXM_HAS_BUILTIN(x) 1
#else
#    define AXM_HAS_BUILTIN(x) 0
#endif

/** Check for Clang-style feature queries. */
#if defined(__has_feature)
#    define AXM_HAS_FEATURE(x) __has_feature(x)
#else
#    define AXM_HAS_FEATURE(x) 0
#endif

/** Check for Clang-style extension queries, falling back to feature queries. */
#if defined(__has_extension)
#    define AXM_HAS_EXTENSION(x) __has_extension(x)
#else
#    define AXM_HAS_EXTENSION(x) AXM_HAS_FEATURE(x)
#endif

/** Check for C++ standard attributes (e.g., [[nodiscard]]). */
#if defined(__has_cpp_attribute)
#    define AXM_HAS_CPP_ATTRIBUTE(x) __has_cpp_attribute(x) < AXM_CXX_STANDARD
#else
#    define AXM_HAS_CPP_ATTRIBUTE(x) 0
#endif

/** Check for header availability. */
#if defined(__has_include)
#    define AXM_HAS_INCLUDE(x) __has_include(x)
#else
#    define AXM_HAS_INCLUDE(x) 0
#endif

/** Check for MSVC-style __has_declspec_attribute support. */
#if defined(__has_declspec_attribute)
#    define AXM_HAS_DECLSPEC(x) __has_declspec_attribute(x)
#else
#    define AXM_HAS_DECLSPEC(x) 0
#endif

#endif
