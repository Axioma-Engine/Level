#ifndef ATOM_QRK_EXTENSION_KEYWORDS_GCC_H
#define ATOM_QRK_EXTENSION_KEYWORDS_GCC_H

/**
 * @file GCC.h
 * @brief GCC/Clang-specific keyword and source-location helpers.
 *
 * Exposes pretty function signatures, builtin-based unreachable/trap implementations
 * and other compiler-provided helpers optimized for GCC-like compilers.
 */

#include "../../Features.h"
#include "../../Utils.h"

#define ATOM_LINE            __LINE__
#define ATOM_FILE            __FILE__
#define ATOM_FUNC_NAME       __func__
#define ATOM_FUNC_SIG        __PRETTY_FUNCTION__
#define ATOM_SOURCE_LOCATION ATOM_FILE ":" ATOM_STRINGIFY(ATOM_LINE)

#if defined(__COUNTER__)
#    define ATOM_COUNTER __COUNTER__
#else
#    define ATOM_COUNTER __LINE__
#endif

#if ATOM_HAS_BUILTIN(unreachable)
#    define ATOM_UNREACHABLE() __builtin_unreachable()
#else
#    define ATOM_UNREACHABLE() ((void)0)
#endif

#if ATOM_HAS_BUILTIN(trap)
#    define ATOM_TRAP() __builtin_trap()
#else
#    define ATOM_TRAP() ((void)0)
#endif

#endif
