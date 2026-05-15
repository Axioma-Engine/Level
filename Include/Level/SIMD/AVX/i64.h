#ifndef AXM_LVL_SIMD_AVX_I64_H
#define AXM_LVL_SIMD_AVX_I64_H

#include <emmintrin.h>
#include <immintrin.h>
#include <smmintrin.h>

#include "../../System/Simd.h"
#include "../../Types.h"
#include "../Simd.h"

namespace Level { namespace SIMD {
    template <>
    union Simd<128, i64> {
        __m128i v128;
        i64     i[2];
        Simd() {}
        Simd(__m128i a0) { v128 = a0; }
        Simd(i64 a0, i64 a1) {
            i[0] = a0;
            i[1] = a1;
        }
    };
    template <>
    union Simd<256, i64> {
        __m256i v256;
        __m128i v128[2];
        i64     i[4];
        Simd() {}
        Simd(__m256i a0) { v256 = a0; }
        Simd(__m128i a0, __m128i a1) {
            v128[0] = a0;
            v128[1] = a1;
        }
        Simd(i64 a0, i64 a1, i64 a2, i64 a3) {
            i[0] = a0;
            i[1] = a1;
            i[2] = a2;
            i[3] = a3;
        }
    };
    template <>
    union Simd<512, i64> {
#if AXM_SIMD_AVX512F
        __m512i v512;
#endif
        __m256i v256[2];
        __m128i v128[4];
        i64     i[8];
        Simd() {}
#if AXM_SIMD_AVX512F
        Simd(__m512i a0) { v512 = a0; }
#endif
        Simd(__m256i a0, __m256i a1) {
            v256[0] = a0;
            v256[1] = a1;
        }
        Simd(__m128i a0, __m128i a1, __m128i a2, __m128i a3) {
            v128[0] = a0;
            v128[1] = a1;
            v128[2] = a2;
            v128[3] = a3;
        }
        Simd(i64 a0, i64 a1, i64 a2, i64 a3, i64 a4, i64 a5, i64 a6, i64 a7) {
            i[0] = a0;
            i[1] = a1;
            i[2] = a2;
            i[3] = a3;
            i[4] = a4;
            i[5] = a5;
            i[6] = a6;
            i[7] = a7;
        }
    };

    template <>
    inline Simd<128, i64> load(const i64* ptr) {
        return Simd<128, i64>(_mm_loadu_si128((__m128i*)ptr));
    }
    template <>
    inline Simd<256, i64> load(const i64* ptr) {
        return Simd<256, i64>(_mm256_loadu_si256((__m256i*)ptr));
    }
    template <>
    inline Simd<512, i64> load(const i64* ptr) {
#if AXM_SIMD_AVX512F
        return Simd<512, i64>(_mm512_loadu_si512((void*)ptr));
#else
        return Simd<512, i64>(
            _mm256_loadu_si256((__m256i*)ptr), _mm256_loadu_si256((__m256i*)(ptr + 4)));
#endif
    }
    template <>
    inline void store(i64* ptr, const Simd<128, i64> &simd) {
        _mm_storeu_si128((__m128i*)ptr, simd.v128);
    }
    template <>
    inline void store(i64* ptr, const Simd<256, i64> &simd) {
        _mm256_storeu_si256((__m256i*)ptr, simd.v256);
    }
    template <>
    inline void store(i64* ptr, const Simd<512, i64> &simd) {
#if AXM_SIMD_AVX512F
        _mm512_storeu_si512((void*)ptr, simd.v512);
#else
        _mm256_storeu_si256((__m256i*)ptr, simd.v256[0]);
        _mm256_storeu_si256((__m256i*)(ptr + 4), simd.v256[1]);
#endif
    }
    template <>
    inline Simd<128, i64> set1(const i64 value) {
        return Simd<128, i64>(_mm_set1_epi64x(value));
    }
    template <>
    inline Simd<256, i64> set1(const i64 value) {
        return Simd<256, i64>(_mm256_set1_epi64x(value));
    }
    template <>
    inline Simd<512, i64> set1(const i64 value) {
#if AXM_SIMD_AVX512F
        return Simd<512, i64>(_mm512_set1_epi64(value));
#else
        __m256i v = _mm256_set1_epi64x(value);
        return Simd<512, i64>(v, v);
#endif
    }
    template <>
    inline Simd<128, i64> set(const i64 a0, const i64 a1) {
        return Simd<128, i64>(_mm_set_epi64x(a1, a0));
    }
    template <>
    inline Simd<256, i64> set(const i64 a0, const i64 a1, const i64 a2, const i64 a3) {
        return Simd<256, i64>(_mm256_set_epi64x(a3, a2, a1, a0));
    }
    template <>
    inline Simd<512, i64>
        set(const i64 a0, const i64 a1, const i64 a2, const i64 a3, const i64 a4, const i64 a5,
            const i64 a6, const i64 a7) {
#if AXM_SIMD_AVX512F
        return Simd<512, i64>(_mm512_set_epi64(a7, a6, a5, a4, a3, a2, a1, a0));
#else
        return Simd<512, i64>(_mm256_set_epi64x(a3, a2, a1, a0), _mm256_set_epi64x(a7, a6, a5, a4));
#endif
    }

