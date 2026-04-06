/**
 * @file System.h
 * @brief Low-level platform, architecture, compiler, and OS detection.
 *
 * @details
 * This header provides comprehensive compile-time detection of:
 * - Operating systems (Windows, Linux, macOS, BSD variants, legacy systems)
 * - CPU architectures (x86, ARM, RISC-V, PowerPC, SPARC, MIPS, LoongArch, etc.)
 * - Compilers (GCC, Clang, MSVC, Intel ICC, Borland, Watcom, Sun Studio, etc.)
 * - C++ standard version (C++98 through C++26)
 * - Build type (debug vs. release)
 * - Endianness (little, big, or PDP-11)
 * - Pointer width (32-bit vs. 64-bit)
 * - SIMD capabilities (SSE, AVX, NEON, SVE, etc.)
 *
 * All macros use the `AXM_` prefix. Most are defined to 1 when true,
 * and left undefined when false. This allows clean `#ifdef` checks.
 *
 * @note
 * This is a C++-only header. Including from C code will generate a warning.
 *
 * @warning
 * The macros defined here are implementation-defined and platform-specific.
 * Always use portable, standard alternatives when available (e.g., stdint.h,
 * limits.h). Use these macros for:
 * - Conditional compilation based on platform capabilities
 * - Choosing fast paths for specific hardware
 * - Implementing fallbacks for unsupported features
 *
 * @see Attributes.h - Use AXM_HAS_ATTRIBUTE() to check feature availability
 * @see Features.h - Use AXM_HAS_BUILTIN(), AXM_HAS_CPP_ATTRIBUTE(), etc.
 * @see Types.h - Portable type aliases based on detected platform
 */
#ifndef AXM_LVL_SYSTEM_H
#define AXM_LVL_SYSTEM_H
#pragma once


/**
 * @defgroup AXM_CXX_VERSION C++ Standard Version Detection
 * @brief Detects and reports the C++ standard version.
 *
 * @details
 * Defines AXM_CXX_STANDARD to the detected C++ version, matching __cplusplus
 * conventions (199711L for C++98, 201103L for C++11, etc.).
 *
 * Also defines AXM_HAS_CXXxx macros (e.g., AXM_HAS_CXX11, AXM_HAS_CXX17)
 * for simple feature gating in preprocessor conditionals.
 *
 * @{
 */
#if !defined(__cplusplus) && !defined(_MSVC_LANG)
#    warning "System.h is a C++-only header. Do not include it from C translation units."
#endif
/** @brief C++ is the language being compiled. Always 1. */
#define AXM_LANGUAGE_CXX 1

/** @brief Detected C++ standard version (matches __cplusplus values).
 *
 * Values:
 * - 199711L: C++98 / C++03
 * - 201103L: C++11
 * - 201402L: C++14
 * - 201703L: C++17
 * - 202002L: C++20
 * - 202302L: C++23
 * - 202400L: C++26
 *
 * @note MSVC uses _MSVC_LANG instead of __cplusplus when compiling in
 *       strict mode; this macro handles both.
 */
#if defined(_MSVC_LANG)
#    define AXM_CXX_STANDARD _MSVC_LANG
#else
#    define AXM_CXX_STANDARD __cplusplus
#endif

/* Fallback for pre-standard compilers or when __cplusplus is not set */
#if AXM_CXX_STANDARD == 0
#    define AXM_CXX_STANDARD 199711L
#endif
/** @} */


/**
 * @defgroup AXM_OS_DETECTION Operating System Detection
 * @brief Detects the target operating system.
 *
 * @details
 * Defines one or more AXM_OS_* macros to 1 based on the target OS.
 *
 * Modern OSes:
 * - @c AXM_OS_WINDOWS (Win32, Win64)
 * - @c AXM_OS_LINUX (Linux, including Android)
 * - @c AXM_OS_APPLE (macOS, iOS, tvOS, watchOS, visionOS)
 *
 * BSD family:
 * - @c AXM_OS_FREEBSD, @c AXM_OS_OPENBSD, @c AXM_OS_NETBSD, @c AXM_OS_DRAGONFLY
 *
 * Legacy & specialized:
 * - @c AXM_OS_SOLARIS, @c AXM_OS_QNX, @c AXM_OS_HAIKU
 * - @c AXM_OS_CYGWIN (Cygwin on Windows)
 * - @c AXM_OS_MSDOS, @c AXM_OS_OS2 (ancient)
 * - @c AXM_OS_POSIX (BSD, Linux, QNX, Solaris, etc. - defined for compatibility)
 *
 * If the OS is not recognized, @c AXM_OS_UNKNOWN is defined instead.
 *
 * @{
 */
#if defined(_WIN32) || defined(_WIN64)
/** @brief Windows OS (32-bit or 64-bit). */
#    define AXM_OS_WINDOWS 1
#    if defined(_WIN64)
/** @brief Windows 64-bit. */
#        define AXM_OS_WIN64 1
#    else
/** @brief Windows 32-bit. */
#        define AXM_OS_WIN32 1
#    endif

#elif defined(__APPLE__) && defined(__MACH__)
/** @brief Apple OS (macOS, iOS, tvOS, watchOS, visionOS). */
#    define AXM_OS_POSIX 1
#    define AXM_OS_APPLE 1
#    include <TargetConditionals.h>
#    if defined(TARGET_OS_VISION) && TARGET_OS_VISION
/** @brief Apple visionOS. */
#        define AXM_OS_VISIONOS 1
#    elif defined(TARGET_OS_TV) && TARGET_OS_TV
/** @brief Apple tvOS. */
#        define AXM_OS_TVOS 1
#    elif defined(TARGET_OS_WATCH) && TARGET_OS_WATCH
/** @brief Apple watchOS. */
#        define AXM_OS_WATCHOS 1
#    elif defined(TARGET_OS_IPHONE) && TARGET_OS_IPHONE
/** @brief Apple iOS. */
#        define AXM_OS_IOS 1
#    else
/** @brief Apple macOS. */
#        define AXM_OS_MACOS 1
#    endif

