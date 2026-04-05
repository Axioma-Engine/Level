/**
 * @file Attributes.h
 * @brief Compiler attribute macros for optimization, visibility, and warnings.
 *
 * @details
 * Provides portable, cross-compiler attribute definitions that abstract
 * away compiler-specific syntax differences. Unifies GCC/Clang attributes,
 * MSVC declspecs, and C++11 standard attributes into consistent macros.
 *
 * All attributes safely degrade to no-ops on compilers that don't support them.
 *
 * **Categories of attributes provided:**
 * - Visibility: AXM_EXPORT, AXM_IMPORT, AXM_LOCAL, AXM_API
 * - Inlining: AXM_FORCE_INLINE, AXM_NOINLINE
 * - Calling conventions: AXM_CDECL, AXM_STDCALL, AXM_FASTCALL
 * - Packing: AXM_PACKED, AXM_PACKED_BEGIN / AXM_PACKED_END
 * - Alignment: axmAlignAs(n), axmAlignOf(t), AXM_CACHE_ALIGN
 * - Function behavior: AXM_PURE, AXM_CONST, AXM_HOT, AXM_COLD
 * - Warnings: AXM_NODISCARD, AXM_MAYBE_UNUSED, AXM_DEPRECATED
 * - Memory: AXM_MALLOC, AXM_RETURNS_NONNULL
 * - Format strings: axmFormatPrintf, axmFormatScanf
 * - Linker: AXM_USED, AXM_WEAK, axmSection
 * - And more...
 *
 * **Example usage:**
 * @code
 * // Force inline for performance-critical function
 * AXM_FORCE_INLINE AXM_PURE int add(int a, int b) { return a + b; }
 *
 * // Packed structure for binary serialization
 * AXM_PACKED_BEGIN struct Message {
 *     uint8_t type;
 *     uint32_t size;
 * } AXM_PACKED AXM_PACKED_END;
 *
 * // Mark return value as important
 * AXM_NODISCARD int* allocate_buffer(size_t size);
 * @endcode
 *
 * @see Features.h - Feature detection predicates used by these definitions
 * @see System.h - Compiler detection macros
 */
#ifndef AXM_LVL_ATTRIBUTES_H
#define AXM_LVL_ATTRIBUTES_H
#pragma once

#include <Axiom/Features.h>
#include <Axiom/System.h>


/* ========================================================================
 * @defgroup AXM_VISIBILITY_ATTRIBUTES Symbol Visibility
 * @brief Controls symbol export/import for dynamic libraries.
 *
 * @details
 * Manages public/private symbol visibility in shared libraries.
 * On Windows, uses __declspec(dllexport/dllimport).
 * On Unix-like systems, uses __attribute__((visibility(...))) if available.
 *
 * **Usage:**
 * @code
 * // In public header
 * AXM_API void public_function();  // Exported
 * AXM_LOCAL void internal_function();  // Hidden
 *
 * // Define AXM_SHARED_BUILD when building the library
 * // (ensures symbols are exported, not imported)
 * @endcode
 *
 * @{
 * ======================================================================== */

#if defined(AXM_COMPILER_MSVC_LIKE) || defined(AXM_OS_WINDOWS)
/** @brief Declare a symbol for export from a shared library (Windows). */
#    define AXM_EXPORT __declspec(dllexport)
/** @brief Declare a symbol for import from a shared library (Windows). */
#    define AXM_IMPORT __declspec(dllimport)
/** @brief Hide a symbol from outside the shared library (Windows).
 *  On Windows, this is a no-op; use static instead. */
#    define AXM_LOCAL
#    if defined(AXM_SHARED_BUILD)
/** @brief Public API: export when building shared library, import when using it. */
#        define AXM_API __declspec(dllexport)
#    elif defined(AXM_STATIC_BUILD)
/** @brief Public API: empty when building static library. */
#        define AXM_API
#    else
/** @brief Public API: import when using shared library. */
#        define AXM_API __declspec(dllimport)
#    endif

