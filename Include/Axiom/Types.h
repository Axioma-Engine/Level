/**
 * @file Types.h
 * @brief Portable type aliases with guaranteed widths and clear naming conventions.
 *
 * @details
 * The default C/C++ integer types (int, long, unsigned long, etc.) have
 * implementation-defined widths that vary by platform, compiler, and ABI.
 * For example, 'long' is 32 bits on Windows and 64 bits on Linux x86-64.
 * Using them in cross-platform code is a common source of silent truncation
 * bugs and serialisation mismatches.
 *
 * This header replaces them with a concise set of aliases inspired by Rust's
 * type naming conventions (u8, i32, f64, ...). The names are short enough to
 * type comfortably but unambiguous about width and signedness. Prefer these
 * types — or the stdint.h / inttypes.h types they alias — over raw C types
 * throughout the codebase.
 *
 * **Type families provided:**
 *
 * **Exact-width integers (u8…u64, i8…i64):**
 *   - Guaranteed to be exactly N bits
 *   - Use whenever the precise width matters: binary formats, network protocols,
 *     hardware register maps, atomic operations, serialisation
 *
 * **Fast integers (u8f…u64f, i8f…i64f):**
 *   - At least N bits wide, chosen to be fastest on the target CPU
 *   - Actual width may be larger; not portable across platforms
 *   - Use for loop counters and accumulators where speed > exact width
 *
 * **Least integers (u8l…u64l, i8l…i64l):**
 *   - The smallest type that can hold at least N bits
 *   - Rarely needed; exact-width types are almost always preferable
 *
 * **Pointer-width types (usize, isize, uptr, iptr, vptr, byte):**
 *   - Sized to match native pointer width (32-bit or 64-bit)
 *   - usize: for sizes, lengths, indices (unsigned)
 *   - isize: for pointer differences and signed offsets
 *   - uptr/iptr: when integers must convert to/from pointers
 *   - vptr: typeless void pointer for generic memory operations
 *   - byte: emphasized as raw memory byte, not small integer
 *
 * **Floating-point (f32, f64, f80):**
 *   - f32: IEEE 754 single precision (4 bytes)
 *   - f64: IEEE 754 double precision (8 bytes)
 *   - f80: extended precision when available (x87 typically 10 bytes)
 *
 * **Boolean (b8, b32):**
 *   - b8: 1-byte boolean for packed structs
 *   - b32: 4-byte boolean for graphics/OS APIs
 *
 * **Character (c8, c16, c32, wc):**
 *   - Explicitly sized: UTF-8, UTF-16, UTF-32, and wide-char types
 *
 * **Compile-time verification:**
 *   - static_assert (C++11) checks verify all sizes are correct
 *   - Pre-C++11 compilers use linker-level verification tricks
 *
 * @see System.h - Platform detection
 * @see Attributes.h - Alignment control macros (AXM_ALIGNAS, AXM_ALIGNOF)
 */
#ifndef AXM_LVL_TYPES_H
#define AXM_LVL_TYPES_H
#pragma once

#include <inttypes.h>
#include <limits.h>
#include <stddef.h>

#include <Axiom/System.h>

/**
 * @cond INTERNAL
 * Support for pre-C++11 compilers that lack complete stdint.h.
 * For MSVC before 2010, we need manual type definitions.
 */
