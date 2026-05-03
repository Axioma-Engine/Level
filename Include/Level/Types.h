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
#ifndef AXM_LVL_TYPES_H
#define AXM_LVL_TYPES_H

#include <float.h>
#include <stddef.h>
#include <stdint.h>

#include "../System/Cpp.h" // IWYU pragma: keep

namespace AXM {

    /**
     * @brief Fixed-width unsigned integers.
     *
     * These types provide exact byte widths (1, 2, 4, 8) and are intended for
     * use in contexts where a specific storage size is required, such as file
     * formats, network protocols, serialization, and hashing. They offer
     * predictable behaviour across compilers and architectures.
     */
    typedef uint8_t  u8;
    typedef uint16_t u16;
    typedef uint32_t u32;
    typedef uint64_t u64;

    /**
     * @brief Fixed-width signed integers.
     *
     * Signed counterparts to the fixed-width unsigned types. Use these when
     * you need portable, predictable signed integer behaviour and clearly
     * defined storage sizes in APIs, arithmetic, or on-disk representations.
     */
    typedef int8_t  i8;
    typedef int16_t i16;
    typedef int32_t i32;
    typedef int64_t i64;

    /**
     * @brief Fast integer types (at least N bits) — performance-oriented.
     *
     * These types provide at least the specified width while allowing the
     * implementation to pick the fastest available type on the platform. They
     * are appropriate when performance is a higher priority than exact layout
     * or binary compatibility.
     */
    typedef uint_fast8_t  u8f;
    typedef uint_fast16_t u16f;
    typedef uint_fast32_t u32f;
    typedef uint_fast64_t u64f;

    typedef int_fast8_t  i8f;
    typedef int_fast16_t i16f;
    typedef int_fast32_t i32f;
    typedef int_fast64_t i64f;

    /**
     * @brief Smallest integer types (at least N bits) — memory-oriented.
     *
     * These aliases guarantee at least the requested width while permitting the
     * implementation to choose a memory-efficient representation. They are
     * useful for large arrays and memory-constrained in-memory structures,
     * but are not intended for persistent or network formats that depend on
     * exact byte layouts.
     */
    typedef uint_least8_t  u8l;
    typedef uint_least16_t u16l;
    typedef uint_least32_t u32l;
    typedef uint_least64_t u64l;

    typedef int_least8_t  i8l;
    typedef int_least16_t i16l;
    typedef int_least32_t i32l;
    typedef int_least64_t i64l;

    /**
     * @brief Pointer-sized and byte-oriented aliases.
     *
     * Aliases for pointer-sized integers and raw bytes. Use `usize`/`isize` for
     * sizes and offsets that match the platform pointer width, `uptr`/`iptr`
     * for integer-backed pointer math, `vptr` for opaque pointer storage, and
     * `byte` for raw byte buffers. These map to platform types and should not
     * be assumed to have fixed numeric widths for persistent layouts.
     */
    typedef void*     vptr;
    typedef size_t    usize;
    typedef ptrdiff_t isize;
    typedef uintptr_t uptr;
    typedef intptr_t  iptr;
    typedef uint8_t   byte;

    /**
     * @brief Floating-point aliases.
     *
     * Short, clear names for common floating-point types. `f32` and `f64`
     * correspond to single- and double-precision where available. `f80` is
     * provided for extended precision where supported, but may be equivalent
     * to `double` on some platforms.
     */
    typedef float  f32;
    typedef double f64;
#if defined(LDBL_MANT_DIG) && defined(DBL_MANT_DIG) && (LDBL_MANT_DIG > DBL_MANT_DIG)
    typedef long double f80;
#else
    typedef double f80;
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
    typedef uint8_t  b8;
    typedef uint32_t b32;

    typedef char           c8;
    typedef uint_least16_t c16;
    typedef uint_least32_t c32;
    typedef wchar_t        wc;

#if AXM_HAS_CXX11
    static_assert(sizeof(u8) == 1, "AXM: u8  must be 1 byte");
    static_assert(sizeof(u16) == 2, "AXM: u16 must be 2 bytes");
    static_assert(sizeof(u32) == 4, "AXM: u32 must be 4 bytes");
    static_assert(sizeof(u64) == 8, "AXM: u64 must be 8 bytes");

    static_assert(sizeof(i8) == 1, "AXM: i8  must be 1 byte");
    static_assert(sizeof(i16) == 2, "AXM: i16 must be 2 bytes");
    static_assert(sizeof(i32) == 4, "AXM: i32 must be 4 bytes");
    static_assert(sizeof(i64) == 8, "AXM: i64 must be 8 bytes");

    static_assert(sizeof(b8) == 1, "AXM: b8  must be 1 byte");
    static_assert(sizeof(b32) == 4, "AXM: b32 must be 4 bytes");

    static_assert(sizeof(c8) == 1, "AXM: c8  must be 1 byte");
#endif
}

#endif