#elif defined(__linux__)
/** @brief Linux kernel (including Android). */
#    define AXM_OS_LINUX 1
#    if defined(__ANDROID__)
/** @brief Android (Linux-based). */
#        define AXM_OS_ANDROID 1
#    else
/** @brief Linux (not Android). */
#        define AXM_OS_POSIX 1
#    endif

#elif defined(__FreeBSD__)
/** @brief FreeBSD. */
#    define AXM_OS_POSIX   1
#    define AXM_OS_BSD     1
#    define AXM_OS_FREEBSD 1

#elif defined(__OpenBSD__)
/** @brief OpenBSD. */
#    define AXM_OS_POSIX   1
#    define AXM_OS_BSD     1
#    define AXM_OS_OPENBSD 1

#elif defined(__NetBSD__)
/** @brief NetBSD. */
#    define AXM_OS_POSIX  1
#    define AXM_OS_BSD    1
#    define AXM_OS_NETBSD 1

#elif defined(__DragonFly__)
/** @brief DragonFly BSD. */
#    define AXM_OS_POSIX     1
#    define AXM_OS_DRAGONFLY 1

#elif defined(__CYGWIN__)
/** @brief Cygwin (POSIX on Windows). */
#    define AXM_OS_POSIX  1
#    define AXM_OS_CYGWIN 1

#elif defined(__HAIKU__)
/** @brief Haiku (BeOS successor). */
#    define AXM_OS_POSIX 1
#    define AXM_OS_HAIKU 1

#elif defined(__sun) && defined(__SVR4)
/** @brief Solaris. */
#    define AXM_OS_POSIX   1
#    define AXM_OS_SOLARIS 1

#elif defined(__QNX__) || defined(__QNXNTO__)
/** @brief QNX Neutrino RTOS. */
#    define AXM_OS_POSIX 1
#    define AXM_OS_QNX   1

#elif defined(__MSDOS__)
/** @brief MS-DOS (legacy). */
#    define AXM_OS_MSDOS 1

#elif defined(__OS2__)
/** @brief IBM OS/2 (legacy). */
#    define AXM_OS_OS2 1

#elif defined(__unix__) || defined(__unix)
/** @brief Generic UNIX-like system. */
#    define AXM_OS_POSIX        1
#    define AXM_OS_UNIX_GENERIC 1

#else
/** @brief Operating system could not be determined. */
#    define AXM_OS_UNKNOWN 1
#endif
/** @} */


/**
 * @defgroup AXM_ARCH_DETECTION CPU Architecture Detection
 * @brief Detects the target CPU architecture.
 *
 * @details
 * Defines one AXM_ARCH_* macro to 1 based on the target architecture.
 *
 * Modern architectures:
 * - @c AXM_ARCH_X64 (x86-64, AMD64)
 * - @c AXM_ARCH_X86 (i386 and later 32-bit x86)
 * - @c AXM_ARCH_ARM64 (AArch64)
 * - @c AXM_ARCH_ARM32 (32-bit ARM)
 * - @c AXM_ARCH_RISCV (RISC-V)
 *
 * Legacy architectures:
 * - @c AXM_ARCH_SPARC (SPARC, SPARC64)
 * - @c AXM_ARCH_MIPS (MIPS, MIPS64)
 * - @c AXM_ARCH_PPC (PowerPC 32/64-bit)
 * - @c AXM_ARCH_IA64 (Itanium)
 * - @c AXM_ARCH_S390 (IBM System z)
 * - @c AXM_ARCH_VAX (DEC VAX - ancient)
 * - @c AXM_ARCH_M68K (Motorola 68000 - ancient)
 *
 * Other:
 * - @c AXM_ARCH_WASM (WebAssembly)
 * - @c AXM_ARCH_LOONGARCH (LoongArch)
 *
 * If the architecture is not recognized, @c AXM_ARCH_UNKNOWN is defined.
 *
 * Also defines family macros (e.g., @c AXM_ARCH_X86_FAMILY for both x86 and x64).
 *
 * @{
 */

/** @defgroup AXM_ARCH_X86 x86 / x86-64 (Intel, AMD)
 * @brief x86 family: 32-bit (i386+) and 64-bit (x86-64/AMD64).
 * @{ */
#if defined(__x86_64__) || defined(__amd64__) || defined(_M_X64) || defined(_M_AMD64)
/** @brief 64-bit x86 (x86-64, AMD64). */
#    define AXM_ARCH_X64        1
/** @brief x86 family (includes x86 32-bit and x86-64). */
#    define AXM_ARCH_X86_FAMILY 1
#elif defined(__i386__)                                                                            \
    || defined(__i486__)                                                                           \
    || defined(__i586__)                                                                           \
    || defined(__i686__)                                                                           \
    || defined(_M_IX86)
/** @brief 32-bit x86 (i386, i486, i586, i686). */
#    define AXM_ARCH_X86        1
/** @brief x86 family. */
#    define AXM_ARCH_X86_FAMILY 1
#endif
/** @} */

/** @defgroup AXM_ARCH_ARM ARM (Advanced RISC Machine)
 * @brief ARM architecture: 32-bit and 64-bit variants.
 * @{ */