#elif AXM_HAS_ATTRIBUTE(visibility)
/** @brief Declare a symbol for export (Unix-like systems). */
#    define AXM_EXPORT __attribute__((visibility("default")))
/** @brief Declare a symbol for import (Unix-like systems). */
#    define AXM_IMPORT __attribute__((visibility("default")))
/** @brief Hide a symbol from outside the shared library (Unix-like systems). */
#    define AXM_LOCAL  __attribute__((visibility("hidden")))
/** @brief Public API: visible by default (Unix-like systems). */
#    define AXM_API    __attribute__((visibility("default")))

#else
/** @brief Fallback: visibility control not supported. */
#    define AXM_EXPORT
/** @brief Fallback: visibility control not supported. */
#    define AXM_IMPORT
/** @brief Fallback: visibility control not supported. */
#    define AXM_LOCAL
/** @brief Fallback: visibility control not supported. */
#    define AXM_API
#endif

/** @} */


/* ========================================================================
 * @defgroup AXM_INLINE_ATTRIBUTES Inlining Control
 * @brief Suggests or prevents inline expansion of functions.
 *
 * @details
 * AXM_FORCE_INLINE requests aggressive inlining (use sparingly—only for
 * performance-critical, small functions). AXM_NOINLINE prevents inlining
 * (useful to preserve stack traces or reduce code size).
 *
 * @code
 * AXM_FORCE_INLINE int min(int a, int b) { return a < b ? a : b; }
 *
 * AXM_NOINLINE void debug_break_point() { }
 * @endcode
 *
 * @{
 * ======================================================================== */

#if defined(AXM_COMPILER_MSVC_LIKE)
/** @brief Force aggressive inlining (MSVC-style). */
#    define AXM_FORCE_INLINE __forceinline
/** @brief Prevent inlining (MSVC-style). */
#    define AXM_NOINLINE     __declspec(noinline)

#elif AXM_HAS_ATTRIBUTE(always_inline)
/** @brief Force aggressive inlining (GCC/Clang-style). */
#    define AXM_FORCE_INLINE __attribute__((always_inline)) inline
#    if AXM_HAS_ATTRIBUTE(noinline)
/** @brief Prevent inlining (GCC/Clang-style). */
#        define AXM_NOINLINE __attribute__((noinline))
#    else
/** @brief Fallback: noinline not available. */
#        define AXM_NOINLINE
#    endif

#else
/** @brief Generic C++ fallback: inline only. */
#    define AXM_FORCE_INLINE inline
/** @brief Generic C++ fallback: no noinline support. */
#    define AXM_NOINLINE
#endif

/** @} */


/* ========================================================================
 * @defgroup AXM_CALLING_CONVENTION Calling Conventions
 * @brief Specifies function calling convention (mostly x86 legacy).
 *
 * @details
 * Calling conventions (cdecl, stdcall, fastcall) are specific to x86 and
 * largely irrelevant on modern 64-bit systems or non-x86 architectures.
 * These macros are provided for compatibility with legacy C APIs.
 *
 * **Modern code should avoid these macros.**
 *
 * @{
 * ======================================================================== */

#if defined(AXM_COMPILER_MSVC_LIKE) || defined(AXM_OS_WINDOWS)
/** @brief __cdecl calling convention (C declaration, stack-based). */
#    define AXM_CDECL    __cdecl
/** @brief __stdcall calling convention (standard call, used by Win32 APIs). */
#    define AXM_STDCALL  __stdcall
/** @brief __fastcall calling convention (fast call, register-based). */
#    define AXM_FASTCALL __fastcall

#elif defined(AXM_ARCH_X86) && (defined(AXM_COMPILER_GCC_LIKE) || AXM_HAS_ATTRIBUTE(cdecl))
/** @brief __cdecl calling convention (GCC attribute syntax). */
#    define AXM_CDECL    __attribute__((cdecl))
/** @brief __stdcall calling convention (GCC attribute syntax). */
#    define AXM_STDCALL  __attribute__((stdcall))
/** @brief __fastcall calling convention (GCC attribute syntax). */
#    define AXM_FASTCALL __attribute__((fastcall))

#else
/** @brief Calling conventions not applicable or not supported. */
#    define AXM_CDECL
/** @brief Calling conventions not applicable or not supported. */
#    define AXM_STDCALL
/** @brief Calling conventions not applicable or not supported. */
#    define AXM_FASTCALL
#endif

