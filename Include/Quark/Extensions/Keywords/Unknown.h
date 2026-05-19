#ifndef ATOM_QRK_EXTENSION_KEYWORDS_UNKNOWN_H
#define ATOM_QRK_EXTENSION_KEYWORDS_UNKNOWN_H

/**
 * @file Unknown.h
 * @brief Fallback definitions for extension keyword macros when compiler is unknown.
 *
 * Provides portable defaults for source-location macros, counters and unreachable/trap
 * helpers when no compiler-specific extension set is available.
 */

#include "../../Utils.h"

#define ATOM_LINE            __LINE__
#define ATOM_FILE            __FILE__
#define ATOM_FUNC_NAME       __func__
#define ATOM_FUNC_SIG        __func__
#define ATOM_SOURCE_LOCATION ATOM_FILE ":" ATOM_STRINGIFY(ATOM_LINE)

#if defined(__COUNTER__)
#    define ATOM_COUNTER __COUNTER__
#else
#    define ATOM_COUNTER __LINE__
#endif

#define ATOM_UNREACHABLE() ((void)0)
#define ATOM_TRAP()        ((void)0)

#endif
