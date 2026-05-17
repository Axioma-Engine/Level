/**
 * @file Attributes.h
 * @brief GCC/Clang attribute mappings and extensions.
 *
 * @details
 * This implementation provides AXM_* macros by preferring standard C++ attributes
 * ([[...]]) when supported, then falling back to GCC/Clang __attribute__((...))
 * forms, and finally to conservative no-ops or portable alternatives.
 *
 * @par Dependencies
 * - Includes ../Features.h for AXM_HAS_ATTRIBUTE / AXM_HAS_BUILTIN / AXM_HAS_CPP_ATTRIBUTE
 * - Includes ../System/Cpp.h to access AXM_CXX_STANDARD and C++ feature gates.
 *
 * @par Attribute Groups
 * - @b StandardAttributes: AXM_NORETURN, AXM_NODISCARD, AXM_MAYBE_UNUSED, AXM_FALLTHROUGH,
 *   AXM_CARRIES_DEPENDENCY, AXM_DEPRECATED, AXM_DEPRECATED_MSG, AXM_NO_UNIQUE_ADDRESS
 * - @b ControlFlow: AXM_LIKELY, AXM_UNLIKELY, AXM_ASSUME, AXM_UNREACHABLE, AXM_NOEXCEPT
 * - @b Visibility: AXM_EXPORT, AXM_IMPORT, AXM_LOCAL, AXM_API
 * - @b Inlining: AXM_FORCE_INLINE, AXM_NO_INLINE
 * - @b Optimization: AXM_HOT, AXM_COLD
 * - @b FunctionProperties: AXM_PURE, AXM_CONST, AXM_MALLOC, AXM_ALLOC_SIZE, AXM_ALLOC_SIZE2,
 *   AXM_ALLOC_ALIGN, AXM_RETURNS_NONNULL, AXM_NONNULL_ALL, AXM_NONNULL
 * - @b FormatChecking: AXM_FORMAT_PRINTF, AXM_FORMAT_SCANF
 * - @b MemoryLayout: AXM_PACKED_BEGIN, AXM_PACKED_END, AXM_PACKED, AXM_RESTRICT, AXM_MAY_ALIAS
 * - @b LanguageFeatures: AXM_CONSTEXPR, AXM_THREAD_LOCAL, AXM_ALIGNAS, AXM_ALIGNOF,
 *   AXM_ALIGNED_VAR, AXM_NULLPTR
 * - @b Diagnostics: AXM_DEBUG_TRAP, AXM_FUNC_NAME, AXM_FUNC_SIG, AXM_LINE
 */
#ifndef AXM_QRK_GCC_ATTRIBUTES_H
#define AXM_QRK_GCC_ATTRIBUTES_H

#include "../Features.h"
#include "../System/Cpp.h" // IWYU pragma: keep

/** @brief Marks dependency chain in lock-free programming (C++11). */
#if AXM_HAS_CPP_ATTRIBUTE(carries_dependency)
#    define AXM_CARRIES_DEPENDENCY [[carries_dependency]]
#elif AXM_HAS_ATTRIBUTE(carries_dependency)
#    define AXM_CARRIES_DEPENDENCY __attribute__((carries_dependency))
#else
#    define AXM_CARRIES_DEPENDENCY
#endif

/** @brief Marks code as deprecated (C++14). Optional message version: AXM_DEPRECATED_MSG. */
#if AXM_HAS_CPP_ATTRIBUTE(deprecated)
#    define AXM_DEPRECATED          [[deprecated]]
#    define AXM_DEPRECATED_MSG(msg) [[deprecated(msg)]]
#elif AXM_HAS_ATTRIBUTE(deprecated)
#    define AXM_DEPRECATED          __attribute__((deprecated))
#    define AXM_DEPRECATED_MSG(msg) __attribute__((deprecated(msg)))
#else
#    define AXM_DEPRECATED
#    define AXM_DEPRECATED_MSG(msg)
#endif