/** @} */


/* ========================================================================
 * @defgroup AXM_PACKING_ATTRIBUTES Structure Packing
 * @brief Controls struct member packing and padding.
 *
 * @details
 * Use to create tightly packed structures for binary serialization or
 * memory mapping.
 *
 * **MSVC/Borland/Watcom syntax:**
 * @code
 * AXM_PACKED_BEGIN
 * struct Message {
 *     uint8_t type;
 *     uint32_t id;
 * } AXM_PACKED;
 * AXM_PACKED_END
 * @endcode
 *
 * **GCC/Clang syntax (same result):**
 * @code
 * struct Message {
 *     uint8_t type;
 *     uint32_t id;
 * } AXM_PACKED;
 * @endcode
 *
 * @{
 * ======================================================================== */

#if defined(AXM_COMPILER_MSVC_LIKE)
/** @brief Begin a packed structure region (MSVC). */
#    define AXM_PACKED_BEGIN __pragma(pack(push, 1))
/** @brief End a packed structure region (MSVC). */
#    define AXM_PACKED_END   __pragma(pack(pop))
/** @brief Mark a struct member or struct as packed (MSVC). */
#    define AXM_PACKED

#elif AXM_HAS_ATTRIBUTE(packed)
/** @brief Begin a packed structure region (GCC/Clang). */
#    define AXM_PACKED_BEGIN
/** @brief End a packed structure region (GCC/Clang). */
#    define AXM_PACKED_END
/** @brief Mark a struct member or struct as packed (GCC/Clang). */
#    define AXM_PACKED __attribute__((packed))

#elif defined(AXM_COMPILER_BORLAND)
/** @brief Begin a packed structure region (Borland). */
#    define AXM_PACKED_BEGIN __pragma(pack(push, 1))
/** @brief End a packed structure region (Borland). */
#    define AXM_PACKED_END   __pragma(pack(pop))
/** @brief Mark a struct member or struct as packed (Borland). */
#    define AXM_PACKED

#elif defined(AXM_COMPILER_WATCOM)
/** @brief Begin a packed structure region (Watcom). */
#    define AXM_PACKED_BEGIN _Pragma("pack(1)")
/** @brief End a packed structure region (Watcom). */
#    define AXM_PACKED_END   _Pragma("pack()")
/** @brief Mark a struct as packed (Watcom) - uses _Packed keyword. */
#    define AXM_PACKED       _Packed

#else
/** @brief Fallback: packing not supported. */
#    define AXM_PACKED_BEGIN
/** @brief Fallback: packing not supported. */
#    define AXM_PACKED_END
/** @brief Fallback: packing not supported. */
#    define AXM_PACKED
#endif

/** @} */


/* ========================================================================
 * @defgroup AXM_ALIGNMENT_ATTRIBUTES Memory Alignment
 * @brief Controls memory alignment of objects.
 *
 * @details
 * Use to create cache-aligned arrays or over-aligned structures.
 *
 * @code
 * // Cache-line aligned data
 * AXM_CACHE_ALIGN uint8_t buffer[4096];
 *
 * // Custom alignment
 * struct Aligned {
 *     axmAlignAs(16) float data[4];  // SSE register-aligned
 * };
 *
 * // Query alignment of a type
 * size_t sz = axmAlignOf(double);
 * @endcode
 *
 * @{
 * ======================================================================== */

#if defined(AXM_HAS_CXX11)
/** @brief Align a variable or struct to at least N bytes (C++11 style). */
#    define axmAlignAs(n) alignas(n)
/** @brief Query the alignment requirement of a type (C++11 style). */
#    define axmAlignOf(t) alignof(t)

#elif defined(AXM_COMPILER_MSVC_LIKE)
/** @brief Align a variable or struct to at least N bytes (MSVC style). */
#    define axmAlignAs(n) __declspec(align(n))
/** @brief Query the alignment requirement of a type (MSVC style). */
#    define axmAlignOf(t) __alignof(t)