    template <>
    inline Simd<128, i64> add(const Simd<128, i64> &a, const Simd<128, i64> &b) {
        return Simd<128, i64>(_mm_add_epi64(a.v128, b.v128));
    }
    template <>
    inline Simd<256, i64> add(const Simd<256, i64> &a, const Simd<256, i64> &b) {
#if AXM_SIMD_AVX2
        return Simd<256, i64>(_mm256_add_epi64(a.v256, b.v256));
#else
        return Simd<256, i64>(
            _mm_add_epi64(a.v128[0], b.v128[0]), _mm_add_epi64(a.v128[1], b.v128[1]));
#endif
    }
    template <>
    inline Simd<512, i64> add(const Simd<512, i64> &a, const Simd<512, i64> &b) {
#if AXM_SIMD_AVX512F
        return Simd<512, i64>(_mm512_add_epi64(a.v512, b.v512));
#elif AXM_SIMD_AVX2
        return Simd<512, i64>(
            _mm256_add_epi64(a.v256[0], b.v256[0]), _mm256_add_epi64(a.v256[1], b.v256[1]));
#else
        return Simd<512, i64>(
            _mm_add_epi64(a.v128[0], b.v128[0]), _mm_add_epi64(a.v128[1], b.v128[1]),
            _mm_add_epi64(a.v128[2], b.v128[2]), _mm_add_epi64(a.v128[3], b.v128[3]));
#endif
    }
    template <>
    inline Simd<128, i64> sub(const Simd<128, i64> &a, const Simd<128, i64> &b) {
        return Simd<128, i64>(_mm_sub_epi64(a.v128, b.v128));
    }
    template <>
    inline Simd<256, i64> sub(const Simd<256, i64> &a, const Simd<256, i64> &b) {
#if AXM_SIMD_AVX2
        return Simd<256, i64>(_mm256_sub_epi64(a.v256, b.v256));
#else
        return Simd<256, i64>(
            _mm_sub_epi64(a.v128[0], b.v128[0]), _mm_sub_epi64(a.v128[1], b.v128[1]));
#endif
    }
    template <>
    inline Simd<512, i64> sub(const Simd<512, i64> &a, const Simd<512, i64> &b) {
#if AXM_SIMD_AVX512F
        return Simd<512, i64>(_mm512_sub_epi64(a.v512, b.v512));
#elif AXM_SIMD_AVX2
        return Simd<512, i64>(
            _mm256_sub_epi64(a.v256[0], b.v256[0]), _mm256_sub_epi64(a.v256[1], b.v256[1]));
#else
        return Simd<512, i64>(
            _mm_sub_epi64(a.v128[0], b.v128[1]), _mm_sub_epi64(a.v128[1], b.v128[1]),
            _mm_sub_epi64(a.v128[2], b.v128[2]), _mm_sub_epi64(a.v128[3], b.v128[3]));
#endif
    }
    template <>
    inline Simd<128, i64> abs(const Simd<128, i64> &a) {
#if AXM_SIMD_AVX512F
        return Simd<128, i64>(_mm_abs_epi64(a.v128));
#else
        __m128i sign = _mm_srai_epi32(a.v128, 31);
        sign         = _mm_shuffle_epi32(sign, _MM_SHUFFLE(3, 3, 1, 1));
        return _mm_sub_epi64(_mm_xor_si128(a.v128, sign), sign);
#endif
    }
    template <>
    inline Simd<256, i64> abs(const Simd<256, i64> &a) {
#if AXM_SIMD_AVX512F
        return Simd<256, i64>(_mm256_abs_epi64(a.v256));
#elif AXM_SIMD_AVX2
        __m256i sign = _mm256_srai_epi32(a.v256, 31);
        sign         = _mm256_shuffle_epi32(sign, _MM_SHUFFLE(3, 3, 1, 1));
        return Simd<256, i64>(_mm256_sub_epi64(_mm256_xor_si256(a.v256, sign), sign));
#else
        __m128i sign0 = _mm_srai_epi32(a.v128[0], 31);
        __m128i sign1 = _mm_srai_epi32(a.v128[1], 31);
        sign0         = _mm_shuffle_epi32(sign0, _MM_SHUFFLE(3, 3, 1, 1));
        sign1         = _mm_shuffle_epi32(sign1, _MM_SHUFFLE(3, 3, 1, 1));
        return Simd<256, i64>(
            _mm_sub_epi64(_mm_xor_si128(a.v128[0], sign0), sign0),
            _mm_sub_epi64(_mm_xor_si128(a.v128[1], sign1), sign1));
#endif
    }
    template <>
    inline Simd<512, i64> abs(const Simd<512, i64> &a) {
#if AXM_SIMD_AVX512F
        return Simd<512, i64>(_mm512_abs_epi64(a.v512));
#elif AXM_SIMD_AVX2
        __m256i sign0 = _mm256_srai_epi32(a.v256[0], 31);
        __m256i sign1 = _mm256_srai_epi32(a.v256[1], 31);
        sign0         = _mm256_shuffle_epi32(sign0, _MM_SHUFFLE(3, 3, 1, 1));
        sign1         = _mm256_shuffle_epi32(sign1, _MM_SHUFFLE(3, 3, 1, 1));
        return Simd<512, i64>(
            _mm256_sub_epi64(_mm256_xor_si256(a.v256[0], sign0), sign0),
            _mm256_sub_epi64(_mm256_xor_si256(a.v256[1], sign1), sign1));
#else
        __m128i sign0 = _mm_srai_epi32(a.v128[0], 31);
        __m128i sign1 = _mm_srai_epi32(a.v128[1], 31);
        __m128i sign2 = _mm_srai_epi32(a.v128[2], 31);
        __m128i sign3 = _mm_srai_epi32(a.v128[3], 31);
        sign0         = _mm_shuffle_epi32(sign0, _MM_SHUFFLE(3, 3, 1, 1));
        sign1         = _mm_shuffle_epi32(sign1, _MM_SHUFFLE(3, 3, 1, 1));
        sign2         = _mm_shuffle_epi32(sign2, _MM_SHUFFLE(3, 3, 1, 1));
        sign3         = _mm_shuffle_epi32(sign3, _MM_SHUFFLE(3, 3, 1, 1));
        return Simd<512, i64>(
            _mm_sub_epi64(_mm_xor_si128(a.v128[0], sign0), sign0),
            _mm_sub_epi64(_mm_xor_si128(a.v128[1], sign1), sign1),
            _mm_sub_epi64(_mm_xor_si128(a.v128[2], sign2), sign2),
            _mm_sub_epi64(_mm_xor_si128(a.v128[3], sign3), sign3));
#endif
    }
    template <>
    inline Simd<128, i64> neg(const Simd<128, i64> &a) {
        return Simd<128, i64>(_mm_sub_epi64(_mm_setzero_si128(), a.v128));
    }
    template <>
    inline Simd<256, i64> neg(const Simd<256, i64> &a) {
#if AXM_SIMD_AVX2
        return Simd<256, i64>(_mm256_sub_epi64(_mm256_setzero_si256(), a.v256));
#else
        return Simd<256, i64>(
            _mm_sub_epi64(_mm_setzero_si128(), a.v128[0]),
            _mm_sub_epi64(_mm_setzero_si128(), a.v128[1]));
#endif
    }
    template <>
    inline Simd<512, i64> neg(const Simd<512, i64> &a) {
#if AXM_SIMD_AVX512F
        return Simd<512, i64>(_mm512_sub_epi64(_mm512_setzero_si512(), a.v512));
#elif AXM_SIMD_AVX2
        return Simd<512, i64>(
            _mm256_sub_epi64(_mm256_setzero_si256(), a.v256[0]),
            _mm256_sub_epi64(_mm256_setzero_si256(), a.v256[1]));
#else
        return Simd<512, i64>(
            _mm_sub_epi64(_mm_setzero_si128(), a.v128[0]),
            _mm_sub_epi64(_mm_setzero_si128(), a.v128[1]),
            _mm_sub_epi64(_mm_setzero_si128(), a.v128[2]),
            _mm_sub_epi64(_mm_setzero_si128(), a.v128[3]));
#endif
    }
    template <>
    inline Simd<128, i64> min(const Simd<128, i64> &a, const Simd<128, i64> &b) {
#if AXM_SIMD_AVX512F
        return Simd<128, i64>(_mm_min_epi64(a.v128, b.v128));
#elif AXM_SIMD_SSE42
        __m128i mask = _mm_cmpgt_epi64(a.v128, b.v128);
        return Simd<128, i64>(
            _mm_or_si128(_mm_andnot_si128(mask, a.v128), _mm_and_si128(mask, b.v128)));
#else
        return Simd<128, i64>(a.i[0] < b.i[0] ? a.i[0] : b.i[0], a.i[1] < b.i[1] ? a.i[1] : b.i[1]);
#endif
    }
    template <>
    inline Simd<256, i64> min(const Simd<256, i64> &a, const Simd<256, i64> &b) {
#if AXM_SIMD_AVX512F
        return Simd<256, i64>(_mm256_min_epi64(a.v256, b.v256));
#elif AXM_SIMD_AVX2
        __m256i mask = _mm256_cmpgt_epi64(a.v256, b.v256);
        return Simd<256, i64>(
            _mm256_or_si256(_mm256_andnot_si256(mask, a.v256), _mm256_and_si256(mask, b.v256)));
#elif AXM_SIMD_SSE42
        __m128i mask0 = _mm_cmpgt_epi64(a.v128[0], b.v128[0]);
        __m128i mask1 = _mm_cmpgt_epi64(a.v128[1], b.v128[1]);
        return Simd<256, i64>(
            _mm_or_si128(_mm_andnot_si128(mask0, a.v128[0]), _mm_and_si128(mask0, b.v128[0])),
            _mm_or_si128(_mm_andnot_si128(mask1, a.v128[1]), _mm_and_si128(mask1, b.v128[1])));
#else
        return Simd<256, i64>(
            a.i[0] < b.i[0] ? a.i[0] : b.i[0], a.i[1] < b.i[1] ? a.i[1] : b.i[1],
            a.i[2] < b.i[2] ? a.i[2] : b.i[2], a.i[3] < b.i[3] ? a.i[3] : b.i[3]);
#endif
    }
    template <>
    inline Simd<512, i64> min(const Simd<512, i64> &a, const Simd<512, i64> &b) {
#if AXM_SIMD_AVX512F
        return Simd<512, i64>(_mm512_min_epi64(a.v512, b.v512));
#elif AXM_SIMD_AVX2
        __m256i mask0 = _mm256_cmpgt_epi64(a.v256[0], b.v256[0]);
        __m256i mask1 = _mm256_cmpgt_epi64(a.v256[1], b.v256[1]);
        return Simd<512, i64>(
            _mm256_or_si256(
                _mm256_andnot_si256(mask0, a.v256[0]), _mm256_and_si256(mask0, b.v256[0])),
            _mm256_or_si256(
                _mm256_andnot_si256(mask1, a.v256[1]), _mm256_and_si256(mask1, b.v256[1])));
#elif AXM_SIMD_SSE42
        __m128i mask0 = _mm_cmpgt_epi64(a.v128[0], b.v128[0]);
        __m128i mask1 = _mm_cmpgt_epi64(a.v128[1], b.v128[1]);
        __m128i mask2 = _mm_cmpgt_epi64(a.v128[2], b.v128[2]);
        __m128i mask3 = _mm_cmpgt_epi64(a.v128[3], b.v128[3]);
        return Simd<512, i64>(
            _mm_or_si128(_mm_andnot_si128(mask0, a.v128[0]), _mm_and_si128(mask0, b.v128[0])),
            _mm_or_si128(_mm_andnot_si128(mask1, a.v128[1]), _mm_and_si128(mask1, b.v128[1])),
            _mm_or_si128(_mm_andnot_si128(mask2, a.v128[2]), _mm_and_si128(mask2, b.v128[2])),
            _mm_or_si128(_mm_andnot_si128(mask3, a.v128[3]), _mm_and_si128(mask3, b.v128[3])));
#else
        return Simd<512, i64>(
            a.i[0] < b.i[0] ? a.i[0] : b.i[0], a.i[1] < b.i[1] ? a.i[1] : b.i[1],
            a.i[2] < b.i[2] ? a.i[2] : b.i[2], a.i[3] < b.i[3] ? a.i[3] : b.i[3],
            a.i[4] < b.i[4] ? a.i[4] : b.i[4], a.i[5] < b.i[5] ? a.i[5] : b.i[5],
            a.i[6] < b.i[6] ? a.i[6] : b.i[6], a.i[7] < b.i[7] ? a.i[7] : b.i[7]);
#endif
    }
    template <>
    inline Simd<128, i64> max(const Simd<128, i64> &a, const Simd<128, i64> &b) {
#if AXM_SIMD_AVX512F
        return Simd<128, i64>(_mm_max_epi64(a.v128, b.v128));
#elif AXM_SIMD_SSE42
        __m128i mask = _mm_cmpgt_epi64(a.v128, b.v128);
        return Simd<128, i64>(
            _mm_or_si128(_mm_and_si128(mask, a.v128), _mm_andnot_si128(mask, b.v128)));
#else
        return Simd<128, i64>(a.i[0] > b.i[0] ? a.i[0] : b.i[0], a.i[1] > b.i[1] ? a.i[1] : b.i[1]);
#endif
    }
    template <>
    inline Simd<256, i64> max(const Simd<256, i64> &a, const Simd<256, i64> &b) {
#if AXM_SIMD_AVX512F
        return Simd<256, i64>(_mm256_max_epi64(a.v256, b.v256));
#elif AXM_SIMD_AVX2
        __m256i mask = _mm256_cmpgt_epi64(a.v256, b.v256);
        return Simd<256, i64>(
            _mm256_or_si256(_mm256_and_si256(mask, a.v256), _mm256_andnot_si256(mask, b.v256)));
#elif AXM_SIMD_SSE42
        __m128i mask0 = _mm_cmpgt_epi64(a.v128[0], b.v128[0]);
        __m128i mask1 = _mm_cmpgt_epi64(a.v128[1], b.v128[1]);
        return Simd<256, i64>(
            _mm_or_si128(_mm_and_si128(mask0, a.v128[0]), _mm_andnot_si128(mask0, b.v128[0])),
            _mm_or_si128(_mm_and_si128(mask1, a.v128[1]), _mm_andnot_si128(mask1, b.v128[1])));
#else
        return Simd<256, i64>(
            a.i[0] > b.i[0] ? a.i[0] : b.i[0], a.i[1] > b.i[1] ? a.i[1] : b.i[1],
            a.i[2] > b.i[2] ? a.i[2] : b.i[2], a.i[3] > b.i[3] ? a.i[3] : b.i[3]);
#endif
    }
    template <>
    inline Simd<512, i64> max(const Simd<512, i64> &a, const Simd<512, i64> &b) {
#if AXM_SIMD_AVX512F
        return Simd<512, i64>(_mm512_max_epi64(a.v512, b.v512));
#elif AXM_SIMD_AVX2
        __m256i mask0 = _mm256_cmpgt_epi64(a.v256[0], b.v256[0]);
        __m256i mask1 = _mm256_cmpgt_epi64(a.v256[1], b.v256[1]);
        return Simd<512, i64>(
            _mm256_or_si256(
                _mm256_and_si256(mask0, a.v256[0]), _mm256_andnot_si256(mask0, b.v256[0])),
            _mm256_or_si256(
                _mm256_and_si256(mask1, a.v256[1]), _mm256_andnot_si256(mask1, b.v256[1])));
#elif AXM_SIMD_SSE42
        __m128i mask0 = _mm_cmpgt_epi64(a.v128[0], b.v128[0]);
        __m128i mask1 = _mm_cmpgt_epi64(a.v128[1], b.v128[1]);
        __m128i mask2 = _mm_cmpgt_epi64(a.v128[2], b.v128[2]);
        __m128i mask3 = _mm_cmpgt_epi64(a.v128[3], b.v128[3]);
        return Simd<512, i64>(
            _mm_or_si128(_mm_and_si128(mask0, a.v128[0]), _mm_andnot_si128(mask0, b.v128[0])),
            _mm_or_si128(_mm_and_si128(mask1, a.v128[1]), _mm_andnot_si128(mask1, b.v128[1])),
            _mm_or_si128(_mm_and_si128(mask2, a.v128[2]), _mm_andnot_si128(mask2, b.v128[2])),
            _mm_or_si128(_mm_and_si128(mask3, a.v128[3]), _mm_andnot_si128(mask3, b.v128[3])));
#else
        return Simd<512, i64>(
            a.i[0] > b.i[0] ? a.i[0] : b.i[0], a.i[1] > b.i[1] ? a.i[1] : b.i[1],
            a.i[2] > b.i[2] ? a.i[2] : b.i[2], a.i[3] > b.i[3] ? a.i[3] : b.i[3],
            a.i[4] > b.i[4] ? a.i[4] : b.i[4], a.i[5] > b.i[5] ? a.i[5] : b.i[5],
            a.i[6] > b.i[6] ? a.i[6] : b.i[6], a.i[7] > b.i[7] ? a.i[7] : b.i[7]);
#endif
    }

