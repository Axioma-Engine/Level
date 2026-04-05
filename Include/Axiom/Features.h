/**
 * @file Features.h
 * @brief Compiler capability detection predicates.
 *
 * @details
 * Provides standardized macros for checking compiler capabilities at
 * preprocessing time. These build on System.h detection and add support
 * for compiler feature-check builtins like __has_attribute, __has_builtin,
 * __has_cpp_attribute, etc.
 *
 * All macros return 1 (true) if the feature is available, 0 (false) if not.
 * This allows safe use in #if directives without additional #ifdef guards.
 *
 * **Example usage:**
 * @code
 * #if AXM_HAS_ATTRIBUTE(constructor)
 *     // Use GCC/Clang __attribute__((constructor))
 * #else
 *     // Use alternative initialization
 * #endif
 * @endcode
 *
 * @see System.h - Platform and compiler detection
 * @see Attributes.h - Concrete attribute definitions using these checks
 */
#ifndef AXM_LVL_FEATURES_H
#define AXM_LVL_FEATURES_H
#pragma once

#include <Axiom/System.h>

/* ========================================================================
 * @defgroup AXM_FEATURE_CHECKS Compiler Feature Detection Macros
 * @brief Checks for compiler feature availability.
 *
 * @details
 * These macros detect compiler capabilities using standard feature-check
 * builtins (__has_attribute, __has_builtin, etc.) with safe fallbacks
 * for compilers that don't support them.
 *
 * All macros expand to either 1 (feature available) or 0 (not available).
 * This is safer than undefined expansion and works in #if conditionals.
 *
 * @{
 * ======================================================================== */

/** @brief Checks if a GCC/Clang attribute is supported.
 *
 * @details
 * Usage: `#if AXM_HAS_ATTRIBUTE(noreturn) ... #endif`
 *
 * Returns 1 if the attribute is available, 0 otherwise.
 * Expands to a compiler builtin check if available, otherwise returns 0.
 */
#if defined(__has_attribute)
#    define AXM_HAS_ATTRIBUTE(x) __has_attribute(x)
#else
#    define AXM_HAS_ATTRIBUTE(x) 0
#endif


/** @brief Checks if a compiler builtin function is supported.
 *
 * @details
 * Usage: `#if AXM_HAS_BUILTIN(__builtin_clz) ... #endif`
 *
 * Returns 1 if the builtin is available, 0 otherwise.
 * Clang and GCC 5+ provide __has_builtin; older compilers return 0.
 */
#if defined(__has_builtin)
#    define AXM_HAS_BUILTIN(x) __has_builtin(x)
#else
#    define AXM_HAS_BUILTIN(x) 0
#endif


/** @brief Checks if a Clang language feature is available.
 *
 * @details
 * Usage: `#if AXM_HAS_FEATURE(address_sanitizer) ... #endif`
 *
 * Returns 1 if the feature is enabled, 0 otherwise.
 * Only Clang and some GCC versions support __has_feature.
 */
#if defined(__has_feature)
#    define AXM_HAS_FEATURE(x) __has_feature(x)
#else
#    define AXM_HAS_FEATURE(x) 0
#endif


/** @brief Checks if a Clang language extension is available.
 *
 * @details
 * Usage: `#if AXM_HAS_EXTENSION(cxx_rvalue_references) ... #endif`
 *
 * Returns 1 if the extension is available, 0 otherwise.
 * Falls back to AXM_HAS_FEATURE on compilers without __has_extension.
 */
#if defined(__has_extension)
#    define AXM_HAS_EXTENSION(x) __has_extension(x)
#elif defined(__has_feature)
#    define AXM_HAS_EXTENSION(x) __has_feature(x)
#else
#    define AXM_HAS_EXTENSION(x) 0
#endif


/** @brief Checks if a C++ standard attribute is available.
 *
 * @details
 * Usage: `#if AXM_HAS_CPP_ATTRIBUTE(nodiscard) ... #endif`
 *
 * Returns 1 if the C++ attribute is available, 0 otherwise.
 * Requires C++ and compiler support for __has_cpp_attribute (C++20).
 * For C++17, a safe default of 0 is used (conservative).
 *
 * Standard C++ attributes (C++17+):
 * - nodiscard
 * - maybe_unused
 * - deprecated
 * - fallthrough
 * - no_unique_address (C++20)
 */
#if defined(__has_cpp_attribute)
#    define AXM_HAS_CPP_ATTRIBUTE(x) __has_cpp_attribute(x)
#elif defined(AXM_CXX_STANDARD) && AXM_CXX_STANDARD >= 201703L
/* C++17 has some standard attributes but __has_cpp_attribute may not exist.
   Be conservative and return 0; specific features are checked elsewhere. */
#    define AXM_HAS_CPP_ATTRIBUTE(x) 0
#else
#    define AXM_HAS_CPP_ATTRIBUTE(x) 0
#endif


