#ifndef AXN_LVL_SIMD_AVX_F32_H
#define AXN_LVL_SIMD_AVX_F32_H

#include <emmintrin.h>
#include <immintrin.h>
#include <smmintrin.h>

#include "../../System/Simd.h" // IWYU pragma: keep
#include "../../Types.h"
#include "../Simd.h"

namespace Level { namespace SIMD {
    template <>
    union Simd<128, f32> {
        __m128 v128;
        f32    v32[4];
        Simd() {}
        Simd(__m128 a0) { v128 = a0; }
        Simd(f32 a0, f32 a1, f32 a2, f32 a3) {
            v32[0] = a0;
            v32[1] = a1;
            v32[2] = a2;
            v32[3] = a3;
        }
    };
    template <>
    union Simd<256, f32> {
        __m256 v256;
        __m128 v128[2];
        f32    v32[8];
        Simd() {}
        Simd(__m256 a0) { v256 = a0; }
        Simd(__m128 a0, __m128 a1) {
            v128[0] = a0;
            v128[1] = a1;
        }
        Simd(f32 a0, f32 a1, f32 a2, f32 a3, f32 a4, f32 a5, f32 a6, f32 a7) {
            v32[0] = a0;
            v32[1] = a1;
            v32[2] = a2;
            v32[3] = a3;
            v32[4] = a4;
            v32[5] = a5;
            v32[6] = a6;
            v32[7] = a7;
        }
    };
    template <>
    union Simd<512, f32> {
#if AXM_SIMD_AVX512F
        __m512 v512;
#endif
        __m256 v256[2];
        __m128 v128[4];
        f32    v32[16];
        Simd() {}
#if AXM_SIMD_AVX512F
        Simd(__m512 a0) { v512 = a0; }
#endif
        Simd(__m256 a0, __m256 a1) {
            v256[0] = a0;
            v256[1] = a1;
        }
        Simd(__m128 a0, __m128 a1, __m128 a2, __m128 a3) {
            v128[0] = a0;
            v128[1] = a1;
            v128[2] = a2;
            v128[3] = a3;
        }
        Simd(
            f32 a0, f32 a1, f32 a2, f32 a3, f32 a4, f32 a5, f32 a6, f32 a7, f32 a8, f32 a9, f32 a10,
            f32 a11, f32 a12, f32 a13, f32 a14, f32 a15) {
            v32[0]  = a0;
            v32[1]  = a1;
            v32[2]  = a2;
            v32[3]  = a3;
            v32[4]  = a4;
            v32[5]  = a5;
            v32[6]  = a6;
            v32[7]  = a7;
            v32[8]  = a8;
            v32[9]  = a9;
            v32[10] = a10;
            v32[11] = a11;
            v32[12] = a12;
            v32[13] = a13;
            v32[14] = a14;
            v32[15] = a15;
        }
    };

