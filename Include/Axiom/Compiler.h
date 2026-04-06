/**
 * @file Compiler.h
 * @brief Portable compiler portability layer: capability queries, declaration
 *        attributes, branch hints, and unreachable/assume primitives.
 *
 * @details
 * This header sits directly on top of System.h and adds everything needed
 * to write portable, well-annotated declarations and optimisation hints
 * without scattering raw compiler-specific syntax through the codebase.
 *
 * It is intentionally free of system includes — nothing here pulls in
 * \<cstdio\>, \<intrin.h\>, or any other heavyweight header.
 *
 * **Capability Queries (AXM_HAS_ATTRIBUTE, AXM_HAS_BUILTIN, ...):**
 *   Uniform wrappers for the __has_*() introspection predicates that
 *   System.h does not provide. Every other section in this file uses
 *   these rather than writing raw `#if defined(__has_attribute)` guards.
 *   They degrade gracefully to 0 on compilers that lack the predicate.
 *
 * **Inlining (AXM_FORCE_INLINE, AXM_NOINLINE):**
 *   Force or suppress inlining independently of the compiler's cost heuristic.
 *
 * **Symbol Visibility (AXM_EXPORT, AXM_IMPORT, AXM_LOCAL, AXM_API):**
 *   Controls shared-library ABI boundaries. AXM_API resolves to AXM_EXPORT
 *   for shared builds (AXM_SHARED_BUILD), empty for static builds
 *   (AXM_STATIC_BUILD), and AXM_IMPORT otherwise.
 *
 * **Calling Conventions (AXM_CDECL, AXM_STDCALL, AXM_FASTCALL):**
 *   Meaningful only on x86 32-bit; expand to nothing on all other targets.
 *
 * **Struct Layout (AXM_PACKED_*, AXM_ALIGNAS, AXM_ALIGNOF, AXM_CACHE_ALIGN):**
 *   Portable packing and alignment control for structs and variables.
 *
 * **Standard Attributes (AXM_NODISCARD, AXM_MAYBE_UNUSED, AXM_DEPRECATED,
 *   AXM_FALLTHROUGH, AXM_NORETURN, AXM_NO_UNIQUE_ADDRESS):**
 *   Portable wrappers for C++ standard [[attributes]] with GCC/MSVC fallbacks.
 *
 * **Storage (AXM_THREAD_LOCAL):**
 *   One independent instance of the annotated variable per thread.
 *
 * **Pointer Semantics (AXM_RESTRICT, AXM_MAY_ALIAS):**
 *   Aliasing contracts that unlock auto-vectorisation and suppress
 *   strict-aliasing reloads.
 *
 * **Function Optimisation (AXM_PURE, AXM_CONST, AXM_HOT, AXM_COLD):**
 *   Hints that inform the compiler about side-effect freedom and call-site
 *   frequency to guide inlining, CSE, and code-layout decisions.
 *
 * **Allocation Hints (AXM_MALLOC, axmAllocSize, axmAllocAlign,
 *   AXM_RETURNS_NONNULL):**
 *   Annotate allocator-like functions so the compiler can track object sizes
 *   and elide redundant null checks.
 *
 * **Static Analysis (axmFormatPrintf, axmFormatScanf, axmNonnull,
 *   AXM_NONNULL_ALL):**
 *   Enable -Wformat and -Wnonnull diagnostics on custom wrapper functions.
 *
 * **Linkage Extras (axmSection, AXM_USED, AXM_WEAK):**
 *   Place symbols in named sections, retain unreferenced symbols, or emit
 *   with weak linkage for overridable defaults.
 *
 * **Branch Hints (AXM_LIKELY, AXM_UNLIKELY):**
 *   Communicate expected branch outcomes to the compiler and CPU's branch
 *   predictor without changing semantics.
 *
 * **Unreachable / Assume (AXM_UNREACHABLE, axmAssume):**
 *   Mark provably dead code paths and supply invariants that the optimiser
 *   may exploit without runtime cost.
 *
 * **Function Name (AXM_FUNC_NAME, AXM_FUNC_SIG, AXM_LINE):**
 *   Portable access to the current function's undecorated name and full
 *   decorated signature for use in diagnostics and logging.
 *
 * **Loop Pragmas (AXM_PRAGMA_UNROLL, AXM_PRAGMA_VECTORIZE, ...):**
 *   Per-loop optimisation directives; silently ignored on unsupported compilers.
 *
 * **Stringify (AXM_STRINGIFY, AXM_SOURCE_LOCATION):**
 *   Token-to-string conversion and source-location string literals for
 *   diagnostic messages and static assertions.
 *
 * @see System.h  - Platform and compiler detection macros
 * @see Types.h   - Portable type aliases
 */

