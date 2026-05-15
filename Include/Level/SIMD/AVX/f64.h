#ifndef AXN_LVL_SIMD_AVX_F64_H
#define AXN_LVL_SIMD_AVX_F64_H

#include <emmintrin.h>
#include <immintrin.h>
#include <smmintrin.h>

#include "../../System/Simd.h" // IWYU pragma: keep
#include "../../Types.h"
#include "../Simd.h"

namespace Level { namespace SIMD {
    template <>
    union Simd<128, f64> {
        __m128d v128;
        f64     v64[2];
        Simd() {}
        Simd(__m128d a0) { v128 = a0; }
        Simd(f64 a0, f64 a1, f64 a2, f64 a3) {
            v64[0] = a0;
            v64[1] = a1;
        }
    };
    template <>
    union Simd<256, f64> {
        __m256d v256;
        __m128d v128[2];
        f64     v64[4];
        Simd() {}
        Simd(__m256d a0) { v256 = a0; }
        Simd(__m128d a0, __m128d a1) {
            v128[0] = a0;
            v128[1] = a1;
        }
        Simd(f64 a0, f64 a1, f64 a2, f64 a3, f64 a4, f64 a5, f64 a6, f64 a7) {
            v64[0] = a0;
            v64[1] = a1;
            v64[2] = a2;
            v64[3] = a3;
        }
    };
    template <>
    union Simd<512, f64> {
#if AXM_SIMD_AVX512F
        __m512d v512;
#endif
        __m256d v256[2];
        __m128d v128[4];
        f64     v64[8];
        Simd() {}
#if AXM_SIMD_AVX512F
        Simd(__m512d a0) { v512 = a0; }
#endif
        Simd(__m256d a0, __m256d a1) {
            v256[0] = a0;
            v256[1] = a1;
        }
        Simd(__m128d a0, __m128d a1, __m128d a2, __m128d a3) {
            v128[0] = a0;
            v128[1] = a1;
            v128[2] = a2;
            v128[3] = a3;
        }
        Simd(f64 a0, f64 a1, f64 a2, f64 a3, f64 a4, f64 a5, f64 a6, f64 a7) {
            v64[0] = a0;
            v64[1] = a1;
            v64[2] = a2;
            v64[3] = a3;
            v64[4] = a4;
            v64[5] = a5;
            v64[6] = a6;
            v64[7] = a7;
        }
    };

    template <>
    inline Simd<128, f64> load(const f64* ptr) {
        return Simd<128, f64>(_mm_loadu_pd(ptr));
    }
    template <>
    inline Simd<256, f64> load(const f64* ptr) {
        return Simd<256, f64>(_mm256_loadu_pd(ptr));
    }
    template <>
    inline Simd<512, f64> load(const f64* ptr) {
#if AXM_SIMD_AVX512F
        return Simd<512, f64>(_mm512_loadu_pd(ptr));
#else
        return Simd<512, f64>(_mm256_loadu_pd(ptr), _mm256_loadu_pd(ptr + 8));
#endif
    }
    template <>
    inline void store(f64* ptr, const Simd<128, f64> &simd) {
        _mm_storeu_pd(ptr, simd.v128);
    }
    template <>
    inline void store(f64* ptr, const Simd<256, f64> &simd) {
        _mm256_storeu_pd(ptr, simd.v256);
    }
    template <>
    inline void store(f64* ptr, const Simd<512, f64> &simd) {
#if AXM_SIMD_AVX512F
        _mm512_storeu_pd(ptr, simd.v512);
#else
        _mm256_storeu_pd(ptr, simd.v256[0]);
        _mm256_storeu_pd(ptr + 8, simd.v256[1]);
#endif
    }
    template <>
    inline Simd<128, f64> set1(const f64 value) {
        return Simd<128, f64>(_mm_set1_pd(value));
    }
    template <>
    inline Simd<256, f64> set1(const f64 value) {
        return Simd<256, f64>(_mm256_set1_pd(value));
    }
    template <>
    inline Simd<512, f64> set1(const f64 value) {
#if AXM_SIMD_AVX512F
        return Simd<512, f64>(_mm512_set1_pd(value));
#else
        __m256d v = _mm256_set1_pd(value);
        return Simd<512, f64>(v, v);
#endif
    }
    template <>
    inline Simd<128, f64> set(const f64 a0, const f64 a1) {
        return Simd<128, f64>(_mm_set_pd(a1, a0));
    }
    template <>
    inline Simd<256, f64> set(const f64 a0, const f64 a1, const f64 a2, const f64 a3) {
        return Simd<256, f64>(_mm256_set_pd(a3, a2, a1, a0));
    }
    template <>
    inline Simd<512, f64>
        set(const f64 a0, const f64 a1, const f64 a2, const f64 a3, const f64 a4, const f64 a5,
            const f64 a6, const f64 a7) {
#if AXM_SIMD_AVX512F
        return Simd<512, f64>(_mm512_set_pd(a7, a6, a5, a4, a3, a2, a1, a0));
#else
        return Simd<512, f64>(_mm256_set_pd(a3, a2, a1, a0), _mm256_set_pd(a7, a6, a5, a4));
#endif
    }