#elif AXM_HAS_ATTRIBUTE(aligned)
/** @brief Align a variable or struct to at least N bytes (GCC/Clang style). */
#    define axmAlignAs(n) __attribute__((aligned(n)))
/** @brief Query the alignment requirement of a type (GCC/Clang style). */
#    define axmAlignOf(t) __alignof__(t)

#else
/** @brief Fallback: alignment control not available. */
#    define axmAlignAs(n)
/** @brief Fallback: alignment control not available. */
#    define axmAlignOf(t) sizeof(t)
#endif

/** @brief CPU cache line size, typically 64 bytes on modern systems. */
#define AXM_CACHE_LINE_SIZE 64

/** @brief Align to cache line size for SIMD and lock-free data structures. */
#define AXM_CACHE_ALIGN axmAlignAs(AXM_CACHE_LINE_SIZE)

/** @} */


/* ========================================================================
 * @defgroup AXM_DIAGNOSTIC_ATTRIBUTES Compiler Diagnostics
 * @brief Attributes for warnings and compiler diagnostics.
 *
 * @details
 * Helps the compiler warn about misuse: ignoring return values, unused
 * variables, deprecated functions, etc.
 *
 * @{
 * ======================================================================== */

/** @brief Mark return value as important to not ignore.
 *
 * Compiler warns if the return value is discarded.
 * @code
 * AXM_NODISCARD int compute_value();
 * @endcode
 */
#if AXM_HAS_CPP_ATTRIBUTE(nodiscard)
/** @brief Mark return value as [[nodiscard]] (C++17). */
#    define AXM_NODISCARD        [[nodiscard]]
/** @brief Mark return value as [[nodiscard(msg)]] with custom message (C++20). */
#    define axmNoDiscardMsg(msg) [[nodiscard(msg)]]

#elif AXM_HAS_ATTRIBUTE(warn_unused_result)
/** @brief Mark return value with __attribute__((warn_unused_result)). */
#    define AXM_NODISCARD        __attribute__((warn_unused_result))
/** @brief Mark return value with __attribute__((warn_unused_result)) (message ignored). */
#    define axmNoDiscardMsg(msg) __attribute__((warn_unused_result))

#else
/** @brief Fallback: nodiscard not supported. */
#    define AXM_NODISCARD
/** @brief Fallback: nodiscard with message not supported. */
#    define axmNoDiscardMsg(msg)
#endif

/** @brief Mark a variable as intentionally unused.
 *
 * Suppresses compiler warnings about unused parameters or variables.
 * @code
 * void handler(AXM_MAYBE_UNUSED int unused_arg) { }
 * @endcode
 */
#if AXM_HAS_CPP_ATTRIBUTE(maybe_unused)
/** @brief Mark variable as [[maybe_unused]] (C++17). */
#    define AXM_MAYBE_UNUSED [[maybe_unused]]

#elif AXM_HAS_ATTRIBUTE(unused)
/** @brief Mark variable with __attribute__((unused)). */
#    define AXM_MAYBE_UNUSED __attribute__((unused))

#else
/** @brief Fallback: maybe_unused not supported. */
#    define AXM_MAYBE_UNUSED
#endif

/** @brief Mark a function or symbol as deprecated.
 *
 * Compiler warns when deprecated code is used.
 * @code
 * AXM_DEPRECATED void old_function();
 * axmDeprecatedMsg("Use new_function() instead") void legacy();
 * @endcode
 */
#if AXM_HAS_CPP_ATTRIBUTE(deprecated)
/** @brief Mark as [[deprecated]] (C++14). */
#    define AXM_DEPRECATED        [[deprecated]]
/** @brief Mark as [[deprecated(msg)]] (C++14). */
#    define axmDeprecatedMsg(msg) [[deprecated(msg)]]

#elif AXM_HAS_ATTRIBUTE(deprecated)
/** @brief Mark with __attribute__((deprecated)). */
#    define AXM_DEPRECATED        __attribute__((deprecated))
/** @brief Mark with __attribute__((deprecated(msg))). */
#    define axmDeprecatedMsg(msg) __attribute__((deprecated(msg)))