#ifndef AXM_LVL_COMPILER_H
#define AXM_LVL_COMPILER_H
#pragma once

#include <Axiom/System.h>


/**
 * @defgroup AXM_CAPABILITY_QUERIES Capability Queries
 * @brief Uniform wrappers for compiler introspection predicates.
 *
 * @details
 * Use these everywhere instead of writing raw `#if defined(__has_attribute)`
 * guards — they degrade gracefully to 0 on compilers that do not implement
 * the underlying predicate.
 *
 * - **AXM_HAS_ATTRIBUTE(x)** — `__attribute__((x))` is accepted.
 * - **AXM_HAS_BUILTIN(x)** — `__builtin_x` is available. On GCC without
 *   `__has_builtin`, conservatively returns 1 because GCC exposes most
 *   builtins without a predicate.
 * - **AXM_HAS_FEATURE(x)** — Clang `__has_feature()` query; always 0 on
 *   non-Clang compilers.
 * - **AXM_HAS_EXTENSION(x)** — Clang `__has_extension()` query; falls back
 *   to AXM_HAS_FEATURE when absent.
 * - **AXM_HAS_CPP_ATTRIBUTE(x)** — `[[x]]` is a recognised C++ attribute.
 * - **AXM_HAS_INCLUDE(x)** — `#include x` would succeed.
 * - **AXM_HAS_DECLSPEC(x)** — `__declspec(x)` is accepted.
 *
 * @{
 */
#if defined(__has_attribute)
#    define AXM_HAS_ATTRIBUTE(x) __has_attribute(x)
#else
#    define AXM_HAS_ATTRIBUTE(x) 0
#endif

#if defined(__has_builtin)
#    define AXM_HAS_BUILTIN(x) __has_builtin(x)
#elif defined(AXM_COMPILER_GCC)
#    define AXM_HAS_BUILTIN(x) 1
#else
#    define AXM_HAS_BUILTIN(x) 0
#endif

#if defined(__has_feature)
#    define AXM_HAS_FEATURE(x) __has_feature(x)
#else
#    define AXM_HAS_FEATURE(x) 0
#endif

#if defined(__has_extension)
#    define AXM_HAS_EXTENSION(x) __has_extension(x)
#else
#    define AXM_HAS_EXTENSION(x) AXM_HAS_FEATURE(x)
#endif

#if defined(__has_cpp_attribute)
#    define AXM_HAS_CPP_ATTRIBUTE(x) __has_cpp_attribute(x)
#else
#    define AXM_HAS_CPP_ATTRIBUTE(x) 0
#endif

#if defined(__has_include)
#    define AXM_HAS_INCLUDE(x)          __has_include(x)
#else
#    define AXM_HAS_INCLUDE(x) 0
#endif

#if defined(__has_declspec_attribute)
#    define AXM_HAS_DECLSPEC(x) __has_declspec_attribute(x)
#elif defined(AXM_COMPILER_MSVC_LIKE)
#    define AXM_HAS_DECLSPEC(x) 1
#else
#    define AXM_HAS_DECLSPEC(x) 0
#endif
/** @} */


/**
 * @defgroup AXM_INLINING Inlining
 * @brief Force or suppress function inlining.
 *
 * @details
 * - **AXM_FORCE_INLINE** — Always inline, bypassing the compiler's cost
 *   heuristic. Reserve for tiny hot functions where the call overhead is
 *   measurably significant.
 * - **AXM_NOINLINE** — Never inline. Use for large cold functions and error
 *   paths that must appear in stack traces.
 *
 * @{
 */
#if defined(AXM_COMPILER_MSVC_LIKE)
#    define AXM_FORCE_INLINE __forceinline
#    define AXM_NOINLINE     __declspec(noinline)
#elif AXM_HAS_ATTRIBUTE(always_inline)
#    define AXM_FORCE_INLINE __attribute__((always_inline)) inline
#    if AXM_HAS_ATTRIBUTE(noinline)
#        define AXM_NOINLINE __attribute__((noinline))
#    else
#        define AXM_NOINLINE
#    endif
#else
#    define AXM_FORCE_INLINE inline
#    define AXM_NOINLINE
#endif
/** @} */