#if !defined(__STDC_INT8_MAX__) && defined(_MSC_VER) && _MSC_VER < 1600
/* MSVC 6.0 through 2008 need manual type definitions */
#    if !defined(uint8_t)
#        define uint8_t        unsigned char
#        define int8_t         signed char
#        define uint16_t       unsigned short
#        define int16_t        signed short
#        define uint32_t       unsigned long
#        define int32_t        signed long
#        define uint64_t       unsigned __int64
#        define int64_t        signed __int64
#        define uint_fast8_t   uint8_t
#        define int_fast8_t    int8_t
#        define uint_fast16_t  uint16_t
#        define int_fast16_t   int16_t
#        define uint_fast32_t  uint32_t
#        define int_fast32_t   int32_t
#        define uint_fast64_t  uint64_t
#        define int_fast64_t   int64_t
#        define uint_least8_t  uint8_t
#        define int_least8_t   int8_t
#        define uint_least16_t uint16_t
#        define int_least16_t  int16_t
#        define uint_least32_t uint32_t
#        define int_least32_t  int32_t
#        define uint_least64_t uint64_t
#        define int_least64_t  int64_t
#        define uintptr_t      unsigned __int64
#        define intptr_t       signed __int64
#    endif
#endif
/** @endcond */

namespace AXM {

    /* ========================================================================
     * @defgroup AXM_EXACT_WIDTH_TYPES Exact-Width Integer Types
     * @brief Fixed-size integer types with guaranteed widths.
     *
     * @details
     * Guaranteed to be exactly N bits wide (N = 8, 16, 32, 64).
     * Direct aliases to stdint.h types. Use whenever width matters.
     *
     * **Unsigned (u8, u16, u32, u64):**
     * - Range [0, 2^N - 1]
     * - Use for: bit fields, flags, counts, indices, non-negative values
     * - Overflow wraps (well-defined)
     *
     * **Signed (i8, i16, i32, i64):**
     * - Range [-2^(N-1), 2^(N-1) - 1] in two's complement
     * - Use for: offsets, differences, error codes, signed coordinates
     * - Overflow is undefined behaviour (in C++20+: defined as wrapping)
     *
     * @{
     * ======================================================================== */

    /** @brief Unsigned 8-bit integer (0–255). */
    using u8  = uint8_t;
    /** @brief Unsigned 16-bit integer (0–65,535). */
    using u16 = uint16_t;
    /** @brief Unsigned 32-bit integer (0–4,294,967,295). */
    using u32 = uint32_t;
    /** @brief Unsigned 64-bit integer (0–18,446,744,073,709,551,615). */
    using u64 = uint64_t;

    /** @brief Signed 8-bit integer (-128–127). */
    using i8  = int8_t;
    /** @brief Signed 16-bit integer (-32,768–32,767). */
    using i16 = int16_t;
    /** @brief Signed 32-bit integer (-2,147,483,648–2,147,483,647). */
    using i32 = int32_t;
    /** @brief Signed 64-bit integer (-9,223,372,036,854,775,808–9,223,372,036,854,775,807). */
    using i64 = int64_t;

    /** @} */


    /* ========================================================================
     * @defgroup AXM_FAST_WIDTH_TYPES Fast Integer Types
     * @brief CPU-native integer types (at least N bits, possibly wider).
     *
     * @details
     * At least N bits wide; compiler chooses the fastest type the CPU can
     * operate on natively (often wider than N bits). Width is not portable.
     *
     * **Use for:** loop counters, accumulators, temporaries in hot paths
     * **Avoid for:** structs, arrays, public APIs, serialised data
     *
     * @code
     * // Fast loop counter (may be wider than 32 bits on 64-bit CPU)
     * for (u32f i = 0; i < count; ++i) { }
     *
     * // Temporary accumulator (speed prioritized over space)
     * u64f sum = 0;
     * for (const auto& elem : data) sum += elem;
     * @endcode
     *
     * @{
     * ======================================================================== */

    /** @brief Unsigned fast integer, at least 8 bits. */
    using u8f  = uint_fast8_t;
    /** @brief Unsigned fast integer, at least 16 bits. */
    using u16f = uint_fast16_t;
    /** @brief Unsigned fast integer, at least 32 bits. */
    using u32f = uint_fast32_t;
    /** @brief Unsigned fast integer, at least 64 bits. */
    using u64f = uint_fast64_t;