#elif defined(AXM_COMPILER_MSVC_LIKE)
/** @brief Mark with __declspec(deprecated). */
#    define AXM_DEPRECATED        __declspec(deprecated)
/** @brief Mark with __declspec(deprecated(msg)). */
#    define axmDeprecatedMsg(msg) __declspec(deprecated(msg))

#else
/** @brief Fallback: deprecated not supported. */
#    define AXM_DEPRECATED
/** @brief Fallback: deprecated with message not supported. */
#    define axmDeprecatedMsg(msg)
#endif

/** @brief Mark intentional fall-through in a switch statement.
 *
 * Suppresses compiler warnings about missing break in switch cases.
 * @code
 * switch (x) {
 *     case 1:
 *         handle_first();
 *         AXM_FALLTHROUGH;
 *     case 2:
 *         handle_both();
 *         break;
 * }
 * @endcode
 */
#if AXM_HAS_CPP_ATTRIBUTE(fallthrough)
/** @brief Mark fall-through with [[fallthrough]] (C++17). */
#    define AXM_FALLTHROUGH [[fallthrough]]

#elif AXM_HAS_ATTRIBUTE(fallthrough)
/** @brief Mark fall-through with __attribute__((fallthrough)). */
#    define AXM_FALLTHROUGH __attribute__((fallthrough))

#else
/** @brief Fallback: empty do-while loop as no-op. */
#    define AXM_FALLTHROUGH                                                                        \
        do {                                                                                       \
        } while (false)
#endif

/** @brief Mark a function as never returning (exits, throws, infinite loop).
 *
 * @code
 * AXM_NORETURN void fatal_error(const char* msg) {
 *     fprintf(stderr, "%s\n", msg);
 *     exit(1);
 * }
 * @endcode
 */
#if AXM_HAS_CPP_ATTRIBUTE(noreturn)
/** @brief Mark as [[noreturn]] (C++11). */
#    define AXM_NORETURN [[noreturn]]

#elif AXM_HAS_ATTRIBUTE(noreturn)
/** @brief Mark with __attribute__((noreturn)). */
#    define AXM_NORETURN __attribute__((noreturn))

#elif defined(AXM_COMPILER_MSVC_LIKE)
/** @brief Mark with __declspec(noreturn). */
#    define AXM_NORETURN __declspec(noreturn)

#else
/** @brief Fallback: noreturn not supported. */
#    define AXM_NORETURN
#endif

/** @} */


/* ========================================================================
 * @defgroup AXM_STORAGE_ATTRIBUTES Storage and Member Layout
 * @brief Controls object storage class and member packing.
 *
 * @details
 * Attributes for thread-local storage, empty base optimization, etc.
 *
 * @{
 * ======================================================================== */

/** @brief Allow zero-overhead optimization of empty member bases.
 *
 * Permits the compiler to place an empty member at the same address as
 * the start of the object (C++20 no_unique_address).
 * @code
 * struct Wrapper {
 *     AXM_NO_UNIQUE_ADDRESS Empty empty;  // May share space
 *     int value;
 * };
 * @endcode
 */
#if AXM_HAS_CPP_ATTRIBUTE(no_unique_address)
/** @brief Apply [[no_unique_address]] (C++20). */
#    define AXM_NO_UNIQUE_ADDRESS [[no_unique_address]]

#elif defined(AXM_COMPILER_MSVC_LIKE) && AXM_HAS_CPP_ATTRIBUTE(msvc::no_unique_address)
/** @brief Apply [[msvc::no_unique_address]] (MSVC extension). */
#    define AXM_NO_UNIQUE_ADDRESS [[msvc::no_unique_address]]

#else
/** @brief Fallback: no_unique_address not supported. */
#    define AXM_NO_UNIQUE_ADDRESS
#endif

/** @brief Mark a variable as thread-local storage.
 *
 * Each thread gets its own copy of the variable.
 * @code
 * AXM_THREAD_LOCAL static int thread_counter = 0;
 * @endcode
 */
#if defined(AXM_HAS_CXX11)
/** @brief Thread-local storage (C++11). */
#    define AXM_THREAD_LOCAL thread_local