    template <>
    inline Simd<128, i64> land(const Simd<128, i64> &a, const Simd<128, i64> &b) {
        return Simd<128, i64>(_mm_and_si128(a.v128, b.v128));
    }
    template <>
    inline Simd<256, i64> land(const Simd<256, i64> &a, const Simd<256, i64> &b) {
#if AXM_SIMD_AVX2
        return Simd<256, i64>(_mm256_and_si256(a.v256, b.v256));
#else
        return Simd<256, i64>(_mm256_castps_si256(
            _mm256_and_ps(_mm256_castsi256_ps(a.v256), _mm256_castsi256_ps(b.v256))));
#endif
    }
    template <>
    inline Simd<512, i64> land(const Simd<512, i64> &a, const Simd<512, i64> &b) {
#if AXM_SIMD_AVX512F
        return Simd<512, i64>(_mm512_and_si512(a.v512, b.v512));
#elif AXM_SIMD_AVX2
        return Simd<512, i64>(
            _mm256_and_si256(a.v256[0], b.v256[0]), _mm256_and_si256(a.v256[1], b.v256[1]));
#else
        return Simd<512, i64>(
            _mm256_castps_si256(
                _mm256_and_ps(_mm256_castsi256_ps(a.v256[0]), _mm256_castsi256_ps(b.v256[0]))),
            _mm256_castps_si256(
                _mm256_and_ps(_mm256_castsi256_ps(a.v256[1]), _mm256_castsi256_ps(b.v256[1]))));
#endif
    }
    template <>
    inline Simd<128, i64> lor(const Simd<128, i64> &a, const Simd<128, i64> &b) {
        return Simd<128, i64>(_mm_or_si128(a.v128, b.v128));
    }
    template <>
    inline Simd<256, i64> lor(const Simd<256, i64> &a, const Simd<256, i64> &b) {
#if AXM_SIMD_AVX2
        return Simd<256, i64>(_mm256_or_si256(a.v256, b.v256));
#else
        return Simd<256, i64>(_mm256_castps_si256(
            _mm256_or_ps(_mm256_castsi256_ps(a.v256), _mm256_castsi256_ps(b.v256))));
#endif
    }
    template <>
    inline Simd<512, i64> lor(const Simd<512, i64> &a, const Simd<512, i64> &b) {
#if AXM_SIMD_AVX512F
        return Simd<512, i64>(_mm512_or_si512(a.v512, b.v512));
#elif AXM_SIMD_AVX2
        return Simd<512, i64>(
            _mm256_or_si256(a.v256[0], b.v256[0]), _mm256_or_si256(a.v256[1], b.v256[1]));
#else
        return Simd<512, i64>(
            _mm256_castps_si256(
                _mm256_or_ps(_mm256_castsi256_ps(a.v256[0]), _mm256_castsi256_ps(b.v256[0]))),
            _mm256_castps_si256(
                _mm256_or_ps(_mm256_castsi256_ps(a.v256[1]), _mm256_castsi256_ps(b.v256[1]))));
#endif
    }
    template <>
    inline Simd<128, i64> lxor(const Simd<128, i64> &a, const Simd<128, i64> &b) {
        return Simd<128, i64>(_mm_xor_si128(a.v128, b.v128));
    }
    template <>
    inline Simd<256, i64> lxor(const Simd<256, i64> &a, const Simd<256, i64> &b) {
#if AXM_SIMD_AVX2
        return Simd<256, i64>(_mm256_xor_si256(a.v256, b.v256));
#else
        return Simd<256, i64>(_mm256_castps_si256(
            _mm256_xor_ps(_mm256_castsi256_ps(a.v256), _mm256_castsi256_ps(b.v256))));
#endif
    }
    template <>
    inline Simd<512, i64> lxor(const Simd<512, i64> &a, const Simd<512, i64> &b) {
#if AXM_SIMD_AVX512F
        return Simd<512, i64>(_mm512_xor_si512(a.v512, b.v512));
#elif AXM_SIMD_AVX2
        return Simd<512, i64>(
            _mm256_xor_si256(a.v256[0], b.v256[0]), _mm256_xor_si256(a.v256[1], b.v256[1]));
#else
        return Simd<512, i64>(
            _mm256_castps_si256(
                _mm256_xor_ps(_mm256_castsi256_ps(a.v256[0]), _mm256_castsi256_ps(b.v256[0]))),
            _mm256_castps_si256(
                _mm256_xor_ps(_mm256_castsi256_ps(a.v256[1]), _mm256_castsi256_ps(b.v256[1]))));
#endif
    }
    template <>
    inline Simd<128, i64> lnot(const Simd<128, i64> &a) {
        return Simd<128, i64>(_mm_xor_si128(a.v128, _mm_set1_epi32(~0)));
    }
    template <>
    inline Simd<256, i64> lnot(const Simd<256, i64> &a) {
#if AXM_SIMD_AVX2
        return Simd<256, i64>(_mm256_xor_si256(a.v256, _mm256_set1_epi32(~0)));
#else
        return Simd<256, i64>(_mm256_castps_si256(_mm256_xor_ps(
            _mm256_castsi256_ps(a.v256), _mm256_castsi256_ps(_mm256_set1_epi32(~0)))));
#endif
    }
    template <>
    inline Simd<512, i64> lnot(const Simd<512, i64> &a) {
#if AXM_SIMD_AVX512F
        return Simd<512, i64>(_mm512_xor_si512(a.v512, _mm512_set1_epi32(~0)));
#elif AXM_SIMD_AVX2
        __m256i ones = _mm256_set1_epi32(~0);
        return Simd<512, i64>(_mm256_xor_si256(a.v256[0], ones), _mm256_xor_si256(a.v256[1], ones));
#else
        __m256 ones = _mm256_set1_ps(~0);
        return Simd<512, i64>(
            _mm256_castps_si256(_mm256_xor_ps(_mm256_castsi256_ps(a.v256[0]), ones)),
            _mm256_castps_si256(_mm256_xor_ps(_mm256_castsi256_ps(a.v256[1]), ones)));
#endif
    }
    template <>
    inline Simd<128, i64> landnot(const Simd<128, i64> &a, const Simd<128, i64> &b) {
        return Simd<128, i64>(_mm_andnot_si128(b.v128, a.v128));
    }
    template <>
    inline Simd<256, i64> landnot(const Simd<256, i64> &a, const Simd<256, i64> &b) {
#if AXM_SIMD_AVX2
        return Simd<256, i64>(_mm256_andnot_si256(b.v256, a.v256));
#else
        return Simd<256, i64>(_mm256_castps_si256(
            _mm256_andnot_ps(_mm256_castsi256_ps(b.v256), _mm256_castsi256_ps(a.v256))));
#endif
    }
    template <>
    inline Simd<512, i64> landnot(const Simd<512, i64> &a, const Simd<512, i64> &b) {
#if AXM_SIMD_AVX512F
        return Simd<512, i64>(_mm512_andnot_si512(b.v512, a.v512));
#elif AXM_SIMD_AVX2
        return Simd<512, i64>(
            _mm256_andnot_si256(b.v256[0], a.v256[0]), _mm256_andnot_si256(b.v256[1], a.v256[1]));
#else
        return Simd<512, i64>(
            _mm256_castps_si256(
                _mm256_andnot_ps(_mm256_castsi256_ps(b.v256[0]), _mm256_castsi256_ps(a.v256[0]))),
            _mm256_castps_si256(
                _mm256_andnot_ps(_mm256_castsi256_ps(b.v256[1]), _mm256_castsi256_ps(a.v256[1]))));
#endif
    }

