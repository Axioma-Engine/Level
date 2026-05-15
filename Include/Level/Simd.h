/**
 * @file Simd.h
 * @brief Top-level SIMD backend selector and re-export header.
 *
 * This umbrella header includes the appropriate SIMD backend header
 * (AVX, SSE, NEON, or scalar fallback) based on detected feature
 * macros from `System/Simd.h`.
 *
 * Provided types (backend-dependent aliases):
 * - `V128I32` : 128-bit vector of four 32-bit integers
 * - `V128I64` : 128-bit vector of two 64-bit integers
 * - `V128F32` : 128-bit vector of four 32-bit floats
 * - `V256I32` : 256-bit pair of two `V128I32` (lo/hi)
 * - `V256F32` : 256-bit pair of two `V128F32` (lo/hi)
 *
 * Commonly-provided functions (mapped per-backend under namespace `AXM`):
 * - `v128i32Load` / `v128i32Store`
 * - `v128i32Add`, `v128i32Sub`, `v128i32Mul`
 * - Bitwise ops: `v128i32And`, `v128i32Or`, `v128i32Xor`
 * - Shift ops: `v128i32Shl`, `v128i32Shr`
 * - Floating ops: `v128f32Add`, `v128f32Sub`, `v128f32Mul`, `v128f32Div`, `v128f32Neg`,
 * `v128f32Abs`
 * - 256-bit wrappers: `v256i32Load`/`Store` and elementwise `v256i32Add`/`Sub`/`Mul` etc.
 */

#ifndef AXM_LVL_SIMD_H
#define AXM_LVL_SIMD_H

#include "System/Simd.h"

// IWYU pragma: begin_exports
#if AXM_SIMD_AVX
#    include "SIMD/AVX/f32.h"
#    include "SIMD/AVX/i32.h"
#elif AXM_SIMD_SSE
#    include "SIMD/SSE/f32.h"
#    include "SIMD/SSE/f64.h"
#    include "SIMD/SSE/i32.h"
#    include "SIMD/SSE/i64.h"
#else
#    include "SIMD/Scalar/f32.h"
#    include "SIMD/Scalar/f64.h"
#    include "SIMD/Scalar/i32.h"
#    include "SIMD/Scalar/i64.h"
#endif
// IWYU pragma: end_exports

#endif