#elif defined(AXM_COMPILER_MSVC_LIKE)
/** @brief Thread-local storage (MSVC). */
#    define AXM_THREAD_LOCAL __declspec(thread)

#elif AXM_HAS_ATTRIBUTE(__thread) || defined(AXM_COMPILER_GCC_LIKE)
/** @brief Thread-local storage (GCC/Clang __thread). */
#    define AXM_THREAD_LOCAL __thread

#else
/** @brief Fallback: thread-local not supported. */
#    define AXM_THREAD_LOCAL
#endif

/** @} */


/* ========================================================================
 * @defgroup AXM_POINTER_ATTRIBUTES Pointer and Reference Attributes
 * @brief Attributes for pointer-related optimizations and safety.
 *
 * @details
 * Helps compiler optimize pointer accesses and warn about unsafe patterns.
 *
 * @{
 * ======================================================================== */

/** @brief Pointer qualifies for strict aliasing and type-based alias analysis.
 *
 * Tells compiler that this pointer doesn't alias other pointers (or only
 * those of compatible types). Enables aggressive optimization.
 * @code
 * void copy(int AXM_RESTRICT* dst, int AXM_RESTRICT* src, size_t n);
 * @endcode
 */
#if defined(AXM_COMPILER_MSVC_LIKE)
/** @brief Restrict keyword (MSVC __restrict). */
#    define AXM_RESTRICT __restrict

#elif defined(AXM_COMPILER_GCC_LIKE)
/** @brief Restrict keyword (GCC __restrict__). */
#    define AXM_RESTRICT __restrict__

#elif defined(AXM_COMPILER_SUNPRO)
/** @brief Sun Studio: restrict support available. */
#    define AXM_RESTRICT _Restrict

#else
/** @brief Fallback: restrict not available. */
#    define AXM_RESTRICT
#endif

/** @brief Pointer is allowed to alias any type (defeats strict aliasing).
 *
 * Used for type-punning and generic memory access where strict aliasing
 * rules would otherwise trigger undefined behavior.
 */
#if AXM_HAS_ATTRIBUTE(may_alias)
/** @brief Mark pointer with __attribute__((may_alias)). */
#    define AXM_MAY_ALIAS __attribute__((may_alias))

#else
/** @brief Fallback: may_alias not supported. */
#    define AXM_MAY_ALIAS
#endif

/** @} */


/* ========================================================================
 * @defgroup AXM_FUNCTION_ATTRIBUTES Function Behavior
 * @brief Describes function side effects for compiler optimization.
 *
 * @details
 * Helps compiler perform better optimization and data flow analysis.
 *
 * @{
 * ======================================================================== */

/** @brief Function has no side effects except through parameters and return value.
 *
 * Compiler may call this function fewer times and cache results.
 * @code
 * AXM_PURE int strlen_cached(const char* s);
 * @endcode
 */
#if AXM_HAS_ATTRIBUTE(pure)
/** @brief Mark with __attribute__((pure)). */
#    define AXM_PURE __attribute__((pure))

#else
/** @brief Fallback: pure not supported. */
#    define AXM_PURE
#endif

/** @brief Function depends only on its parameters (no global state access).
 *
 * Stronger than AXM_PURE: no memory reads except parameters.
 * @code
 * AXM_CONST int max(int a, int b) { return a > b ? a : b; }
 * @endcode
 */
#if AXM_HAS_ATTRIBUTE(const)
/** @brief Mark with __attribute__((const)). */
#    define AXM_CONST __attribute__((const))

#else
/** @brief Fallback: const not supported. */
#    define AXM_CONST
#endif

/** @brief Function is performance-critical; optimize aggressively.
 *
 * Compiler may spend extra effort optimizing this function.
 * @code
 * AXM_HOT void fast_inner_loop() { }
 * @endcode
 */
#if AXM_HAS_ATTRIBUTE(hot)
/** @brief Mark with __attribute__((hot)). */
#    define AXM_HOT __attribute__((hot))

#else
/** @brief Fallback: hot not supported. */
#    define AXM_HOT
#endif

/** @brief Function is rarely executed; optimize for code size.
 *
 * Compiler may prefer smaller code over speed for this function.
 * @code
 * AXM_COLD void error_path() { }
 * @endcode
 */
