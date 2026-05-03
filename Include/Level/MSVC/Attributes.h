/**
 * @file Attributes.h
 * @brief MSVC attribute and declspec mappings.
 *
 * @details
 * This implementation provides AXM_* macros using MSVC-supported annotations
 * (__declspec, __assume, __forceinline, __debugbreak, etc.) and standard C++
 * attributes where available. Unsupported features are provided as conservative
 * no-ops or portable fallbacks.
 *
 * @par Dependencies
 * - Includes ../Features.h for AXM_HAS_DECLSPEC and AXM_HAS_CPP_ATTRIBUTE checks.
 * - Includes ../System/Cpp.h for AXM_CXX_STANDARD feature gates.
 *
 * @par Attribute Groups
 * - @b StandardAttributes: AXM_NORETURN, AXM_NODISCARD, AXM_NODISCARD_MSG, AXM_MAYBE_UNUSED,
 *   AXM_FALLTHROUGH, AXM_CARRIES_DEPENDENCY, AXM_DEPRECATED, AXM_DEPRECATED_MSG,
 * AXM_NO_UNIQUE_ADDRESS
 * - @b ControlFlow: AXM_LIKELY, AXM_UNLIKELY, AXM_ASSUME, AXM_UNREACHABLE, AXM_NOEXCEPT
 * - @b Debugging: AXM_DEBUG_TRAP
 * - @b Visibility: AXM_EXPORT, AXM_IMPORT, AXM_LOCAL, AXM_API
 * - @b Inlining: AXM_FORCE_INLINE, AXM_NO_INLINE
 * - @b Optimization: AXM_HOT, AXM_COLD (not supported, empty)
 * - @b FunctionProperties: AXM_PURE, AXM_CONST, AXM_MALLOC, AXM_ALLOC_SIZE, AXM_ALLOC_SIZE2,
 *   AXM_ALLOC_ALIGN, AXM_RETURNS_NONNULL (all not supported, empty)
 * - @b FormatChecking: AXM_FORMAT_PRINTF, AXM_FORMAT_SCANF (not supported, empty)
 * - @b NullnessChecking: AXM_NONNULL_ALL, AXM_NONNULL (not supported, empty)
 * - @b MemoryLayout: AXM_PACKED_BEGIN, AXM_PACKED_END, AXM_PACKED, AXM_RESTRICT, AXM_MAY_ALIAS
 * - @b LanguageFeatures: AXM_CONSTEXPR, AXM_THREAD_LOCAL, AXM_ALIGNAS, AXM_ALIGNOF,
 *   AXM_ALIGNED_VAR, AXM_NULLPTR
 * - @b Diagnostics: AXM_FUNC_NAME, AXM_FUNC_SIG, AXM_LINE
 *
 * @note MSVC does not support many GCC-style attributes; those are provided as
 *       empty fallbacks to maintain consistent header usage across platforms.
 */
#ifndef AXM_LVL_MSVC_ATTRIBUTES_H
#define AXM_LVL_MSVC_ATTRIBUTES_H

#include "../Features.h"
#include "../System/Cpp.h" // IWYU pragma: keep

/** @brief Marks dependency chain in lock-free programming (C++11). */
#if AXM_HAS_CPP_ATTRIBUTE(carries_dependency)
#    define AXM_CARRIES_DEPENDENCY [[carries_dependency]]
#else
#    define AXM_CARRIES_DEPENDENCY
#endif

/** @brief Marks code as deprecated (C++14). Optional message version: AXM_DEPRECATED_MSG. */
#if AXM_HAS_CPP_ATTRIBUTE(deprecated)
#    define AXM_DEPRECATED          [[deprecated]]
#    define AXM_DEPRECATED_MSG(msg) [[deprecated(msg)]]
#elif AXM_HAS_DECLSPEC(deprecated)
#    define AXM_DEPRECATED          __declspec(deprecated)
#    define AXM_DEPRECATED_MSG(msg) __declspec(deprecated(msg))
#else
#    define AXM_DEPRECATED
#    define AXM_DEPRECATED_MSG(msg)
#endif

/** @brief Compiler should warn if return value is discarded (C++17). Message version:
 * AXM_NODISCARD_MSG. */
#if AXM_HAS_CPP_ATTRIBUTE(nodiscard)
#    define AXM_NODISCARD [[nodiscard]]
#    if AXM_HAS_CXX20
#        define AXM_NODISCARD_MSG(msg) [[nodiscard(msg)]]
#    else
#        define AXM_NODISCARD_MSG(msg) [[nodiscard]]
#    endif
#else
#    define AXM_NODISCARD          _Check_return_
#    define AXM_NODISCARD_MSG(msg) _Check_return_
#endif

/** @brief Marks variables/parameters that may be intentionally unused (C++17). */
#if AXM_HAS_CPP_ATTRIBUTE(maybe_unused)
#    define AXM_MAYBE_UNUSED [[maybe_unused]]
#else
#    define AXM_MAYBE_UNUSED
#endif

/** @brief Marks intentional fallthrough in switch statements (C++17). */
#if AXM_HAS_CPP_ATTRIBUTE(fallthrough)
#    define AXM_FALLTHROUGH [[fallthrough]]
#else
#    define AXM_FALLTHROUGH
#endif

/** @brief Marks branch as likely/unlikely to be taken (C++20). */
#if AXM_HAS_CPP_ATTRIBUTE(likely)
#    define AXM_LIKELY(x)   (x) [[likely]]
#    define AXM_UNLIKELY(x) (x) [[unlikely]]
#else
#    define AXM_LIKELY(x)   (x)
#    define AXM_UNLIKELY(x) (x)
#endif

