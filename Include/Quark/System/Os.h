/**
 * @file Os.h
 * @brief Compile-time operating-system detection.
 *
 * This header identifies the host operating system and publishes AXM_OS_*
 * macros for platform-specific compilation paths.
 *
 * Macro hierarchy:
 * - AXM_OS_WINDOWS
 *   - Windows family base macro.
 *   - Refined into AXM_OS_WIN64 or AXM_OS_WIN32.
 *
 * - AXM_OS_APPLE
 *   - Apple platform base macro.
 *   - Refined into AXM_OS_VISIONOS, AXM_OS_TVOS, AXM_OS_WATCHOS,
 *     AXM_OS_IOS, or AXM_OS_MACOS.
 *   - Also defines AXM_OS_POSIX.
 *
 * - AXM_OS_LINUX
 *   - Linux kernel-based systems.
 *   - Refined into AXM_OS_ANDROID or AXM_OS_POSIX.
 *
 * - AXM_OS_BSD family
 *   - AXM_OS_BSD plus one of AXM_OS_FREEBSD, AXM_OS_OPENBSD,
 *     AXM_OS_NETBSD, or AXM_OS_DRAGONFLY.
 *
 * - Other Unix-like systems
 *   - AXM_OS_CYGWIN, AXM_OS_HAIKU, AXM_OS_SOLARIS, AXM_OS_QNX,
 *     AXM_OS_UNIX_GENERIC.
 *
 * - Legacy systems
 *   - AXM_OS_MSDOS, AXM_OS_OS2.
 *
 * - AXM_OS_UNKNOWN
 *   - Fallback when no platform match is found.
 *
 * POSIX policy:
 * - AXM_OS_POSIX is defined for systems intended to behave like POSIX
 *   environments, including many Unix-like and Apple targets.
 */
#ifndef AXM_QRK_SYSTEM_OS_H
#define AXM_QRK_SYSTEM_OS_H

/** Operating-system detection entry point. */
#if defined(_WIN32) || defined(_WIN64)
#    define AXM_OS_WINDOWS 1
#    if defined(_WIN64)
#        define AXM_OS_WIN64 1
#    elif defined(_WIN32)
#        define AXM_OS_WIN32 1
#    endif

/** Apple platform family detection. */
#elif defined(__APPLE__) && defined(__MACH__)
#    define AXM_OS_POSIX 1
#    define AXM_OS_APPLE 1
#    include <TargetConditionals.h>
#    if defined(TARGET_OS_VISION) && TARGET_OS_VISION
#        define AXM_OS_VISIONOS 1
#    elif defined(TARGET_OS_TV) && TARGET_OS_TV
#        define AXM_OS_TVOS 1
#    elif defined(TARGET_OS_WATCH) && TARGET_OS_WATCH
#        define AXM_OS_WATCHOS 1
#    elif defined(TARGET_OS_IPHONE) && TARGET_OS_IPHONE
#        define AXM_OS_IOS 1
#    else
#        define AXM_OS_MACOS 1
#    endif

/** Linux and Android family detection. */
#elif defined(__linux__)
#    define AXM_OS_LINUX 1
#    if defined(__ANDROID__)
#        define AXM_OS_ANDROID 1
#    else
#        define AXM_OS_POSIX 1
#    endif

/** FreeBSD detection. */
#elif defined(__FreeBSD__)
#    define AXM_OS_POSIX   1
#    define AXM_OS_BSD     1
#    define AXM_OS_FREEBSD 1

/** OpenBSD detection. */
#elif defined(__OpenBSD__)
#    define AXM_OS_POSIX   1
#    define AXM_OS_BSD     1
#    define AXM_OS_OPENBSD 1

/** NetBSD detection. */
#elif defined(__NetBSD__)
#    define AXM_OS_POSIX  1
#    define AXM_OS_BSD    1
#    define AXM_OS_NETBSD 1

/** DragonFly BSD detection. */
#elif defined(__DragonFly__)
#    define AXM_OS_POSIX     1
#    define AXM_OS_BSD       1
#    define AXM_OS_DRAGONFLY 1

/** Cygwin detection. */
#elif defined(__CYGWIN__)
#    define AXM_OS_POSIX  1
#    define AXM_OS_CYGWIN 1

/** Haiku detection. */
#elif defined(__HAIKU__)
#    define AXM_OS_POSIX 1
#    define AXM_OS_HAIKU 1

/** Solaris or illumos detection. */
#elif defined(__sun) && defined(__SVR4)
#    define AXM_OS_POSIX   1
#    define AXM_OS_SOLARIS 1

/** QNX detection. */
#elif defined(__QNX__) || defined(__QNXNTO__)
#    define AXM_OS_POSIX 1
#    define AXM_OS_QNX   1

/** MS-DOS detection. */
#elif defined(__MSDOS__)
#    define AXM_OS_MSDOS 1

/** OS/2 detection. */
#elif defined(__OS2__)
#    define AXM_OS_OS2 1

/** Generic Unix or POSIX-like fallback. */
#elif defined(__unix__) || defined(__unix)
#    define AXM_OS_POSIX        1
#    define AXM_OS_UNIX_GENERIC 1

#else
#    define AXM_OS_UNKNOWN 1
#endif


#if defined(AXM_OS_UNKNOWN)
#    pragma message "AXM: Unknown OS - Please report this issue to increase Axiom's portability."
#    pragma message("AXM: Unknown OS - Please report this issue to increase Axiom's portability.")
#endif

#endif
