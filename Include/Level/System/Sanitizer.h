/**
 * @file Sanitizer.h
 * @brief Compile-time detection of runtime sanitizer instrumentation.
 *
 * This header detects whether sanitizers are active and exports AXM_SANITIZER_*
 * macros describing the active instrumentation set.
 *
 * Macro hierarchy:
 * - AXM_SANITIZERS_ACTIVE
 *   - Defined when one or more sanitizer modes are detected.
 *
 * - Individual sanitizer flags
 *   - AXM_SANITIZER_ASAN
 *   - AXM_SANITIZER_TSAN
 *   - AXM_SANITIZER_MSAN
 *   - AXM_SANITIZER_UBSAN
 *   - AXM_SANITIZER_LSAN
 *
 * Detection sources:
 * - Clang __has_feature(...) checks are preferred when available.
 * - GCC-style __SANITIZE_* macros are used as a fallback.
 */
#ifndef AXM_LVL_SYSTEM_SANITIZER_H
#define AXM_LVL_SYSTEM_SANITIZER_H

/** Sanitizer instrumentation detection. */
#if defined(__has_feature)
#    if __has_feature(address_sanitizer)
#        define AXM_SANITIZER_ASAN    1
#        define AXM_SANITIZERS_ACTIVE 1
#    endif
#    if __has_feature(thread_sanitizer)
#        define AXM_SANITIZER_TSAN    1
#        define AXM_SANITIZERS_ACTIVE 1
#    endif
#    if __has_feature(memory_sanitizer)
#        define AXM_SANITIZER_MSAN    1
#        define AXM_SANITIZERS_ACTIVE 1
#    endif
#    if __has_feature(undefined_behavior_sanitizer)
#        define AXM_SANITIZER_UBSAN   1
#        define AXM_SANITIZERS_ACTIVE 1
#    endif
#    if __has_feature(leak_sanitizer)
#        define AXM_SANITIZER_LSAN    1
#        define AXM_SANITIZERS_ACTIVE 1
#    endif
#else
#    if defined(__SANITIZE_ADDRESS__)
#        define AXM_SANITIZER_ASAN    1
#        define AXM_SANITIZERS_ACTIVE 1
#    endif
#    if defined(__SANITIZE_THREAD__)
#        define AXM_SANITIZER_TSAN    1
#        define AXM_SANITIZERS_ACTIVE 1
#    endif
#endif

#endif