/**
 * @defgroup AXM_SYMBOL_VISIBILITY Symbol Visibility
 * @brief Controls shared-library ABI boundaries.
 *
 * @details
 * - **AXM_EXPORT** — Part of the public shared-library ABI.
 * - **AXM_IMPORT** — Imported from a shared library.
 * - **AXM_LOCAL** — Hidden from the shared-library ABI (GCC/Clang only).
 * - **AXM_API** — Resolves based on build type:
 *   - `AXM_SHARED_BUILD` defined → AXM_EXPORT (building the shared library)
 *   - `AXM_STATIC_BUILD` defined → empty (no import/export decoration needed)
 *   - Neither defined → AXM_IMPORT (consuming the shared library)
 *
 * @code
 * // In shared-library build:   -DAXM_SHARED_BUILD
 * // In static-library build:   -DAXM_STATIC_BUILD
 * // In consumer build:         (neither flag)
 * AXM_API void myPublicFunction();
 * @endcode
 *
 * @{
 */
#if defined(AXM_COMPILER_MSVC_LIKE)
#    define AXM_EXPORT __declspec(dllexport)
#    define AXM_IMPORT __declspec(dllimport)
#    define AXM_LOCAL
#elif AXM_HAS_ATTRIBUTE(visibility)
#    define AXM_EXPORT __attribute__((visibility("default")))
#    define AXM_IMPORT __attribute__((visibility("default")))
#    define AXM_LOCAL  __attribute__((visibility("hidden")))
#else
#    define AXM_EXPORT
#    define AXM_IMPORT
#    define AXM_LOCAL
#endif

#ifndef AXM_API
#    if defined(AXM_SHARED_BUILD)
#        define AXM_API AXM_EXPORT
#    elif defined(AXM_STATIC_BUILD)
#        define AXM_API
#    else
#        define AXM_API AXM_IMPORT
#    endif
#endif
/** @} */


/**
 * @defgroup AXM_CALLING_CONVENTIONS Calling Conventions
 * @brief Portable calling-convention annotations.
 *
 * @details
 * Meaningful only on x86 32-bit targets; expand to nothing everywhere else
 * because the ABI fully specifies the convention on 64-bit and non-x86
 * architectures.
 *
 * - **AXM_CDECL** — Caller cleans the stack (default for C / variadic).
 * - **AXM_STDCALL** — Callee cleans the stack (default for Win32 APIs).
 * - **AXM_FASTCALL** — First two integer arguments passed in registers.
 *
 * @{
 */
#if defined(AXM_COMPILER_MSVC_LIKE) || defined(AXM_OS_WINDOWS)
#    define AXM_CDECL    __cdecl
#    define AXM_STDCALL  __stdcall
#    define AXM_FASTCALL __fastcall
#elif defined(AXM_ARCH_X86)
#    define AXM_CDECL    __attribute__((cdecl))
#    define AXM_STDCALL  __attribute__((stdcall))
#    define AXM_FASTCALL __attribute__((fastcall))
#else
#    define AXM_CDECL
#    define AXM_STDCALL
#    define AXM_FASTCALL
#endif
/** @} */


/**
 * @defgroup AXM_STRUCT_LAYOUT Struct Layout
 * @brief Portable packing and alignment control.
 *
 * @details
 * **Packing:**
 *   AXM_PACKED_BEGIN / AXM_PACKED_END bracket a struct on MSVC.
 *   AXM_PACKED is a per-type attribute on GCC/Clang.
 *   Use both together for portable packed structs:
 *
 *   @code
 *   AXM_PACKED_BEGIN
 *   struct WireHeader { u16 type; u32 length; } AXM_PACKED;
 *   AXM_PACKED_END
 *   @endcode
 *
 * **Alignment:**
 *   - **AXM_ALIGNAS(n)** — Align a variable or member to n bytes.
 *   - **AXM_ALIGNOF(t)** — Alignment requirement of type t.
 *   - **AXM_CACHE_LINE_SIZE** — Cache-line size in bytes (default 64).
 *     Override by defining before this header.
 *   - **AXM_CACHE_ALIGN** — Align to one cache line. Prevents false
 *     sharing on hot shared data between threads.
 *
 * @{
 */