    template <>
    inline Simd<128, f32> load(const f32* ptr) {
        return Simd<128, f32>(_mm_loadu_ps(ptr));
    }
    template <>
    inline Simd<256, f32> load(const f32* ptr) {
        return Simd<256, f32>(_mm256_loadu_ps(ptr));
    }
    template <>
    inline Simd<512, f32> load(const f32* ptr) {
#if AXM_SIMD_AVX512F
        return Simd<512, f32>(_mm512_loadu_ps(ptr));
#else
        return Simd<512, f32>(_mm256_loadu_ps(ptr), _mm256_loadu_ps(ptr + 8));
#endif
    }
    template <>
    inline void store(f32* ptr, const Simd<128, f32> &simd) {
        _mm_storeu_ps(ptr, simd.v128);
    }
    template <>
    inline void store(f32* ptr, const Simd<256, f32> &simd) {
        _mm256_storeu_ps(ptr, simd.v256);
    }
    template <>
    inline void store(f32* ptr, const Simd<512, f32> &simd) {
#if AXM_SIMD_AVX512F
        _mm512_storeu_ps(ptr, simd.v512);
#else
        _mm256_storeu_ps(ptr, simd.v256[0]);
        _mm256_storeu_ps(ptr + 8, simd.v256[1]);
#endif
    }
    template <>
    inline Simd<128, f32> set1(const f32 value) {
        return Simd<128, f32>(_mm_set1_ps(value));
    }
    template <>
    inline Simd<256, f32> set1(const f32 value) {
        return Simd<256, f32>(_mm256_set1_ps(value));
    }
    template <>
    inline Simd<512, f32> set1(const f32 value) {
#if AXM_SIMD_AVX512F
        return Simd<512, f32>(_mm512_set1_ps(value));
#else
        __m256 v = _mm256_set1_ps(value);
        return Simd<512, f32>(v, v);
#endif
    }
    template <>
    inline Simd<128, f32> set(const f32 a0, const f32 a1, const f32 a2, const f32 a3) {
        return Simd<128, f32>(_mm_set_ps(a3, a2, a1, a0));
    }
    template <>
    inline Simd<256, f32>
        set(const f32 a0, const f32 a1, const f32 a2, const f32 a3, const f32 a4, const f32 a5,
            const f32 a6, const f32 a7) {
        return Simd<256, f32>(_mm256_set_ps(a7, a6, a5, a4, a3, a2, a1, a0));
    }
    template <>
    inline Simd<512, f32>
        set(const f32 a0, const f32 a1, const f32 a2, const f32 a3, const f32 a4, const f32 a5,
            const f32 a6, const f32 a7, const f32 a8, const f32 a9, const f32 a10, const f32 a11,
            const f32 a12, const f32 a13, const f32 a14, const f32 a15) {
#if AXM_SIMD_AVX512F
        return Simd<512, f32>(
            _mm512_set_ps(a15, a14, a13, a12, a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1, a0));
#else
        return Simd<512, f32>(
            _mm256_set_ps(a7, a6, a5, a4, a3, a2, a1, a0),
            _mm256_set_ps(a15, a14, a13, a12, a11, a10, a9, a8));
#endif
    }

