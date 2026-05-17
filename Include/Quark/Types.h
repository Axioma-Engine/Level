/**
 * @file Types.h
 * @brief Lightweight, portable type aliases for fixed-width and convenience use.
 *
 * This header defines a compact set of typedefs that wrap standard integer,
 * pointer-sized, floating-point, boolean, and character types. The aliases
 * prioritise clarity and portability across platforms (32/64-bit) and aim to
 * reduce verbosity in the codebase while providing explicit size guarantees
 * where required. Use these aliases for public-facing APIs, serialization,
 * binary formats, and anywhere exact widths or clear intent improve
 * maintainability.
 */
#ifndef AXM_QRK_TYPES_H
#define AXM_QRK_TYPES_H

#include <float.h>
#include <stddef.h>
#include <stdint.h>

#include "Utils.h"

/**
 * @brief Fixed-width unsigned integers.
 *
 * These types provide exact byte widths (1, 2, 4, 8) and are intended for
 * use in contexts where a specific storage size is required, such as file
 * formats, network protocols, serialization, and hashing. They offer
 * predictable behaviour across compilers and architectures.
 */
AXM_ALIAS(uint8_t, u8)
AXM_ALIAS(uint16_t, u16)
AXM_ALIAS(uint32_t, u32)
AXM_ALIAS(uint64_t, u64)

/**
 * @brief Fixed-width signed integers.
 *
 * Signed counterparts to the fixed-width unsigned types. Use these when
 * you need portable, predictable signed integer behaviour and clearly
 * defined storage sizes in APIs, arithmetic, or on-disk representations.
 */
AXM_ALIAS(int8_t, i8)
AXM_ALIAS(int16_t, i16)
AXM_ALIAS(int32_t, i32)
AXM_ALIAS(int64_t, i64)

/**
 * @brief Fast integer types (at least N bits) — performance-oriented.
 *
 * These types provide at least the specified width while allowing the
 * implementation to pick the fastest available type on the platform. They
 * are appropriate when performance is a higher priority than exact layout
 * or binary compatibility.
 */
AXM_ALIAS(uint_fast8_t, u8f)
AXM_ALIAS(uint_fast16_t, u16f)
AXM_ALIAS(uint_fast32_t, u32f)
AXM_ALIAS(uint_fast64_t, u64f)

AXM_ALIAS(int_fast8_t, i8f)
AXM_ALIAS(int_fast16_t, i16f)
AXM_ALIAS(int_fast32_t, i32f)
AXM_ALIAS(int_fast64_t, i64f)

/**
 * @brief Smallest integer types (at least N bits) — memory-oriented.
 *
 * These aliases guarantee at least the requested width while permitting the
 * implementation to choose a memory-efficient representation. They are
 * useful for large arrays and memory-constrained in-memory structures,
 * but are not intended for persistent or network formats that depend on
 * exact byte layouts.
 */
AXM_ALIAS(uint_least8_t, u8l)
AXM_ALIAS(uint_least16_t, u16l)
AXM_ALIAS(uint_least32_t, u32l)
AXM_ALIAS(uint_least64_t, u64l)

AXM_ALIAS(int_least8_t, i8l)
AXM_ALIAS(int_least16_t, i16l)
AXM_ALIAS(int_least32_t, i32l)
AXM_ALIAS(int_least64_t, i64l)

/**
 * @brief Pointer-sized and byte-oriented aliases.
 *
 * Aliases for pointer-sized integers and raw bytes. Use `usize`/`isize` for
 * sizes and offsets that match the platform pointer width, `uptr`/`iptr`
 * for integer-backed pointer math, `vptr` for opaque pointer storage, and
 * `byte` for raw byte buffers. These map to platform types and should not
 * be assumed to have fixed numeric widths for persistent layouts.
 */
AXM_ALIAS(void*, vptr)
AXM_ALIAS(size_t, usize)
AXM_ALIAS(ptrdiff_t, isize)
AXM_ALIAS(uintptr_t, uptr)
AXM_ALIAS(intptr_t, iptr)
AXM_ALIAS(uint8_t, byte)

/**
 * @brief Floating-point aliases.
 *
 * Short, clear names for common floating-point types. `f32` and `f64`
 * correspond to single- and double-precision where available. `f80` is
 * provided for extended precision where supported, but may be equivalent
 * to `double` on some platforms.
 */
AXM_ALIAS(float, f32)
AXM_ALIAS(double, f64)
#if defined(LDBL_MANT_DIG) && defined(DBL_MANT_DIG) && (LDBL_MANT_DIG > DBL_MANT_DIG)
AXM_ALIAS(long double, f80)
#else
AXM_ALIAS(double, f80)
#endif

/**
 * @brief Boolean and character storage aliases.
 *
 * Storage-focused aliases for boolean and character-sized data. Use `b8`
 * for compact boolean arrays and `b32` when a 32-bit storage unit is
 * required. Character aliases (`c8`, `c16`, `c32`, `wc`) describe the
 * intended storage width; prefer higher-level string types for text and
 * encoding-aware operations.
 */
AXM_ALIAS(uint8_t, b8)
AXM_ALIAS(uint32_t, b32)

#define AXM_TRUE  1
#define AXM_FALSE 0

AXM_ALIAS(uint_least8_t, c8)
AXM_ALIAS(uint_least16_t, c16)
AXM_ALIAS(uint_least32_t, c32)
AXM_ALIAS(wchar_t, wc)

#endif