#if defined(_M_ARM64EC)
/** @brief ARM64EC (x64 emulation). */
#    define AXM_ARCH_ARM64EC    1
/** @brief 64-bit ARM (AArch64). */
#    define AXM_ARCH_ARM64      1
/** @brief ARM family. */
#    define AXM_ARCH_ARM_FAMILY 1
#elif defined(__aarch64__) || defined(_M_ARM64)
/** @brief 64-bit ARM (AArch64). */
#    define AXM_ARCH_ARM64      1
/** @brief ARM family. */
#    define AXM_ARCH_ARM_FAMILY 1
#elif defined(__arm__) || defined(__ARM_ARCH) || defined(_M_ARM)
/** @brief 32-bit ARM. */
#    define AXM_ARCH_ARM32      1
/** @brief ARM family. */
#    define AXM_ARCH_ARM_FAMILY 1
#endif
/** @} */

/** @defgroup AXM_ARCH_RISCV RISC-V
 * @brief RISC-V open ISA.
 * @{ */
#if defined(__riscv)
/** @brief RISC-V architecture. */
#    define AXM_ARCH_RISCV 1
#    if defined(__riscv_xlen)
#        if __riscv_xlen == 64
/** @brief 64-bit RISC-V. */
#            define AXM_ARCH_RISCV64 1
#        elif __riscv_xlen == 32
/** @brief 32-bit RISC-V. */
#            define AXM_ARCH_RISCV32 1
#        endif
#    else
/** @brief RISC-V with unknown width. */
#        define AXM_ARCH_RISCV_UNKNOWN 1
#    endif
#endif
/** @} */

/** @defgroup AXM_ARCH_OTHER Other Architectures
 * @brief WebAssembly, MIPS, PowerPC, SPARC, LoongArch, etc.
 * @{ */
/** @brief WebAssembly. */
#if defined(__EMSCRIPTEN__) || defined(__wasm__)
#    define AXM_ARCH_WASM 1
#endif
/** @brief MIPS and MIPS64. */
#if defined(__mips__) || defined(__mips)
#    define AXM_ARCH_MIPS_FAMILY 1
#    if defined(__mips64) || defined(__mips64__)
#        define AXM_ARCH_MIPS64 1
#    elif defined(__mips32) || defined(__mips32__)
#        define AXM_ARCH_MIPS32 1
#    else
#        define AXM_ARCH_MIPS_UNKNOWN 1
#    endif
#endif
/** @brief PowerPC 32-bit and 64-bit. */
#if defined(__PPC64__) || defined(__powerpc64__) || defined(_ARCH_PPC64)
#    define AXM_ARCH_PPC64      1
#    define AXM_ARCH_PPC_FAMILY 1
#elif defined(__PPC__) || defined(__powerpc__) || defined(_ARCH_PPC)
#    define AXM_ARCH_PPC32      1
#    define AXM_ARCH_PPC_FAMILY 1
#endif
/** @brief SPARC and SPARC64. */
#if defined(__sparc__) || defined(__sparc)
#    define AXM_ARCH_SPARC_FAMILY 1
#    if defined(__sparcv9) || defined(__sparc_v9__)
#        define AXM_ARCH_SPARC64 1
#    else
#        define AXM_ARCH_SPARC32 1
#    endif
#endif
/** @brief LoongArch (LOONGSON). */
#if defined(__loongarch__)
#    define AXM_ARCH_LOONGARCH_FAMILY 1
#    if defined(__loongarch64)
#        define AXM_ARCH_LOONGARCH64 1
#    else
#        define AXM_ARCH_LOONGARCH32 1
#    endif
#endif
/** @brief IBM System z (mainframe, 64-bit and 31-bit). */
#if defined(__s390x__)
#    define AXM_ARCH_S390X 1
#elif defined(__s390__)
#    define AXM_ARCH_S390 1
#endif
/** @brief Itanium (IA-64). */
#if defined(__ia64__) || defined(_M_IA64) || defined(__ia64)
#    define AXM_ARCH_IA64 1
#endif
/** @brief DEC VAX (ancient, 32-bit). */
#if defined(__vax__)
#    define AXM_ARCH_VAX 1
#endif
/** @brief Motorola 68000 (ancient, 32-bit). */
#if defined(__m68k__) || defined(__m68000__)
#    define AXM_ARCH_M68K 1
#endif
/** @} */

#if !defined(AXM_ARCH_X86_FAMILY)                                                                  \
    && !defined(AXM_ARCH_ARM_FAMILY)                                                               \
    && !defined(AXM_ARCH_RISCV)                                                                    \
    && !defined(AXM_ARCH_WASM)                                                                     \
    && !defined(AXM_ARCH_MIPS_FAMILY)                                                              \
    && !defined(AXM_ARCH_PPC_FAMILY)                                                               \
    && !defined(AXM_ARCH_SPARC_FAMILY)                                                             \
    && !defined(AXM_ARCH_LOONGARCH_FAMILY)                                                         \
    && !defined(AXM_ARCH_S390X)                                                                    \
    && !defined(AXM_ARCH_S390)                                                                     \
    && !defined(AXM_ARCH_IA64)                                                                     \
    && !defined(AXM_ARCH_VAX)                                                                      \
    && !defined(AXM_ARCH_M68K)
/** @brief Architecture could not be determined. */
#    define AXM_ARCH_UNKNOWN 1
#endif
/** @} */