/** @brief Compiler assumes expression is always true (C++23). */
#if AXM_HAS_CPP_ATTRIBUTE(assume)
#    define AXM_ASSUME(expr) [[assume(expr)]]
#else
#    define AXM_ASSUME(expr) __assume(expr)
#endif

/** @brief Tells compiler this code point is unreachable (C++23 assume(false)). */
#if AXM_HAS_CPP_ATTRIBUTE(assume)
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

/** @brief Qualifies function signature as no-throw (exception-safe). Usage: AXM_NOEXCEPT(void
 * func()) */
#if AXM_HAS_CXX11
#    define AXM_NOEXCEPT(x) x noexcept
#elif AXM_HAS_DECLSPEC(nothrow)
#    define AXM_NOEXCEPT(x) __declspec(nothrow) x
#else
#    define AXM_NOEXCEPT(x)
#endif

/** @} */

/** @defgroup Debugging Debugging Support
 * @brief Triggers debugger breakpoint via __debugbreak(). @{ */
#define AXM_DEBUG_TRAP __debugbreak()
/** @} */

/** @defgroup FunctionProperties Function Property Hints
 * @brief MSVC does not support GCC-style function hints.
 * @{
 */
/** @brief Function is pure (not supported on MSVC). */
#define AXM_PURE

/** @brief Function is const (not supported on MSVC). */
#define AXM_CONST

/** @brief Function returns dynamically allocated memory (not supported on MSVC). */
#define AXM_MALLOC

/** @brief Annotates allocation size parameter(s) (not supported on MSVC). */
#define AXM_ALLOC_SIZE(idx)
#define AXM_ALLOC_SIZE2(idx, idx2)

/** @brief Specifies which parameter controls allocation alignment (not supported on MSVC). */
#define AXM_ALLOC_ALIGN(idx)

/** @brief Function always returns non-null pointer (not supported on MSVC). */
#define AXM_RETURNS_NONNULL
/** @} */

/** @defgroup FormatChecking Format String Validation
 * @brief Format string checking (not supported on MSVC).
 * @{
 */
#define AXM_FORMAT_PRINTF(fmt, args)
#define AXM_FORMAT_SCANF(fmt, args)
/** @} */

/** @defgroup NullnessChecking Null Pointer Checking
 * @brief Null pointer validation (not supported on MSVC).
 * @{
 */
#define AXM_NONNULL_ALL
#define AXM_NONNULL(x)
/** @} */

/** @defgroup VisibilityControl Symbol Visibility & Export
 * @brief Macros for controlling symbol visibility via dllexport/dllimport.
 * @{
 */
#if AXM_HAS_DECLSPEC(dllexport)
#    define AXM_EXPORT __declspec(dllexport)
#    define AXM_IMPORT __declspec(dllimport)
#    define AXM_LOCAL
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
/** @brief Forces function inlining via __forceinline. */
#define AXM_FORCE_INLINE __forceinline

/** @brief Prevents function inlining. */
#if AXM_HAS_DECLSPEC(noinline)
#    define AXM_NO_INLINE __declspec(noinline)
#else
#    define AXM_NO_INLINE
#endif
/** @} */

/** @defgroup CacheOptimization Cache-Aware Optimization
 * @brief Cache optimization (not supported on MSVC).
 * @{
 */
#define AXM_HOT
#define AXM_COLD
/** @} */

/** @defgroup MemoryLayout Memory Layout & Data Alignment
 * @brief Macros for controlling struct/type layout and alignment.
 * @{
 */
/** @brief Packs struct to minimize size (1-byte alignment). */
#define AXM_PACKED_BEGIN __pragma(pack(push, 1))
#define AXM_PACKED_END   __pragma(pack(pop))
#define AXM_PACKED

/** @brief Pointer can alias any type (strict aliasing override). */
#define AXM_RESTRICT __restrict

/** @brief Type may alias other types (not supported on MSVC). */
#define AXM_MAY_ALIAS
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
#elif AXM_HAS_DECLSPEC(thread)
#    define AXM_THREAD_LOCAL __declspec(thread)
#else
#    define AXM_THREAD_LOCAL
#endif

/** @brief Specify alignment requirement for type or variable. */
#if AXM_HAS_CXX11
#    define AXM_ALIGNAS(n) alignas(n)
#    define AXM_ALIGNOF(T) alignof(T)
#elif AXM_HAS_DECLSPEC(align)
#    define AXM_ALIGNAS(n) __declspec(align(n))
#    define AXM_ALIGNOF(T) __alignof(T)
#else
#    define AXM_ALIGNAS(n)
#    define AXM_ALIGNOF(T) __alignof(T)
#endif

/** @brief Declares aligned variable. Usage: AXM_ALIGNED_VAR(int, 16, x) */
#define AXM_ALIGNED_VAR(T, n, name) AXM_ALIGNAS(n) T name

/** @brief Null pointer literal (C++11+ uses nullptr). */
#if AXM_HAS_CXX11
#    define AXM_NULLPTR nullptr
#else
namespace AXM {
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
#    define AXM_NULLPTR AXM::NULLPTR
#endif
/** @} */

/** @defgroup DiagnosticInfo Diagnostic Information
 * @brief Macros providing diagnostic information for debugging.
 * @{
 */
/** @brief Current function name string. */
#define AXM_FUNC_NAME __func__
/** @brief Current function signature string. */
#define AXM_FUNC_SIG  __FUNCSIG__
/** @brief Current source line number. */
#define AXM_LINE      __LINE__
/** @} */

#endif