    template <>
    inline Simd<128, f64> add(const Simd<128, f64> &a, const Simd<128, f64> &b) {
        return Simd<128, f64>(_mm_add_pd(a.v128, b.v128));
    }
    template <>
    inline Simd<256, f64> add(const Simd<256, f64> &a, const Simd<256, f64> &b) {
        return Simd<256, f64>(_mm256_add_pd(a.v256, b.v256));
    }
    template <>
    inline Simd<512, f64> add(const Simd<512, f64> &a, const Simd<512, f64> &b) {
#if AXM_SIMD_AVX512F
        return Simd<512, f64>(_mm512_add_pd(a.v512, b.v512));
#else
        return Simd<512, f64>(
            _mm256_add_pd(a.v256[0], b.v256[0]), _mm256_add_pd(a.v256[1], b.v256[1]));
#endif
    }
    template <>
    inline Simd<128, f64> sub(const Simd<128, f64> &a, const Simd<128, f64> &b) {
        return Simd<128, f64>(_mm_sub_pd(a.v128, b.v128));
    }
    template <>
    inline Simd<256, f64> sub(const Simd<256, f64> &a, const Simd<256, f64> &b) {
        return Simd<256, f64>(_mm256_sub_pd(a.v256, b.v256));
    }
    template <>
    inline Simd<512, f64> sub(const Simd<512, f64> &a, const Simd<512, f64> &b) {
#if AXM_SIMD_AVX512F
        return Simd<512, f64>(_mm512_sub_pd(a.v512, b.v512));
#else
        return Simd<512, f64>(
            _mm256_sub_pd(a.v256[0], b.v256[0]), _mm256_sub_pd(a.v256[1], b.v256[1]));
#endif
    }
    template <>
    inline Simd<128, f64> abs(const Simd<128, f64> &a) {
        __m128d mask = _mm_set_pd1((f32)0x7FFFFFFF);
        return Simd<128, f64>(_mm_and_pd(a.v128, mask));
    }
    template <>
    inline Simd<256, f64> abs(const Simd<256, f64> &a) {
        __m256d mask = _mm256_set1_pd((f32)0x7FFFFFFF);
        return Simd<256, f64>(_mm256_and_pd(a.v256, mask));
    }
    template <>
    inline Simd<512, f64> abs(const Simd<512, f64> &a) {
#if AXM_SIMD_AVX512F
        return Simd<512, f64>(_mm512_abs_pd(a.v512));
#else
        __m256d mask = _mm256_set1_pd((f32)0x7FFFFFFF);
        return Simd<512, f64>(_mm256_and_pd(a.v256[0], mask), _mm256_and_pd(a.v256[1], mask));
#endif
    }
    template <>
    inline Simd<128, f64> neg(const Simd<128, f64> &a) {
        return Simd<128, f64>(_mm_xor_pd(a.v128, _mm_set1_pd(-0.0f)));
    }
    template <>
    inline Simd<256, f64> neg(const Simd<256, f64> &a) {
        return Simd<256, f64>(_mm256_xor_pd(a.v256, _mm256_set1_pd(-0.0f)));
    }
    template <>
    inline Simd<512, f64> neg(const Simd<512, f64> &a) {
#if AXM_SIMD_AVX512F
        return Simd<512, f64>(_mm512_xor_pd(a.v512, _mm512_set1_pd(-0.0f)));
#else
        __m256d sign = _mm256_set1_pd(-0.0f);
        return Simd<512, f64>(_mm256_xor_pd(a.v256[0], sign), _mm256_xor_pd(a.v256[1], sign));
#endif
    }
    template <>
    inline Simd<128, f64> min(const Simd<128, f64> &a, const Simd<128, f64> &b) {
        return Simd<128, f64>(_mm_min_pd(a.v128, b.v128));
    }
    template <>
    inline Simd<256, f64> min(const Simd<256, f64> &a, const Simd<256, f64> &b) {
        return Simd<256, f64>(_mm256_min_pd(a.v256, b.v256));
    }
    template <>
    inline Simd<512, f64> min(const Simd<512, f64> &a, const Simd<512, f64> &b) {
#if AXM_SIMD_AVX512F
        return Simd<512, f64>(_mm512_min_pd(a.v512, b.v512));
#else
        return Simd<512, f64>(
            _mm256_min_pd(a.v256[0], b.v256[0]), _mm256_min_pd(a.v256[1], b.v256[1]));
#endif
    }
    template <>
    inline Simd<128, f64> max(const Simd<128, f64> &a, const Simd<128, f64> &b) {
        return Simd<128, f64>(_mm_max_pd(a.v128, b.v128));
    }
    template <>
    inline Simd<256, f64> max(const Simd<256, f64> &a, const Simd<256, f64> &b) {
        return Simd<256, f64>(_mm256_max_pd(a.v256, b.v256));
    }

