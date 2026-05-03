#ifndef AXM_LVL_UTILS_H
#define AXM_LVL_UTILS_H

#include "System/Cpp.h" // IWYU pragma: keep

#define AXM_CONCAT_INNER(a, b) a##b
#define AXM_CONCAT(a, b)       AXM_CONCAT_INNER(a, b)

#if AXM_HAS_CXX11
#    define AXM_ALIAS(type, alias) using alias = type
#else
#    define AXM_ALIAS(type, alias) typedef type alias
#endif

#if AXM_HAS_CXX11
#    define AXM_STATIC_ASSERT(cond, msg)              static_assert(cond, msg)
#    define AXM_STATIC_ASSERT_SUPPORT(cond, msg, sml) static_assert(cond, msg)
#else
#    define AXM_STATIC_ASSERT(cond, msg)                                                           \
        int AXM_CONCAT(STATIC_ASSERT_LINE_, __LINE__)[(cond ? 1 : -1)]
#    define AXM_STATIC_ASSERT_SUPPORT(cond, msg, sml) int AXM_CONCAT(sml, __LINE__)[(cond ? 1 : -1)]
#endif

#endif