#if AXM_HAS_ATTRIBUTE(cold)
/** @brief Mark with __attribute__((cold)). */
#    define AXM_COLD __attribute__((cold))

#else
/** @brief Fallback: cold not supported. */
#    define AXM_COLD
#endif

/** @} */


/* ========================================================================
 * @defgroup AXM_MEMORY_ATTRIBUTES Memory Management
 * @brief Attributes for heap allocation and deallocation.
 *
 * @details
 * Helps compiler track lifetime and size of dynamically allocated memory.
 *
 * @{
 * ======================================================================== */

/** @brief Function returns a newly allocated pointer (like malloc).
 *
 * Pointer is not aliased by any existing pointer.
 * @code
 * AXM_MALLOC AXM_RETURNS_NONNULL void* my_malloc(size_t size);
 * @endcode
 */
#if AXM_HAS_ATTRIBUTE(malloc)
/** @brief Mark with __attribute__((malloc)). */
#    define AXM_MALLOC __attribute__((malloc))

#else
/** @brief Fallback: malloc not supported. */
#    define AXM_MALLOC
#endif

/** @brief Parameter N specifies the allocation size.
 *
 * Used for allocation size analysis and bounds checking.
 * @code
 * axmAllocSize(1) void* allocate(size_t size);
 * axmAllocSize2(1, 2) void* allocate_2d(size_t rows, size_t cols);
 * @endcode
 */
#if AXM_HAS_ATTRIBUTE(alloc_size)
/** @brief Mark allocation size (single parameter). */
#    define axmAllocSize(idx)        __attribute__((alloc_size(idx)))
/** @brief Mark allocation size (two parameters: rows, cols). */
#    define axmAllocSize2(idx, idx2) __attribute__((alloc_size(idx, idx2)))

#else
/** @brief Fallback: alloc_size not supported. */
#    define axmAllocSize(idx)
/** @brief Fallback: alloc_size not supported. */
#    define axmAllocSize2(idx, idx2)
#endif

/** @brief Parameter N specifies the alignment of allocated memory.
 *
 * @code
 * axmAllocAlign(1) void* aligned_alloc(size_t align, size_t size);
 * @endcode
 */
#if AXM_HAS_ATTRIBUTE(alloc_align)
/** @brief Mark allocation alignment parameter. */
#    define axmAllocAlign(idx) __attribute__((alloc_align(idx)))

#else
/** @brief Fallback: alloc_align not supported. */
#    define axmAllocAlign(idx)
#endif

/** @brief Function always returns a non-NULL pointer.
 *
 * Compiler assumes pointer is not null and omits checks.
 * @code
 * AXM_RETURNS_NONNULL int* get_buffer();
 * @endcode
 */
#if AXM_HAS_ATTRIBUTE(returns_nonnull)
/** @brief Mark with __attribute__((returns_nonnull)). */
#    define AXM_RETURNS_NONNULL __attribute__((returns_nonnull))

#else
/** @brief Fallback: returns_nonnull not supported. */
#    define AXM_RETURNS_NONNULL
#endif

/** @} */


/* ========================================================================
 * @defgroup AXM_FORMAT_ATTRIBUTES Format String Attributes
 * @brief Enables format string validation for printf/scanf-like functions.
 *
 * @details
 * Compiler checks format string and arguments for mismatches.
 *
 * @{
 * ======================================================================== */

/** @brief Function takes a printf-style format string.
 *
 * Format string is parameter fmt; first argument parameter is args.
 * @code
 * axmFormatPrintf(1, 2) void log_msg(const char* fmt, ...);
 * @endcode
 */
#if AXM_HAS_ATTRIBUTE(format)
/** @brief Enable printf format string checking. */
#    define axmFormatPrintf(fmt, args) __attribute__((format(printf, fmt, args)))
/** @brief Enable scanf format string checking. */
#    define axmFormatScanf(fmt, args)  __attribute__((format(scanf, fmt, args)))

#else
/** @brief Fallback: format not supported. */
#    define axmFormatPrintf(fmt, args)
/** @brief Fallback: format not supported. */
#    define axmFormatScanf(fmt, args)
#endif