/**
 * @defgroup AXM_COMPILER_DETECTION Compiler Detection
 * @brief Detects the C++ compiler and version.
 *
 * @details
 * Defines one primary AXM_COMPILER_* macro and related compatibility macros:
 *
 * **Compiler Families (for conditional compilation):**
 * - @c AXM_COMPILER_MSVC_LIKE: MSVC, Clang-cl (uses __declspec)
 * - @c AXM_COMPILER_GCC_LIKE: GCC, Clang, MinGW, Intel (uses __attribute__)
 *
 * **Modern compilers:**
 * - @c AXM_COMPILER_MSVC (Microsoft Visual C++)
 * - @c AXM_COMPILER_GCC (GNU C++ Compiler)
 * - @c AXM_COMPILER_CLANG (Clang/LLVM)
 * - @c AXM_COMPILER_INTEL (Intel ICC)
 * - @c AXM_COMPILER_CLANG_CL (Clang-cl, MSVC-compatible)
 * - @c AXM_COMPILER_INTEL_LLVM (Intel oneAPI LLVM)
 * - @c AXM_COMPILER_MINGW (MinGW: GCC-like)
 * - @c AXM_COMPILER_ARMCC (ARM Compiler, Keil MDK)
 * - @c AXM_COMPILER_IBM_XL (IBM XL Compiler)
 * - @c AXM_COMPILER_NVCC (NVIDIA CUDA Compiler)
 *
 * **Legacy/specialized compilers (use own macros):**
 * - @c AXM_COMPILER_BORLAND (Borland C++, pre-2008)
 * - @c AXM_COMPILER_WATCOM (Watcom C/C++, pre-2009)
 * - @c AXM_COMPILER_SUNPRO (Sun Studio, legacy)
 * - @c AXM_COMPILER_METROWERKS (Metrowerks CodeWarrior, pre-2005)
 * - @c AXM_COMPILER_TINYC (TinyC, lightweight)
 *
 * All define: AXM_COMPILER_VERSION_MAJOR, _MINOR, _PATCH
 *
 * If the compiler is not recognized, @c AXM_COMPILER_UNKNOWN is defined.
 *
 * @{
 */
#if defined(__NVCC__)
/** @brief NVIDIA CUDA Compiler (GCC-like). */
#    define AXM_COMPILER_NVCC          1
#    define AXM_COMPILER_GCC_LIKE      1
#    define AXM_COMPILER_VERSION_MAJOR __CUDACC_VER_MAJOR__
#    define AXM_COMPILER_VERSION_MINOR __CUDACC_VER_MINOR__
#    define AXM_COMPILER_VERSION_PATCH __CUDACC_VER_BUILD__

#elif defined(__clang__) && defined(_MSC_VER)
/** @brief Clang-cl (Clang front-end with MSVC back-end). */
#    define AXM_COMPILER_CLANG_CL      1
#    define AXM_COMPILER_MSVC_LIKE     1
#    define AXM_COMPILER_VERSION_MAJOR __clang_major__
#    define AXM_COMPILER_VERSION_MINOR __clang_minor__
#    define AXM_COMPILER_VERSION_PATCH __clang_patchlevel__

#elif defined(__clang__)
/** @brief Clang/LLVM C++ compiler. */
#    define AXM_COMPILER_CLANG         1
#    define AXM_COMPILER_GCC_LIKE      1
#    define AXM_COMPILER_VERSION_MAJOR __clang_major__
#    define AXM_COMPILER_VERSION_MINOR __clang_minor__
#    define AXM_COMPILER_VERSION_PATCH __clang_patchlevel__

#elif defined(__INTEL_LLVM_COMPILER)
/** @brief Intel LLVM Compiler (oneAPI). */
#    define AXM_COMPILER_INTEL_LLVM    1
#    define AXM_COMPILER_GCC_LIKE      1
#    define AXM_COMPILER_VERSION_MAJOR (__INTEL_LLVM_COMPILER / 10000)
#    define AXM_COMPILER_VERSION_MINOR ((__INTEL_LLVM_COMPILER % 10000) / 100)
#    define AXM_COMPILER_VERSION_PATCH (__INTEL_LLVM_COMPILER % 100)

#elif defined(__INTEL_COMPILER) || defined(__ICC)
/** @brief Intel C++ Compiler. */
#    define AXM_COMPILER_INTEL         1
#    define AXM_COMPILER_GCC_LIKE      1
#    define AXM_COMPILER_VERSION_MAJOR (__INTEL_COMPILER / 100)
#    define AXM_COMPILER_VERSION_MINOR (__INTEL_COMPILER % 100)
#    define AXM_COMPILER_VERSION_PATCH 0

#elif defined(__GNUC__) && (defined(__MINGW32__) || defined(__MINGW64__))
/** @brief MinGW (GNU tools for Windows). */
#    define AXM_COMPILER_MINGW    1
#    define AXM_COMPILER_GCC_LIKE 1
#    if defined(__MINGW64__)
/** @brief MinGW 64-bit. */
#        define AXM_COMPILER_MINGW64 1
#    else
/** @brief MinGW 32-bit. */
#        define AXM_COMPILER_MINGW32 1
#    endif
#    define AXM_COMPILER_VERSION_MAJOR __GNUC__
#    define AXM_COMPILER_VERSION_MINOR __GNUC_MINOR__
#    define AXM_COMPILER_VERSION_PATCH __GNUC_PATCHLEVEL__

#elif defined(__GNUC__)
/** @brief GNU C++ Compiler (g++). */
#    define AXM_COMPILER_GCC           1
#    define AXM_COMPILER_GCC_LIKE      1
#    define AXM_COMPILER_VERSION_MAJOR __GNUC__
#    define AXM_COMPILER_VERSION_MINOR __GNUC_MINOR__
#    define AXM_COMPILER_VERSION_PATCH __GNUC_PATCHLEVEL__

