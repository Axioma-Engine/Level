/**
 * @file Attributes.h
 * @brief Public attribute macros facade - selects compiler-specific implementation.
 *
 * This header provides a single include point for all attribute and
 * compiler-quirk macros used throughout Level. It insulates the rest of the
 * codebase from compiler differences by choosing one of three implementations
 * at compile time:
 *
 * Implementation files (selected by AXM_COMPILER_* macros from System/Compiler.h):
 * - "GCC/Attributes.h"     : For GCC, Clang, and other GCC-like toolchains.
 * - "MSVC/Attributes.h"    : For MSVC and MSVC-compatible toolchains.
 * - "Generic/Attributes.h" : Minimal fallbacks for unknown or unsupported compilers.
 *
 * Attribute groups provided consistently across implementations:
 * - Standard C++ attributes: AXM_NORETURN, AXM_NODISCARD, AXM_MAYBE_UNUSED, AXM_FALLTHROUGH
 * - Control flow / exceptions: AXM_NOEXCEPT, AXM_ASSUME, AXM_UNREACHABLE
 * - Deprecation: AXM_DEPRECATED, AXM_DEPRECATED_MSG
 * - Visibility / linkage: AXM_EXPORT, AXM_IMPORT, AXM_LOCAL, AXM_API
 * - Inlining: AXM_FORCE_INLINE, AXM_NO_INLINE
 * - Optimization hints: AXM_LIKELY, AXM_UNLIKELY, AXM_HOT, AXM_COLD
 * - Function properties: AXM_PURE, AXM_CONST, AXM_MALLOC, AXM_ALLOC_SIZE, AXM_RETURNS_NONNULL
 * - Format checking: AXM_FORMAT_PRINTF, AXM_FORMAT_SCANF
 * - Memory/layout: AXM_PACKED_BEGIN, AXM_PACKED_END, AXM_PACKED, AXM_RESTRICT, AXM_MAY_ALIAS
 * - Language feature shims: AXM_CONSTEXPR, AXM_THREAD_LOCAL, AXM_ALIGNAS, AXM_NULLPTR
 * - Diagnostics: AXM_DEBUG_TRAP, AXM_FUNC_NAME, AXM_FUNC_SIG, AXM_LINE
 *
 * Notes:
 * - The chosen implementation tries to use standard C++ attributes first,
 *   then compiler extensions, and finally conservative fallbacks.
 * - For feature probing this header relies on System/Compiler.h and
 *   Features.h which provide AXM_COMPILER_* and AXM_HAS_* helpers.
 */
#ifndef AXM_LVL_ATTRIBUTES_H
#define AXM_LVL_ATTRIBUTES_H

#include "System/Compiler.h"

// IWYU pragma: begin_exports
#if AXM_COMPILER_GCC_LIKE
#    include "GCC/Attributes.h"
#elif AXM_COMPILER_MSVC_LIKE
#    include "MSVC/Attributes.h"
#else
#    include "Generic/Attributes.h"
#endif
// IWYU pragma: end_exports

#endif