#if defined(AXM_COMPILER_MSVC_LIKE)
#    define AXM_PACKED_BEGIN __pragma(pack(push, 1))
#    define AXM_PACKED_END   __pragma(pack(pop))
#    define AXM_PACKED
#elif AXM_HAS_ATTRIBUTE(packed)
#    define AXM_PACKED_BEGIN
#    define AXM_PACKED_END
#    define AXM_PACKED __attribute__((packed))
#else
#    define AXM_PACKED_BEGIN
#    define AXM_PACKED_END
#    define AXM_PACKED
#endif

#if defined(AXM_HAS_CXX11)
#    define AXM_ALIGNAS(n) alignas(n)
#    define AXM_ALIGNOF(t) alignof(t)
#elif defined(AXM_COMPILER_MSVC_LIKE)
#    define AXM_ALIGNAS(n) __declspec(align(n))
#    define AXM_ALIGNOF(t) __alignof(t)
#elif AXM_HAS_ATTRIBUTE(aligned)
#    define AXM_ALIGNAS(n) __attribute__((aligned(n)))
#    define AXM_ALIGNOF(t) __alignof__(t)
#else
#    define AXM_ALIGNAS(n)
#    define AXM_ALIGNOF(t) sizeof(t)
#endif

#ifndef AXM_CACHE_LINE_SIZE
#    define AXM_CACHE_LINE_SIZE 64
#endif
#define AXM_CACHE_ALIGN AXM_ALIGNAS(AXM_CACHE_LINE_SIZE)
/** @} */


/**
 * @defgroup AXM_STANDARD_ATTRIBUTES Standard [[attributes]]
 * @brief Portable wrappers for C++ standard attributes with compiler fallbacks.
 *
 * @details
 * - **AXM_NODISCARD** — Warn when the return value is discarded.
 * - **axmNodiscardMsg(msg)** — Same with an explanatory message (C++17).
 * - **AXM_MAYBE_UNUSED** — Suppress unused-entity warnings.
 * - **AXM_DEPRECATED** — Mark a declaration deprecated.
 * - **axmDeprecatedMsg(msg)** — Same with a migration hint.
 * - **AXM_FALLTHROUGH** — Annotate an intentional switch fall-through.
 * - **AXM_NORETURN** — Function does not return to its caller.
 * - **AXM_NO_UNIQUE_ADDRESS** — Allow an empty member to share storage
 *   with adjacent members (C++20).
 *
 * @{
 */
#if AXM_HAS_CPP_ATTRIBUTE(nodiscard)
#    define AXM_NODISCARD        [[nodiscard]]
#    define axmNodiscardMsg(msg) [[nodiscard(msg)]]
#elif AXM_HAS_ATTRIBUTE(warn_unused_result)
#    define AXM_NODISCARD        __attribute__((warn_unused_result))
#    define axmNodiscardMsg(msg) __attribute__((warn_unused_result))
#else
#    define AXM_NODISCARD
#    define axmNodiscardMsg(msg)
#endif

#if AXM_HAS_CPP_ATTRIBUTE(maybe_unused)
#    define AXM_MAYBE_UNUSED [[maybe_unused]]
#elif AXM_HAS_ATTRIBUTE(unused)
#    define AXM_MAYBE_UNUSED __attribute__((unused))
#else
#    define AXM_MAYBE_UNUSED
#endif

#if AXM_HAS_CPP_ATTRIBUTE(deprecated)
#    define AXM_DEPRECATED        [[deprecated]]
#    define axmDeprecatedMsg(msg) [[deprecated(msg)]]
#elif AXM_HAS_ATTRIBUTE(deprecated)
#    define AXM_DEPRECATED        __attribute__((deprecated))
#    define axmDeprecatedMsg(msg) __attribute__((deprecated(msg)))
#elif defined(AXM_COMPILER_MSVC_LIKE)
#    define AXM_DEPRECATED        __declspec(deprecated)
#    define axmDeprecatedMsg(msg) __declspec(deprecated(msg))
#else
#    define AXM_DEPRECATED
#    define axmDeprecatedMsg(msg)
#endif

#if AXM_HAS_CPP_ATTRIBUTE(fallthrough)
#    define AXM_FALLTHROUGH [[fallthrough]]
#elif AXM_HAS_ATTRIBUTE(fallthrough)
#    define AXM_FALLTHROUGH __attribute__((fallthrough))
#else
#    define AXM_FALLTHROUGH                                                                        \
        do {                                                                                       \
        } while (false)