    template <>
    inline Simd<128, i64> shl(const Simd<128, i64> &a, const int count) {
        return Simd<128, i64>(_mm_slli_epi64(a.v128, count));
    }
    template <>
    inline Simd<256, i64> shl(const Simd<256, i64> &a, const int count) {
#if AXM_SIMD_AVX2
        return Simd<256, i64>(_mm256_slli_epi64(a.v256, count));
#else
        return Simd<256, i64>(_mm_slli_epi64(a.v128[0], count), _mm_slli_epi64(a.v128[1], count));
#endif
    }
    template <>
    inline Simd<512, i64> shl(const Simd<512, i64> &a, const int count) {
#if AXM_SIMD_AVX512F
        return Simd<512, i64>(_mm512_slli_epi64(a.v512, count));
#elif AXM_SIMD_AVX2
        return Simd<512, i64>(
            _mm256_slli_epi64(a.v256[0], count), _mm256_slli_epi64(a.v256[1], count));
#else
        return Simd<512, i64>(
            _mm_slli_epi64(a.v128[0], count), _mm_slli_epi64(a.v128[1], count),
            _mm_slli_epi64(a.v128[2], count), _mm_slli_epi64(a.v128[3], count));
#endif
    }
    template <>
    inline Simd<128, i64> shr(const Simd<128, i64> &a, const int count) {
        return Simd<128, i64>(_mm_srli_epi64(a.v128, count));
    }
    template <>
    inline Simd<256, i64> shr(const Simd<256, i64> &a, const int count) {
#if AXM_SIMD_AVX2
        return Simd<256, i64>(_mm256_srli_epi64(a.v256, count));
#else
        return Simd<256, i64>(_mm_srli_epi64(a.v128[0], count), _mm_srli_epi64(a.v128[1], count));
#endif
    }
    template <>
    inline Simd<512, i64> shr(const Simd<512, i64> &a, const int count) {
#if AXM_SIMD_AVX512F
        return Simd<512, i64>(_mm512_srli_epi64(a.v512, count));
#elif AXM_SIMD_AVX2
        return Simd<512, i64>(
            _mm256_srli_epi64(a.v256[0], count), _mm256_srli_epi64(a.v256[1], count));
#else
        return Simd<512, i64>(
            _mm_srli_epi64(a.v128[0], count), _mm_srli_epi64(a.v128[1], count),
            _mm_srli_epi64(a.v128[2], count), _mm_srli_epi64(a.v128[3], count));
#endif
    }
    template <>
    inline Simd<128, i64> sar(const Simd<128, i64> &a, const int count) {
#if AXM_SIMD_AVX512F
        return Simd<128, i64>(_mm_srai_epi64(a.v128, count));
#else
        return Simd<128, i64>(a.i[0] >> count, a.i[1] >> count);
#endif
    }
    template <>
    inline Simd<256, i64> sar(const Simd<256, i64> &a, const int count) {
#if AXM_SIMD_AVX512F
        return Simd<256, i64>(_mm256_srai_epi64(a.v256, count));
#else
        return Simd<256, i64>(a.i[0] >> count, a.i[1] >> count, a.i[2] >> count, a.i[3] >> count);
#endif
    }
    template <>
    inline Simd<512, i64> sar(const Simd<512, i64> &a, const int count) {
#if AXM_SIMD_AVX512F
        return Simd<512, i64>(_mm512_srai_epi64(a.v512, count));
#else
        return Simd<512, i64>(
            a.i[0] >> count, a.i[1] >> count, a.i[2] >> count, a.i[3] >> count, a.i[4] >> count,
            a.i[5] >> count, a.i[6] >> count, a.i[7] >> count);
#endif
    }

