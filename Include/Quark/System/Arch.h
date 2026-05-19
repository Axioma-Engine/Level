/**
 * @file Arch.h
 * @brief Compile-time target CPU architecture detection.
 *
 * This header identifies the active architecture and publishes a consistent
 * set of ATOM_ARCH_* macros for use across the project.
 *
 * Macro hierarchy:
 * - ATOM_ARCH_UNKNOWN
 *   - Default fallback until a concrete target architecture is detected.
 *
 * - Width macros
 *   - ATOM_64BIT: target uses 64-bit pointers.
 *   - ATOM_32BIT: target uses 32-bit pointers.
 *
 * - Family macros
 *   - ATOM_ARCH_X86_FAMILY
 *   - ATOM_ARCH_ARM_FAMILY
 *   - ATOM_ARCH_MIPS_FAMILY
 *   - ATOM_ARCH_PPC_FAMILY
 *   - ATOM_ARCH_SPARC_FAMILY
 *   - ATOM_ARCH_LOONGARCH_FAMILY
 *
 * - Specific architecture macros
 *   - ATOM_ARCH_X64, ATOM_ARCH_X86
 *   - ATOM_ARCH_ARM64EC, ATOM_ARCH_ARM64, ATOM_ARCH_ARM32
 *   - ATOM_ARCH_RISCV64, ATOM_ARCH_RISCV32, ATOM_ARCH_RISCV_UNKNOWN
 *   - ATOM_ARCH_WASM
 *   - ATOM_ARCH_MIPS64, ATOM_ARCH_MIPS32, ATOM_ARCH_MIPS_UNKNOWN
 *   - ATOM_ARCH_PPC64, ATOM_ARCH_PPC32
 *   - ATOM_ARCH_SPARC64, ATOM_ARCH_SPARC32
 *   - ATOM_ARCH_LOONGARCH64, ATOM_ARCH_LOONGARCH32
 *   - ATOM_ARCH_S390X, ATOM_ARCH_S390
 *   - ATOM_ARCH_IA64, ATOM_ARCH_VAX, ATOM_ARCH_M68K
 *
 * Detection order:
 * - The first matching block for a target family defines the relevant macros.
 * - Some targets define both a family macro and a specific macro.
 * - ATOM_ARCH_UNKNOWN remains defined only if no known target is detected.
 */
#ifndef ATOM_QRK_SYSTEM_ARCH_H
#define ATOM_QRK_SYSTEM_ARCH_H

/** Default fallback until a concrete architecture is identified. */
#define ATOM_ARCH_UNKNOWN 1


/** x86 family detection, covering both 64-bit and 32-bit targets. */
#if defined(__x86_64__) || defined(__amd64__) || defined(_M_X64) || defined(_M_AMD64)
#    undef ATOM_ARCH_UNKNOWN
#    define ATOM_64BIT           1
#    define ATOM_ARCH_X64        1
#    define ATOM_ARCH_X86_FAMILY 1
#elif defined(__i386__)                                                                            \
    || defined(__i486__)                                                                           \
    || defined(__i586__)                                                                           \
    || defined(__i686__)                                                                           \
    || defined(_M_IX86)
#    undef ATOM_ARCH_UNKNOWN
#    define ATOM_32BIT           1
#    define ATOM_ARCH_X86        1
#    define ATOM_ARCH_X86_FAMILY 1
#endif


/** ARM family detection, including ARM64EC, ARM64, and ARM32. */
#if defined(_M_ARM64EC)
#    undef ATOM_ARCH_UNKNOWN
#    define ATOM_64BIT           1
#    define ATOM_ARCH_ARM64EC    1
#    define ATOM_ARCH_ARM64      1
#    define ATOM_ARCH_ARM_FAMILY 1
#elif defined(__aarch64__) || defined(_M_ARM64)
#    undef ATOM_ARCH_UNKNOWN
#    define ATOM_64BIT           1
#    define ATOM_ARCH_ARM64      1
#    define ATOM_ARCH_ARM_FAMILY 1
#elif defined(__arm__) || defined(__ARM_ARCH) || defined(_M_ARM)
#    undef ATOM_ARCH_UNKNOWN
#    define ATOM_32BIT           1
#    define ATOM_ARCH_ARM32      1
#    define ATOM_ARCH_ARM_FAMILY 1
#endif