#endif

#if AXM_HAS_CPP_ATTRIBUTE(noreturn)
#    define AXM_NORETURN [[noreturn]]
#elif AXM_HAS_ATTRIBUTE(noreturn)
#    define AXM_NORETURN __attribute__((noreturn))
#elif defined(AXM_COMPILER_MSVC_LIKE)
#    define AXM_NORETURN __declspec(noreturn)
#else
#    define AXM_NORETURN
#endif

#if AXM_HAS_CPP_ATTRIBUTE(no_unique_address)
#    define AXM_NO_UNIQUE_ADDRESS [[no_unique_address]]
#elif defined(AXM_COMPILER_MSVC_LIKE) && AXM_HAS_CPP_ATTRIBUTE(msvc::no_unique_address)
#    define AXM_NO_UNIQUE_ADDRESS [[msvc::no_unique_address]]
#else
#    define AXM_NO_UNIQUE_ADDRESS
#endif
/** @} */


/**
 * @defgroup AXM_THREAD_LOCAL_STORAGE Thread-Local Storage
 * @brief Per-thread variable storage annotation.
 *
 * @details
 * **AXM_THREAD_LOCAL** — One independent instance per thread. Must be applied
 * to variables with static storage duration (file-scope globals or
 * function-local statics).
 *
 * @{
 */
#if defined(AXM_HAS_CXX11)
#    define AXM_THREAD_LOCAL thread_local
#elif defined(AXM_COMPILER_MSVC_LIKE)
#    define AXM_THREAD_LOCAL __declspec(thread)
#elif AXM_HAS_ATTRIBUTE(__thread)
#    define AXM_THREAD_LOCAL __thread
#else
#    define AXM_THREAD_LOCAL
#endif
/** @} */


/**
 * @defgroup AXM_POINTER_SEMANTICS Pointer Semantics
 * @brief Aliasing contracts for pointer arguments.
 *
 * @details
 * - **AXM_RESTRICT** — The pointer does not alias any other pointer in scope.
 *   Skips aliasing-safety reloads in loops and frequently enables
 *   auto-vectorisation that would otherwise be blocked. Semantically
 *   equivalent to C99 `restrict`.
 *
 * - **AXM_MAY_ALIAS** — The pointed-to type may alias objects of a different
 *   type, bypassing strict aliasing. Essential for types that act as raw
 *   byte views of other objects.
 *
 * @{
 */
#if defined(AXM_COMPILER_MSVC_LIKE)
#    define AXM_RESTRICT __restrict
#elif defined(AXM_COMPILER_GCC_LIKE)
#    define AXM_RESTRICT __restrict__
#else
#    define AXM_RESTRICT
#endif

#if AXM_HAS_ATTRIBUTE(may_alias)
#    define AXM_MAY_ALIAS __attribute__((may_alias))
#else
#    define AXM_MAY_ALIAS
#endif
/** @} */


/**
 * @defgroup AXM_FUNCTION_OPTIMISATION Function Optimisation Hints
 * @brief Hints that inform the compiler about side-effect freedom and call frequency.
 *
 * @details
 * - **AXM_PURE** — Result depends only on arguments and visible global memory;
 *   no observable side effects. The compiler may eliminate repeated calls
 *   with identical arguments.
 *
 * - **AXM_CONST** — Stronger than AXM_PURE: result depends only on arguments,
 *   with no reads from global memory at all. Do not apply to functions that
 *   dereference pointer arguments.
 *
 * - **AXM_HOT** — On a performance-critical hot path. May influence code layout
 *   to keep hot code in the same cache lines.
 *
 * - **AXM_COLD** — Rarely executed. The compiler may pessimise its code size
 *   and move it away from hot paths.
 *
 * @{
 */
#if AXM_HAS_ATTRIBUTE(pure)
#    define AXM_PURE __attribute__((pure))
#else
#    define AXM_PURE
#endif

#if AXM_HAS_ATTRIBUTE(const)
#    define AXM_CONST __attribute__((const))
#else
#    define AXM_CONST
#endif

#if AXM_HAS_ATTRIBUTE(hot)
#    define AXM_HOT __attribute__((hot))
#else
#    define AXM_HOT
#endif