/** @brief Compiler should warn if return value is discarded (C++17). */
#if AXM_HAS_CPP_ATTRIBUTE(nodiscard)
#    define AXM_NODISCARD [[nodiscard]]
#    if AXM_HAS_CXX20
#        define AXM_NODISCARD_MSG(msg) [[nodiscard(msg)]]
#    else
#        define AXM_NODISCARD_MSG(msg)
#    endif
#elif AXM_HAS_ATTRIBUTE(warn_unused_result)
#    define AXM_NODISCARD          __attribute__((warn_unused_result))
#    define AXM_NODISCARD_MSG(msg) __attribute__((warn_unused_result))
#else
#    define AXM_NODISCARD
#    define AXM_NODISCARD_MSG(msg)
#endif

/** @brief Marks variables/parameters that may be intentionally unused (C++17). */
#if AXM_HAS_CPP_ATTRIBUTE(maybe_unused)
#    define AXM_MAYBE_UNUSED [[maybe_unused]]
#elif AXM_HAS_ATTRIBUTE(unused)
#    define AXM_MAYBE_UNUSED __attribute__((unused))
#else
#    define AXM_MAYBE_UNUSED
#endif

/** @brief Marks intentional fallthrough in switch statements (C++17). */
#if AXM_HAS_CPP_ATTRIBUTE(fallthrough)
#    define AXM_FALLTHROUGH [[fallthrough]]
#elif AXM_HAS_ATTRIBUTE(fallthrough)
#    define AXM_FALLTHROUGH __attribute__((fallthrough))
#else
#    define AXM_FALLTHROUGH
#endif

/** @brief Marks branch as likely/unlikely to be taken (C++20). */
#if AXM_HAS_CPP_ATTRIBUTE(likely)
#    define AXM_LIKELY(x)   (x) [[likely]]
#    define AXM_UNLIKELY(x) (x) [[unlikely]]
#elif AXM_HAS_BUILTIN(__builtin_expect)
#    define AXM_LIKELY(x)   (__builtin_expect(!!(x), true))
#    define AXM_UNLIKELY(x) (__builtin_expect(!!(x), false))
#else
#    define AXM_LIKELY(x)   (x)
#    define AXM_UNLIKELY(x) (x)
#endif

/** @brief Compiler assumes expression is always true (C++23). */
#if AXM_HAS_CPP_ATTRIBUTE(assume)
#    define AXM_ASSUME(expr) [[assume(expr)]]
#elif AXM_HAS_ATTRIBUTE(assume)
#    define AXM_ASSUME(expr) __attribute__((assume(expr)))
#elif AXM_HAS_BUILTIN(__builtin_assume)
#    define AXM_ASSUME(expr) __builtin_assume(!!(expr))
#else
#    define AXM_ASSUME(expr)
#endif

/** @brief Tells compiler this code point is unreachable (C++23 assume(false)). */
#if AXM_HAS_BUILTIN(__builtin_unreachable)
#    define AXM_UNREACHABLE() __builtin_unreachable()
#elif AXM_HAS_CPP_ATTRIBUTE(assume)
#    define AXM_UNREACHABLE() [[assume(false)]]
#else
#    define AXM_UNREACHABLE()                                                                      \
        do {                                                                                       \
        } while (0)
#endif

/** @brief Prevents empty base class optimization (C++20). */
#if AXM_HAS_CPP_ATTRIBUTE(no_unique_address)
#    define AXM_NO_UNIQUE_ADDRESS [[no_unique_address]]
#else
#    define AXM_NO_UNIQUE_ADDRESS
#endif

/** @} */

/** @defgroup ControlFlow Control Flow & Exception Handling
 * @brief Exception safety and function control attributes.
 * @{
 */

/** @brief Qualifies function signature as no-throw (exception-safe). */
#if AXM_HAS_CXX11
#    define AXM_NOEXCEPT(x) x noexcept
#elif AXM_HAS_ATTRIBUTE(nothrow)
#    define AXM_NOEXCEPT(x) __attribute__((nothrow)) x
#else
#    define AXM_NOEXCEPT(x) x throw()
#endif

/** @} */

/** @defgroup Debugging Debugging Support
 * @brief Triggers debugger breakpoint or trap. @{
 */
#if AXM_HAS_BUILTIN(__builtin_debugtrap)
#    define AXM_DEBUG_TRAP __builtin_debugtrap()
#elif AXM_HAS_BUILTIN(__builtin_trap)
#    define AXM_DEBUG_TRAP __builtin_trap()
#else
#    define AXM_DEBUG_TRAP                                                                         \
        do {                                                                                       \
        } while (0)
