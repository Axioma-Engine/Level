#ifndef ATOM_QRK_EXTENSION_ATTRIBUTES_MSVC_H
#define ATOM_QRK_EXTENSION_ATTRIBUTES_MSVC_H

/**
 * @file MSVC.h
 * @brief MSVC-specific attribute macros implemented with `__declspec` where needed.
 *
 * Provides MSVC-compliant definitions of common attribute macros used across
 * the codebase.
 */

#define ATOM_ALWAYS_INLINE __forceinline
#define ATOM_NO_INLINE     __declspec(noinline)
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
