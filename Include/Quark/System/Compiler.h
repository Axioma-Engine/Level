/**
 * @file Compiler.h
 * @brief Compile-time compiler identification, family classification, and version data.
 *
 * This header detects the active compiler and publishes standardized macros
 * for compiler identity, compiler family, and compiler version components.
 *
 * Macro hierarchy:
 * - Primary compiler identity
 *   - AXM_COMPILER_NVCC
 *   - AXM_COMPILER_EMSCRIPTEN
 *   - AXM_COMPILER_CLANG_CL
 *   - AXM_COMPILER_CLANG
 *   - AXM_COMPILER_INTEL_LLVM
 *   - AXM_COMPILER_INTEL
 *   - AXM_COMPILER_GCC
 *   - AXM_COMPILER_MSVC
 *   - AXM_COMPILER_ARMCC
 *   - AXM_COMPILER_IBM_XL
 *   - AXM_COMPILER_BORLAND
 *   - AXM_COMPILER_WATCOM
 *   - AXM_COMPILER_SUNPRO
 *   - AXM_COMPILER_METROWERKS
 *   - AXM_COMPILER_TINYC
 *   - AXM_COMPILER_UNKNOWN
 *
 * - Family classification
 *   - AXM_COMPILER_GCC_LIKE
 *   - AXM_COMPILER_MSVC_LIKE
 *   - AXM_COMPILER_MINGW
 *   - AXM_COMPILER_MINGW32 / AXM_COMPILER_MINGW64
 *
 * - Version macros
 *   - AXM_COMPILER_VERSION_MAJOR
 *   - AXM_COMPILER_VERSION_MINOR
 *   - AXM_COMPILER_VERSION_PATCH
 *
 * Detection order:
 * - Specific compilers are tested first.
 * - Family macros are then refined, including MinGW after the primary pass.
 * - If no known compiler matches, AXM_COMPILER_UNKNOWN is defined.
 */
#ifndef AXM_QRK_SYSTEM_COMPILER_H
#define AXM_QRK_SYSTEM_COMPILER_H

/** Compiler-specific detection and version extraction. */

/** NVIDIA CUDA Compiler (nvcc). */
#if defined(__NVCC__)
#    define AXM_COMPILER_NVCC          1
#    define AXM_COMPILER_GCC_LIKE      1
#    define AXM_COMPILER_VERSION_MAJOR __CUDACC_VER_MAJOR__
#    define AXM_COMPILER_VERSION_MINOR __CUDACC_VER_MINOR__
#    define AXM_COMPILER_VERSION_PATCH __CUDACC_VER_BUILD__

/** Emscripten compiler for WebAssembly targets. */
#elif defined(__EMSCRIPTEN__)
#    define AXM_COMPILER_EMSCRIPTEN    1
#    define AXM_COMPILER_GCC_LIKE      1
#    define AXM_COMPILER_VERSION_MAJOR __EMSCRIPTEN_MAJOR__
#    define AXM_COMPILER_VERSION_MINOR __EMSCRIPTEN_MINOR__
#    define AXM_COMPILER_VERSION_PATCH __EMSCRIPTEN_TINY__

/** Clang in MSVC compatibility mode. */
#elif defined(__clang__) && defined(_MSC_VER)
#    define AXM_COMPILER_CLANG_CL      1
#    define AXM_COMPILER_MSVC_LIKE     1
#    define AXM_COMPILER_VERSION_MAJOR __clang_major__
#    define AXM_COMPILER_VERSION_MINOR __clang_minor__
#    define AXM_COMPILER_VERSION_PATCH __clang_patchlevel__

/** Clang in native mode. */
#elif defined(__clang__)
#    define AXM_COMPILER_CLANG         1
#    define AXM_COMPILER_GCC_LIKE      1
#    define AXM_COMPILER_VERSION_MAJOR __clang_major__
#    define AXM_COMPILER_VERSION_MINOR __clang_minor__
#    define AXM_COMPILER_VERSION_PATCH __clang_patchlevel__

/** Intel LLVM compiler (icx). */
#elif defined(__INTEL_LLVM_COMPILER)
#    define AXM_COMPILER_INTEL_LLVM    1
#    define AXM_COMPILER_GCC_LIKE      1
#    define AXM_COMPILER_VERSION_MAJOR (__INTEL_LLVM_COMPILER / 10000)
#    define AXM_COMPILER_VERSION_MINOR ((__INTEL_LLVM_COMPILER % 10000) / 100)
#    define AXM_COMPILER_VERSION_PATCH (__INTEL_LLVM_COMPILER % 100)

/** Classic Intel compiler (icc). */
#elif defined(__INTEL_COMPILER) || defined(__ICC)
#    define AXM_COMPILER_INTEL         1
#    define AXM_COMPILER_GCC_LIKE      1
#    define AXM_COMPILER_VERSION_MAJOR (__INTEL_COMPILER / 100)
#    define AXM_COMPILER_VERSION_MINOR (__INTEL_COMPILER % 100)
#    define AXM_COMPILER_VERSION_PATCH 0

