/*
 * @file Simd.h
 * @brief Compile-time SIMD and vector-feature detection.
 *
 * This header identifies available instruction sets and vector extensions
 * for the active target architecture.
 *
 * Macro hierarchy:
 * - x86/x86-64 feature macros
 *   - ATOM_SIMD_SSE, ATOM_SIMD_SSE2, ATOM_SIMD_SSE3, ATOM_SIMD_SSSE3
 *   - ATOM_SIMD_SSE41, ATOM_SIMD_SSE42
 *   - ATOM_SIMD_AVX, ATOM_SIMD_AVX2
 *   - ATOM_SIMD_AVX512F, ATOM_SIMD_AVX512BW, ATOM_SIMD_AVX512DQ,
 *     ATOM_SIMD_AVX512VL, ATOM_SIMD_AVX512VBMI
 *   - ATOM_SIMD_FMA, ATOM_SIMD_BMI1, ATOM_SIMD_BMI2, ATOM_SIMD_POPCNT,
 *     ATOM_SIMD_LZCNT, ATOM_SIMD_F16C, ATOM_SIMD_SHA
 *
 * - ARM/ARM64 feature macros
 *   - ATOM_SIMD_NEON
 *   - ATOM_SIMD_SVE, ATOM_SIMD_SVE2
 *   - ATOM_SIMD_DOTPROD, ATOM_SIMD_I8MM, ATOM_SIMD_CRC32, ATOM_SIMD_CRYPTO
 *
 * - Other targets
 *   - ATOM_SIMD_RISCV_V
 *   - ATOM_SIMD_WASM128
 *
 * Detection policy:
 * - Features are reported only when the compiler exposes the relevant target
 *   define for that instruction set.
 * - Multiple SIMD macros may be defined together when the target supports
 *   multiple layers of acceleration.
 */
#ifndef ATOM_QRK_SYSTEM_SIMD_H
#define ATOM_QRK_SYSTEM_SIMD_H

/** x86 and x86-64 SIMD feature detection. */
#if defined(__x86_64__)                                                                            \
    || defined(__amd64__)                                                                          \
    || defined(_M_X64)                                                                             \
    || defined(_M_AMD64)                                                                           \
    || defined(__i386__)                                                                           \
    || defined(__i486__)                                                                           \
    || defined(__i586__)                                                                           \
    || defined(__i686__)                                                                           \
    || defined(_M_IX86)
#    if defined(__AVX512F__)
#        define ATOM_SIMD_AVX512F 1
#    endif
#    if defined(__AVX512BW__)
#        define ATOM_SIMD_AVX512BW 1
#    endif
#    if defined(__AVX512DQ__)
#        define ATOM_SIMD_AVX512DQ 1
#    endif
#    if defined(__AVX512VL__)
#        define ATOM_SIMD_AVX512VL 1
#    endif
#    if defined(__AVX512VBMI__)
#        define ATOM_SIMD_AVX512VBMI 1
#    endif
#    if defined(__AVX2__)
#        define ATOM_SIMD_AVX2 1
#    endif
#    if defined(__AVX__)
#        define ATOM_SIMD_AVX 1
#    endif
#    if defined(__SSE4_2__)
#        define ATOM_SIMD_SSE42 1
#    endif
#    if defined(__SSE4_1__)
#        define ATOM_SIMD_SSE41 1
#    endif
#    if defined(__SSSE3__)
#        define ATOM_SIMD_SSSE3 1
#    endif
#    if defined(__SSE3__)
#        define ATOM_SIMD_SSE3 1
#    endif
#    if defined(__SSE2__)
#        define ATOM_SIMD_SSE2 1
#    endif
#    if defined(__SSE__)
#        define ATOM_SIMD_SSE 1
#    endif
#    if defined(__FMA__)
#        define ATOM_SIMD_FMA 1
#    endif
#    if defined(__BMI__)
#        define ATOM_SIMD_BMI1 1
#    endif
#    if defined(__BMI2__)
#        define ATOM_SIMD_BMI2 1
#    endif
#    if defined(__POPCNT__)
#        define ATOM_SIMD_POPCNT 1
#    endif
#    if defined(__LZCNT__)
#        define ATOM_SIMD_LZCNT 1
#    endif
#    if defined(__F16C__)
#        define ATOM_SIMD_F16C 1
#    endif
#    if defined(__SHA__)
#        define ATOM_SIMD_SHA 1
#    endif
#endif


/** ARM and ARM64 SIMD and vector feature detection. */
#if defined(_M_ARM64EC)                                                                            \
    || defined(__aarch64__)                                                                        \
    || defined(_M_ARM64)                                                                           \
    || defined(__arm__)                                                                            \
    || defined(__ARM_ARCH)                                                                         \
    || defined(_M_ARM)
#    if defined(__ARM_NEON) || defined(__ARM_NEON__)
#        define ATOM_SIMD_NEON 1
#    endif
#    if defined(__ARM_FEATURE_SVE2)
#        define ATOM_SIMD_SVE2 1
#        define ATOM_SIMD_SVE  1
#    elif defined(__ARM_FEATURE_SVE)
#        define ATOM_SIMD_SVE 1
#    endif
#    if defined(__ARM_FEATURE_DOTPROD)
#        define ATOM_SIMD_DOTPROD 1
#    endif
#    if defined(__ARM_FEATURE_MATOMUL_INT8)
#        define ATOM_SIMD_I8MM 1
#    endif
#    if defined(__ARM_FEATURE_CRC32)
#        define ATOM_SIMD_CRC32 1
#    endif
#    if defined(__ARM_FEATURE_CRYPTO)
#        define ATOM_SIMD_CRYPTO 1
#    endif
#endif


/** RISC-V vector extension detection. */
#if defined(__riscv)
#    if defined(__riscv_v)
#        define ATOM_SIMD_RISCV_V 1
#    endif
#endif


/** WebAssembly SIMD-128 detection. */
#if defined(__wasm__)
#    if defined(__wasm_simd128__)
#        define ATOM_SIMD_WASM128 1
#    endif
#endif

#endif