#elif defined(_MSC_VER)
/** @brief Microsoft Visual C++ Compiler. */
#    define AXM_COMPILER_MSVC          1
#    define AXM_COMPILER_MSVC_LIKE     1
#    define AXM_COMPILER_VERSION_MAJOR (_MSC_VER / 100)
#    define AXM_COMPILER_VERSION_MINOR (_MSC_VER % 100)
#    define AXM_COMPILER_VERSION_PATCH (_MSVC_FULL_VER % 100000)

#elif defined(__ARMCC_VERSION)
/** @brief ARM Compiler (Keil MDK). Uses own macro; limited attribute support. */
#    define AXM_COMPILER_ARMCC         1
#    define AXM_COMPILER_VERSION_MAJOR (__ARMCC_VERSION / 1000000)
#    define AXM_COMPILER_VERSION_MINOR ((__ARMCC_VERSION % 1000000) / 10000)
#    define AXM_COMPILER_VERSION_PATCH (__ARMCC_VERSION % 10000)

#elif defined(__ibmxl__) || defined(__xlC__)
/** @brief IBM XL Compiler. Uses own macro; limited attribute support. */
#    define AXM_COMPILER_IBM_XL 1
#    if defined(__ibmxl__)
#        define AXM_COMPILER_VERSION_MAJOR __ibmxl_version__
#        define AXM_COMPILER_VERSION_MINOR __ibmxl_release__
#        define AXM_COMPILER_VERSION_PATCH __ibmxl_modification__
#    else
#        define AXM_COMPILER_VERSION_MAJOR (__xlC__ >> 8)
#        define AXM_COMPILER_VERSION_MINOR (__xlC__ & 0xFF)
#        define AXM_COMPILER_VERSION_PATCH 0
#    endif

#elif defined(__BORLANDC__)
/** @brief Borland C++ (legacy, pre-2008). Uses own macro. */
#    define AXM_COMPILER_BORLAND       1
#    define AXM_COMPILER_VERSION_MAJOR (__BORLANDC__ >> 8)
#    define AXM_COMPILER_VERSION_MINOR (__BORLANDC__ & 0xFF)
#    define AXM_COMPILER_VERSION_PATCH 0

#elif defined(__WATCOMC__)
/** @brief Watcom C/C++ (legacy, pre-2009). Uses own macro. */
#    define AXM_COMPILER_WATCOM        1
#    define AXM_COMPILER_VERSION_MAJOR (__WATCOMC__ / 100)
#    define AXM_COMPILER_VERSION_MINOR (__WATCOMC__ % 100)
#    define AXM_COMPILER_VERSION_PATCH 0

#elif defined(__SUNPRO_CC)
/** @brief Sun Studio C++ (legacy). Uses own macro. */
#    define AXM_COMPILER_SUNPRO        1
#    define AXM_COMPILER_VERSION_MAJOR (__SUNPRO_CC / 0x100)
#    define AXM_COMPILER_VERSION_MINOR (__SUNPRO_CC / 0x10 & 0xF)
#    define AXM_COMPILER_VERSION_PATCH (__SUNPRO_CC & 0xF)

#elif defined(__MWERKS__)
/** @brief Metrowerks CodeWarrior (legacy, pre-2005). Uses own macro. */
#    define AXM_COMPILER_METROWERKS    1
#    define AXM_COMPILER_VERSION_MAJOR (__MWERKS__ / 0x1000)
#    define AXM_COMPILER_VERSION_MINOR (__MWERKS__ / 0x100 & 0xF)
#    define AXM_COMPILER_VERSION_PATCH (__MWERKS__ & 0xFF)

#elif defined(_COMPILER_VERSION)
/** @brief TinyC Compiler (lightweight). Uses own macro. */
#    define AXM_COMPILER_TINYC         1
#    define AXM_COMPILER_VERSION_MAJOR (_COMPILER_VERSION / 100)
#    define AXM_COMPILER_VERSION_MINOR (_COMPILER_VERSION % 100)
#    define AXM_COMPILER_VERSION_PATCH 0

#else
/** @brief Compiler could not be determined. */
#    define AXM_COMPILER_UNKNOWN 1
#endif
/** @} */


/**
 * @defgroup AXM_CXX_FEATURES C++ Language Features
 * @brief Compile-time detection of C++ standard features.
 *
 * @details
 * Defines AXM_HAS_CXXxx macros (where xx is the standard year) based on
 * detected C++ version. Use these for simple feature gating:
 *
 * @code
 * #if defined(AXM_HAS_CXX17)
 *     // Use C++17 features
 * #elif defined(AXM_HAS_CXX14)
 *     // Use C++14 features as fallback
 * #else
 *     // C++11 or earlier
 * #endif
 * @endcode
 *
 * @{
 */
#if AXM_CXX_STANDARD >= 202400L
/** @brief C++26 or later is available. */
#    define AXM_HAS_CXX26 1
#endif

#if AXM_CXX_STANDARD >= 202302L
/** @brief C++23 or later is available. */
#    define AXM_HAS_CXX23 1
#endif

#if AXM_CXX_STANDARD >= 202002L
/** @brief C++20 or later is available. */
#    define AXM_HAS_CXX20 1
#endif

#if AXM_CXX_STANDARD >= 201703L
/** @brief C++17 or later is available. */
#    define AXM_HAS_CXX17 1
#endif

#if AXM_CXX_STANDARD >= 201402L
/** @brief C++14 or later is available. */
#    define AXM_HAS_CXX14 1
#endif

#if AXM_CXX_STANDARD >= 201103L
/** @brief C++11 or later is available. */
#    define AXM_HAS_CXX11 1
#endif

#if AXM_CXX_STANDARD >= 199711L
/** @brief C++98 (original standard) or later. */
#    define AXM_HAS_CXX98 1
#endif
/** @} */