/** @brief Checks if a C standard attribute is available.
 *
 * @details
 * Usage: `#if AXM_HAS_C_ATTRIBUTE(noreturn) ... #endif`
 *
 * Returns 1 if the C attribute is available, 0 otherwise.
 * Only C11 and later have standard attributes.
 */
#if defined(__has_c_attribute)
#    define AXM_HAS_C_ATTRIBUTE(x) __has_c_attribute(x)
#else
#    define AXM_HAS_C_ATTRIBUTE(x) 0
#endif


/** @brief Checks if a header file can be included.
 *
 * @details
 * Usage: `#if AXM_HAS_INCLUDE(<optional>) ... #endif`
 *
 * Returns 1 if the header exists and is includable, 0 otherwise.
 * Useful for conditional support of C++17+ headers like <optional>.
 */
#if defined(__has_include)
#    define AXM_HAS_INCLUDE(x) __has_include(x)
#else
#    define AXM_HAS_INCLUDE(x) 0
#endif


/** @brief Checks if an MSVC __declspec attribute is available.
 *
 * @details
 * Usage: `#if AXM_HAS_DECLSPEC_ATTRIBUTE(dllexport) ... #endif`
 *
 * Returns 1 if the declspec is available, 0 otherwise.
 * MSVC and compatible compilers (Clang-cl) support declspecs.
 */
#if defined(__has_declspec_attribute)
#    define AXM_HAS_DECLSPEC_ATTRIBUTE(x) __has_declspec_attribute(x)
#elif defined(AXM_COMPILER_MSVC) || defined(AXM_COMPILER_MSVC_LIKE)
/** All common declspecs are assumed available on MSVC-like compilers. */
#    define AXM_HAS_DECLSPEC_ATTRIBUTE(x) 1
#else
#    define AXM_HAS_DECLSPEC_ATTRIBUTE(x) 0
#endif

/** @} */


/* ========================================================================
 * @defgroup AXM_LEGACY_COMPILER_FEATURES Legacy Compiler Feature Fallbacks
 * @brief Version-based feature detection for compilers without __has_*.
 *
 * @details
 * For very old compilers (pre-GCC 4, pre-MSVC 7) that don't support
 * __has_attribute and similar predicates, provide version-based fallbacks.
 *
 * These are mostly historical for extremely old toolchains that are
 * rarely used today, but they ensure the library compiles everywhere.
 *
 * @{
 * ======================================================================== */

/** @cond INTERNAL */

#if defined(AXM_COMPILER_GCC_LIKE) && !defined(__has_attribute)
/* GCC before version 4 lacked many attributes; version 4 and later
   tend to have most common ones. This is approximate. */
#    if AXM_COMPILER_VERSION_MAJOR >= 4
/** @brief GCC 4+: packed attribute available. */
#        define AXM_HAS_ATTRIBUTE_packed   1
/** @brief GCC 4+: aligned attribute available. */
#        define AXM_HAS_ATTRIBUTE_aligned  1
/** @brief GCC 4+: unused attribute available. */
#        define AXM_HAS_ATTRIBUTE_unused   1
/** @brief GCC 4+: noreturn attribute available. */
#        define AXM_HAS_ATTRIBUTE_noreturn 1
/** @brief GCC 4+: format attribute available. */
#        define AXM_HAS_ATTRIBUTE_format   1
#    elif AXM_COMPILER_VERSION_MAJOR >= 3                                                          \
        || (AXM_COMPILER_VERSION_MAJOR == 2 && AXM_COMPILER_VERSION_MINOR >= 95)
/** @brief GCC 2.95-3.x: limited attribute support. */
#        define AXM_HAS_ATTRIBUTE_noreturn 1
#    endif
#endif

#if defined(AXM_COMPILER_MSVC_LIKE) && AXM_COMPILER_VERSION_MAJOR < 7
/** @brief MSVC 6.0 and earlier had very limited feature support. */
#    define AXM_LEGACY_MSVC_6 1
#endif

#if defined(AXM_COMPILER_SUNPRO) && AXM_COMPILER_VERSION_MAJOR < 5
/** @brief Sun Studio before 5.0 had minimal attribute support. */
#    define AXM_LEGACY_SUNPRO_OLD 1
#endif

#if defined(AXM_COMPILER_BORLAND) && AXM_COMPILER_VERSION_MAJOR < 6
/** @brief Borland C++ before 6.0 had minimal modern features. */
#    define AXM_LEGACY_BORLAND_OLD 1
#endif

#if defined(AXM_COMPILER_WATCOM) && AXM_COMPILER_VERSION_MAJOR < 11
/** @brief Watcom before 11.0 had limited attribute support. */
#    define AXM_LEGACY_WATCOM_OLD 1
#endif

/** @endcond */

/** @} */

#endif