#endif
/** @} */

/** @defgroup FunctionProperties Function Property Hints
 * @brief GCC-specific function behavior hints for optimization.
 * @{
 */
/** @brief Function is pure: depends only on arguments, no side effects. */
#if AXM_HAS_ATTRIBUTE(pure)
#    define AXM_PURE __attribute__((pure))
#else
#    define AXM_PURE
#endif

/** @brief Function is const: returns same value for same arguments, no side effects. */
#if AXM_HAS_ATTRIBUTE(const)
#    define AXM_CONST __attribute__((const))
#else
#    define AXM_CONST
#endif

/** @brief Function returns dynamically allocated memory. */
#if AXM_HAS_ATTRIBUTE(malloc)
#    define AXM_MALLOC __attribute__((malloc))
#else
#    define AXM_MALLOC
#endif

/** @brief Annotates allocation size parameter(s). Single or two index parameters. */
#if AXM_HAS_ATTRIBUTE(alloc_size)
#    define AXM_ALLOC_SIZE(idx)        __attribute__((alloc_size(idx)))
#    define AXM_ALLOC_SIZE2(idx, idx2) __attribute__((alloc_size(idx, idx2)))
#else
#    define AXM_ALLOC_SIZE(idx)
#    define AXM_ALLOC_SIZE2(idx, idx2)
#endif

/** @brief Specifies which parameter controls allocation alignment. */
#if AXM_HAS_ATTRIBUTE(alloc_align)
#    define AXM_ALLOC_ALIGN(idx) __attribute__((alloc_align(idx)))
#else
#    define AXM_ALLOC_ALIGN(idx)
#endif

/** @brief Function always returns non-null pointer. */
#if AXM_HAS_ATTRIBUTE(returns_nonnull)
#    define AXM_RETURNS_NONNULL __attribute__((returns_nonnull))
#else
#    define AXM_RETURNS_NONNULL
#endif
/** @} */

/** @defgroup FormatChecking Format String Validation
 * @brief GCC-specific format string checking for printf/scanf-style functions.
 * @{
 */
#if AXM_HAS_ATTRIBUTE(format)
#    define AXM_FORMAT_PRINTF(fmt, args) __attribute__((format(printf, fmt, args)))
#    define AXM_FORMAT_SCANF(fmt, args)  __attribute__((format(scanf, fmt, args)))
#else
#    define AXM_FORMAT_PRINTF(fmt, args)
#    define AXM_FORMAT_SCANF(fmt, args)
#endif
/** @} */

/** @defgroup NullnessChecking Null Pointer Checking
 * @brief GCC-specific null pointer validation.
 * @{
 */
#if AXM_HAS_ATTRIBUTE(nonnull)
#    define AXM_NONNULL_ALL __attribute__((nonnull))
#    define AXM_NONNULL(x)  __attribute__((nonnull(x)))
#else
#    define AXM_NONNULL_ALL
#    define AXM_NONNULL(x)
#endif
/** @} */

/** @defgroup VisibilityControl Symbol Visibility & Export
 * @brief Macros for controlling symbol visibility in shared libraries.
 * @{
 */
#if AXM_HAS_ATTRIBUTE(visibility)
#    define AXM_EXPORT __attribute__((visibility("default")))
#    define AXM_IMPORT __attribute__((visibility("default")))
#    define AXM_LOCAL  __attribute__((visibility("hidden")))
#else
#    define AXM_EXPORT
#    define AXM_IMPORT
#    define AXM_LOCAL
#endif

/** @brief Main API macro. Uses AXM_EXPORT/IMPORT based on build type. */
#if defined(AXM_SHARED_BUILD)
#    define AXM_API AXM_EXPORT
#elif defined(AXM_STATIC_BUILD)
#    define AXM_API
#else
#    define AXM_API AXM_IMPORT
#endif
/** @} */

/** @defgroup InliningControl Function Inlining
 * @brief Macros to force or prevent function inlining.
 * @{
 */
/** @brief Forces function inlining for performance-critical code. */
#if AXM_HAS_ATTRIBUTE(always_inline)
#    define AXM_FORCE_INLINE __attribute__((always_inline)) inline
#else
#    define AXM_FORCE_INLINE inline
#endif