/** GNU Compiler Collection. */
#elif defined(__GNUC__)
#    define AXM_COMPILER_GCC           1
#    define AXM_COMPILER_GCC_LIKE      1
#    define AXM_COMPILER_VERSION_MAJOR __GNUC__
#    define AXM_COMPILER_VERSION_MINOR __GNUC_MINOR__
#    define AXM_COMPILER_VERSION_PATCH __GNUC_PATCHLEVEL__

/** Microsoft Visual C++. */
#elif defined(_MSC_VER)
#    define AXM_COMPILER_MSVC          1
#    define AXM_COMPILER_MSVC_LIKE     1
#    define AXM_COMPILER_VERSION_MAJOR (_MSC_VER / 100)
#    define AXM_COMPILER_VERSION_MINOR (_MSC_VER % 100)
#    define AXM_COMPILER_VERSION_PATCH (_MSVC_FULL_VER % 100000)

/** Arm Compiler. */
#elif defined(__ARMCC_VERSION)
#    define AXM_COMPILER_ARMCC         1
#    define AXM_COMPILER_GCC_LIKE      1
#    define AXM_COMPILER_VERSION_MAJOR (__ARMCC_VERSION / 1000000)
#    define AXM_COMPILER_VERSION_MINOR ((__ARMCC_VERSION % 1000000) / 10000)
#    define AXM_COMPILER_VERSION_PATCH (__ARMCC_VERSION % 10000)

/** IBM XL C++. */
#elif defined(__ibmxl__) || defined(__xlC__)
#    define AXM_COMPILER_IBM_XL   1
#    define AXM_COMPILER_GCC_LIKE 1
#    if defined(__ibmxl__)
#        define AXM_COMPILER_VERSION_MAJOR __ibmxl_version__
#        define AXM_COMPILER_VERSION_MINOR __ibmxl_release__
#        define AXM_COMPILER_VERSION_PATCH __ibmxl_modification__
#    else
#        define AXM_COMPILER_VERSION_MAJOR (__xlC__ >> 8)
#        define AXM_COMPILER_VERSION_MINOR (__xlC__ & 0xFF)
#        define AXM_COMPILER_VERSION_PATCH 0
#    endif

/** Borland C++. */
#elif defined(__BORLANDC__)
#    define AXM_COMPILER_BORLAND       1
#    define AXM_COMPILER_VERSION_MAJOR (__BORLANDC__ >> 8)
#    define AXM_COMPILER_VERSION_MINOR (__BORLANDC__ & 0xFF)
#    define AXM_COMPILER_VERSION_PATCH 0
#    pragma message("Nice compiler, but we don't support Borland yet.")

/** Watcom C++. */
#elif defined(__WATCOMC__)
#    define AXM_COMPILER_WATCOM        1
#    define AXM_COMPILER_VERSION_MAJOR (__WATCOMC__ / 100)
#    define AXM_COMPILER_VERSION_MINOR (__WATCOMC__ % 100)
#    define AXM_COMPILER_VERSION_PATCH 0
#    pragma message("Nice compiler, but we don't support Watcom yet.")

/** Oracle Sun Pro C++. */
#elif defined(__SUNPRO_CC__)
#    define AXM_COMPILER_SUNPRO        1
#    define AXM_COMPILER_GCC_LIKE      1
#    define AXM_COMPILER_VERSION_MAJOR (__SUNPRO_CC / 0x100)
#    define AXM_COMPILER_VERSION_MINOR (__SUNPRO_CC / 0x10 & 0xF)
#    define AXM_COMPILER_VERSION_PATCH (__SUNPRO_CC & 0xF)

/** Metrowerks CodeWarrior. */
#elif defined(__MWERKS__)
#    define AXM_COMPILER_METROWERKS    1
#    define AXM_COMPILER_VERSION_MAJOR (__MWERKS__ / 0x1000)
#    define AXM_COMPILER_VERSION_MINOR (__MWERKS__ / 0x100 & 0xF)
#    define AXM_COMPILER_VERSION_PATCH (__MWERKS__ & 0xFF)
#    pragma message("Nice compiler, but we don't support Metrowerks yet.")

/** Tiny C Compiler. */
#elif defined(__TINYC__)
#    define AXM_COMPILER_TINYC         1
#    define AXM_COMPILER_GCC_LIKE      1
#    define AXM_COMPILER_VERSION_MAJOR (_COMPILER_VERSION / 100)
#    define AXM_COMPILER_VERSION_MINOR (_COMPILER_VERSION % 100)
#    define AXM_COMPILER_VERSION_PATCH 0

/** Fallback for unknown or unsupported compilers. */
#else
#    define AXM_COMPILER_UNKNOWN 1
#endif

/** End of primary compiler-identification group. */

/** MinGW refinement layered on top of compiler detection. */
#if defined(__MINGW32__) || defined(__MINGW64__)
#    define AXM_COMPILER_MINGW    1
#    define AXM_COMPILER_GCC_LIKE 1
#    if defined(__MINGW64__)
#        define AXM_COMPILER_MINGW64 1
#    else
#        define AXM_COMPILER_MINGW32 1
#    endif
#endif

#if defined(AXM_COMPILER_UNKNOWN)
#    pragma message "AXM: Unknown compiler - axiom may not function properly"
#    pragma message("AXM: Unknown compiler - axiom may not function properly")
#endif

#endif
