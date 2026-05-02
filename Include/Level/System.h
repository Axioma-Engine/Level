/**
 * @file System.h
 * @brief Umbrella header for all environment-detection macros used by Level.
 *
 * This header collects the platform, compiler, language, endianness,
 * sanitizer, and SIMD detection headers into a single include point.
 *
 * Macro hierarchy:
 * - AXM_LVL_SYSTEM_H
 *   - Include guard for this umbrella header.
 *
 * - Build configuration
 *   - AXM_BUILD_RELEASE: defined when NDEBUG is set.
 *   - AXM_BUILD_DEBUG: defined when NDEBUG is not set.
 *
 * Included detection groups:
 * - AXM_ARCH_*        : CPU architecture and pointer-width detection
 * - AXM_COMPILER_*     : Compiler identification, family, and version data
 * - AXM_LANGUAGE_CXX   : C++ language marker and AXM_CXX_STANDARD feature level
 * - AXM_ENDIAN_*       : Byte-order detection
 * - AXM_OS_*           : Operating-system detection
 * - AXM_SANITIZER_*    : Runtime sanitizer detection
 * - AXM_SIMD_*         : SIMD and vector feature detection
 */
#ifndef AXM_LVL_SYSTEM_H
#define AXM_LVL_SYSTEM_H

// IWYU pragma: begin_exports
#include "System/Arch.h"
#include "System/Compiler.h"
#include "System/Cpp.h"
#include "System/Endian.h"
#include "System/Os.h"
#include "System/Sanitizer.h"
#include "System/Simd.h"
// IWYU pragma: end_exports

/**
 * Build mode derived from NDEBUG.
 * - AXM_BUILD_RELEASE: defined when NDEBUG is enabled.
 * - AXM_BUILD_DEBUG: defined when NDEBUG is disabled.
 */
#if defined(NDEBUG)
#    define AXM_BUILD_RELEASE 1
#else
#    define AXM_BUILD_DEBUG 1
#endif

#endif