    template <>
    inline Simd<128, i64> mul(const Simd<128, i64> &a, const Simd<128, i64> &b) {
#if AXM_SIMD_AVX512DQ
        return Simd<128, i64>(_mm_mullo_epi64(a.v, b.v));
#else
        return Simd<128, i64>(a.i[0] * b.i[0], a.i[1] * b.i[1]);
#endif
    }
    template <>
    inline Simd<256, i64> mul(const Simd<256, i64> &a, const Simd<256, i64> &b) {
#if AXM_SIMD_AVX512DQ
        return Simd<256, i64>(_mm256_mullo_epi64(a.v, b.v));
#else
        return Simd<256, i64>(a.i[0] * b.i[0], a.i[1] * b.i[1], a.i[2] * b.i[2], a.i[3] * b.i[3]);
#endif
    }
    template <>
    inline Simd<512, i64> mul(const Simd<512, i64> &a, const Simd<512, i64> &b) {
#if AXM_SIMD_AVX512DQ
        return Simd<512, i64>(_mm512_mullo_epi64(a.v, b.v));
#else
        return Simd<512, i64>(
            a.i[0] * b.i[0], a.i[1] * b.i[1], a.i[2] * b.i[2], a.i[3] * b.i[3], a.i[4] * b.i[4],
            a.i[5] * b.i[5], a.i[6] * b.i[6], a.i[7] * b.i[7]);
#endif
    }

