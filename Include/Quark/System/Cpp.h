/**
 * @file Cpp.h
 * @brief C++ language-mode and standard-version detection.
 *
 * This header confirms compilation as C++ and exports a standard-version
 * macro plus feature gates for common language levels.
 *
 * Macro hierarchy:
 * - AXM_LANGUAGE_CXX
 *   - Indicates the translation unit is intended to be compiled as C++.
 *
 * - AXM_CXX_STANDARD
 *   - Uses _MSVC_LANG when available.
 *   - Falls back to __cplusplus on other compilers.
 *
 * - Feature flags derived from AXM_CXX_STANDARD
 *   - AXM_HAS_CXX26
 *   - AXM_HAS_CXX23
 *   - AXM_HAS_CXX20
 *   - AXM_HAS_CXX17
 *   - AXM_HAS_CXX14
 *   - AXM_HAS_CXX11
 *   - AXM_HAS_CXX98
 *
 * The higher-level flags are cumulative: a newer standard implies all older
 * feature macros that compare below its version value.
 */
#ifndef AXM_QRK_SYSTEM_CPP_H
#define AXM_QRK_SYSTEM_CPP_H

/** Warn when the header is included from non-C++ code. */
#if !defined(__cplusplus) && !defined(_MSVC_LANG)
#    pragma message("Axiom is a C++-only header. Do not include it from C projects")
#endif

/** Marker that this codebase expects C++ compilation. */
#define AXM_LANGUAGE_CXX 1

/** C++ standard version detection and feature gating. */

/** Prefer _MSVC_LANG under MSVC, otherwise use __cplusplus. */
#if defined(_MSVC_LANG)
#    define AXM_CXX_STANDARD _MSVC_LANG
#else
#    define AXM_CXX_STANDARD __cplusplus
#endif

/** C++26 or later. */
#if AXM_CXX_STANDARD >= 202602L
#    define AXM_HAS_CXX26 1
#endif

/** C++23 or later. */
#if AXM_CXX_STANDARD >= 202302L
#    define AXM_HAS_CXX23 1
#endif

/** C++20 or later. */
#if AXM_CXX_STANDARD >= 202002L
#    define AXM_HAS_CXX20 1
#endif

/** C++17 or later. */
#if AXM_CXX_STANDARD >= 201703L
#    define AXM_HAS_CXX17 1
#endif

/** C++14 or later. */
#if AXM_CXX_STANDARD >= 201402L
#    define AXM_HAS_CXX14 1
#endif

/** C++11 or later. */
#if AXM_CXX_STANDARD >= 201103L
#    define AXM_HAS_CXX11 1
#endif

/** C++98/03 or later. */
#if AXM_CXX_STANDARD >= 199711L
#    define AXM_HAS_CXX98 1
#endif

#endif
