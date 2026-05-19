/**
 * @file System.h
 * @brief Umbrella header for all environment-detection macros used by Quark.
 *
 * This header collects the platform, compiler, language, endianness,
 * sanitizer, and SIMD detection headers into a single include point.
 *
 * Macro hierarchy:
 * - ATOM_QRK_SYSTEM_H
 *   - Include guard for this umbrella header.
 *
 * - Build configuration
 *   - ATOM_BUILD_RELEASE: defined when NDEBUG is set.
 *   - ATOM_BUILD_DEBUG: defined when NDEBUG is not set.
 *
 * Included detection groups:
 * - ATOM_ARCH_*        : CPU architecture and pointer-width detection
 * - ATOM_COMPILER_*     : Compiler identification, family, and version data
 * - ATOM_LANGUAGE_CXX   : C++ language marker and ATOM_CXX_STANDARD feature level
 * - ATOM_ENDIAN_*       : Byte-order detection
 * - ATOM_OS_*           : Operating-system detection
 * - ATOM_SANITIZER_*    : Runtime sanitizer detection
 * - ATOM_SIMD_*         : SIMD and vector feature detection
 */
#ifndef ATOM_QRK_SYSTEM_H
#define ATOM_QRK_SYSTEM_H

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
 * - ATOM_BUILD_RELEASE: defined when NDEBUG is enabled.
 * - ATOM_BUILD_DEBUG: defined when NDEBUG is disabled.
 */
#if defined(NDEBUG)
#    define ATOM_BUILD_RELEASE 1
#else
#    define ATOM_BUILD_DEBUG 1
#endif

#endif
