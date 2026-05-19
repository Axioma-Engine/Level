#ifndef ATOM_QRK_UTILS_H
#define ATOM_QRK_UTILS_H

/**
 * @file Utils.h
 * @brief Common utility macros and small helpers used across Quark headers.
 *
 * Provides token concatenation, stringification, unused-variable suppression,
 * portability shims for `using`/`typedef` aliases and a small set of helper
 * macros used by other public headers. The macros are intentionally small and
 * documented to be safe for inclusion in both public and internal headers.
 */

#include "System.h" // IWYU pragma: keep

#if ATOM_HAS_CXX11
#    define ATOM_ALIAS(type, alias) using alias = type;
#else
#    define ATOM_ALIAS(type, alias) typedef type alias;
#endif

#define ATOM_CONCAT_INNER(a, b)     a##b
#define ATOM_CONCAT(a, b)           ATOM_CONCAT_INNER(a, b)
#define ATOM_CONCAT3(a, b, c)       ATOM_CONCAT(ATOM_CONCAT(a, b), c)
#define ATOM_CONCAT4(a, b, c, d)    ATOM_CONCAT(ATOM_CONCAT3(a, b, c), d)
#define ATOM_CONCAT5(a, b, c, d, e) ATOM_CONCAT(ATOM_CONCAT4(a, b, c, d), e)

#define ATOM_STRINGIFY_INNER(x) #x
#define ATOM_STRINGIFY(x)       ATOM_STRINGIFY_INNER(x)

#define ATOM_UNUSED(x)              (void)(x)
#define ATOM_UNUSED2(a, b)          ATOM_UNUSED(a), ATOM_UNUSED(b)
#define ATOM_UNUSED3(a, b, c)       ATOM_UNUSED2(a, b), ATOM_UNUSED(c)
#define ATOM_UNUSED4(a, b, c, d)    ATOM_UNUSED3(a, b, c), ATOM_UNUSED(d)
#define ATOM_UNUSED5(a, b, c, d, e) ATOM_UNUSED4(a, b, c, d), ATOM_UNUSED(e)

#ifdef __COUNTER__
#    define ATOM_UNIQUE_NAME(prefix) ATOM_CONCAT3(prefix, __LINE__, __COUNTER__)
#else
#    define ATOM_UNIQUE_NAME(prefix) ATOM_CONCAT(prefix, __LINE__)
#endif

#define ATOM_ARGS_INNER(x) x
#define ATOM_ARGS(x)       ATOM_ARGS_INNER x

#endif
