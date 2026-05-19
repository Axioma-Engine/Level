#ifndef ATOM_QRK_EXTENSION_KEYWORDS_MSVC_H
#define ATOM_QRK_EXTENSION_KEYWORDS_MSVC_H

/**
 * @file MSVC.h
 * @brief MSVC-specific keyword and source-location helpers.
 *
 * Provides `__FUNCSIG__`-based function signatures, MSVC-specific trap/assume
 * implementations and other helpers tailored for MSVC-like compilers.
 */

#include "../../Utils.h"

#define ATOM_LINE            __LINE__
#define ATOM_FILE            __FILE__
#define ATOM_FUNC_NAME       __func__
#define ATOM_FUNC_SIG        __FUNCSIG__
#define ATOM_SOURCE_LOCATION ATOM_FILE ":" ATOM_STRINGIFY(ATOM_LINE)

#if defined(__COUNTER__)
#    define ATOM_COUNTER __COUNTER__
#else
#    define ATOM_COUNTER __LINE__
#endif

#define ATOM_UNREACHABLE() __assume(0)
#define ATOM_TRAP()        __debugbreak()

#endif