    template <>
    inline Simd<128, f32> add(const Simd<128, f32> &a, const Simd<128, f32> &b) {
        return Simd<128, f32>(_mm_add_ps(a.v128, b.v128));
    }
    template <>
    inline Simd<256, f32> add(const Simd<256, f32> &a, const Simd<256, f32> &b) {
        return Simd<256, f32>(_mm256_add_ps(a.v256, b.v256));
    }
    template <>
    inline Simd<512, f32> add(const Simd<512, f32> &a, const Simd<512, f32> &b) {
#if AXM_SIMD_AVX512F
        return Simd<512, f32>(_mm512_add_ps(a.v512, b.v512));
#else
        return Simd<512, f32>(
            _mm256_add_ps(a.v256[0], b.v256[0]), _mm256_add_ps(a.v256[1], b.v256[1]));
#endif
    }
    template <>
    inline Simd<128, f32> sub(const Simd<128, f32> &a, const Simd<128, f32> &b) {
        return Simd<128, f32>(_mm_sub_ps(a.v128, b.v128));
    }
    template <>
    inline Simd<256, f32> sub(const Simd<256, f32> &a, const Simd<256, f32> &b) {
        return Simd<256, f32>(_mm256_sub_ps(a.v256, b.v256));
    }
    template <>
    inline Simd<512, f32> sub(const Simd<512, f32> &a, const Simd<512, f32> &b) {
#if AXM_SIMD_AVX512F
        return Simd<512, f32>(_mm512_sub_ps(a.v512, b.v512));
#else
        return Simd<512, f32>(
            _mm256_sub_ps(a.v256[0], b.v256[0]), _mm256_sub_ps(a.v256[1], b.v256[1]));
#endif
    }
    template <>
    inline Simd<128, f32> abs(const Simd<128, f32> &a) {
        __m128 mask = _mm_set_ps1((f32)0x7FFFFFFF);
        return Simd<128, f32>(_mm_and_ps(a.v128, mask));
    }
    template <>
    inline Simd<256, f32> abs(const Simd<256, f32> &a) {
        __m256 mask = _mm256_set1_ps((f32)0x7FFFFFFF);
        return Simd<256, f32>(_mm256_and_ps(a.v256, mask));
    }
    template <>
    inline Simd<512, f32> abs(const Simd<512, f32> &a) {
#if AXM_SIMD_AVX512F
        return Simd<512, f32>(_mm512_abs_ps(a.v512));
#else
        __m256 mask = _mm256_set1_ps((f32)0x7FFFFFFF);
        return Simd<512, f32>(_mm256_and_ps(a.v256[0], mask), _mm256_and_ps(a.v256[1], mask));
#endif
    }
    template <>
    inline Simd<128, f32> neg(const Simd<128, f32> &a) {
        return Simd<128, f32>(_mm_xor_ps(a.v128, _mm_set1_ps(-0.0f)));
    }
    template <>
    inline Simd<256, f32> neg(const Simd<256, f32> &a) {
        return Simd<256, f32>(_mm256_xor_ps(a.v256, _mm256_set1_ps(-0.0f)));
    }
    template <>
    inline Simd<512, f32> neg(const Simd<512, f32> &a) {
#if AXM_SIMD_AVX512F
        return Simd<512, f32>(_mm512_xor_ps(a.v512, _mm512_set1_ps(-0.0f)));
#else
        __m256 sign = _mm256_set1_ps(-0.0f);
        return Simd<512, f32>(_mm256_xor_ps(a.v256[0], sign), _mm256_xor_ps(a.v256[1], sign));
#endif
    }
    template <>
    inline Simd<128, f32> min(const Simd<128, f32> &a, const Simd<128, f32> &b) {
        return Simd<128, f32>(_mm_min_ps(a.v128, b.v128));
    }
    template <>
    inline Simd<256, f32> min(const Simd<256, f32> &a, const Simd<256, f32> &b) {
        return Simd<256, f32>(_mm256_min_ps(a.v256, b.v256));
    }
    template <>
    inline Simd<512, f32> min(const Simd<512, f32> &a, const Simd<512, f32> &b) {
#if AXM_SIMD_AVX512F
        return Simd<512, f32>(_mm512_min_ps(a.v512, b.v512));
#else
        return Simd<512, f32>(
            _mm256_min_ps(a.v256[0], b.v256[0]), _mm256_min_ps(a.v256[1], b.v256[1]));
#endif
    }
    template <>
    inline Simd<128, f32> max(const Simd<128, f32> &a, const Simd<128, f32> &b) {
        return Simd<128, f32>(_mm_max_ps(a.v128, b.v128));
    }
    template <>
    inline Simd<256, f32> max(const Simd<256, f32> &a, const Simd<256, f32> &b) {
        return Simd<256, f32>(_mm256_max_ps(a.v256, b.v256));
    }

    template <>
    inline Simd<512, f32> max(const Simd<512, f32> &a, const Simd<512, f32> &b) {
#if AXM_SIMD_AVX512F
        return Simd<512, f32>(_mm512_max_ps(a.v512, b.v512));
#else
        return Simd<512, f32>(
            _mm256_max_ps(a.v256[0], b.v256[0]), _mm256_max_ps(a.v256[1], b.v256[1]));
#endif
    }

