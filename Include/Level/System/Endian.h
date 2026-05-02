/**
 * @file Endian.h
 * @brief Compile-time byte-order detection.
 *
 * This header determines the target endianness and publishes a single
 * AXM_ENDIAN_* macro describing the detected byte order.
 *
 * Macro hierarchy:
 * - AXM_LITTLE_ENDIAN
 *   - Little-endian byte order.
 * - AXM_BIG_ENDIAN
 *   - Big-endian byte order.
 * - AXM_PDP_ENDIAN
 *   - PDP-style mixed byte order.
 * - AXM_ENDIAN_UNKNOWN
 *   - Fallback when no reliable detection path matches.
 *
 * Detection order:
 * - __BYTE_ORDER__ is preferred when available.
 * - Windows defaults to little-endian.
 * - Platform-specific little-endian and big-endian macros are used next.
 * - PDP-11 is handled as a rare legacy case.
 * - Unknown endianness is reported when no rule matches.
 */
#ifndef AXM_LVL_SYSTEM_ENDIAN_H
#define AXM_LVL_SYSTEM_ENDIAN_H

/** Byte-order detection entry point. */
#if defined(__BYTE_ORDER__)
#    if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#        define AXM_LITTLE_ENDIAN 1
#    elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#        define AXM_BIG_ENDIAN 1
#    elif __BYTE_ORDER__ == __ORDER_PDP_ENDIAN__
#        define AXM_PDP_ENDIAN 1
#    endif
#elif defined(_WIN32) || defined(_WIN64)
#    define AXM_LITTLE_ENDIAN 1
#elif defined(__LITTLE_ENDIAN__)                                                                   \
    || defined(__ARMEL__)                                                                          \
    || defined(__THUMBEL__)                                                                        \
    || defined(__AARCH64EL__)                                                                      \
    || defined(__MIPSEL__)                                                                         \
    || defined(__MIPSEL)                                                                           \
    || defined(_MIPSEL)                                                                            \
    || defined(__PPC_LE__)                                                                         \
    || defined(__LOONGARCH_LE__)
#    define AXM_LITTLE_ENDIAN 1
#elif defined(__BIG_ENDIAN__)                                                                      \
    || defined(__ARMEB__)                                                                          \
    || defined(__THUMBEB__)                                                                        \
    || defined(__AARCH64EB__)                                                                      \
    || defined(__MIPSEB__)                                                                         \
    || defined(__MIPSEB)                                                                           \
    || defined(_MIPSEB)                                                                            \
    || defined(__PPC_BE__)                                                                         \
    || defined(__s390__)                                                                           \
    || defined(__s390x__)                                                                          \
    || defined(__LOONGARCH_BE__)
#    define AXM_BIG_ENDIAN 1
#elif defined(__PDP11__)
#    define AXM_PDP_ENDIAN 1
#else
#    define AXM_ENDIAN_UNKNOWN 1
#endif


#if !defined(AXM_LITTLE_ENDIAN) && !defined(AXM_BIG_ENDIAN) && !defined(AXM_PDP_ENDIAN)
#    pragma message "AXM: Unknown endianness"
#    pragma message("AXM: Unknown endianness")
#endif

#endif