#if AXM_HAS_ATTRIBUTE(cold)
#    define AXM_COLD __attribute__((cold))
#else
#    define AXM_COLD
#endif
/** @} */


/**
 * @defgroup AXM_ALLOCATION_HINTS Allocation Hints
 * @brief Annotate allocator-like functions to aid static analysis and optimisation.
 *
 * @details
 * - **AXM_MALLOC** — Return value is a freshly allocated, non-aliased pointer
 *   unrelated to any object already visible to the caller.
 *
 * - **axmAllocSize(idx)** — Argument at 1-based index idx is the size of the
 *   allocation in bytes. Enables `-Walloc-size` and `__builtin_object_size`.
 *
 * - **axmAllocSize2(i, j)** — Two arguments describe the allocation:
 *   element count (i) × element size (j).
 *
 * - **axmAllocAlign(idx)** — Argument at 1-based index idx is the required
 *   alignment of the returned pointer.
 *
 * - **AXM_RETURNS_NONNULL** — The function never returns null. Lets the
 *   compiler elide null checks at call sites.
 *
 * @{
 */
#if AXM_HAS_ATTRIBUTE(malloc)
#    define AXM_MALLOC __attribute__((malloc))
#else
#    define AXM_MALLOC
#endif

#if AXM_HAS_ATTRIBUTE(alloc_size)
#    define axmAllocSize(idx)        __attribute__((alloc_size(idx)))
#    define axmAllocSize2(idx, idx2) __attribute__((alloc_size(idx, idx2)))
#else
#    define axmAllocSize(idx)
#    define axmAllocSize2(idx, idx2)
#endif

#if AXM_HAS_ATTRIBUTE(alloc_align)
#    define axmAllocAlign(idx) __attribute__((alloc_align(idx)))
#else
#    define axmAllocAlign(idx)
#endif

#if AXM_HAS_ATTRIBUTE(returns_nonnull)
#    define AXM_RETURNS_NONNULL __attribute__((returns_nonnull))
#else
#    define AXM_RETURNS_NONNULL
#endif
/** @} */


/**
 * @defgroup AXM_STATIC_ANALYSIS Static Analysis
 * @brief Enable format and non-null diagnostics on custom wrapper functions.
 *
 * @details
 * - **axmFormatPrintf(fmt_idx, args_idx)** / **axmFormatScanf(fmt_idx, args_idx)**
 *   — Both take 1-based indices: fmt_idx is the format string argument,
 *   args_idx is the first variadic argument (pass 0 for va_list). Enable
 *   `-Wformat` diagnostics on custom printf / scanf wrappers:
 *
 *   @code
 *   void logf(const c8* fmt, ...) axmFormatPrintf(1, 2);
 *   @endcode
 *
 * - **axmNonnull(...)** — Listed 1-based argument indices must not be null.
 * - **AXM_NONNULL_ALL** — Every pointer argument must not be null.
 *
 * @{
 */
#if AXM_HAS_ATTRIBUTE(format)
#    define axmFormatPrintf(fmt, args) __attribute__((format(printf, fmt, args)))
#    define axmFormatScanf(fmt, args)  __attribute__((format(scanf, fmt, args)))
#else
#    define axmFormatPrintf(fmt, args)
#    define axmFormatScanf(fmt, args)
#endif

#if AXM_HAS_ATTRIBUTE(nonnull)
#    define axmNonnull(...) __attribute__((nonnull(__VA_ARGS__)))
#    define AXM_NONNULL_ALL __attribute__((nonnull))
#else
#    define axmNonnull(...)
#    define AXM_NONNULL_ALL
#endif
/** @} */


/**
 * @defgroup AXM_LINKAGE_EXTRAS Linkage Extras
 * @brief Place symbols in named sections, retain unreferenced symbols, or emit with weak linkage.
 *
 * @details
 * - **axmSection(name)** — Place the symbol in the named linker section. Use
 *   for plugin registration tables, constructor lists, and firmware memory maps.
 *
 * - **AXM_USED** — Keep the symbol even if it appears unreferenced. Needed
 *   when a symbol is referenced only from assembly, linker scripts, or opaque
 *   pointer casts.
 *
 * - **AXM_WEAK** — Emit with weak linkage. A strong definition in any other
 *   translation unit silently overrides it.
 *
 * @{
 */