    /** @brief Signed fast integer, at least 8 bits. */
    using i8f  = int_fast8_t;
    /** @brief Signed fast integer, at least 16 bits. */
    using i16f = int_fast16_t;
    /** @brief Signed fast integer, at least 32 bits. */
    using i32f = int_fast32_t;
    /** @brief Signed fast integer, at least 64 bits. */
    using i64f = int_fast64_t;

    /** @} */


    /* ========================================================================
     * @defgroup AXM_LEAST_WIDTH_TYPES Least-Width Integer Types
     * @brief Smallest integer types that hold at least N bits.
     *
     * @details
     * The smallest type guaranteed to hold at least N bits. On common platforms
     * they match exact-width types, but on exotic hardware without native bytes
     * they may be wider (rare).
     *
     * **Primary use:** dense storage where minimising memory > access speed.
     * **Rarely needed:** exact-width types (u8–u64) are almost always better.
     *
     * @{
     * ======================================================================== */

    /** @brief Unsigned least integer, at least 8 bits. */
    using u8l  = uint_least8_t;
    /** @brief Unsigned least integer, at least 16 bits. */
    using u16l = uint_least16_t;
    /** @brief Unsigned least integer, at least 32 bits. */
    using u32l = uint_least32_t;
    /** @brief Unsigned least integer, at least 64 bits. */
    using u64l = uint_least64_t;

    /** @brief Signed least integer, at least 8 bits. */
    using i8l  = int_least8_t;
    /** @brief Signed least integer, at least 16 bits. */
    using i16l = int_least16_t;
    /** @brief Signed least integer, at least 32 bits. */
    using i32l = int_least32_t;
    /** @brief Signed least integer, at least 64 bits. */
    using i64l = int_least64_t;

    /** @} */


    /* ========================================================================
     * @defgroup AXM_POINTER_WIDTH_TYPES Pointer-Width and Address Types
     * @brief Integers and pointers sized to match architecture (32 or 64-bit).
     *
     * @details
     * All sized to match native pointer width. Static_assert verifies this
     * relationship at compile time.
     *
     * **vptr:** Typeless (void*) pointer for generic memory operations.
     *   @code
     *   vptr buffer = malloc(1024);
     *   @endcode
     *
     * **usize:** Unsigned pointer-width integer (equivalent to size_t).
     *   @code
     *   usize len = strlen("hello");  // Safe: no signed/unsigned mismatch
     *   usize index = find_element(vec);
     *   @endcode
     *
     * **isize:** Signed pointer-width integer (equivalent to ptrdiff_t).
     *   @code
     *   isize offset = end - begin;  // Difference between pointers
     *   isize delta = -100;
     *   @endcode
     *
     * **uptr:** Integer wide enough to hold any pointer without loss.
     *   @code
     *   uptr addr = (uptr)my_pointer;
     *   addr |= 0x3;  // Tag the low 2 bits
     *   MyType* ptr = (MyType*)addr;
     *   @endcode
     *
     * **iptr:** Signed counterpart to uptr.
     *   @code
     *   iptr addr = (iptr)ptr1 - (iptr)ptr2;
     *   @endcode
     *
     * **byte:** Alias for u8, emphasizing raw memory byte (not arithmetic).
     *   @code
     *   void* memcpy_custom(byte* dst, const byte* src, usize len) { }
     *   @endcode
     *
     * @{
     * ======================================================================== */

    /** @brief Typeless (void) pointer. */
    using vptr = void*;

    /** @brief Unsigned pointer-width integer (size_t equivalent).
     *  Use for sizes, lengths, array indices. */
    using usize = size_t;

    /** @brief Signed pointer-width integer (ptrdiff_t equivalent).
     *  Use for pointer differences and signed offsets. */
    using isize = ptrdiff_t;

    /** @brief Unsigned integer wide enough to hold any pointer value. */
    using uptr = uintptr_t;

    /** @brief Signed integer wide enough to hold any pointer value. */
    using iptr = intptr_t;

    /** @brief Alias for u8, emphasizing a raw memory byte. */
    using byte = uint8_t;