    template <>
    inline Simd<512, f64> max(const Simd<512, f64> &a, const Simd<512, f64> &b) {
#if AXM_SIMD_AVX512F
        return Simd<512, f64>(_mm512_max_pd(a.v512, b.v512));
#else
        return Simd<512, f64>(
            _mm256_max_pd(a.v256[0], b.v256[0]), _mm256_max_pd(a.v256[1], b.v256[1]));
#endif
    }

    template <>
    inline Simd<128, f64> land(const Simd<128, f64> &a, const Simd<128, f64> &b) {
        return Simd<128, f64>(_mm_and_pd(a.v128, b.v128));
    }
    template <>
    inline Simd<256, f64> land(const Simd<256, f64> &a, const Simd<256, f64> &b) {
        return Simd<256, f64>(_mm256_and_pd(a.v256, b.v256));
    }
    template <>
    inline Simd<512, f64> land(const Simd<512, f64> &a, const Simd<512, f64> &b) {
#if AXM_SIMD_AVX512F
        return Simd<512, f64>(_mm512_and_pd(a.v512, b.v512));
#else
        return Simd<512, f64>(
            _mm256_and_pd(a.v256[0], b.v256[0]), _mm256_and_pd(a.v256[1], b.v256[1]));
#endif
    }
    template <>
    inline Simd<128, f64> lor(const Simd<128, f64> &a, const Simd<128, f64> &b) {
        return Simd<128, f64>(_mm_or_pd(a.v128, b.v128));
    }
    template <>
    inline Simd<256, f64> lor(const Simd<256, f64> &a, const Simd<256, f64> &b) {
        return Simd<256, f64>(_mm256_or_pd(a.v256, b.v256));
    }
    template <>
    inline Simd<512, f64> lor(const Simd<512, f64> &a, const Simd<512, f64> &b) {
#if AXM_SIMD_AVX512F
        return Simd<512, f64>(_mm512_or_pd(a.v512, b.v512));
#else
        return Simd<512, f64>(
            _mm256_or_pd(a.v256[0], b.v256[0]), _mm256_or_pd(a.v256[1], b.v256[1]));
#endif
    }
    template <>
    inline Simd<128, f64> lxor(const Simd<128, f64> &a, const Simd<128, f64> &b) {
        return Simd<128, f64>(_mm_xor_pd(a.v128, b.v128));
    }
    template <>
    inline Simd<256, f64> lxor(const Simd<256, f64> &a, const Simd<256, f64> &b) {
        return Simd<256, f64>(_mm256_xor_pd(a.v256, b.v256));
    }
    template <>
    inline Simd<512, f64> lxor(const Simd<512, f64> &a, const Simd<512, f64> &b) {
#if AXM_SIMD_AVX512F
        return Simd<512, f64>(_mm512_xor_pd(a.v512, b.v512));
#else
        return Simd<512, f64>(
            _mm256_xor_pd(a.v256[0], b.v256[0]), _mm256_xor_pd(a.v256[1], b.v256[1]));
#endif
    }
    template <>
    inline Simd<128, f64> lnot(const Simd<128, f64> &a) {
        __m128d ones = _mm_set_pd1(~0);
        return Simd<128, f64>(_mm_xor_pd(a.v128, ones));
    }
    template <>
    inline Simd<256, f64> lnot(const Simd<256, f64> &a) {
        __m256d ones = _mm256_set1_pd(~0);
        return Simd<256, f64>(_mm256_xor_pd(a.v256, ones));
    }
    template <>
    inline Simd<512, f64> lnot(const Simd<512, f64> &a) {
#if AXM_SIMD_AVX512F
        return Simd<512, f64>(_mm512_castsi512_pd(_mm512_ternarylogic_epi32(
            _mm512_castps_si512(a.v512), _mm512_castps_si512(a.v512), _mm512_castps_si512(a.v512),
            0x0F)));
#else
        __m256d ones = _mm256_set1_pd(~0);
        return Simd<512, f64>(_mm256_xor_pd(a.v256[0], ones), _mm256_xor_pd(a.v256[1], ones));
#endif
    }
    template <>
    inline Simd<128, f64> landnot(const Simd<128, f64> &a, const Simd<128, f64> &b) {
        return Simd<128, f64>(_mm_andnot_pd(b.v128, a.v128));
    }
    template <>
    inline Simd<256, f64> landnot(const Simd<256, f64> &a, const Simd<256, f64> &b) {
        return Simd<256, f64>(_mm256_andnot_pd(b.v256, a.v256));
    }
    template <>
    inline Simd<512, f64> landnot(const Simd<512, f64> &a, const Simd<512, f64> &b) {
#if AXM_SIMD_AVX512F
        return Simd<512, f64>(_mm512_castsi512_pd(_mm512_ternarylogic_epi32(
            _mm512_castps_si512(a.v512), _mm512_castps_si512(b.v512), _mm512_castps_si512(b.v512),
            0x40)));
#else
        return Simd<512, f64>(
            _mm256_andnot_pd(b.v256[0], a.v256[0]), _mm256_andnot_pd(b.v256[1], a.v256[1]));
#endif
    }