#if AXM_HAS_ATTRIBUTE(section)
#    define axmSection(name) __attribute__((section(name)))
#elif defined(AXM_COMPILER_MSVC_LIKE)
#    define axmSection(name) __declspec(allocate(name))
#else
#    define axmSection(name)
#endif

#if AXM_HAS_ATTRIBUTE(used)
#    define AXM_USED __attribute__((used))
#else
#    define AXM_USED
#endif

#if AXM_HAS_ATTRIBUTE(weak)
#    define AXM_WEAK __attribute__((weak))
#elif defined(AXM_COMPILER_MSVC_LIKE)
#    define AXM_WEAK __declspec(selectany)
#else
#    define AXM_WEAK
#endif
/** @} */


/**
 * @defgroup AXM_BRANCH_HINTS Branch-Prediction Hints
 * @brief Communicate expected branch outcomes to the compiler and CPU predictor.
 *
 * @details
 * - **AXM_LIKELY(expr)** — expr is expected true most of the time.
 * - **AXM_UNLIKELY(expr)** — expr is expected false most of the time.
 *
 * Place around the condition in an `if` / `while` / `for` when profiling or
 * domain knowledge shows a strongly biased outcome. Both evaluate expr exactly
 * once and return its boolean value unchanged.
 *
 * @{
 */
#if AXM_HAS_BUILTIN(__builtin_expect)
#    define AXM_LIKELY(expr)   (__builtin_expect(!!(expr), 1))
#    define AXM_UNLIKELY(expr) (__builtin_expect(!!(expr), 0))
#else
#    define AXM_LIKELY(expr)   (!!(expr))
#    define AXM_UNLIKELY(expr) (!!(expr))
#endif
/** @} */


/**
 * @defgroup AXM_UNREACHABLE_ASSUME Unreachable and Assume
 * @brief Mark provably dead paths and supply optimiser invariants.
 *
 * @details
 * - **AXM_UNREACHABLE** — Marks a point the programmer guarantees is never
 *   reached. Reaching it is undefined behaviour. Use to eliminate dead
 *   branches and silence "missing return" warnings.
 *
 * - **axmAssume(expr)** — Promises the compiler that expr is true without
 *   evaluating it at runtime. The compiler may exploit this as a proven
 *   invariant for downstream optimisations:
 *
 *   @code
 *   axmAssume(n > 0);  // elides a negative-n code path below
 *   @endcode
 *
 * @{
 */
#if AXM_HAS_BUILTIN(__builtin_unreachable)
#    define AXM_UNREACHABLE (__builtin_unreachable())
#elif defined(AXM_COMPILER_MSVC_LIKE)
#    define AXM_UNREACHABLE (__assume(0))
#else
#    define AXM_UNREACHABLE                                                                        \
        do {                                                                                       \
            while (true) {}                                                                        \
        } while (false) // NOLINT
#endif

#if defined(AXM_HAS_CXX23) && defined(__cpp_lib_assume)
#    include <utility>
#    define axmAssume(expr) (std::assume(expr))
#elif defined(AXM_COMPILER_MSVC_LIKE)
#    define axmAssume(expr) (__assume(expr))
#elif AXM_HAS_BUILTIN(__builtin_assume)
#    define axmAssume(expr) (__builtin_assume(expr))
#elif AXM_HAS_BUILTIN(__builtin_unreachable)
#    define axmAssume(expr) ((expr) ? void(0) : __builtin_unreachable())
#else
#    define axmAssume(expr) ((void)(expr))
#endif
/** @} */


/**
 * @defgroup AXM_FUNCTION_NAME Function Name
 * @brief Portable access to the current function's name and signature.
 *
 * @details
 * - **AXM_FUNC_NAME** — Undecorated function name, suitable for use in
 *   diagnostic messages and logging.
 * - **AXM_FUNC_SIG** — Full decorated signature including return type and
 *   parameters. Not portable across compilers; use only for debugging.
 * - **AXM_LINE** — Full decorated signature including return type and
 *   parameters. Not portable across compilers; use only for debugging.
 *
 * @{
 */
#if defined(AXM_COMPILER_MSVC_LIKE)
#    define AXM_FUNC_NAME __FUNCTION__
#    define AXM_FUNC_SIG  __FUNCSIG__
#elif defined(AXM_COMPILER_GCC_LIKE)
#    define AXM_FUNC_NAME __func__
#    define AXM_FUNC_SIG  __PRETTY_FUNCTION__
#else
#    define AXM_FUNC_NAME __func__
#    define AXM_FUNC_SIG  __func__
#endif
#define AXM_LINE __LINE__
/** @} */