    /** @} */


    /* ========================================================================
     * @defgroup AXM_FLOATING_POINT Floating-Point Types
     * @brief IEEE 754 floating-point types and extended precision.
     *
     * @details
     * **f32:** IEEE 754 binary32 (single precision, 32 bits).
     *   - ~7 significant decimal digits
     *   - Range: ±3.4 × 10^38
     *   - **Use for:** graphics, audio, GPU compute, when bandwidth matters
     *   - Lower precision but half the memory of f64
     *
     * **f64:** IEEE 754 binary64 (double precision, 64 bits).
     *   - ~15 significant decimal digits
     *   - Range: ±1.8 × 10^308
     *   - **Use for:** physics, finance, scientific computing
     *   - Default for most numerical algorithms
     *
     * **f80:** Extended precision (x87 typically 10 bytes, platform-dependent).
     *   - **WARNING:** Portability is poor. Not portable across platforms.
     *   - May not exist, may be == f64, or may be 128-bit on some ABIs.
     *   - Only use for x87-specific code or legacy math libraries.
     *   - Falls back to f64 on platforms without extended precision.
     *
     * **Note:** long double was intentionally excluded from original Types.h
     *   because its size varies wildly. f80 provides an explicit extended-precision
     *   alternative when truly needed, with awareness of portability issues.
     *
     * @{
     * ======================================================================== */

    /** @brief IEEE 754 single-precision floating-point (32 bits).
     *  ~7 decimal digits, ±3.4 × 10^38. */
    using f32 = float;

    /** @brief IEEE 754 double-precision floating-point (64 bits).
     *  ~15 decimal digits, ±1.8 × 10^308. */
    using f64 = double;

/** @brief Extended-precision floating-point (x87 extended, ~10–16 bytes).
 *  @warning Portability is poor. May not exist, may equal f64, or be 128-bit.
 *  Only use for x87-specific code or when legacy math libraries require it.
 *  Automatically falls back to f64 on non-x87 or unsupported platforms. */
#if defined(__SIZEOF_LONG_DOUBLE__) && __SIZEOF_LONG_DOUBLE__ >= 10
    using f80 = long double;
#elif defined(AXM_ARCH_X86) || defined(AXM_ARCH_X64)
    using f80 = long double;
#else
    using f80 = double; /* Fallback: extended precision not available */
#endif

    /** @} */


    /* ========================================================================
     * @defgroup AXM_BOOLEAN Boolean Types
     * @brief Explicitly sized boolean values.
     *
     * @details
     * **b8:** Single byte (u8), used in packed structs and arrays.
     * **b32:** Four bytes (u32), matches graphics/OS API boolean sizes.
     *
     * @note Neither type enforces canonical 0/1 values; compiler does not
     *       check that non-zero values are valid booleans. When receiving
     *       untrusted boolean data, normalize with !!x before using.
     *
     * @code
     * AXM_PACKED_BEGIN
     * struct Flags {
     *     b8 visible;   // 1 byte
     *     b8 enabled;   // 1 byte
     * } AXM_PACKED AXM_PACKED_END;  // Total 2 bytes, not 8
     *
     * // For graphics APIs expecting 32-bit booleans
     * b32 vulkan_bool = VK_TRUE;  // Actually 1 (u32)
     * @endcode
     *
     * @{
     * ======================================================================== */

    /** @brief 8-bit boolean (single byte, suitable for packed structs). */
    using b8 = uint8_t;

    /** @brief 32-bit boolean (4 bytes, for graphics/OS APIs). */
    using b32 = uint32_t;

    /** @} */