    template <>
    inline Simd<128, f64> mul(const Simd<128, f64> &a, const Simd<128, f64> &b) {
        return Simd<128, f64>(_mm_mul_pd(a.v128, b.v128));
    }
    template <>
    inline Simd<256, f64> mul(const Simd<256, f64> &a, const Simd<256, f64> &b) {
        return Simd<256, f64>(_mm256_mul_pd(a.v256, b.v256));
    }
    template <>
    inline Simd<512, f64> mul(const Simd<512, f64> &a, const Simd<512, f64> &b) {
#if AXM_SIMD_AVX512F
        return Simd<512, f64>(_mm512_mul_pd(a.v512, b.v512));
#else
        return Simd<512, f64>(
            _mm256_mul_pd(a.v256[0], b.v256[0]), _mm256_mul_pd(a.v256[1], b.v256[1]));
#endif
    }
    template <>
    inline Simd<128, f64> div(const Simd<128, f64> &a, const Simd<128, f64> &b) {
        return Simd<128, f64>(_mm_div_pd(a.v128, b.v128));
    }
    template <>
    inline Simd<256, f64> div(const Simd<256, f64> &a, const Simd<256, f64> &b) {
        return Simd<256, f64>(_mm256_div_pd(a.v256, b.v256));
    }
    template <>
    inline Simd<512, f64> div(const Simd<512, f64> &a, const Simd<512, f64> &b) {
#if AXM_SIMD_AVX512F
        return Simd<512, f64>(_mm512_div_pd(a.v512, b.v512));
#else
        return Simd<512, f64>(
            _mm256_div_pd(a.v256[0], b.v256[0]), _mm256_div_pd(a.v256[1], b.v256[1]));
#endif
    }
    template <>
    inline Simd<128, f64> sqrt(const Simd<128, f64> &a) {
        return Simd<128, f64>(_mm_sqrt_pd(a.v128));
    }
    template <>
    inline Simd<256, f64> sqrt(const Simd<256, f64> &a) {
        return Simd<256, f64>(_mm256_sqrt_pd(a.v256));
    }
    template <>
    inline Simd<512, f64> sqrt(const Simd<512, f64> &a) {
#if AXM_SIMD_AVX512F
        return Simd<512, f64>(_mm512_sqrt_pd(a.v512));
#else
        return Simd<512, f64>(_mm256_sqrt_pd(a.v256[0]), _mm256_sqrt_pd(a.v256[1]));
#endif
    }
    template <>
    inline Simd<128, f64> rsqrt(const Simd<128, f64> &a) {
#if AXM_SIMD_AVX512F
        return Simd<128, f64>(_mm_rsqrt14_pd(a.v128));
#else
        return Simd<128, f64>(_mm_div_pd(_mm_set1_pd(1.0), _mm_sqrt_pd(a.v128)));
#endif
    }
    template <>
    inline Simd<256, f64> rsqrt(const Simd<256, f64> &a) {
#if AXM_SIMD_AVX512F
        return Simd<256, f64>(_mm256_rsqrt14_pd(a.v256));
#else
        return Simd<256, f64>(_mm256_div_pd(_mm256_set1_pd(1.0), _mm256_sqrt_pd(a.v256)));
#endif
    }
    template <>
    inline Simd<512, f64> rsqrt(const Simd<512, f64> &a) {
#if AXM_SIMD_AVX512F
        return Simd<512, f64>(_mm512_rsqrt14_pd(a.v512));
#else
        __m256d one = _mm256_set1_pd(1.0);
        return Simd<512, f64>(
            _mm256_div_pd(one, _mm256_sqrt_pd(a.v256[0])),
            _mm256_div_pd(one, _mm256_sqrt_pd(a.v256[1])));
#endif
    }
    template <>
    inline Simd<128, f64> reciprocal(const Simd<128, f64> &a) {
#if AXM_SIMD_AVX512F
        return Simd<128, f64>(_mm_rcp14_pd(a.v128));
#else
        return Simd<128, f64>(_mm_div_pd(_mm_set1_pd(1.0), a.v128));
#endif
    }
    template <>
    inline Simd<256, f64> reciprocal(const Simd<256, f64> &a) {
#if AXM_SIMD_AVX512F
        return Simd<256, f64>(_mm256_rcp14_pd(a.v256));
#else
        return Simd<256, f64>(_mm256_div_pd(_mm256_set1_pd(1.0), a.v256));
#endif
    }
    template <>
    inline Simd<512, f64> reciprocal(const Simd<512, f64> &a) {
#if AXM_SIMD_AVX512F
        return Simd<512, f64>(_mm512_rcp14_pd(a.v512));
#else
        __m256d one = _mm256_set1_pd(1.0);
        return Simd<512, f64>(_mm256_div_pd(one, a.v256[0]), _mm256_div_pd(one, a.v256[1]));
#endif
    }

