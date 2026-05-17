#ifndef AXM_QRK_UTILS_H
#define AXM_QRK_UTILS_H

#include "System.h" // IWYU pragma: keep

#define AXM_CONCAT_INNER(a, b) a##b
#define AXM_CONCAT(a, b)       AXM_CONCAT_INNER(a, b)
#define AXM_CONCAT3(a, b, c)   AXM_CONCAT(AXM_CONCAT(a, b), c)

#define AXM_UNUSED(x) (void)(x)

#if AXM_HAS_CXX11
#    define AXM_ALIAS(type, alias) using alias = type;
#else
#    define AXM_ALIAS(type, alias) typedef type alias;
#endif

#endif