    template <>
    inline Simd<128, i64> cmpEq(const Simd<128, i64> &a, const Simd<128, i64> &b) {
        return Simd<128, i64>(_mm_cmpeq_epi64(a.v128, b.v128));
    }
    template <>
    inline Simd<256, i64> cmpEq(const Simd<256, i64> &a, const Simd<256, i64> &b) {
#if AXM_SIMD_AVX2
        return Simd<256, i64>(_mm256_cmpeq_epi64(a.v256, b.v256));
#else
        return Simd<256, i64>(
            _mm_cmpeq_epi64(a.v128[0], b.v128[0]), _mm_cmpeq_epi64(a.v128[1], b.v128[1]));
#endif
    }
    template <>
    inline Simd<512, i64> cmpEq(const Simd<512, i64> &a, const Simd<512, i64> &b) {
#if AXM_SIMD_AVX512F
        __mmask8 k = _mm512_cmpneq_epi64_mask(a.v512, b.v512);
        return Simd<512, i64>(_mm512_maskz_mov_epi64(k, _mm512_set1_epi64(~0)));
#elif AXM_SIMD_AVX2
        return Simd<512, i64>(
            _mm256_cmpeq_epi64(a.v256[0], b.v256[0]), _mm256_cmpeq_epi64(a.v256[1], b.v256[1]));
#else
        return Simd<512, i64>(
            _mm_cmpeq_epi64(a.v128[0], b.v128[0]), _mm_cmpeq_epi64(a.v128[1], b.v128[1]),
            _mm_cmpeq_epi64(a.v128[2], b.v128[2]), _mm_cmpeq_epi64(a.v128[3], b.v128[3]));
#endif
    }
    template <>
    inline Simd<128, i64> cmpNe(const Simd<128, i64> &a, const Simd<128, i64> &b) {
#if AXM_SIMD_AVX2
        return Simd<128, i64>(_mm_xor_si128(_mm_cmpeq_epi64(a.v128, b.v128), _mm_set1_epi32(~0)));
#else
        return Simd<128, i64>(_mm_xor_si128(_mm_cmpeq_epi64(a.v128, b.v128), _mm_set1_epi32(~0)));
#endif
    }
    template <>
    inline Simd<256, i64> cmpNe(const Simd<256, i64> &a, const Simd<256, i64> &b) {
#if AXM_SIMD_AVX2
        return Simd<256, i64>(
            _mm256_xor_si256(_mm256_cmpeq_epi64(a.v256, b.v256), _mm256_set1_epi32(~0)));
#else
        return Simd<256, i64>(
            _mm_xor_si128(_mm_cmpeq_epi64(a.v128[0], b.v128[0]), _mm_set1_epi32(~0)),
            _mm_xor_si128(_mm_cmpeq_epi64(a.v128[1], b.v128[1]), _mm_set1_epi32(~0)));
#endif
    }
    template <>
    inline Simd<512, i64> cmpNe(const Simd<512, i64> &a, const Simd<512, i64> &b) {
#if AXM_SIMD_AVX512F
        __mmask8 k = _mm512_cmpneq_epi64_mask(a.v512, b.v512);
        return Simd<512, i64>(_mm512_maskz_mov_epi64(k, _mm512_set1_epi64(~0)));
#elif AXM_SIMD_AVX2
        __m256i ones = _mm256_set1_epi32(~0);
        return Simd<512, i64>(
            _mm256_xor_si256(_mm256_cmpeq_epi64(a.v256[0], b.v256[0]), ones),
            _mm256_xor_si256(_mm256_cmpeq_epi64(a.v256[1], b.v256[1]), ones));
#else
        __m128i ones = _mm_set1_epi32(~0);
        return Simd<512, i64>(
            _mm_xor_si128(_mm_cmpeq_epi64(a.v128[0], b.v128[0]), ones),
            _mm_xor_si128(_mm_cmpeq_epi64(a.v128[1], b.v128[1]), ones),
            _mm_xor_si128(_mm_cmpeq_epi64(a.v128[2], b.v128[2]), ones),
            _mm_xor_si128(_mm_cmpeq_epi64(a.v128[3], b.v128[3]), ones));
#endif
    }
    template <>
    inline Simd<128, i64> cmpLt(const Simd<128, i64> &a, const Simd<128, i64> &b) {
#if AXM_SIMD_SSE42
        return Simd<128, i64>(_mm_cmpgt_epi64(b.v128, a.v128));
#elif AXM_SIMD_AVX2
        return Simd<128, i64>(_mm256_castsi256_si128(
            _mm256_cmpgt_epi64(_mm256_castsi128_si256(b.v), _mm256_castsi128_si256(a.v))));
#else
        return Simd<128, i64>(a.i[0] < b.i[0] ? ~0 : 0, a.i[1] < b.i[1] ? ~0 : 0);
#endif
    }
    template <>
    inline Simd<256, i64> cmpLt(const Simd<256, i64> &a, const Simd<256, i64> &b) {
#if AXM_SIMD_AVX2
        return Simd<256, i64>(_mm256_cmpgt_epi64(b.v256, a.v256));
#elif AXM_SIMD_SSE42
        return Simd<256, i64>(
            _mm_cmpgt_epi64(b.v128[0], a.v128[0]), _mm_cmpgt_epi64(b.v128[1], a.v128[1]));
#else
        return Simd<256, i64>(
            a.i[0] < b.i[0] ? ~0 : 0, a.i[1] < b.i[1] ? ~0 : 0, a.i[2] < b.i[2] ? ~0 : 0,
            a.i[3] < b.i[3] ? ~0 : 0);
#endif
    }
    template <>
    inline Simd<512, i64> cmpLt(const Simd<512, i64> &a, const Simd<512, i64> &b) {
#if AXM_SIMD_AVX512F
        __mmask8 k = _mm512_cmpgt_epi64_mask(b.v512, a.v512);
        return Simd<512, i64>(_mm512_maskz_mov_epi64(k, _mm512_set1_epi64(~0)));
#elif AXM_SIMD_AVX2
        return Simd<512, i64>(
            _mm256_cmpgt_epi64(b.v256[0], a.v256[0]), _mm256_cmpgt_epi64(b.v256[1], a.v256[1]));
#elif AXM_SIMD_SSE42
        return Simd<512, i64>(
            _mm_cmpgt_epi64(b.v128[0], a.v128[0]), _mm_cmpgt_epi64(b.v128[1], a.v128[1]),
            _mm_cmpgt_epi64(b.v128[2], a.v128[2]), _mm_cmpgt_epi64(b.v128[3], a.v128[3]));
#else
        return Simd<512, i64>(
            a.i[0] < b.i[0] ? ~0 : 0, a.i[1] < b.i[1] ? ~0 : 0, a.i[2] < b.i[2] ? ~0 : 0,
            a.i[3] < b.i[3] ? ~0 : 0, a.i[4] < b.i[4] ? ~0 : 0, a.i[5] < b.i[5] ? ~0 : 0,
            a.i[6] < b.i[6] ? ~0 : 0, a.i[7] < b.i[7] ? ~0 : 0);
#endif
    }
    template <>
    inline Simd<128, i64> cmpLe(const Simd<128, i64> &a, const Simd<128, i64> &b) {
#if AXM_SIMD_SSE42
        return Simd<128, i64>(_mm_xor_si128(_mm_cmpgt_epi64(a.v128, b.v128), _mm_set1_epi32(~0)));
#elif AXM_SIMD_AVX2
        return Simd<128, i64>(_mm256_castsi256_si128(_mm256_xor_si256(
            _mm256_cmpgt_epi64(_mm256_castsi128_si256(a.v), _mm256_castsi128_si256(b.v)),
            _mm256_set1_epi32(~0))));
#else
        return Simd<128, i64>(a.i[0] <= b.i[0] ? ~0 : 0, a.i[1] <= b.i[1] ? ~0 : 0);
#endif
    }
    template <>
    inline Simd<256, i64> cmpLe(const Simd<256, i64> &a, const Simd<256, i64> &b) {
#if AXM_SIMD_AVX2
        return Simd<256, i64>(
            _mm256_xor_si256(_mm256_cmpgt_epi64(a.v256, b.v256), _mm256_set1_epi32(~0)));
#elif AXM_SIMD_SSE42
        __m128i ones = _mm_set1_epi32(~0);
        return Simd<256, i64>(
            _mm_xor_si128(_mm_cmpgt_epi64(a.v128[0], b.v128[0]), ones),
            _mm_xor_si128(_mm_cmpgt_epi64(a.v128[1], b.v128[1]), ones));
#else
        return Simd<256, i64>(
            a.i[0] <= b.i[0] ? ~0 : 0, a.i[1] <= b.i[1] ? ~0 : 0, a.i[2] <= b.i[2] ? ~0 : 0,
            a.i[3] <= b.i[3] ? ~0 : 0);
#endif
    }
    template <>
    inline Simd<512, i64> cmpLe(const Simd<512, i64> &a, const Simd<512, i64> &b) {
#if AXM_SIMD_AVX512F
        __mmask8 k = _mm512_cmpgt_epi64_mask(a.v512, b.v512);
        return Simd<512, i64>(_mm512_xor_si512(
            _mm512_maskz_mov_epi64(k, _mm512_set1_epi64(~0)), _mm512_set1_epi64(~0)));
#elif AXM_SIMD_AVX2
        __m256i ones = _mm256_set1_epi32(~0);
        return Simd<512, i64>(
            _mm256_xor_si256(_mm256_cmpgt_epi64(a.v256[0], b.v256[0]), ones),
            _mm256_xor_si256(_mm256_cmpgt_epi64(a.v256[1], b.v256[1]), ones));
#elif AXM_SIMD_SSE42
        __m128i ones = _mm_set1_epi32(~0);
        return Simd<512, i64>(
            _mm_xor_si128(_mm_cmpgt_epi64(a.v128[0], b.v128[0]), ones),
            _mm_xor_si128(_mm_cmpgt_epi64(a.v128[1], b.v128[1]), ones),
            _mm_xor_si128(_mm_cmpgt_epi64(a.v128[2], b.v128[2]), ones),
            _mm_xor_si128(_mm_cmpgt_epi64(a.v128[3], b.v128[3]), ones));
#else
        return Simd<512, i64>(
            a.i[0] <= b.i[0] ? ~0 : 0, a.i[1] <= b.i[1] ? ~0 : 0, a.i[2] <= b.i[2] ? ~0 : 0,
            a.i[3] <= b.i[3] ? ~0 : 0, a.i[4] <= b.i[4] ? ~0 : 0, a.i[5] <= b.i[5] ? ~0 : 0,
            a.i[6] <= b.i[6] ? ~0 : 0, a.i[7] <= b.i[7] ? ~0 : 0);
#endif
    }
    template <>
    inline Simd<128, i64> cmpGt(const Simd<128, i64> &a, const Simd<128, i64> &b) {
#if AXM_SIMD_SSE42
        return Simd<128, i64>(_mm_cmpgt_epi64(a.v128, b.v128));
#elif AXM_SIMD_AVX2
        return Simd<128, i64>(_mm256_castsi256_si128(
            _mm256_cmpgt_epi64(_mm256_castsi128_si256(a.v), _mm256_castsi128_si256(b.v))));
#else
        return Simd<128, i64>(a.i[0] > b.i[0] ? ~0 : 0, a.i[1] > b.i[1] ? ~0 : 0);
#endif
    }
    template <>
    inline Simd<256, i64> cmpGt(const Simd<256, i64> &a, const Simd<256, i64> &b) {
#if AXM_SIMD_AVX2
        return Simd<256, i64>(_mm256_cmpgt_epi64(a.v256, b.v256));
#elif AXM_SIMD_SSE42
        return Simd<256, i64>(
            _mm_cmpgt_epi64(a.v128[0], b.v128[0]), _mm_cmpgt_epi64(a.v128[1], b.v128[1]));
#else
        return Simd<256, i64>(
            a.i[0] > b.i[0] ? ~0 : 0, a.i[1] > b.i[1] ? ~0 : 0, a.i[2] > b.i[2] ? ~0 : 0,
            a.i[3] > b.i[3] ? ~0 : 0);
#endif
    }
    template <>
    inline Simd<512, i64> cmpGt(const Simd<512, i64> &a, const Simd<512, i64> &b) {
#if AXM_SIMD_AVX512F
        __mmask8 k = _mm512_cmpgt_epi64_mask(a.v512, b.v512);
        return Simd<512, i64>(_mm512_maskz_mov_epi64(k, _mm512_set1_epi64(~0)));
#elif AXM_SIMD_AVX2
        return Simd<512, i64>(
            _mm256_cmpgt_epi64(a.v256[0], b.v256[0]), _mm256_cmpgt_epi64(a.v256[1], b.v256[1]));
#elif AXM_SIMD_SSE42
        return Simd<512, i64>(
            _mm_cmpgt_epi64(a.v128[0], b.v128[0]), _mm_cmpgt_epi64(a.v128[1], b.v128[1]),
            _mm_cmpgt_epi64(a.v128[2], b.v128[2]), _mm_cmpgt_epi64(a.v128[3], b.v128[3]));
#else
        return Simd<512, i64>(
            a.i[0] > b.i[0] ? ~0 : 0, a.i[1] > b.i[1] ? ~0 : 0, a.i[2] > b.i[2] ? ~0 : 0,
            a.i[3] > b.i[3] ? ~0 : 0, a.i[4] > b.i[4] ? ~0 : 0, a.i[5] > b.i[5] ? ~0 : 0,
            a.i[6] > b.i[6] ? ~0 : 0, a.i[7] > b.i[7] ? ~0 : 0);
#endif
    }
    template <>
    inline Simd<128, i64> cmpGe(const Simd<128, i64> &a, const Simd<128, i64> &b) {
#if AXM_SIMD_SSE42
        return Simd<128, i64>(_mm_xor_si128(_mm_cmpgt_epi64(b.v128, a.v128), _mm_set1_epi32(~0)));
#elif AXM_SIMD_AVX2
        return Simd<128, i64>(_mm256_castsi256_si128(_mm256_xor_si256(
            _mm256_cmpgt_epi64(_mm256_castsi128_si256(b.v), _mm256_castsi128_si256(a.v)),
            _mm256_set1_epi32(~0))));
#else
        return Simd<128, i64>(a.i[0] >= b.i[0] ? ~0 : 0, a.i[1] >= b.i[1] ? ~0 : 0);
#endif
    }
    template <>
    inline Simd<256, i64> cmpGe(const Simd<256, i64> &a, const Simd<256, i64> &b) {
#if AXM_SIMD_AVX2
        return Simd<256, i64>(
            _mm256_xor_si256(_mm256_cmpgt_epi64(b.v256, a.v256), _mm256_set1_epi32(~0)));
#elif AXM_SIMD_SSE42
        __m128i ones = _mm_set1_epi32(~0);
        return Simd<256, i64>(
            _mm_xor_si128(_mm_cmpgt_epi64(b.v128[0], a.v128[0]), ones),
            _mm_xor_si128(_mm_cmpgt_epi64(b.v128[1], a.v128[1]), ones));
#else
        return Simd<256, i64>(
            a.i[0] >= b.i[0] ? ~0 : 0, a.i[1] >= b.i[1] ? ~0 : 0, a.i[2] >= b.i[2] ? ~0 : 0,
            a.i[3] >= b.i[3] ? ~0 : 0);
#endif
    }
    template <>
    inline Simd<512, i64> cmpGe(const Simd<512, i64> &a, const Simd<512, i64> &b) {
#if AXM_SIMD_AVX512F
        __mmask8 k = _mm512_cmpgt_epi64_mask(b.v512, a.v512);
        return Simd<512, i64>(_mm512_xor_si512(
            _mm512_maskz_mov_epi64(k, _mm512_set1_epi64(~0)), _mm512_set1_epi64(~0)));
#elif AXM_SIMD_AVX2
        __m256i ones = _mm256_set1_epi32(~0);
        return Simd<512, i64>(
            _mm256_xor_si256(_mm256_cmpgt_epi64(b.v256[0], a.v256[0]), ones),
            _mm256_xor_si256(_mm256_cmpgt_epi64(b.v256[1], a.v256[1]), ones));
#elif AXM_SIMD_SSE42
        __m128i ones = _mm_set1_epi32(~0);
        return Simd<512, i64>(
            _mm_xor_si128(_mm_cmpgt_epi64(b.v128[0], a.v128[0]), ones),
            _mm_xor_si128(_mm_cmpgt_epi64(b.v128[1], a.v128[1]), ones),
            _mm_xor_si128(_mm_cmpgt_epi64(b.v128[2], a.v128[2]), ones),
            _mm_xor_si128(_mm_cmpgt_epi64(b.v128[3], a.v128[3]), ones));
#else
        return Simd<512, i64>(
            a.i[0] >= b.i[0] ? ~0 : 0, a.i[1] >= b.i[1] ? ~0 : 0, a.i[2] >= b.i[2] ? ~0 : 0,
            a.i[3] >= b.i[3] ? ~0 : 0, a.i[4] >= b.i[4] ? ~0 : 0, a.i[5] >= b.i[5] ? ~0 : 0,
            a.i[6] >= b.i[6] ? ~0 : 0, a.i[7] >= b.i[7] ? ~0 : 0);
#endif
    }

    template <>
    inline u32 movemask(const Simd<128, i64> &a) {
        return (u32)_mm_movemask_epi8(a.v128);
    }
    template <>
    inline u32 movemask(const Simd<256, i64> &a) {
#if AXM_SIMD_AVX2
        return (u32)_mm256_movemask_epi8(a.v256);
#else
        return (u32)_mm256_movemask_ps(_mm256_castsi256_ps(a.v256));
#endif
    }
    template <>
    inline u64 movemask(const Simd<512, i64> &a) {
#if AXM_SIMD_AVX512BW
        return (u64)_mm512_movepi8_mask(a.v);
#elif AXM_SIMD_AVX2
        return (u64)_mm256_movemask_epi8(a.v256[0]) | ((u64)_mm256_movemask_epi8(a.v256[1]) << 32);
#else
        return (u64)_mm256_movemask_ps(_mm256_castsi256_ps(a.v256[0]))
             | ((u64)_mm256_movemask_ps(_mm256_castsi256_ps(a.v256[1])) << 8);
#endif
    }
}}

#endif