/** RISC-V detection with width-specific refinement. */
#if defined(__riscv)
#    undef ATOM_ARCH_UNKNOWN
#    define ATOM_ARCH_RISCV 1
#    if defined(__riscv_xlen)
#        if __riscv_xlen == 64
#            define ATOM_64BIT        1
#            define ATOM_ARCH_RISCV64 1
#        elif __riscv_xlen == 32
#            define ATOM_32BIT        1
#            define ATOM_ARCH_RISCV32 1
#        endif
#    else
#        define ATOM_ARCH_RISCV_UNKNOWN 1
#    endif
#endif


/** WebAssembly target detection. */
#if defined(__EMSCRIPTEN__) || defined(__wasm__)
#    undef ATOM_ARCH_UNKNOWN
#    define ATOM_ARCH_WASM 1
#    if defined(__wasm64__)
#        define ATOM_64BIT 1
#    elif defined(__wasm32__)
#        define ATOM_32BIT 1
#    endif
#endif


/** MIPS family detection with 64-bit, 32-bit, and unknown variants. */
#if defined(__mips__) || defined(__mips)
#    undef ATOM_ARCH_UNKNOWN
#    define ATOM_ARCH_MIPS_FAMILY 1
#    if defined(__mips64) || defined(__mips64__)
#        define ATOM_64BIT       1
#        define ATOM_ARCH_MIPS64 1
#    elif defined(__mips32) || defined(__mips32__)
#        define ATOM_32BIT       1
#        define ATOM_ARCH_MIPS32 1
#    else
#        define ATOM_ARCH_MIPS_UNKNOWN 1
#    endif
#endif


/** PowerPC detection for both 64-bit and 32-bit targets. */
#if defined(__PPC64__) || defined(__powerpc64__) || defined(_ARCH_PPC64)
#    undef ATOM_ARCH_UNKNOWN
#    define ATOM_64BIT           1
#    define ATOM_ARCH_PPC64      1
#    define ATOM_ARCH_PPC_FAMILY 1
#elif defined(__PPC__) || defined(__powerpc__) || defined(_ARCH_PPC)
#    undef ATOM_ARCH_UNKNOWN
#    define ATOM_32BIT           1
#    define ATOM_ARCH_PPC32      1
#    define ATOM_ARCH_PPC_FAMILY 1
#endif


/** SPARC detection with explicit width classification. */
#if defined(__sparc__) || defined(__sparc)
#    undef ATOM_ARCH_UNKNOWN
#    define ATOM_ARCH_SPARC_FAMILY 1
#    if defined(__sparcv9) || defined(__sparc_v9__)
#        define ATOM_64BIT        1
#        define ATOM_ARCH_SPARC64 1
#    else
#        define ATOM_32BIT        1
#        define ATOM_ARCH_SPARC32 1
#    endif
#endif


/** LoongArch detection with 64-bit and 32-bit variants. */
#if defined(__loongarch__)
#    undef ATOM_ARCH_UNKNOWN
#    define ATOM_ARCH_LOONGARCH_FAMILY 1
#    if defined(__loongarch64)
#        define ATOM_64BIT            1
#        define ATOM_ARCH_LOONGARCH64 1
#    else
#        define ATOM_32BIT            1
#        define ATOM_ARCH_LOONGARCH32 1
#    endif
#endif


/** IBM Z / s390 family detection. */
#if defined(__s390x__)
#    undef ATOM_ARCH_UNKNOWN
#    define ATOM_64BIT      1
#    define ATOM_ARCH_S390X 1
#elif defined(__s390__)
#    undef ATOM_ARCH_UNKNOWN
#    define ATOM_32BIT     1
#    define ATOM_ARCH_S390 1
#endif


/** Legacy architecture fallbacks for older or niche targets. */
#if defined(__ia64__) || defined(_M_IA64) || defined(__ia64)
#    undef ATOM_ARCH_UNKNOWN
#    define ATOM_64BIT     1
#    define ATOM_ARCH_IA64 1
#endif
#if defined(__vax__)
#    undef ATOM_ARCH_UNKNOWN
#    define ATOM_32BIT    1
#    define ATOM_ARCH_VAX 1
#endif
#if defined(__m68k__) || defined(__m68000__)
#    undef ATOM_ARCH_UNKNOWN
#    define ATOM_32BIT     1
#    define ATOM_ARCH_M68K 1
#endif


#if defined(ATOM_ARCH_UNKNOWN)
#    pragma message                                                                                \
        "ATOM: Unknown architecture - pointer width and SIMD detection may be incomplete."
#    pragma message(                                                                               \
        "ATOM: Unknown architecture - pointer width and SIMD detection may be incomplete.")
#endif

#endif
