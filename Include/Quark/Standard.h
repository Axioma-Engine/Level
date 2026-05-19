#ifndef ATOM_QRK_STANDARD_H
#define ATOM_QRK_STANDARD_H

/**
 * @file Standard.h
 * @brief Facade for standard-language keyword and attribute shims.
 *
 * Selects the appropriate `Standard/Attributes/` and `Standard/Keywords/`
 * headers for the detected compiler family so higher-level code can use
 * consistent macros for language features and standard attributes.
 */

#include "System/Compiler.h"

// IWYU pragma: begin_exports
#if ATOM_COMPILER_GCC_LIKE
#    include "Standard/Attributes/GCC.h"
#    include "Standard/Keywords/GCC.h"
#elif ATOM_COMPILER_MSVC_LIKE
#    include "Standard/Attributes/MSVC.h"
#    include "Standard/Keywords/MSVC.h"
#else
#    include "Standard/Attributes/Unknown.h"
#    include "Standard/Keywords/Unknown.h"

#endif
// IWYU pragma: end_exports

#endif