/**
 * @defgroup AXM_BUILD_TYPE Build Type Detection
 * @brief Detects debug vs. release build configuration.
 *
 * @details
 * Checks NDEBUG to determine build type. Exactly one of
 * AXM_BUILD_DEBUG or AXM_BUILD_RELEASE is defined.
 *
 * @{
 */
#if defined(NDEBUG)
/** @brief Release build (NDEBUG defined, assertions disabled). */
#    define AXM_BUILD_RELEASE 1
#else
/** @brief Debug build (NDEBUG not defined, assertions enabled). */
#    define AXM_BUILD_DEBUG 1
#endif
/** @} */


/**
 * @defgroup AXM_SANITIZERS Sanitizer Detection
 * @brief Detects active code sanitizers (ASAN, TSAN, UBSAN, etc.).
 *
 * @details
 * When AddressSanitizer, ThreadSanitizer, MemorySanitizer, UndefinedBehaviorSanitizer,
 * or LeakSanitizer is active, corresponding AXM_SANITIZER_* macros are defined to 1.
 *
 * If any sanitizer is active, AXM_SANITIZERS_ACTIVE is also defined.
 *
 * Use this to enable instrumentation or alter behavior under sanitizers:
 *
 * @code
 * #ifdef AXM_SANITIZERS_ACTIVE
 *     // Disable aggressive optimizations that interfere with sanitizers
 * #endif
 * @endcode
 *
 * @{
 */
#if defined(__has_feature)
#    if __has_feature(address_sanitizer)
/** @brief AddressSanitizer (ASAN) is active. */
#        define AXM_SANITIZER_ASAN 1
#    endif
#    if __has_feature(thread_sanitizer)
/** @brief ThreadSanitizer (TSAN) is active. */
#        define AXM_SANITIZER_TSAN 1
#    endif
#    if __has_feature(memory_sanitizer)
/** @brief MemorySanitizer (MSAN) is active. */
#        define AXM_SANITIZER_MSAN 1
#    endif
#    if __has_feature(undefined_behavior_sanitizer)
/** @brief UndefinedBehaviorSanitizer (UBSAN) is active. */
#        define AXM_SANITIZER_UBSAN 1
#    endif
#    if __has_feature(leak_sanitizer)
/** @brief LeakSanitizer (LSAN) is active. */
#        define AXM_SANITIZER_LSAN 1
#    endif
#else
#    if defined(__SANITIZE_ADDRESS__)
#        define AXM_SANITIZER_ASAN 1
#    endif
#    if defined(__SANITIZE_THREAD__)
#        define AXM_SANITIZER_TSAN 1
#    endif
#    if defined(__SANITIZE_UNDEFINED__)
#        define AXM_SANITIZER_UBSAN 1
#    endif
#endif

/** @brief At least one sanitizer is active. */
#if defined(AXM_SANITIZER_ASAN)                                                                    \
    || defined(AXM_SANITIZER_TSAN)                                                                 \
    || defined(AXM_SANITIZER_MSAN)                                                                 \
    || defined(AXM_SANITIZER_UBSAN)                                                                \
    || defined(AXM_SANITIZER_LSAN)
#    define AXM_SANITIZERS_ACTIVE 1
#endif
/** @} */


/**
 * @defgroup AXM_ENDIANNESS Byte Order (Endianness) Detection
 * @brief Detects the byte order of the target platform.
 *
 * @details
 * Defines one of: AXM_LITTLE_ENDIAN, AXM_BIG_ENDIAN, AXM_PDP_ENDIAN, or AXM_ENDIAN_UNKNOWN.
 *
 * Most modern systems use little-endian (x86, ARM, RISC-V).
 * Big-endian is used on some legacy systems (PowerPC, SPARC, MIPS in BE mode).
 * PDP-endian (middle-endian) was used on DEC PDP-11 systems.
 *
 * @{
 */
#if defined(__BYTE_ORDER__)
#    if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
/** @brief Platform uses little-endian byte order. */
#        define AXM_LITTLE_ENDIAN 1
#    elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
/** @brief Platform uses big-endian byte order. */
#        define AXM_BIG_ENDIAN 1
#    elif __BYTE_ORDER__ == __ORDER_PDP_ENDIAN__
/** @brief Platform uses PDP-endian (middle-endian) byte order. */
#        define AXM_PDP_ENDIAN 1
#    endif
#elif defined(AXM_OS_WINDOWS)
#    define AXM_LITTLE_ENDIAN 1
#elif defined(__LITTLE_ENDIAN__)                                                                   \
    || defined(__ARMEL__)                                                                          \
    || defined(__THUMBEL__)                                                                        \
    || defined(__AARCH64EL__)                                                                      \
    || defined(__MIPSEL__)                                                                         \
    || defined(__MIPSEL)                                                                           \
    || defined(_MIPSEL)                                                                            \
    || defined(__PPC_LE__)                                                                         \
    || defined(__FLOAT_WORD_ORDER__)                                                               \
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
#elif defined(AXM_ARCH_VAX) || defined(__PDP11__)
/** @brief Platform uses PDP-endian byte order (VAX, PDP-11). */
#    define AXM_PDP_ENDIAN 1
#else
/** @brief Byte order could not be determined. */
#    define AXM_ENDIAN_UNKNOWN 1
#endif
/** @} */


/**
 * @defgroup AXM_POINTER_WIDTH Pointer Width Detection
 * @brief Detects 32-bit vs. 64-bit pointer width.
 *
 * @details
 * Defines one of: AXM_PTR_WIDTH (32 or 64), AXM_32BIT, or AXM_64BIT.
 *
 * Use AXM_PTR_WIDTH for sizeof comparisons or when the exact width matters.
 * Use AXM_32BIT / AXM_64BIT for simple conditional compilation.
 *
 * @{
 */
