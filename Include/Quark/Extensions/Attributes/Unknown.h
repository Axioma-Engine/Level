#ifndef ATOM_QRK_EXTENSION_ATTRIBUTES_UNKNOWN_H
#define ATOM_QRK_EXTENSION_ATTRIBUTES_UNKNOWN_H

/**
 * @file Unknown.h
 * @brief Minimal fallback attribute macros for unknown compilers.
 *
 * Supplies conservative defaults for attribute macros when no compiler-specific
 * support is detected, keeping code portable and warning-free.
 */

#define ATOM_ALWAYS_INLINE inline
#define ATOM_NO_INLINE
#define ATOM_COLD
#define ATOM_HOT
#define ATOM_FLATTEN
#define ATOM_PURE
#define ATOM_CONST
#define ATOM_USED
#define ATOM_MALLOC
#define ATOM_ALLOC_SIZE(idx)
#define ATOM_ALLOC_SIZE2(idx1, idx2)
#define ATOM_ALLOC_ALIGN(idx)
#define ATOM_FORMAT_PRINTF(fmt_idx, arg_idx)
#define ATOM_FORMAT_SCANF(fmt_idx, arg_idx)
#define ATOM_FORMAT(type, fmt_idx, arg_idx)
#define ATOM_NONNULL_ALL
#define ATOM_NONNULL(idx)

#endif