    /* ========================================================================
     * @defgroup AXM_CHARACTER Character and String Unit Types
     * @brief Explicitly sized character types for text and Unicode.
     *
     * @details
     * **c8:** 8-bit char for UTF-8 and ASCII text (preferred for modern C++).
     * **c16:** 16-bit char for UTF-16 (Windows native, cross-platform interop).
     * **c32:** 32-bit char for UTF-32 (fixed-width code points).
     * **wc:** Platform-dependent wide char (usually 16-bit Windows, 32-bit Unix).
     *
     * **Recommendation:**
     * - New code: prefer **c8** for UTF-8 (modern standard)
     * - Unicode processing: **c32** for random-access code points
     * - Interop: **c16** for UTF-16, **wc** for platform-specific APIs only
     *
     * @code
     * // UTF-8 string (modern)
     * const c8* msg = "Hello, 世界";
     *
     * // UTF-32 for processing (each element is one code point)
     * std::vector<c32> codepoints;
     *
     * // Windows wide-character API (old-style, for legacy code)
     * LPCWSTR path = L"C:\\Users";  // wc* on Windows
     * @endcode
     *
     * @{
     * ======================================================================== */

    /** @brief 8-bit character (char), for UTF-8 and ASCII.
     *  Preferred for modern string literals and UTF-8 processing. */
    using c8 = char;

    /** @brief 16-bit character (char16_t), for UTF-16 strings. */
    using c16 = char16_t;

    /** @brief 32-bit character (char32_t), for UTF-32 strings.
     *  Fixed-width code points; ideal for random-access processing. */
    using c32 = char32_t;

    /** @brief Wide character (wchar_t), platform-dependent width.
     *  Usually 16-bit on Windows, 32-bit on Unix.
     *  Avoid in portable code; use c16 or c32 instead.
     *  Only use when required by OS APIs (Win32 W-functions). */
    using wc = wchar_t;

    /** @} */


    /* ========================================================================
     * @defgroup AXM_STATIC_ASSERTIONS Compile-Time Size Verification
     * @brief Verifies type sizes at compile time.
     *
     * @details
     * static_assert checks (C++11) or linker-level tricks (C++98) verify:
     * - Exact-width integers have the correct widths
     * - IEEE 754 floats are 4 and 8 bytes respectively
     * - Pointer-width types match pointer size
     *
     * If any check fails, compilation is halted with a clear diagnostic.
     * This catches ABI mismatches, misconfigured toolchains, and exotic
     * hardware without the expected integer widths.
     *
     * @{
     * ======================================================================== */

    /** @cond INTERNAL */

#if defined(AXM_HAS_CXX11)
    /** Verify exact-width unsigned integers. */
    static_assert(sizeof(u8) == 1, "AXM: u8  must be 1 byte");
    static_assert(sizeof(u16) == 2, "AXM: u16 must be 2 bytes");
    static_assert(sizeof(u32) == 4, "AXM: u32 must be 4 bytes");
    static_assert(sizeof(u64) == 8, "AXM: u64 must be 8 bytes");

    /** Verify exact-width signed integers. */
    static_assert(sizeof(i8) == 1, "AXM: i8  must be 1 byte");
    static_assert(sizeof(i16) == 2, "AXM: i16 must be 2 bytes");
    static_assert(sizeof(i32) == 4, "AXM: i32 must be 4 bytes");
    static_assert(sizeof(i64) == 8, "AXM: i64 must be 8 bytes");

    /** Verify IEEE 754 floating-point sizes. */
    static_assert(sizeof(f32) == 4, "AXM: f32 must be 4 bytes (IEEE 754 single)");
    static_assert(sizeof(f64) == 8, "AXM: f64 must be 8 bytes (IEEE 754 double)");

    /** Verify pointer-width types match pointer size. */
    static_assert(sizeof(usize) == sizeof(vptr), "AXM: usize must match pointer width");
    static_assert(sizeof(isize) == sizeof(vptr), "AXM: isize must match pointer width");
    static_assert(sizeof(uptr) == sizeof(vptr), "AXM: uptr must match pointer width");
    static_assert(sizeof(iptr) == sizeof(vptr), "AXM: iptr must match pointer width");

#endif

    /** @endcond */

    /** @} */

}

#endif