    template <>
    inline Simd<128, f64> cmpEq(const Simd<128, f64> &a, const Simd<128, f64> &b) {
        return Simd<128, f64>(_mm_cmpeq_pd(a.v128, b.v128));
    }
    template <>
    inline Simd<256, f64> cmpEq(const Simd<256, f64> &a, const Simd<256, f64> &b) {
        return Simd<256, f64>(_mm256_cmp_pd(a.v256, b.v256, _CMP_EQ_OQ));
    }
    template <>
    inline Simd<512, f64> cmpEq(const Simd<512, f64> &a, const Simd<512, f64> &b) {
#if AXM_SIMD_AVX512F
        __mmask16 k = _mm512_cmp_pd_mask(a.v512, b.v512, _CMP_EQ_OQ);
        return Simd<512, f64>(_mm512_maskz_mov_pd(k, _mm512_set1_pd(-1.0f)));
#else
        return Simd<512, f64>(
            _mm256_cmp_pd(a.v256[0], b.v256[0], _CMP_EQ_OQ),
            _mm256_cmp_pd(a.v256[1], b.v256[1], _CMP_EQ_OQ));
#endif
    }
    template <>
    inline Simd<128, f64> cmpNe(const Simd<128, f64> &a, const Simd<128, f64> &b) {
        return Simd<128, f64>(_mm_cmpneq_pd(a.v128, b.v128));
    }
    template <>
    inline Simd<256, f64> cmpNe(const Simd<256, f64> &a, const Simd<256, f64> &b) {
        return Simd<256, f64>(_mm256_cmp_pd(a.v256, b.v256, _CMP_NEQ_OQ));
    }
    template <>
    inline Simd<512, f64> cmpNe(const Simd<512, f64> &a, const Simd<512, f64> &b) {
#if AXM_SIMD_AVX512F
        __mmask16 k = _mm512_cmp_pd_mask(a.v512, b.v512, _CMP_NEQ_OQ);
        return Simd<512, f64>(_mm512_maskz_mov_pd(k, _mm512_set1_pd(-1.0f)));
#else
        return Simd<512, f64>(
            _mm256_cmp_pd(a.v256[0], b.v256[0], _CMP_NEQ_OQ),
            _mm256_cmp_pd(a.v256[1], b.v256[1], _CMP_NEQ_OQ));
#endif
    }
    template <>
    inline Simd<128, f64> cmpLt(const Simd<128, f64> &a, const Simd<128, f64> &b) {
        return Simd<128, f64>(_mm_cmplt_pd(a.v128, b.v128));
    }
    template <>
    inline Simd<256, f64> cmpLt(const Simd<256, f64> &a, const Simd<256, f64> &b) {
        return Simd<256, f64>(_mm256_cmp_pd(a.v256, b.v256, _CMP_LT_OQ));
    }
    template <>
    inline Simd<512, f64> cmpLt(const Simd<512, f64> &a, const Simd<512, f64> &b) {
#if AXM_SIMD_AVX512F
        __mmask16 k = _mm512_cmp_pd_mask(a.v512, b.v512, _CMP_LT_OQ);
        return Simd<512, f64>(_mm512_maskz_mov_pd(k, _mm512_set1_pd(-1.0f)));
#else
        return Simd<512, f64>(
            _mm256_cmp_pd(a.v256[0], b.v256[0], _CMP_LT_OQ),
            _mm256_cmp_pd(a.v256[1], b.v256[1], _CMP_LT_OQ));
#endif
    }
    template <>
    inline Simd<128, f64> cmpLe(const Simd<128, f64> &a, const Simd<128, f64> &b) {
        return Simd<128, f64>(_mm_cmple_pd(a.v128, b.v128));
    }
    template <>
    inline Simd<256, f64> cmpLe(const Simd<256, f64> &a, const Simd<256, f64> &b) {
        return Simd<256, f64>(_mm256_cmp_pd(a.v256, b.v256, _CMP_LE_OQ));
    }
    template <>
    inline Simd<512, f64> cmpLe(const Simd<512, f64> &a, const Simd<512, f64> &b) {
#if AXM_SIMD_AVX512F
        __mmask16 k = _mm512_cmp_pd_mask(a.v512, b.v512, _CMP_LE_OQ);
        return Simd<512, f64>(_mm512_maskz_mov_pd(k, _mm512_set1_pd(-1.0f)));
#else
        return Simd<512, f64>(
            _mm256_cmp_pd(a.v256[0], b.v256[0], _CMP_LE_OQ),
            _mm256_cmp_pd(a.v256[1], b.v256[1], _CMP_LE_OQ));
#endif
    }
    template <>
    inline Simd<128, f64> cmpGt(const Simd<128, f64> &a, const Simd<128, f64> &b) {
        return Simd<128, f64>(_mm_cmpgt_pd(a.v128, b.v128));
    }
    template <>
    inline Simd<256, f64> cmpGt(const Simd<256, f64> &a, const Simd<256, f64> &b) {
        return Simd<256, f64>(_mm256_cmp_pd(a.v256, b.v256, _CMP_GT_OQ));
    }
    template <>
    inline Simd<512, f64> cmpGt(const Simd<512, f64> &a, const Simd<512, f64> &b) {
#if AXM_SIMD_AVX512F
        __mmask16 k = _mm512_cmp_pd_mask(a.v512, b.v512, _CMP_GT_OQ);
        return Simd<512, f64>(_mm512_maskz_mov_pd(k, _mm512_set1_pd(-1.0f)));
#else
        return Simd<512, f64>(
            _mm256_cmp_pd(a.v256[0], b.v256[0], _CMP_GT_OQ),
            _mm256_cmp_pd(a.v256[1], b.v256[1], _CMP_GT_OQ));
#endif
    }
    template <>
    inline Simd<128, f64> cmpGe(const Simd<128, f64> &a, const Simd<128, f64> &b) {
        return Simd<128, f64>(_mm_cmpge_pd(a.v128, b.v128));
    }
    template <>
    inline Simd<256, f64> cmpGe(const Simd<256, f64> &a, const Simd<256, f64> &b) {
        return Simd<256, f64>(_mm256_cmp_pd(a.v256, b.v256, _CMP_GE_OQ));
    }
    template <>
    inline Simd<512, f64> cmpGe(const Simd<512, f64> &a, const Simd<512, f64> &b) {
#if AXM_SIMD_AVX512F
        __mmask16 k = _mm512_cmp_pd_mask(a.v512, b.v512, _CMP_GE_OQ);
        return Simd<512, f64>(_mm512_maskz_mov_pd(k, _mm512_set1_pd(-1.0f)));
#else
        return Simd<512, f64>(
            _mm256_cmp_pd(a.v256[0], b.v256[0], _CMP_GE_OQ),
            _mm256_cmp_pd(a.v256[1], b.v256[1], _CMP_GE_OQ));
#endif
    }

    template <>
    inline u32 movemask(const Simd<128, f64> &a) {
        return (u32)_mm_movemask_pd(a.v128);
    }
    template <>
    inline u32 movemask(const Simd<256, f64> &a) {
        return (u32)_mm256_movemask_pd(a.v256);
    }

    template <>
    inline u64 movemask(const Simd<512, f64> &a) {
#if AXM_SIMD_AVX512BW
        return (u64)_mm512_movepi8_mask(a.v512);
#else
        return (u64)_mm256_movemask_pd(a.v256[0]) | ((u64)_mm256_movemask_pd(a.v256[1]) << 8);
#endif
    }
}}

#endif
