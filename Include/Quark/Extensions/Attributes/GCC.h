#ifndef ATOM_QRK_EXTENSION_ATTRIBUTES_GCC_H
#define ATOM_QRK_EXTENSION_ATTRIBUTES_GCC_H

/**
 * @file GCC.h
 * @brief GCC/Clang-specific attribute macros mapped to `__attribute__` forms.
 *
 * Defines common optimization and attribute macros when supported by the
 * compiler's attribute set (always_inline, noinline, cold, hot, flatten, etc.).
 */

#include "../../Features.h"
#include "../../Utils.h"

#if ATOM_HAS_ATTRIBUTE(always_inline)
#    define ATOM_ALWAYS_INLINE __attribute__((always_inline)) inline
#else
#    define ATOM_ALWAYS_INLINE
#endif

#if ATOM_HAS_ATTRIBUTE(noinline)
#    define ATOM_NO_INLINE __attribute__((noinline))
#else
#    define ATOM_NO_INLINE
#endif

#if ATOM_HAS_ATTRIBUTE(cold)
#    define ATOM_COLD __attribute__((cold))
#else
#    define ATOM_COLD
#endif

#if ATOM_HAS_ATTRIBUTE(hot)
#    define ATOM_HOT __attribute__((hot))
#else
#    define ATOM_HOT
#endif

#if ATOM_HAS_ATTRIBUTE(flatten)
#    define ATOM_FLATTEN __attribute__((flatten))
#else
#    define ATOM_FLATTEN
#endif

#if ATOM_HAS_ATTRIBUTE(pure)
#    define ATOM_PURE __attribute__((pure))
#else
#    define ATOM_PURE
#endif

#if ATOM_HAS_ATTRIBUTE(const)
#    define ATOM_CONST __attribute__((const))
#else
#    define ATOM_CONST
#endif

#if ATOM_HAS_ATTRIBUTE(used)
#    define ATOM_USED __attribute__((used))
#else
#    define ATOM_USED
#endif

#if ATOM_HAS_ATTRIBUTE(malloc)
#    define ATOM_MALLOC __attribute__((malloc))
#else
#    define ATOM_MALLOC
#endif

#if ATOM_HAS_ATTRIBUTE(alloc_size)
#    define ATOM_ALLOC_SIZE(idx)         __attribute__((alloc_size(idx)))
#    define ATOM_ALLOC_SIZE2(idx1, idx2) __attribute__((alloc_size(idx1, idx2)))
#else
#    define ATOM_ALLOC_SIZE(idx)
#    define ATOM_ALLOC_SIZE2(idx1, idx2)
#endif

#if ATOM_HAS_ATTRIBUTE(alloc_align)
#    define ATOM_ALLOC_ALIGN(idx) __attribute__((alloc_align(idx)))
#else
#    define ATOM_ALLOC_ALIGN(idx)
#endif

#if ATOM_HAS_ATTRIBUTE(format)
#    define ATOM_FORMAT_PRINTF(fmt_idx, arg_idx) __attribute__((format(printf, fmt_idx, arg_idx)))
#    define ATOM_FORMAT_SCANF(fmt_idx, arg_idx)  __attribute__((format(scanf, fmt_idx, arg_idx)))
#    define ATOM_FORMAT(type, fmt_idx, arg_idx)  __attribute__((format(type, fmt_idx, arg_idx)))
#else
#    define ATOM_FORMAT_PRINTF(fmt_idx, arg_idx)
#    define ATOM_FORMAT_SCANF(fmt_idx, arg_idx)
#    define ATOM_FORMAT(type, fmt_idx, arg_idx)
#endif

#if ATOM_HAS_ATTRIBUTE(nonnull)
#    define ATOM_NONNULL_ALL  __attribute__((nonnull))
#    define ATOM_NONNULL(idx) __attribute__((nonnull(ATOM_ARGS(idx))))
#else
#    define ATOM_NONNULL_ALL
#    define ATOM_NONNULL(idx)
#endif

#endif