/** @brief Specified pointer parameters must not be NULL.
 *
 * Compiler warns if NULL is passed and omits null checks.
 * @code
 * axmNonnull(1, 2) void process(int* a, int* b);
 * AXM_NONNULL_ALL void critical_function(int* a, int* b, int* c);
 * @endcode
 */
#if AXM_HAS_ATTRIBUTE(nonnull)
/** @brief Mark specific parameters as non-null. */
#    define axmNonnull(...) __attribute__((nonnull(__VA_ARGS__)))
/** @brief Mark all pointer parameters as non-null. */
#    define AXM_NONNULL_ALL __attribute__((nonnull))

#else
/** @brief Fallback: nonnull not supported. */
#    define axmNonnull(...)
/** @brief Fallback: nonnull not supported. */
#    define AXM_NONNULL_ALL
#endif

/** @} */


/* ========================================================================
 * @defgroup AXM_LINKER_ATTRIBUTES Linker and Section Attributes
 * @brief Controls how symbols are linked and placed in memory.
 *
 * @details
 * Place code/data in specific sections, mark as used, make weak, etc.
 *
 * @{
 * ======================================================================== */

/** @brief Place symbol in a specific linker section.
 *
 * Useful for grouping initialization code, placing data in specific regions, etc.
 * @code
 * axmSection(".preinit_array") void* init_func = &initialize;
 * @endcode
 */
#if AXM_HAS_ATTRIBUTE(section)
/** @brief Place in section (GCC/Clang). */
#    define axmSection(name) __attribute__((section(name)))

#elif defined(AXM_COMPILER_MSVC_LIKE)
/** @brief Place in section (MSVC). */
#    define axmSection(name) __declspec(allocate(name))

#else
/** @brief Fallback: section not supported. */
#    define axmSection(name)
#endif

/** @brief Prevent linker from discarding this symbol (even if unused).
 *
 * Useful for module registration and metadata structures.
 * @code
 * AXM_USED static const Module modules[] = { };
 * @endcode
 */
#if AXM_HAS_ATTRIBUTE(used)
/** @brief Mark with __attribute__((used)). */
#    define AXM_USED __attribute__((used))

#else
/** @brief Fallback: used not supported. */
#    define AXM_USED
#endif

/** @brief Define a weak symbol that may be overridden at link time.
 *
 * Allows application or other libraries to provide alternative implementations.
 * @code
 * AXM_WEAK void default_handler() { }
 * @endcode
 */
#if AXM_HAS_ATTRIBUTE(weak)
/** @brief Define weak symbol (GCC/Clang). */
#    define AXM_WEAK __attribute__((weak))

#elif defined(AXM_COMPILER_MSVC_LIKE)
/** @brief Define weak symbol (MSVC). */
#    define AXM_WEAK __declspec(selectany)

#else
/** @brief Fallback: weak not supported. */
#    define AXM_WEAK
#endif

/** @} */


/* ========================================================================
 * @defgroup AXM_BRANCH_HINTS Branch Prediction Hints
 * @brief Provides hints to the branch predictor.
 *
 * @details
 * Helps CPU's branch predictor by hinting which branch is more likely.
 * Use sparingly—profiling data is more reliable than guessing.
 *
 * @{
 * ======================================================================== */

/** @brief Hint that a condition is likely true (likely branch).
 *
 * @code
 * if (axmLikely(ptr != nullptr)) {
 *     // This branch is usually taken
 * }
 * @endcode
 */
#if AXM_HAS_BUILTIN(__builtin_expect)
/** @brief Hint likely condition using __builtin_expect. */
#    define axmLikely(expr)   (__builtin_expect(!!(expr), 1))
/** @brief Hint unlikely condition using __builtin_expect. */
#    define axmUnlikely(expr) (__builtin_expect(!!(expr), 0))

#else
/** @brief Fallback: branch hints not available. */
#    define axmLikely(expr)   (!!(expr))
/** @brief Fallback: branch hints not available. */
#    define axmUnlikely(expr) (!!(expr))
#endif

/** @} */

#endif
