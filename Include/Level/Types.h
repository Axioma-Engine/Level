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

#include <stdint.h>

namespace AXM {

    /**
     * @brief Fixed-width unsigned integers.
     *
     * Summary:
     *  - Pros: Exact byte widths (1,2,4,8), ideal for binary protocols and
     *    serialization. Predictable behaviour across compilers/architectures.
     *  - Cons: Can be more verbose than plain "unsigned", but safer when size
     *    matters. Not tied to the machine's natural word size.
     *  - Usage: Use u8/u16/u32/u64 where the bit-width is mandatory (file
     *    formats, network packets, hashing, deterministic storage).
     */
    typedef uint8_t  u8;
    typedef uint16_t u16;
    typedef uint32_t u32;
    typedef uint64_t u64;

    /**
     * @brief Fixed-width signed integers.
     *
     * Summary:
     *  - Pros: Signed counterparts to the fixed-width unsigned types. Useful
     *    for arithmetic that relies on predictable ranges/overflow behaviour.
     *  - Cons: Same size constraints as unsigned types; consider overflow and
     *    sign when converting between sizes.
     *  - Usage: Use i8/i16/i32/i64 for portable signed integer semantics and
     *    for clear intent in interfaces.
     */
    typedef int8_t  i8;
    typedef int16_t i16;
    typedef int32_t i32;
    typedef int64_t i64;

    /**
     * @brief Fast integer types (at least N bits) - tuned for speed.
     *
     * Summary:
     *  - Pros: Choose the fastest integer type provided by the platform with at
     *    least the requested width. Helpful when performance matters more than
     *    exact layout.
     *  - Cons: Size can vary between platforms; not suitable for persistent
     *    binary formats or network protocols.
     *  - Usage: Use u8f/u16f/u32f/u64f and i8f/... when you want potential
     *    performance benefits and do not require exact width stability.
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
     * @brief Smallest integer types (at least N bits) - tuned for memory.
     *
     * Summary:
     *  - Pros: Minimize memory usage while guaranteeing at least the requested
     *    width. Useful in large arrays or memory-constrained contexts.
     *  - Cons: Like fast types, sizes may differ across platforms and are not
     *    suitable for on-disk or across-network representations.
     *  - Usage: Use u8l/u16l/... and i8l/... for compact in-memory storage when
     *    exact byte-for-byte layout is not required.
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
     * Summary:
     *  - Pros: Abstracts pointer and pointer-difference types to clear aliases
     *    (usize/isize/uptr/iptr) that match the architecture's pointer width.
     *  - Cons: These map directly to platform types; avoid assuming exact
     *    numeric widths in portable binary layouts.
     *  - Usage: Use usize/isize for sizes and offsets, vptr for opaque pointer
     *    storage, uptr/iptr when you need integer-backed pointer math, and
     *    byte for raw byte buffers.
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
     * Summary:
     *  - Pros: Short, clear names for common floating types. f32/f64 map to
     *    IEEE-754 single/double when available and are portable for numeric
     *    algorithms.
     *  - Cons: long double precision/size varies by platform; f80 is an alias
     *    that may equal double on some platforms.
     *  - Usage: Use f32 for performance-sensitive or lower-precision needs,
     *    f64 for general-purpose numeric stability, and f80 when extended
     *    precision is explicitly required and supported.
     */
    typedef float  f32;
    typedef double f64;
#if defined(__SIZEOF_LONG_DOUBLE__) && __SIZEOF_LONG_DOUBLE__ >= 10
    typedef long double f80;
#else
    typedef double f80;
#endif

    /**
     * @brief Boolean and character storage aliases.
     *
     * Summary:
     *  - Pros: Explicit-width boolean types (b8/b32) can aid in alignment and
     *    serialization. Character aliases clarify expected storage unit sizes.
     *  - Cons: These are storage-focused; they do not replace language bool or
     *    character semantics (e.g., signedness/encoding of char).
     *  - Usage: Use b8 for compact boolean arrays and b32 when 32-bit packing
     *    or API requirements demand it. Use c8/c16/c32/wc for character storage
     *    sized intents; prefer higher-level string types for text handling.
     */
    typedef uint8_t  b8;
    typedef uint32_t b32;

    typedef char           c8;
    typedef uint_least16_t c16;
    typedef uint_least32_t c32;
    typedef wchar_t        wc;

    /**
     * @brief Compile-time sanity checks for the public type aliases.
     *
     * Summary:
     *  - Pros: static_asserts catch mismatches early when building with C++11
     *    or newer. They ensure alias assumptions about sizes hold on the target
     *    platform.
     *  - Cons: Requires AXM_HAS_CXX11 to be defined. On older compilers these
     *    checks are omitted.
     *  - Usage: Keeps invariants explicit; no runtime overhead.
     */
#if AXM_HAS_CXX11
    static_assert(sizeof(u8) == 1, "AXM: u8  must be 1 byte");
    static_assert(sizeof(u16) == 2, "AXM: u16 must be 2 bytes");
    static_assert(sizeof(u32) == 4, "AXM: u32 must be 4 bytes");
    static_assert(sizeof(u64) == 8, "AXM: u64 must be 8 bytes");

    static_assert(sizeof(i8) == 1, "AXM: i8  must be 1 byte");
    static_assert(sizeof(i16) == 2, "AXM: i16 must be 2 bytes");
    static_assert(sizeof(i32) == 4, "AXM: i32 must be 4 bytes");
    static_assert(sizeof(i64) == 8, "AXM: i64 must be 8 bytes");

    static_assert(sizeof(f32) == 4, "AXM: f32 must be 4 bytes (IEEE 754 single)");
    static_assert(sizeof(f64) == 8, "AXM: f64 must be 8 bytes (IEEE 754 double)");

    static_assert(sizeof(usize) == sizeof(vptr), "AXM: usize must match pointer width");
    static_assert(sizeof(isize) == sizeof(vptr), "AXM: isize must match pointer width");
    static_assert(sizeof(uptr) == sizeof(vptr), "AXM: uptr  must match pointer width");
    static_assert(sizeof(iptr) == sizeof(vptr), "AXM: iptr  must match pointer width");

    static_assert(sizeof(b8) == 1, "AXM: b8  must be 1 byte");
    static_assert(sizeof(b32) == 4, "AXM: b32 must be 4 bytes");

    static_assert(sizeof(c8) == 1, "AXM: c8  must be 1 byte");
    static_assert(sizeof(c16) == 2, "AXM: c16 must be 2 bytes");
    static_assert(sizeof(c32) == 4, "AXM: c32 must be 4 bytes");
#endif
}

#endif
