/**
 * @file Os.h
 * @brief Compile-time operating-system detection.
 *
 * This header identifies the host operating system and publishes ATOM_OS_*
 * macros for platform-specific compilation paths.
 *
 * Macro hierarchy:
 * - ATOM_OS_WINDOWS
 *   - Windows family base macro.
 *   - Refined into ATOM_OS_WIN64 or ATOM_OS_WIN32.
 *
 * - ATOM_OS_APPLE
 *   - Apple platform base macro.
 *   - Refined into ATOM_OS_VISIONOS, ATOM_OS_TVOS, ATOM_OS_WATCHOS,
 *     ATOM_OS_IOS, or ATOM_OS_MACOS.
 *   - Also defines ATOM_OS_POSIX.
 *
 * - ATOM_OS_LINUX
 *   - Linux kernel-based systems.
 *   - Refined into ATOM_OS_ANDROID or ATOM_OS_POSIX.
 *
 * - ATOM_OS_BSD family
 *   - ATOM_OS_BSD plus one of ATOM_OS_FREEBSD, ATOM_OS_OPENBSD,
 *     ATOM_OS_NETBSD, or ATOM_OS_DRAGONFLY.
 *
 * - Other Unix-like systems
 *   - ATOM_OS_CYGWIN, ATOM_OS_HAIKU, ATOM_OS_SOLARIS, ATOM_OS_QNX,
 *     ATOM_OS_UNIX_GENERIC.
 *
 * - Legacy systems
 *   - ATOM_OS_MSDOS, ATOM_OS_OS2.
 *
 * - ATOM_OS_UNKNOWN
 *   - Fallback when no platform match is found.
 *
 * POSIX policy:
 * - ATOM_OS_POSIX is defined for systems intended to behave like POSIX
 *   environments, including many Unix-like and Apple targets.
 */
#ifndef ATOM_QRK_SYSTEM_OS_H
#define ATOM_QRK_SYSTEM_OS_H

/** Operating-system detection entry point. */
#if defined(_WIN32) || defined(_WIN64)
#    define ATOM_OS_WINDOWS 1
#    if defined(_WIN64)
#        define ATOM_OS_WIN64 1
#    elif defined(_WIN32)
#        define ATOM_OS_WIN32 1
#    endif

/** Apple platform family detection. */
#elif defined(__APPLE__) && defined(__MACH__)
#    define ATOM_OS_POSIX 1
#    define ATOM_OS_APPLE 1
#    include <TargetConditionals.h>
#    if defined(TARGET_OS_VISION) && TARGET_OS_VISION
#        define ATOM_OS_VISIONOS 1
#    elif defined(TARGET_OS_TV) && TARGET_OS_TV
#        define ATOM_OS_TVOS 1
#    elif defined(TARGET_OS_WATCH) && TARGET_OS_WATCH
#        define ATOM_OS_WATCHOS 1
#    elif defined(TARGET_OS_IPHONE) && TARGET_OS_IPHONE
#        define ATOM_OS_IOS 1
#    else
#        define ATOM_OS_MACOS 1
#    endif

/** Linux and Android family detection. */
#elif defined(__linux__)
#    define ATOM_OS_LINUX 1
#    if defined(__ANDROID__)
#        define ATOM_OS_ANDROID 1
#    else
#        define ATOM_OS_POSIX 1
#    endif

/** FreeBSD detection. */
#elif defined(__FreeBSD__)
#    define ATOM_OS_POSIX   1
#    define ATOM_OS_BSD     1
#    define ATOM_OS_FREEBSD 1

/** OpenBSD detection. */
#elif defined(__OpenBSD__)
#    define ATOM_OS_POSIX   1
#    define ATOM_OS_BSD     1
#    define ATOM_OS_OPENBSD 1

/** NetBSD detection. */
#elif defined(__NetBSD__)
#    define ATOM_OS_POSIX  1
#    define ATOM_OS_BSD    1
#    define ATOM_OS_NETBSD 1

/** DragonFly BSD detection. */
#elif defined(__DragonFly__)
#    define ATOM_OS_POSIX     1
#    define ATOM_OS_BSD       1
#    define ATOM_OS_DRAGONFLY 1

/** Cygwin detection. */
#elif defined(__CYGWIN__)
#    define ATOM_OS_POSIX  1
#    define ATOM_OS_CYGWIN 1

/** Haiku detection. */
#elif defined(__HAIKU__)
#    define ATOM_OS_POSIX 1
#    define ATOM_OS_HAIKU 1

/** Solaris or illumos detection. */
#elif defined(__sun) && defined(__SVR4)
#    define ATOM_OS_POSIX   1
#    define ATOM_OS_SOLARIS 1

/** QNX detection. */
#elif defined(__QNX__) || defined(__QNXNTO__)
#    define ATOM_OS_POSIX 1
#    define ATOM_OS_QNX   1

/** MS-DOS detection. */
#elif defined(__MSDOS__)
#    define ATOM_OS_MSDOS 1

/** OS/2 detection. */
#elif defined(__OS2__)
#    define ATOM_OS_OS2 1

/** Generic Unix or POSIX-like fallback. */
#elif defined(__unix__) || defined(__unix)
#    define ATOM_OS_POSIX        1
#    define ATOM_OS_UNIX_GENERIC 1

#else
#    define ATOM_OS_UNKNOWN 1
#endif


#if defined(ATOM_OS_UNKNOWN)
#    pragma message "ATOM: Unknown OS - Please report this issue to increase Atom's portability."
#    pragma message("ATOM: Unknown OS - Please report this issue to increase Atom's portability.")
#endif

#endif