#if defined(AXM_ARCH_X64)                                                                          \
    || defined(AXM_ARCH_ARM64)                                                                     \
    || defined(AXM_ARCH_PPC64)                                                                     \
    || defined(AXM_ARCH_RISCV64)                                                                   \
    || defined(AXM_ARCH_SPARC64)                                                                   \
    || defined(AXM_ARCH_MIPS64)                                                                    \
    || defined(AXM_ARCH_LOONGARCH64)                                                               \
    || defined(AXM_ARCH_S390X)                                                                     \
    || defined(AXM_ARCH_IA64)
/** @brief Pointer width: 64 bits. */
#    define AXM_PTR_WIDTH 64
/** @brief Platform is 64-bit. */
#    define AXM_64BIT     1

#elif defined(AXM_ARCH_X86)                                                                        \
    || defined(AXM_ARCH_ARM32)                                                                     \
    || defined(AXM_ARCH_MIPS32)                                                                    \
    || defined(AXM_ARCH_PPC32)                                                                     \
    || defined(AXM_ARCH_RISCV32)                                                                   \
    || defined(AXM_ARCH_SPARC32)                                                                   \
    || defined(AXM_ARCH_LOONGARCH32)                                                               \
    || defined(AXM_ARCH_S390)                                                                      \
    || defined(AXM_ARCH_WASM)                                                                      \
    || defined(AXM_ARCH_VAX)                                                                       \
    || defined(AXM_ARCH_M68K)
/** @brief Pointer width: 32 bits. */
#    define AXM_PTR_WIDTH 32
/** @brief Platform is 32-bit. */
#    define AXM_32BIT     1

#else
#    if defined(__SIZEOF_POINTER__)
#        if __SIZEOF_POINTER__ == 8
#            define AXM_PTR_WIDTH 64
#            define AXM_64BIT     1
#        elif __SIZEOF_POINTER__ == 4
#            define AXM_PTR_WIDTH 32
#            define AXM_32BIT     1
#        endif
#    endif
#endif
/** @} */


/**
 * @defgroup AXM_SIMD_EXTENSIONS SIMD/Vector Extension Detection
 * @brief Detects available SIMD instruction sets.
 *
 * @details
 * Defines AXM_SIMD_* macros to 1 when corresponding vector extensions
 * are available:
 *
 * **x86/x86-64:**
 * - SSE, SSE2, SSE3, SSSE3, SSE4.1, SSE4.2 (Streaming SIMD Extensions)
 * - AVX, AVX2 (Advanced Vector Extensions)
 * - AVX-512 variants (F, BW, DQ, VL, VBMI)
 * - FMA (Fused Multiply-Add)
 * - BMI1, BMI2 (Bit Manipulation)
 * - POPCNT, LZCNT (Bit counting)
 * - F16C (Half-precision conversion)
 * - SHA (SHA-NI)
 *
 * **ARM:**
 * - NEON (Advanced SIMD)
 * - SVE, SVE2 (Scalable Vector Extension)
 * - DOTPROD, I8MM (Matrix multiply)
 * - CRC32 (Cyclic Redundancy Check)
 * - CRYPTO (Cryptographic extensions)
 *
 * **RISC-V:**
 * - RVV (RISC-V Vector Extension)
 *
 * **WebAssembly:**
 * - WASM128 (128-bit SIMD)
 *
 * Graceful degradation: If SIMD is not available, the code compiles
 * but no AXM_SIMD_* macros are defined. Use them for fast paths:
 *
 * @code
 * #ifdef AXM_SIMD_AVX2
 *     // Use AVX2 intrinsics for vectorization
 * #else
 *     // Scalar fallback
 * #endif
 * @endcode
 *
 * @{
 */
#if defined(AXM_ARCH_X86_FAMILY)
#    if defined(__AVX512F__)
/** @brief AVX-512 Foundation is available. */
#        define AXM_SIMD_AVX512F 1
#    endif
#    if defined(__AVX512BW__)
/** @brief AVX-512 Byte and Word is available. */
#        define AXM_SIMD_AVX512BW 1
#    endif
#    if defined(__AVX512DQ__)
/** @brief AVX-512 Doubleword and Quadword is available. */
#        define AXM_SIMD_AVX512DQ 1
#    endif
#    if defined(__AVX512VL__)
/** @brief AVX-512 Vector Length is available. */
#        define AXM_SIMD_AVX512VL 1
#    endif
#    if defined(__AVX512VBMI__)
/** @brief AVX-512 Vector Byte Manipulation Instruction is available. */
#        define AXM_SIMD_AVX512VBMI 1
#    endif
#    if defined(__AVX2__)
/** @brief Advanced Vector Extensions 2 is available. */
#        define AXM_SIMD_AVX2 1
#    endif
#    if defined(__AVX__)
/** @brief Advanced Vector Extensions is available. */
#        define AXM_SIMD_AVX 1
#    endif
#    if defined(__SSE4_2__)
/** @brief Streaming SIMD Extensions 4.2 is available. */
#        define AXM_SIMD_SSE42 1
#    endif
#    if defined(__SSE4_1__)
/** @brief Streaming SIMD Extensions 4.1 is available. */
#        define AXM_SIMD_SSE41 1
#    endif
#    if defined(__SSSE3__)
/** @brief Supplemental Streaming SIMD Extensions 3 is available. */
#        define AXM_SIMD_SSSE3 1
#    endif
#    if defined(__SSE3__)
/** @brief Streaming SIMD Extensions 3 is available. */
#        define AXM_SIMD_SSE3 1
#    endif
#    if defined(__SSE2__) || (defined(AXM_COMPILER_MSVC_LIKE) && defined(AXM_ARCH_X64))
/** @brief Streaming SIMD Extensions 2 is available. */
#        define AXM_SIMD_SSE2 1
#    endif
#    if defined(__SSE__)
/** @brief Streaming SIMD Extensions is available. */
#        define AXM_SIMD_SSE 1
#    endif
#    if defined(__FMA__)
/** @brief Fused Multiply-Add is available. */
#        define AXM_SIMD_FMA 1
#    endif
#    if defined(__BMI__)
/** @brief Bit Manipulation Instruction Set 1 is available. */
#        define AXM_SIMD_BMI1 1
#    endif
#    if defined(__BMI2__)
/** @brief Bit Manipulation Instruction Set 2 is available. */
#        define AXM_SIMD_BMI2 1
#    endif
#    if defined(__POPCNT__)
/** @brief POPCNT (population count) instruction is available. */
#        define AXM_SIMD_POPCNT 1
#    endif
#    if defined(__LZCNT__)
/** @brief LZCNT (leading zero count) instruction is available. */
#        define AXM_SIMD_LZCNT 1
#    endif
#    if defined(__F16C__)
/** @brief F16C (half-precision conversion) is available. */
#        define AXM_SIMD_F16C 1
#    endif
#    if defined(__SHA__)
/** @brief SHA-NI (SHA extension) is available. */
#        define AXM_SIMD_SHA 1
#    endif
#endif