    template <>
    inline Simd<128, f32> land(const Simd<128, f32> &a, const Simd<128, f32> &b) {
        return Simd<128, f32>(_mm_and_ps(a.v128, b.v128));
    }
    template <>
    inline Simd<256, f32> land(const Simd<256, f32> &a, const Simd<256, f32> &b) {
        return Simd<256, f32>(_mm256_and_ps(a.v256, b.v256));
    }
    template <>
    inline Simd<512, f32> land(const Simd<512, f32> &a, const Simd<512, f32> &b) {
#if AXM_SIMD_AVX512F
        return Simd<512, f32>(_mm512_and_ps(a.v512, b.v512));
#else
        return Simd<512, f32>(
            _mm256_and_ps(a.v256[0], b.v256[0]), _mm256_and_ps(a.v256[1], b.v256[1]));
#endif
    }
    template <>
    inline Simd<128, f32> lor(const Simd<128, f32> &a, const Simd<128, f32> &b) {
        return Simd<128, f32>(_mm_or_ps(a.v128, b.v128));
    }
    template <>
    inline Simd<256, f32> lor(const Simd<256, f32> &a, const Simd<256, f32> &b) {
        return Simd<256, f32>(_mm256_or_ps(a.v256, b.v256));
    }
    template <>
    inline Simd<512, f32> lor(const Simd<512, f32> &a, const Simd<512, f32> &b) {
#if AXM_SIMD_AVX512F
        return Simd<512, f32>(_mm512_or_ps(a.v512, b.v512));
#else
        return Simd<512, f32>(
            _mm256_or_ps(a.v256[0], b.v256[0]), _mm256_or_ps(a.v256[1], b.v256[1]));
#endif
    }
    template <>
    inline Simd<128, f32> lxor(const Simd<128, f32> &a, const Simd<128, f32> &b) {
        return Simd<128, f32>(_mm_xor_ps(a.v128, b.v128));
    }
    template <>
    inline Simd<256, f32> lxor(const Simd<256, f32> &a, const Simd<256, f32> &b) {
        return Simd<256, f32>(_mm256_xor_ps(a.v256, b.v256));
    }
    template <>
    inline Simd<512, f32> lxor(const Simd<512, f32> &a, const Simd<512, f32> &b) {
#if AXM_SIMD_AVX512F
        return Simd<512, f32>(_mm512_xor_ps(a.v512, b.v512));
#else
        return Simd<512, f32>(
            _mm256_xor_ps(a.v256[0], b.v256[0]), _mm256_xor_ps(a.v256[1], b.v256[1]));
#endif
    }
    template <>
    inline Simd<128, f32> lnot(const Simd<128, f32> &a) {
        __m128 ones = _mm_set_ps1(~0);
        return Simd<128, f32>(_mm_xor_ps(a.v128, ones));
    }
    template <>
    inline Simd<256, f32> lnot(const Simd<256, f32> &a) {
        __m256 ones = _mm256_set1_ps(~0);
        return Simd<256, f32>(_mm256_xor_ps(a.v256, ones));
    }
    template <>
    inline Simd<512, f32> lnot(const Simd<512, f32> &a) {
#if AXM_SIMD_AVX512F
        return Simd<512, f32>(_mm512_castsi512_ps(_mm512_ternarylogic_epi32(
            _mm512_castps_si512(a.v512), _mm512_castps_si512(a.v512), _mm512_castps_si512(a.v512),
            0x0F)));
#else
        __m256 ones = _mm256_set1_ps(~0);
        return Simd<512, f32>(_mm256_xor_ps(a.v256[0], ones), _mm256_xor_ps(a.v256[1], ones));
#endif
    }
    template <>
    inline Simd<128, f32> landnot(const Simd<128, f32> &a, const Simd<128, f32> &b) {
        return Simd<128, f32>(_mm_andnot_ps(b.v128, a.v128));
    }
    template <>
    inline Simd<256, f32> landnot(const Simd<256, f32> &a, const Simd<256, f32> &b) {
        return Simd<256, f32>(_mm256_andnot_ps(b.v256, a.v256));
    }
    template <>
    inline Simd<512, f32> landnot(const Simd<512, f32> &a, const Simd<512, f32> &b) {
#if AXM_SIMD_AVX512F
        return Simd<512, f32>(_mm512_castsi512_ps(_mm512_ternarylogic_epi32(
            _mm512_castps_si512(a.v512), _mm512_castps_si512(b.v512), _mm512_castps_si512(b.v512),
            0x40)));
#else
        return Simd<512, f32>(
            _mm256_andnot_ps(b.v256[0], a.v256[0]), _mm256_andnot_ps(b.v256[1], a.v256[1]));
#endif
    }

