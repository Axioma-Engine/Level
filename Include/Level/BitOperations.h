/**
 * @file BitOperations.h
 * @brief Public bit-operation facade - selects compiler-specific implementation.
 *
 * This header provides a single include point for common bit-manipulation
 * helpers used throughout Level. It forwards to one of three backends at
 * compile time via the Level::Bits:: namespace.
 *
 * Implementation files (selected by AXM_COMPILER_* macros from System/Compiler.h):
 * - "GCC/BitOperations.h"     : GCC, Clang, and other GCC-like toolchains.
 * - "MSVC/BitOperations.h"    : MSVC and MSVC-compatible toolchains.
 * - "Generic/BitOperations.h" : Portable fallbacks for unsupported compilers.
 *
 * Functions provided in Level::Bits:: namespace:
 * - Count trailing zeros: ctz32(u32), ctz64(u64)
 * - Count leading zeros: clz32(u32), clz64(u64)
 * - Population count: popcount32(u32), popcount64(u64)
 * - Byte swap: swap16(u16), swap32(u32), swap64(u64)
 * - Host-to-little-endian: htole16(u16), htole32(u32), htole64(u64)
 * - Little-endian-to-host: letoh16(u16), letoh32(u32), letoh64(u64)
 * - Host-to-big-endian: htobe16(u16), htobe32(u32), htobe64(u64)
 * - Big-endian-to-host: betoh16(u16), betoh32(u32), betoh64(u64)
 */
#ifndef AXM_LVL_BITOPERATIONS_H
#define AXM_LVL_BITOPERATIONS_H

#include "System/Compiler.h"

// IWYU pragma: begin_exports
#if AXM_COMPILER_GCC_LIKE
#    include "GCC/BitOperations.h"
#elif AXM_COMPILER_MSVC_LIKE
#    include "MSVC/BitOperations.h"
#else
#    include "Generic/BitOperations.h"
#endif
// IWYU pragma: end_exports

#endif