/** @brief Prevents function inlining. */
#if AXM_HAS_ATTRIBUTE(noinline)
#    define AXM_NO_INLINE __attribute__((noinline))
#else
#    define AXM_NO_INLINE
#endif
/** @} */

/** @defgroup CacheOptimization Cache-Aware Optimization
 * @brief GCC-specific cache optimization hints.
 * @{
 */
/** @brief Function is hot: optimize for speed and place in hot section. */
#if AXM_HAS_ATTRIBUTE(hot)
#    define AXM_HOT __attribute__((hot))
#else
#    define AXM_HOT
#endif

/** @brief Function is cold: optimize for size. */
#if AXM_HAS_ATTRIBUTE(cold)
#    define AXM_COLD __attribute__((cold))
#else
#    define AXM_COLD
#endif
/** @} */

/** @defgroup MemoryLayout Memory Layout & Data Alignment
 * @brief Macros for controlling struct/type layout and alignment.
 * @{
 */
/** @brief Packs struct to minimize size (1-byte alignment). */
#if AXM_HAS_ATTRIBUTE(packed)
#    define AXM_PACKED_BEGIN
#    define AXM_PACKED_END
#    define AXM_PACKED __attribute__((packed))
#else
#    define AXM_PACKED_BEGIN
#    define AXM_PACKED_END
#    define AXM_PACKED
#endif

/** @brief Pointer can alias any type (strict aliasing override). */
#define AXM_RESTRICT __restrict__

/** @brief Type may alias other types (disables strict aliasing rules). */
#if AXM_HAS_ATTRIBUTE(may_alias)
#    define AXM_MAY_ALIAS __attribute__((may_alias))
#else
#    define AXM_MAY_ALIAS
#endif
/* AXM_NO_UNIQUE_ADDRESS already in StandardCppAttributes */
/** @} */

/** @defgroup LanguageFeatures C++ Language Features
 * @brief C++11+ language features: constexpr, thread_local, alignment.
 * @{
 */
/** @brief Compile-time constant expression (C++11+). */
#if AXM_HAS_CXX11
#    define AXM_CONSTEXPR constexpr
#else
#    define AXM_CONSTEXPR
#endif

/** @brief Thread-local storage (C++11+). */
#if AXM_HAS_CXX11
#    define AXM_THREAD_LOCAL thread_local
#else
#    define AXM_THREAD_LOCAL __thread
#endif

/** @brief Specify alignment requirement for type or variable. */
#if AXM_HAS_CXX11
#    define AXM_ALIGNAS(n) alignas(n)
#    define AXM_ALIGNOF(T) alignof(T)
#elif AXM_HAS_ATTRIBUTE(aligned)
#    define AXM_ALIGNAS(n) __attribute__((aligned(n)))
#    define AXM_ALIGNOF(T) __alignof__(T)
#else
#    define AXM_ALIGNAS(n)
#    define AXM_ALIGNOF(T) __alignof__(T)
#endif

/** @brief Declares aligned variable. Usage: AXM_ALIGNED_VAR(int, 16, x) */
#define AXM_ALIGNED_VAR(T, n, name) AXM_ALIGNAS(n) T name

/** @brief Null pointer literal (C++11+ uses nullptr). */
#if AXM_HAS_CXX11
#    define AXM_NULLPTR nullptr
#else
namespace Quark {
    class Nullptr {
      public:
        template <class T>
        operator T*() const {
            return 0;
        }
        template <class T, class U>
        operator T U::*() const {
            return 0;
        }

      private:
        void operator&() const;
    };
    static const Nullptr NULLPTR = {};
}
#    define AXM_NULLPTR Quark::NULLPTR
#endif
/** @} */

/** @defgroup DiagnosticInfo Diagnostic Information
 * @brief Macros providing diagnostic information for debugging.
 * @{
 */
/** @brief Current function name string. */
#define AXM_FUNC_NAME __func__
/** @brief Current function signature (GCC extension: __PRETTY_FUNCTION__). */
#define AXM_FUNC_SIG  __PRETTY_FUNCTION__
/** @brief Current source line number. */
#define AXM_LINE      __LINE__
/** @brief Current source file name. */
#define AXM_FILE      __FILE__
/** @} */

#endif
