/*
 * @file Simd.h
 * @brief Compile-time SIMD and vector-feature detection.
 *
 * This header identifies available instruction sets and vector extensions
 * for the active target architecture.
 *
 * Macro hierarchy:
 * - x86/x86-64 feature macros
 *   - AXM_SIMD_SSE, AXM_SIMD_SSE2, AXM_SIMD_SSE3, AXM_SIMD_SSSE3
 *   - AXM_SIMD_SSE41, AXM_SIMD_SSE42
 *   - AXM_SIMD_AVX, AXM_SIMD_AVX2
 *   - AXM_SIMD_AVX512F, AXM_SIMD_AVX512BW, AXM_SIMD_AVX512DQ,
 *     AXM_SIMD_AVX512VL, AXM_SIMD_AVX512VBMI
 *   - AXM_SIMD_FMA, AXM_SIMD_BMI1, AXM_SIMD_BMI2, AXM_SIMD_POPCNT,
 *     AXM_SIMD_LZCNT, AXM_SIMD_F16C, AXM_SIMD_SHA
 *
 * - ARM/ARM64 feature macros
 *   - AXM_SIMD_NEON
 *   - AXM_SIMD_SVE, AXM_SIMD_SVE2
 *   - AXM_SIMD_DOTPROD, AXM_SIMD_I8MM, AXM_SIMD_CRC32, AXM_SIMD_CRYPTO
 *
 * - Other targets
 *   - AXM_SIMD_RISCV_V
 *   - AXM_SIMD_WASM128
 *
 * Detection policy:
 * - Features are reported only when the compiler exposes the relevant target
 *   define for that instruction set.
 * - Multiple SIMD macros may be defined together when the target supports
 *   multiple layers of acceleration.
 */
#ifndef AXM_LVL_SYSTEM_SIMD_H
#define AXM_LVL_SYSTEM_SIMD_H

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
#        define AXM_SIMD_AVX512F 1
#    endif
#    if defined(__AVX512BW__)
#        define AXM_SIMD_AVX512BW 1
#    endif
#    if defined(__AVX512DQ__)
#        define AXM_SIMD_AVX512DQ 1
#    endif
#    if defined(__AVX512VL__)
#        define AXM_SIMD_AVX512VL 1
#    endif
#    if defined(__AVX512VBMI__)
#        define AXM_SIMD_AVX512VBMI 1
#    endif
#    if defined(__AVX2__)
#        define AXM_SIMD_AVX2 1
#    endif
#    if defined(__AVX__)
#        define AXM_SIMD_AVX 1
#    endif
#    if defined(__SSE4_2__)
#        define AXM_SIMD_SSE42 1
#    endif
#    if defined(__SSE4_1__)
#        define AXM_SIMD_SSE41 1
#    endif
#    if defined(__SSSE3__)
#        define AXM_SIMD_SSSE3 1
#    endif
#    if defined(__SSE3__)
#        define AXM_SIMD_SSE3 1
#    endif
#    if defined(__SSE2__)
#        define AXM_SIMD_SSE2 1
#    endif
#    if defined(__SSE__)
#        define AXM_SIMD_SSE 1
#    endif
#    if defined(__FMA__)
#        define AXM_SIMD_FMA 1
#    endif
#    if defined(__BMI__)
#        define AXM_SIMD_BMI1 1
#    endif
#    if defined(__BMI2__)
#        define AXM_SIMD_BMI2 1
#    endif
#    if defined(__POPCNT__)
#        define AXM_SIMD_POPCNT 1
#    endif
#    if defined(__LZCNT__)
#        define AXM_SIMD_LZCNT 1
#    endif
#    if defined(__F16C__)
#        define AXM_SIMD_F16C 1
#    endif
#    if defined(__SHA__)
#        define AXM_SIMD_SHA 1
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
#        define AXM_SIMD_NEON 1
#    endif
#    if defined(__ARM_FEATURE_SVE2)
#        define AXM_SIMD_SVE2 1
#        define AXM_SIMD_SVE  1
#    elif defined(__ARM_FEATURE_SVE)
#        define AXM_SIMD_SVE 1
#    endif
#    if defined(__ARM_FEATURE_DOTPROD)
#        define AXM_SIMD_DOTPROD 1
#    endif
#    if defined(__ARM_FEATURE_MATMUL_INT8)
#        define AXM_SIMD_I8MM 1
#    endif
#    if defined(__ARM_FEATURE_CRC32)
#        define AXM_SIMD_CRC32 1
#    endif
#    if defined(__ARM_FEATURE_CRYPTO)
#        define AXM_SIMD_CRYPTO 1
#    endif
#endif


/** RISC-V vector extension detection. */
#if defined(__riscv)
#    if defined(__riscv_v)
#        define AXM_SIMD_RISCV_V 1
#    endif
#endif


/** WebAssembly SIMD-128 detection. */
#if defined(__wasm__)
#    if defined(__wasm_simd128__)
#        define AXM_SIMD_WASM128 1
#    endif
#endif

#endif
