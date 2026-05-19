/**
 * @file Sanitizer.h
 * @brief Compile-time detection of runtime sanitizer instrumentation.
 *
 * This header detects whether sanitizers are active and exports ATOM_SANITIZER_*
 * macros describing the active instrumentation set.
 *
 * Macro hierarchy:
 * - ATOM_SANITIZERS_ACTIVE
 *   - Defined when one or more sanitizer modes are detected.
 *
 * - Individual sanitizer flags
 *   - ATOM_SANITIZER_ASAN
 *   - ATOM_SANITIZER_TSAN
 *   - ATOM_SANITIZER_MSAN
 *   - ATOM_SANITIZER_UBSAN
 *   - ATOM_SANITIZER_LSAN
 *
 * Detection sources:
 * - Clang __has_feature(...) checks are preferred when available.
 * - GCC-style __SANITIZE_* macros are used as a fallback.
 */
#ifndef ATOM_QRK_SYSTEM_SANITIZER_H
#define ATOM_QRK_SYSTEM_SANITIZER_H

/** Sanitizer instrumentation detection. */
#if defined(__has_feature)
#    if __has_feature(address_sanitizer)
#        define ATOM_SANITIZER_ASAN    1
#        define ATOM_SANITIZERS_ACTIVE 1
#    endif
#    if __has_feature(thread_sanitizer)
#        define ATOM_SANITIZER_TSAN    1
#        define ATOM_SANITIZERS_ACTIVE 1
#    endif
#    if __has_feature(memory_sanitizer)
#        define ATOM_SANITIZER_MSAN    1
#        define ATOM_SANITIZERS_ACTIVE 1
#    endif
#    if __has_feature(undefined_behavior_sanitizer)
#        define ATOM_SANITIZER_UBSAN   1
#        define ATOM_SANITIZERS_ACTIVE 1
#    endif
#    if __has_feature(leak_sanitizer)
#        define ATOM_SANITIZER_LSAN    1
#        define ATOM_SANITIZERS_ACTIVE 1
#    endif
#else
#    if defined(__SANITIZE_ADDRESS__)
#        define ATOM_SANITIZER_ASAN    1
#        define ATOM_SANITIZERS_ACTIVE 1
#    endif
#    if defined(__SANITIZE_THREAD__)
#        define ATOM_SANITIZER_TSAN    1
#        define ATOM_SANITIZERS_ACTIVE 1
#    endif
#endif

#endif