#if defined(AXM_ARCH_ARM_FAMILY)
#    if defined(__ARM_NEON) || defined(__ARM_NEON__)
/** @brief ARM NEON is available. */
#        define AXM_SIMD_NEON 1
#    endif
#    if defined(__ARM_FEATURE_SVE2)
/** @brief ARM Scalable Vector Extension 2 is available. */
#        define AXM_SIMD_SVE2 1
/** @brief ARM Scalable Vector Extension is available. */
#        define AXM_SIMD_SVE  1
#    elif defined(__ARM_FEATURE_SVE)
/** @brief ARM Scalable Vector Extension is available. */
#        define AXM_SIMD_SVE 1
#    endif
#    if defined(__ARM_FEATURE_DOTPROD)
/** @brief ARM DOTPROD (dot product) is available. */
#        define AXM_SIMD_DOTPROD 1
#    endif
#    if defined(__ARM_FEATURE_MATMUL_INT8)
/** @brief ARM I8MM (8-bit integer matrix multiply) is available. */
#        define AXM_SIMD_I8MM 1
#    endif
#    if defined(__ARM_FEATURE_CRC32)
/** @brief ARM CRC32 is available. */
#        define AXM_SIMD_CRC32 1
#    endif
#    if defined(__ARM_FEATURE_CRYPTO)
/** @brief ARM CRYPTO (cryptographic) extensions are available. */
#        define AXM_SIMD_CRYPTO 1
#    endif
#endif

#if defined(AXM_ARCH_RISCV)
#    if defined(__riscv_v)
/** @brief RISC-V Vector Extension is available. */
#        define AXM_SIMD_RISCV_V 1
#    endif
#endif

#if defined(AXM_ARCH_WASM)
#    if defined(__wasm_simd128__)
/** @brief WebAssembly SIMD 128-bit is available. */
#        define AXM_SIMD_WASM128 1
#    endif
#endif
/** @} */


/**
 * @defgroup AXM_PLATFORM_WARNINGS Platform Detection Warnings
 * @brief Compile-time warnings for unrecognized or unusual platforms.
 *
 * @details
 * The Axiom library tries to detect all known platforms, but if an
 * unrecognized OS, architecture, compiler, or endianness is encountered,
 * a pragma message warning is issued at compile time. This alerts the
 * developer to verify the configuration manually.
 *
 * @{
 */
#if defined(AXM_OS_UNKNOWN)
#    if defined(AXM_COMPILER_GCC_LIKE)
#        pragma message                                                                            \
            "AXM: Unknown OS — POSIX shims will be used. Verify all AXM modules manually."
#    elif defined(AXM_COMPILER_MSVC_LIKE)
#        pragma message(                                                                           \
            "AXM: Unknown OS — POSIX shims will be used. Verify all AXM modules manually.")
#    endif
#endif

#if defined(AXM_ARCH_UNKNOWN)
#    if defined(AXM_COMPILER_GCC_LIKE)
#        pragma message                                                                            \
            "AXM: Unknown architecture — pointer width and SIMD detection may be incomplete."
#    elif defined(AXM_COMPILER_MSVC_LIKE)
#        pragma message(                                                                           \
            "AXM: Unknown architecture — pointer width and SIMD detection may be incomplete.")
#    endif
#endif

#if defined(AXM_COMPILER_UNKNOWN)
#    if defined(AXM_COMPILER_GCC_LIKE)
#        pragma message "AXM: Unknown compiler — AXM_COMPILER_GCC_LIKE is not set."
#    elif defined(AXM_COMPILER_MSVC_LIKE)
#        pragma message("AXM: Unknown compiler — AXM_COMPILER_MSVC_LIKE is not set.")
#    else
#        pragma message "AXM: Unknown compiler detected."
#    endif
#endif

#if !defined(AXM_LITTLE_ENDIAN) && !defined(AXM_BIG_ENDIAN) && !defined(AXM_PDP_ENDIAN)
#    if defined(AXM_COMPILER_GCC_LIKE)
#        pragma message "AXM: Endianness could not be determined."
#    elif defined(AXM_COMPILER_MSVC_LIKE)
#        pragma message("AXM: Endianness could not be determined.")
#    endif
#endif
/** @} */

#endif