    template <>
    inline Simd<128, f32> mul(const Simd<128, f32> &a, const Simd<128, f32> &b) {
        return Simd<128, f32>(_mm_mul_ps(a.v128, b.v128));
    }
    template <>
    inline Simd<256, f32> mul(const Simd<256, f32> &a, const Simd<256, f32> &b) {
        return Simd<256, f32>(_mm256_mul_ps(a.v256, b.v256));
    }
    template <>
    inline Simd<512, f32> mul(const Simd<512, f32> &a, const Simd<512, f32> &b) {
#if AXM_SIMD_AVX512F
        return Simd<512, f32>(_mm512_mul_ps(a.v512, b.v512));
#else
        return Simd<512, f32>(
            _mm256_mul_ps(a.v256[0], b.v256[0]), _mm256_mul_ps(a.v256[1], b.v256[1]));
#endif
    }
    template <>
    inline Simd<128, f32> div(const Simd<128, f32> &a, const Simd<128, f32> &b) {
        return Simd<128, f32>(_mm_div_ps(a.v128, b.v128));
    }
    template <>
    inline Simd<256, f32> div(const Simd<256, f32> &a, const Simd<256, f32> &b) {
        return Simd<256, f32>(_mm256_div_ps(a.v256, b.v256));
    }
    template <>
    inline Simd<512, f32> div(const Simd<512, f32> &a, const Simd<512, f32> &b) {
#if AXM_SIMD_AVX512F
        return Simd<512, f32>(_mm512_div_ps(a.v512, b.v512));
#else
        return Simd<512, f32>(
            _mm256_div_ps(a.v256[0], b.v256[0]), _mm256_div_ps(a.v256[1], b.v256[1]));
#endif
    }
    template <>
    inline Simd<128, f32> sqrt(const Simd<128, f32> &a) {
        return Simd<128, f32>(_mm_sqrt_ps(a.v128));
    }
    template <>
    inline Simd<256, f32> sqrt(const Simd<256, f32> &a) {
        return Simd<256, f32>(_mm256_sqrt_ps(a.v256));
    }
    template <>
    inline Simd<512, f32> sqrt(const Simd<512, f32> &a) {
#if AXM_SIMD_AVX512F
        return Simd<512, f32>(_mm512_sqrt_ps(a.v512));
#else
        return Simd<512, f32>(_mm256_sqrt_ps(a.v256[0]), _mm256_sqrt_ps(a.v256[1]));
#endif
    }
    template <>
    inline Simd<128, f32> rsqrt(const Simd<128, f32> &a) {
        return Simd<128, f32>(_mm_rsqrt_ps(a.v128));
    }
    template <>
    inline Simd<256, f32> rsqrt(const Simd<256, f32> &a) {
        return Simd<256, f32>(_mm256_rsqrt_ps(a.v256));
    }
    template <>
    inline Simd<512, f32> rsqrt(const Simd<512, f32> &a) {
#if AXM_SIMD_AVX512F
        return Simd<512, f32>(_mm512_rsqrt14_ps(a.v512));
#else
        return Simd<512, f32>(_mm256_rsqrt_ps(a.v256[0]), _mm256_rsqrt_ps(a.v256[1]));
#endif
    }
    template <>
    inline Simd<128, f32> reciprocal(const Simd<128, f32> &a) {
        return Simd<128, f32>(_mm_rcp_ps(a.v128));
    }
    template <>
    inline Simd<256, f32> reciprocal(const Simd<256, f32> &a) {
        return Simd<256, f32>(_mm256_rcp_ps(a.v256));
    }
    template <>
    inline Simd<512, f32> reciprocal(const Simd<512, f32> &a) {
#if AXM_SIMD_AVX512F
        return Simd<512, f32>(_mm512_rcp14_ps(a.v512));
#else
        return Simd<512, f32>(_mm256_rcp_ps(a.v256[0]), _mm256_rcp_ps(a.v256[1]));
#endif
    }