/**
 * @defgroup AXM_LOOP_PRAGMAS Loop Pragmas
 * @brief Per-loop optimisation directives.
 *
 * @details
 * Place the macro immediately before the loop it annotates. None have any
 * effect on compilers that do not understand the underlying pragma.
 *
 * - **AXM_PRAGMA_UNROLL** — Ask the compiler to unroll the next loop.
 * - **AXM_PRAGMA_UNROLL_N(n)** — Unroll exactly n times.
 * - **AXM_PRAGMA_VECTORIZE** — Force vectorisation of the next loop.
 * - **AXM_PRAGMA_IVDEP** — Assert no loop-carried dependencies.
 * - **AXM_PRAGMA_NOUNROLL** — Prevent unrolling (preserves code size).
 *
 * @{
 */
#define AXM__PRAGMA(x) _Pragma(#x)

#if defined(AXM_COMPILER_CLANG)
#    define AXM_PRAGMA_UNROLL      AXM__PRAGMA(clang loop unroll(enable))
#    define AXM_PRAGMA_UNROLL_N(n) AXM__PRAGMA(clang loop unroll_count(n))
#    define AXM_PRAGMA_VECTORIZE   AXM__PRAGMA(clang loop vectorize(enable))
#    define AXM_PRAGMA_IVDEP       AXM__PRAGMA(clang loop vectorize_predicate(enable))
#    define AXM_PRAGMA_NOUNROLL    AXM__PRAGMA(clang loop unroll(disable))
#elif defined(AXM_COMPILER_GCC)
#    define AXM_PRAGMA_UNROLL      AXM__PRAGMA(GCC unroll 8)
#    define AXM_PRAGMA_UNROLL_N(n) AXM__PRAGMA(GCC unroll n)
#    define AXM_PRAGMA_VECTORIZE   AXM__PRAGMA(GCC ivdep)
#    define AXM_PRAGMA_IVDEP       AXM__PRAGMA(GCC ivdep)
#    define AXM_PRAGMA_NOUNROLL    AXM__PRAGMA(GCC unroll 1)
#elif defined(AXM_COMPILER_MSVC_LIKE)
#    define AXM_PRAGMA_UNROLL AXM__PRAGMA(loop(hint_parallel(8)))
#    define AXM_PRAGMA_UNROLL_N(n)
#    define AXM_PRAGMA_VECTORIZE AXM__PRAGMA(loop(ivdep))
#    define AXM_PRAGMA_IVDEP     AXM__PRAGMA(loop(ivdep))
#    define AXM_PRAGMA_NOUNROLL
#else
#    define AXM_PRAGMA_UNROLL
#    define AXM_PRAGMA_UNROLL_N(n)
#    define AXM_PRAGMA_VECTORIZE
#    define AXM_PRAGMA_IVDEP
#    define AXM_PRAGMA_NOUNROLL
#endif
/** @} */


/**
 * @defgroup AXM_STRINGIFY Stringify
 * @brief Token-to-string conversion and source-location literals.
 *
 * @details
 * - **AXM_STRINGIFY(x)** — Fully expands x before stringifying.
 *   `AXM_STRINGIFY(1 + 2)` → `"1 + 2"`;
 *   `AXM_STRINGIFY(VERSION)` → `"3"` (if `VERSION=3`).
 *
 * - **AXM_STRINGIFY_RAW(x)** — Stringifies x literally without macro expansion.
 *   `AXM_STRINGIFY_RAW(VERSION)` → `"VERSION"`.
 *
 * - **AXM_LINE_STRING** — Current line number as a string literal.
 *
 * - **AXM_SOURCE_LOCATION** — `"file.cpp:42"` string for use in diagnostics.
 *
 * @{
 */
#define AXM_STRINGIFY_RAW(x) #x
#define AXM_STRINGIFY(x)     AXM_STRINGIFY_RAW(x)
#define AXM_LINE_STRING      AXM_STRINGIFY(__LINE__)
#define AXM_SOURCE_LOCATION  __FILE__ ":" AXM_LINE_STRING
/** @} */

#endif // AXM_LVL_COMPILER_H
