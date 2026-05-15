#ifndef AXM_LVL_UTILS_H
#define AXM_LVL_UTILS_H

#include "System.h" // IWYU pragma: keep

#define AXM_CONCAT_INNER(a, b) a##b
#define AXM_CONCAT(a, b)       AXM_CONCAT_INNER(a, b)
#define AXM_CONCAT3(a, b, c)   AXM_CONCAT(AXM_CONCAT(a, b), c)

#define AXM_UNUSED(x) (void)(x)

#define AXM_KB(x) 1024 * x
#define AXM_MB(x) 1024 * AXM_KB(x)
#define AXM_GB(x) 1024 * AXM_MB(x)
#define AXM_TB(x) 1024 * AXM_GB(x)

#if AXM_HAS_CXX11
#    define AXM_ALIAS(type, alias) using alias = type;
#else
#    define AXM_ALIAS(type, alias) typedef type alias;
#endif

#define AXM_ALIGNBUF(ptr, alignment) ((uptr)ptr + alignment - 1) & ~(alignment - 1)

#if AXM_BUILD_DEBUG
#    include <stdio.h>
#    define AXM_DEBUG_MESSAGE(msg)      fprintf(stdout, msg);
#    define AXM_DEBUG_MESSAGE_ARGS(fmt) printf fmt;
#else
#    define AXM_DEBUG_MESSAGE(msg)
#    define AXM_DEBUG_MESSAGE_ARGS(fmt)
#endif

#if AXM_BUILD_DEBUG
#    include <stdio.h>  // IWYU pragma: export
#    include <stdlib.h> // IWYU pragma: export
#    define AXM_ASSERT(cond)                                                                       \
        if (!(cond)) { abort(); }
#    define AXM_ASSERT_MSG(cond, msg)                                                              \
        if (!(cond)) {                                                                             \
            fprintf(                                                                               \
                stderr,                                                                            \
                "Assertion failed: %s\n"                                                           \
                "File: %s, Line: %d\n"                                                             \
                "Message: %s\n",                                                                   \
                #cond, __FILE__, __LINE__, msg);                                                   \
            abort();                                                                               \
        }
#else
#    define AXM_ASSERT(cond)          AXM_UNUSED(cond);
#    define AXM_ASSERT_MSG(cond, msg) AXM_UNUSED(cond);
#endif

#if AXM_HAS_CXX11
#    define AXM_STATIC_ASSERT(cond, msg) static_assert(cond, msg);
#else
#    define AXM_STATIC_ASSERT(cond, msg)
#endif

#if AXM_HAS_CXX11
#    define AXM_DEFAULT_CONSTRUCTOR(Class)     Class() = default;
#    define AXM_DEFAULT_DESTRUCTOR(Class)      ~Class() = default;
#    define AXM_DEFAULT_COPY(Class)            Class(const Class &) = default;
#    define AXM_DEFAULT_COPY_ASSIGNMENT(Class) Class &operator=(const Class &) = default
#    define AXM_DELETE_COPY(Class)             Class(const Class &) = delete;
#    define AXM_DELETE_COPY_ASSIGNMENT(Class)  Class &operator=(const Class &) = delete;
#    define AXM_DEFAULT_MOVE(Class)            Class(Class &&) noexcept = default;
#    define AXM_DEFAULT_MOVE_ASSIGNMENT(Class) Class &operator=(Class &&) noexcept = default;
#else
#    define AXM_DEFAULT_CONSTRUCTOR(Class)     Class() {};
#    define AXM_DEFAULT_DESTRUCTOR(Class)      ~Class() {};
#    define AXM_DEFAULT_COPY(Class)            Class(const Class &);
#    define AXM_DEFAULT_COPY_ASSIGNMENT(Class) Class &operator=(const Class &);
#    define AXM_DELETE_COPY(Class)                                                                 \
                                                                                                   \
      private:                                                                                     \
        Class(const Class &);                                                                      \
                                                                                                   \
      public:
#    define AXM_DELETE_COPY_ASSIGNMENT(Class)                                                      \
                                                                                                   \
      private:                                                                                     \
        Class &operator=(const Class &);                                                           \
                                                                                                   \
      public:
#    define AXM_DEFAULT_MOVE(Class)
#    define AXM_DEFAULT_MOVE_ASSIGNMENT(Class)
#endif

#endif