    template <>
    inline Simd<128, f32> cmpEq(const Simd<128, f32> &a, const Simd<128, f32> &b) {
        return Simd<128, f32>(_mm_cmpeq_ps(a.v128, b.v128));
    }
    template <>
    inline Simd<256, f32> cmpEq(const Simd<256, f32> &a, const Simd<256, f32> &b) {
        return Simd<256, f32>(_mm256_cmp_ps(a.v256, b.v256, _CMP_EQ_OQ));
    }
    template <>
    inline Simd<512, f32> cmpEq(const Simd<512, f32> &a, const Simd<512, f32> &b) {
#if AXM_SIMD_AVX512F
        __mmask16 k = _mm512_cmp_ps_mask(a.v512, b.v512, _CMP_EQ_OQ);
        return Simd<512, f32>(_mm512_maskz_mov_ps(k, _mm512_set1_ps(-1.0f)));
#else
        return Simd<512, f32>(
            _mm256_cmp_ps(a.v256[0], b.v256[0], _CMP_EQ_OQ),
            _mm256_cmp_ps(a.v256[1], b.v256[1], _CMP_EQ_OQ));
#endif
    }
    template <>
    inline Simd<128, f32> cmpNe(const Simd<128, f32> &a, const Simd<128, f32> &b) {
        return Simd<128, f32>(_mm_cmpneq_ps(a.v128, b.v128));
    }
    template <>
    inline Simd<256, f32> cmpNe(const Simd<256, f32> &a, const Simd<256, f32> &b) {
        return Simd<256, f32>(_mm256_cmp_ps(a.v256, b.v256, _CMP_NEQ_OQ));
    }
    template <>
    inline Simd<512, f32> cmpNe(const Simd<512, f32> &a, const Simd<512, f32> &b) {
#if AXM_SIMD_AVX512F
        __mmask16 k = _mm512_cmp_ps_mask(a.v512, b.v512, _CMP_NEQ_OQ);
        return Simd<512, f32>(_mm512_maskz_mov_ps(k, _mm512_set1_ps(-1.0f)));
#else
        return Simd<512, f32>(
            _mm256_cmp_ps(a.v256[0], b.v256[0], _CMP_NEQ_OQ),
            _mm256_cmp_ps(a.v256[1], b.v256[1], _CMP_NEQ_OQ));
#endif
    }
    template <>
    inline Simd<128, f32> cmpLt(const Simd<128, f32> &a, const Simd<128, f32> &b) {
        return Simd<128, f32>(_mm_cmplt_ps(a.v128, b.v128));
    }
    template <>
    inline Simd<256, f32> cmpLt(const Simd<256, f32> &a, const Simd<256, f32> &b) {
        return Simd<256, f32>(_mm256_cmp_ps(a.v256, b.v256, _CMP_LT_OQ));
    }
    template <>
    inline Simd<512, f32> cmpLt(const Simd<512, f32> &a, const Simd<512, f32> &b) {
#if AXM_SIMD_AVX512F
        __mmask16 k = _mm512_cmp_ps_mask(a.v512, b.v512, _CMP_LT_OQ);
        return Simd<512, f32>(_mm512_maskz_mov_ps(k, _mm512_set1_ps(-1.0f)));
#else
        return Simd<512, f32>(
            _mm256_cmp_ps(a.v256[0], b.v256[0], _CMP_LT_OQ),
            _mm256_cmp_ps(a.v256[1], b.v256[1], _CMP_LT_OQ));
#endif
    }
    template <>
    inline Simd<128, f32> cmpLe(const Simd<128, f32> &a, const Simd<128, f32> &b) {
        return Simd<128, f32>(_mm_cmple_ps(a.v128, b.v128));
    }
    template <>
    inline Simd<256, f32> cmpLe(const Simd<256, f32> &a, const Simd<256, f32> &b) {
        return Simd<256, f32>(_mm256_cmp_ps(a.v256, b.v256, _CMP_LE_OQ));
    }
    template <>
    inline Simd<512, f32> cmpLe(const Simd<512, f32> &a, const Simd<512, f32> &b) {
#if AXM_SIMD_AVX512F
        __mmask16 k = _mm512_cmp_ps_mask(a.v512, b.v512, _CMP_LE_OQ);
        return Simd<512, f32>(_mm512_maskz_mov_ps(k, _mm512_set1_ps(-1.0f)));
#else
        return Simd<512, f32>(
            _mm256_cmp_ps(a.v256[0], b.v256[0], _CMP_LE_OQ),
            _mm256_cmp_ps(a.v256[1], b.v256[1], _CMP_LE_OQ));
#endif
    }
    template <>
    inline Simd<128, f32> cmpGt(const Simd<128, f32> &a, const Simd<128, f32> &b) {
        return Simd<128, f32>(_mm_cmpgt_ps(a.v128, b.v128));
    }
    template <>
    inline Simd<256, f32> cmpGt(const Simd<256, f32> &a, const Simd<256, f32> &b) {
        return Simd<256, f32>(_mm256_cmp_ps(a.v256, b.v256, _CMP_GT_OQ));
    }
    template <>
    inline Simd<512, f32> cmpGt(const Simd<512, f32> &a, const Simd<512, f32> &b) {
#if AXM_SIMD_AVX512F
        __mmask16 k = _mm512_cmp_ps_mask(a.v512, b.v512, _CMP_GT_OQ);
        return Simd<512, f32>(_mm512_maskz_mov_ps(k, _mm512_set1_ps(-1.0f)));
#else
        return Simd<512, f32>(
            _mm256_cmp_ps(a.v256[0], b.v256[0], _CMP_GT_OQ),
            _mm256_cmp_ps(a.v256[1], b.v256[1], _CMP_GT_OQ));
#endif
    }
    template <>
    inline Simd<128, f32> cmpGe(const Simd<128, f32> &a, const Simd<128, f32> &b) {
        return Simd<128, f32>(_mm_cmpge_ps(a.v128, b.v128));
    }
    template <>
    inline Simd<256, f32> cmpGe(const Simd<256, f32> &a, const Simd<256, f32> &b) {
        return Simd<256, f32>(_mm256_cmp_ps(a.v256, b.v256, _CMP_GE_OQ));
    }
    template <>
    inline Simd<512, f32> cmpGe(const Simd<512, f32> &a, const Simd<512, f32> &b) {
#if AXM_SIMD_AVX512F
        __mmask16 k = _mm512_cmp_ps_mask(a.v512, b.v512, _CMP_GE_OQ);
        return Simd<512, f32>(_mm512_maskz_mov_ps(k, _mm512_set1_ps(-1.0f)));
#else
        return Simd<512, f32>(
            _mm256_cmp_ps(a.v256[0], b.v256[0], _CMP_GE_OQ),
            _mm256_cmp_ps(a.v256[1], b.v256[1], _CMP_GE_OQ));
#endif
    }

    template <>
    inline u32 movemask(const Simd<128, f32> &a) {
        return (u32)_mm_movemask_ps(a.v128);
    }
    template <>
    inline u32 movemask(const Simd<256, f32> &a) {
        return (u32)_mm256_movemask_ps(a.v256);
    }

    template <>
    inline u64 movemask(const Simd<512, f32> &a) {
#if AXM_SIMD_AVX512BW
        return (u64)_mm512_movepi8_mask(a.v512);
#else
        return (u64)_mm256_movemask_ps(a.v256[0]) | ((u64)_mm256_movemask_ps(a.v256[1]) << 8);
#endif
    }
}}

#endif
