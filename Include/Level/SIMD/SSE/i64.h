#ifndef AXM_LVL_SIMD_SSE_I64_H
#define AXM_LVL_SIMD_SSE_I64_H

#include "../../System/Simd.h" // IWYU pragma: keep
#include "../../Types.h"
#include "../Simd.h"

#if AXM_SIMD_SSE41
#    include <smmintrin.h>
#endif
#if AXM_SIMD_SSSE3
#    include <tmmintrin.h>
#endif
#if AXM_SIMD_SSE2
#    include <emmintrin.h>
#endif
#include <xmmintrin.h>

namespace Level { namespace SIMD {
    template <>
    union Simd<128, i64> {
#if AXM_SIMD_SSE2
        __m128i v128;
#else
        __m128 v128;
#endif
        i64 i[2];
        Simd() {}
#if AXM_SIMD_SSE2
        Simd(__m128i a0) { v128 = a0; }
#else
        Simd(__m128 a0) { v128 = a0; }
#endif
        Simd(i64 a0, i64 a1) {
            i[0] = a0;
            i[1] = a1;
        }
    };
    template <>
    union Simd<256, i64> {
#if AXM_SIMD_SSE2
        __m128i v128[2];
#else
        __m128 v128[2];
#endif
        i64 i[4];
        Simd() {}
#if AXM_SIMD_SSE2
        Simd(__m128i a0, __m128i a1) {
            v128[0] = a0;
            v128[1] = a1;
        }
#else
        Simd(__m128 a0, __m128 a1) {
            v128[0] = a0;
            v128[1] = a1;
        }
#endif
        Simd(i64 a0, i64 a1, i64 a2, i64 a3) {
            i[0] = a0;
            i[1] = a1;
            i[2] = a2;
            i[3] = a3;
        }
    };
    template <>
    union Simd<512, i64> {
#if AXM_SIMD_SSE2
        __m128i v128[4];
#else
        __m128 v128[4];
#endif
        i64 i[8];
        Simd() {}
#if AXM_SIMD_SSE2
        Simd(__m128i a0, __m128i a1, __m128i a2, __m128i a3) {
            v128[0] = a0;
            v128[1] = a1;
            v128[2] = a2;
            v128[3] = a3;
        }
#else
        Simd(__m128 a0, __m128 a1, __m128 a2, __m128 a3) {
            v128[0] = a0;
            v128[1] = a1;
            v128[2] = a2;
            v128[3] = a3;
        }
#endif
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
#if AXM_SIMD_SSE2
        return Simd<128, i64>(_mm_loadu_si128((__m128i*)ptr));
#else
        return Simd<128, i64>(_mm_loadu_ps((f32*)ptr));
#endif
    }
    template <>
    inline Simd<256, i64> load(const i64* ptr) {
#if AXM_SIMD_SSE2
        return Simd<256, i64>(
            _mm_loadu_si128((__m128i*)(ptr)), _mm_loadu_si128((__m128i*)(ptr + 2)));
#else
        return Simd<256, i64>(_mm_loadu_ps((f32*)(ptr)), _mm_loadu_ps((f32*)(ptr + 2)));
#endif
    }
    template <>
    inline Simd<512, i64> load(const i64* ptr) {
#if AXM_SIMD_SSE2
        return Simd<512, i64>(
            _mm_loadu_si128((__m128i*)(ptr)), _mm_loadu_si128((__m128i*)(ptr + 2)),
            _mm_loadu_si128((__m128i*)(ptr + 4)), _mm_loadu_si128((__m128i*)(ptr + 6)));
#else
        return Simd<512, i64>(
            _mm_loadu_ps((f32*)(ptr)), _mm_loadu_ps((f32*)(ptr + 2)), _mm_loadu_ps((f32*)(ptr + 4)),
            _mm_loadu_ps((f32*)(ptr + 6)));
#endif
    }
    template <>
    inline void store(i64* ptr, const Simd<128, i64> &simd) {
#if AXM_SIMD_SSE2
        _mm_storeu_si128((__m128i*)ptr, simd.v128);
#else
        _mm_storeu_ps((f32*)ptr, simd.v128);
#endif
    }
    template <>
    inline void store(i64* ptr, const Simd<256, i64> &simd) {
#if AXM_SIMD_SSE2
        _mm_storeu_si128((__m128i*)(ptr), simd.v128[0]);
        _mm_storeu_si128((__m128i*)(ptr + 2), simd.v128[1]);
#else
        _mm_storeu_ps((f32*)(ptr), simd.v128[0]);
        _mm_storeu_ps((f32*)(ptr + 2), simd.v128[1]);
#endif
    }
    template <>
    inline void store(i64* ptr, const Simd<512, i64> &simd) {
#if AXM_SIMD_SSE2
        _mm_storeu_si128((__m128i*)(ptr), simd.v128[0]);
        _mm_storeu_si128((__m128i*)(ptr + 2), simd.v128[1]);
        _mm_storeu_si128((__m128i*)(ptr + 4), simd.v128[2]);
        _mm_storeu_si128((__m128i*)(ptr + 6), simd.v128[3]);
#else
        _mm_storeu_ps((f32*)(ptr), simd.v128[0]);
        _mm_storeu_ps((f32*)(ptr + 2), simd.v128[1]);
        _mm_storeu_ps((f32*)(ptr + 4), simd.v128[2]);
        _mm_storeu_ps((f32*)(ptr + 6), simd.v128[3]);
#endif
    }
    template <>
    inline Simd<128, i64> set1(const i64 value) {
#if AXM_SIMD_SSE2
        return Simd<128, i64>(_mm_set1_epi64x(value));
#else
        return Simd<128, i64>(
            _mm_set_ps((f32)(value >> 32), (f32)value, (f32)(value >> 32), (f32)value));
#endif
    }
    template <>
    inline Simd<256, i64> set1(const i64 value) {
#if AXM_SIMD_SSE2
        __m128i v = _mm_set1_epi64x(value);
        return Simd<256, i64>(v, v);
#else
        return Simd<256, i64>(
            _mm_set_ps((f32)(value >> 32), (f32)value, (f32)(value >> 32), (f32)value),
            _mm_set_ps((f32)(value >> 32), (f32)value, (f32)(value >> 32), (f32)value));
#endif
    }
    template <>
    inline Simd<512, i64> set1(const i64 value) {
#if AXM_SIMD_SSE2
        __m128i v = _mm_set1_epi64x(value);
        return Simd<512, i64>(v, v, v, v);
#else
        __m128 v = _mm_set_ps((f32)(value >> 32), (f32)value, (f32)(value >> 32), (f32)value);
        return Simd<512, i64>(v, v, v, v);
#endif
    }
    template <>
    inline Simd<128, i64> set(const i64 a0, const i64 a1) {
#if AXM_SIMD_SSE2
        return Simd<128, i64>(_mm_set_epi64x(a1, a0));
#else
        return Simd<128, i64>(_mm_set_ps((f32)(a1 >> 32), (f32)a1, (f32)(a0 >> 32), (f32)a0));
#endif
    }
    template <>
    inline Simd<256, i64> set(const i64 a0, const i64 a1, const i64 a2, const i64 a3) {
#if AXM_SIMD_SSE2
        return Simd<256, i64>(_mm_set_epi64x(a1, a0), _mm_set_epi64x(a3, a2));
#else
        return Simd<256, i64>(
            _mm_set_ps((f32)(a1 >> 32), (f32)a1, (f32)(a0 >> 32), (f32)a0),
            _mm_set_ps((f32)(a3 >> 32), (f32)a3, (f32)(a2 >> 32), (f32)a2));
#endif
    }
    template <>
    inline Simd<512, i64>
        set(const i64 a0, const i64 a1, const i64 a2, const i64 a3, const i64 a4, const i64 a5,
            const i64 a6, const i64 a7) {
#if AXM_SIMD_SSE2
        return Simd<512, i64>(
            _mm_set_epi64x(a1, a0), _mm_set_epi64x(a3, a2), _mm_set_epi64x(a5, a4),
            _mm_set_epi64x(a7, a6));
#else
        return Simd<512, i64>(
            _mm_set_ps((f32)(a1 >> 32), (f32)a1, (f32)(a0 >> 32), (f32)a0),
            _mm_set_ps((f32)(a3 >> 32), (f32)a3, (f32)(a2 >> 32), (f32)a2),
            _mm_set_ps((f32)(a5 >> 32), (f32)a5, (f32)(a4 >> 32), (f32)a4),
            _mm_set_ps((f32)(a7 >> 32), (f32)a7, (f32)(a6 >> 32), (f32)a6));
#endif
    }

    template <>
    inline Simd<128, i64> add(const Simd<128, i64> &a, const Simd<128, i64> &b) {
#if AXM_SIMD_SSE2
        return Simd<128, i64>(_mm_add_epi64(a.v128, b.v128));
#else
        return Simd<128, i64>(a.i[0] + b.i[0], a.i[1] + b.i[1]);
#endif
    }
    template <>
    inline Simd<256, i64> add(const Simd<256, i64> &a, const Simd<256, i64> &b) {
#if AXM_SIMD_SSE2
        return Simd<256, i64>(
            _mm_add_epi64(a.v128[0], b.v128[0]), _mm_add_epi64(a.v128[1], b.v128[1]));
#else
        return Simd<256, i64>(a.i[0] + b.i[0], a.i[1] + b.i[1], a.i[2] + b.i[2], a.i[3] + b.i[3]);
#endif
    }
    template <>
    inline Simd<512, i64> add(const Simd<512, i64> &a, const Simd<512, i64> &b) {
#if AXM_SIMD_SSE2
        return Simd<512, i64>(
            _mm_add_epi64(a.v128[0], b.v128[0]), _mm_add_epi64(a.v128[1], b.v128[1]),
            _mm_add_epi64(a.v128[2], b.v128[2]), _mm_add_epi64(a.v128[3], b.v128[3]));
#else
        return Simd<512, i64>(
            a.i[0] + b.i[0], a.i[1] + b.i[1], a.i[2] + b.i[2], a.i[3] + b.i[3], a.i[4] + b.i[4],
            a.i[5] + b.i[5], a.i[6] + b.i[6], a.i[7] + b.i[7]);
#endif
    }
    template <>
    inline Simd<128, i64> sub(const Simd<128, i64> &a, const Simd<128, i64> &b) {
#if AXM_SIMD_SSE2
        return Simd<128, i64>(_mm_sub_epi64(a.v128, b.v128));
#else
        return Simd<128, i64>(a.i[0] - b.i[0], a.i[1] - b.i[1]);
#endif
    }
    template <>
    inline Simd<256, i64> sub(const Simd<256, i64> &a, const Simd<256, i64> &b) {
#if AXM_SIMD_SSE2
        return Simd<256, i64>(
            _mm_sub_epi64(a.v128[0], b.v128[0]), _mm_sub_epi64(a.v128[1], b.v128[1]));
#else
        return Simd<256, i64>(a.i[0] - b.i[0], a.i[1] - b.i[1], a.i[2] - b.i[2], a.i[3] - b.i[3]);
#endif
    }
    template <>
    inline Simd<512, i64> sub(const Simd<512, i64> &a, const Simd<512, i64> &b) {
#if AXM_SIMD_SSE2
        return Simd<512, i64>(
            _mm_sub_epi64(a.v128[0], b.v128[0]), _mm_sub_epi64(a.v128[1], b.v128[1]),
            _mm_sub_epi64(a.v128[2], b.v128[2]), _mm_sub_epi64(a.v128[3], b.v128[3]));
#else
        return Simd<512, i64>(
            a.i[0] - b.i[0], a.i[1] - b.i[1], a.i[2] - b.i[2], a.i[3] - b.i[3], a.i[4] - b.i[4],
            a.i[5] - b.i[5], a.i[6] - b.i[6], a.i[7] - b.i[7]);
#endif
    }
    template <>
    inline Simd<128, i64> abs(const Simd<128, i64> &a) {
#if AXM_SIMD_SSE2
        __m128i sign = _mm_srai_epi32(a.v128, 31);
        sign         = _mm_shuffle_epi32(sign, _MM_SHUFFLE(3, 3, 1, 1));
        return Simd<128, i64>(_mm_sub_epi64(_mm_xor_si128(a.v128, sign), sign));
#else
        return Simd<128, i64>(a.i[0] < 0 ? -a.i[0] : a.i[0], a.i[1] < 0 ? -a.i[1] : a.i[1]);
#endif
    }
    template <>
    inline Simd<256, i64> abs(const Simd<256, i64> &a) {
#if AXM_SIMD_SSE2
        __m128i sign0 = _mm_srai_epi32(a.v128[0], 31);
        __m128i sign1 = _mm_srai_epi32(a.v128[1], 31);
        sign0         = _mm_shuffle_epi32(sign0, _MM_SHUFFLE(3, 3, 1, 1));
        sign1         = _mm_shuffle_epi32(sign1, _MM_SHUFFLE(3, 3, 1, 1));
        return Simd<256, i64>(
            _mm_sub_epi64(_mm_xor_si128(a.v128[0], sign0), sign0),
            _mm_sub_epi64(_mm_xor_si128(a.v128[1], sign1), sign1));
#else
        return Simd<256, i64>(
            a.i[0] < 0 ? -a.i[0] : a.i[0], a.i[1] < 0 ? -a.i[1] : a.i[1],
            a.i[2] < 0 ? -a.i[2] : a.i[2], a.i[3] < 0 ? -a.i[3] : a.i[3]);
#endif
    }
    template <>
    inline Simd<512, i64> abs(const Simd<512, i64> &a) {
#if AXM_SIMD_SSE2
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
#else
        return Simd<512, i64>(
            a.i[0] < 0 ? -a.i[0] : a.i[0], a.i[1] < 0 ? -a.i[1] : a.i[1],
            a.i[2] < 0 ? -a.i[2] : a.i[2], a.i[3] < 0 ? -a.i[3] : a.i[3],
            a.i[4] < 0 ? -a.i[4] : a.i[4], a.i[5] < 0 ? -a.i[5] : a.i[5],
            a.i[6] < 0 ? -a.i[6] : a.i[6], a.i[7] < 0 ? -a.i[7] : a.i[7]);
#endif
    }
    template <>
    inline Simd<128, i64> neg(const Simd<128, i64> &a) {
#if AXM_SIMD_SSE2
        return Simd<128, i64>(_mm_sub_epi64(_mm_setzero_si128(), a.v128));
#else
        return Simd<128, i64>(-a.i[0], -a.i[1]);
#endif
    }
    template <>
    inline Simd<256, i64> neg(const Simd<256, i64> &a) {
#if AXM_SIMD_SSE2
        return Simd<256, i64>(
            _mm_sub_epi64(_mm_setzero_si128(), a.v128[0]),
            _mm_sub_epi64(_mm_setzero_si128(), a.v128[1]));
#else
        return Simd<256, i64>(-a.i[0], -a.i[1], -a.i[2], -a.i[3]);
#endif
    }
    template <>
    inline Simd<512, i64> neg(const Simd<512, i64> &a) {
#if AXM_SIMD_SSE2
        return Simd<512, i64>(
            _mm_sub_epi64(_mm_setzero_si128(), a.v128[0]),
            _mm_sub_epi64(_mm_setzero_si128(), a.v128[1]),
            _mm_sub_epi64(_mm_setzero_si128(), a.v128[2]),
            _mm_sub_epi64(_mm_setzero_si128(), a.v128[3]));
#else
        return Simd<512, i64>(
            -a.i[0], -a.i[1], -a.i[2], -a.i[3], -a.i[4], -a.i[5], -a.i[6], -a.i[7]);
#endif
    }
    template <>
    inline Simd<128, i64> min(const Simd<128, i64> &a, const Simd<128, i64> &b) {
#if AXM_SIMD_SSE42
        __m128i mask = _mm_cmpgt_epi64(a.v128, b.v128);
        return Simd<128, i64>(
            _mm_or_si128(_mm_andnot_si128(mask, a.v128), _mm_and_si128(mask, b.v128)));
#else
        return Simd<128, i64>(a.i[0] < b.i[0] ? a.i[0] : b.i[0], a.i[1] < b.i[1] ? a.i[1] : b.i[1]);
#endif
    }
    template <>
    inline Simd<256, i64> min(const Simd<256, i64> &a, const Simd<256, i64> &b) {
#if AXM_SIMD_SSE42
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
#if AXM_SIMD_SSE42
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
#if AXM_SIMD_SSE42
        __m128i mask = _mm_cmpgt_epi64(a.v128, b.v128);
        return Simd<128, i64>(
            _mm_or_si128(_mm_and_si128(mask, a.v128), _mm_andnot_si128(mask, b.v128)));
#else
        return Simd<128, i64>(a.i[0] > b.i[0] ? a.i[0] : b.i[0], a.i[1] > b.i[1] ? a.i[1] : b.i[1]);
#endif
    }
    template <>
    inline Simd<256, i64> max(const Simd<256, i64> &a, const Simd<256, i64> &b) {
#if AXM_SIMD_SSE42
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
#if AXM_SIMD_SSE42
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
#if AXM_SIMD_SSE2
        return Simd<128, i64>(_mm_and_si128(a.v128, b.v128));
#else
        return Simd<128, i64>(_mm_and_ps(a.v128, b.v128));
#endif
    }
    template <>
    inline Simd<256, i64> land(const Simd<256, i64> &a, const Simd<256, i64> &b) {
#if AXM_SIMD_SSE2
        return Simd<256, i64>(
            _mm_and_si128(a.v128[0], b.v128[0]), _mm_and_si128(a.v128[1], b.v128[1]));
#else
        return Simd<256, i64>(_mm_and_ps(a.v128[0], b.v128[0]), _mm_and_ps(a.v128[1], b.v128[1]));
#endif
    }
    template <>
    inline Simd<512, i64> land(const Simd<512, i64> &a, const Simd<512, i64> &b) {
#if AXM_SIMD_SSE2
        return Simd<512, i64>(
            _mm_and_si128(a.v128[0], b.v128[0]), _mm_and_si128(a.v128[1], b.v128[1]),
            _mm_and_si128(a.v128[2], b.v128[2]), _mm_and_si128(a.v128[3], b.v128[3]));
#else
        return Simd<512, i64>(
            _mm_and_ps(a.v128[0], b.v128[0]), _mm_and_ps(a.v128[1], b.v128[1]),
            _mm_and_ps(a.v128[2], b.v128[2]), _mm_and_ps(a.v128[3], b.v128[3]));
#endif
    }
    template <>
    inline Simd<128, i64> lor(const Simd<128, i64> &a, const Simd<128, i64> &b) {
#if AXM_SIMD_SSE2
        return Simd<128, i64>(_mm_or_si128(a.v128, b.v128));
#else
        return Simd<128, i64>(_mm_or_ps(a.v128, b.v128));
#endif
    }
    template <>
    inline Simd<256, i64> lor(const Simd<256, i64> &a, const Simd<256, i64> &b) {
#if AXM_SIMD_SSE2
        return Simd<256, i64>(
            _mm_or_si128(a.v128[0], b.v128[0]), _mm_or_si128(a.v128[1], b.v128[1]));
#else
        return Simd<256, i64>(_mm_or_ps(a.v128[0], b.v128[0]), _mm_or_ps(a.v128[1], b.v128[1]));
#endif
    }
    template <>
    inline Simd<512, i64> lor(const Simd<512, i64> &a, const Simd<512, i64> &b) {
#if AXM_SIMD_SSE2
        return Simd<512, i64>(
            _mm_or_si128(a.v128[0], b.v128[0]), _mm_or_si128(a.v128[1], b.v128[1]),
            _mm_or_si128(a.v128[2], b.v128[2]), _mm_or_si128(a.v128[3], b.v128[3]));
#else
        return Simd<512, i64>(
            _mm_or_ps(a.v128[0], b.v128[0]), _mm_or_ps(a.v128[1], b.v128[1]),
            _mm_or_ps(a.v128[2], b.v128[2]), _mm_or_ps(a.v128[3], b.v128[3]));
#endif
    }
    template <>
    inline Simd<128, i64> lxor(const Simd<128, i64> &a, const Simd<128, i64> &b) {
#if AXM_SIMD_SSE2
        return Simd<128, i64>(_mm_xor_si128(a.v128, b.v128));
#else
        return Simd<128, i64>(_mm_xor_ps(a.v128, b.v128));
#endif
    }
    template <>
    inline Simd<256, i64> lxor(const Simd<256, i64> &a, const Simd<256, i64> &b) {
#if AXM_SIMD_SSE2
        return Simd<256, i64>(
            _mm_xor_si128(a.v128[0], b.v128[0]), _mm_xor_si128(a.v128[1], b.v128[1]));
#else
        return Simd<256, i64>(_mm_xor_ps(a.v128[0], b.v128[0]), _mm_xor_ps(a.v128[1], b.v128[1]));
#endif
    }
    template <>
    inline Simd<512, i64> lxor(const Simd<512, i64> &a, const Simd<512, i64> &b) {
#if AXM_SIMD_SSE2
        return Simd<512, i64>(
            _mm_xor_si128(a.v128[0], b.v128[0]), _mm_xor_si128(a.v128[1], b.v128[1]),
            _mm_xor_si128(a.v128[2], b.v128[2]), _mm_xor_si128(a.v128[3], b.v128[3]));
#else
        return Simd<512, i64>(
            _mm_xor_ps(a.v128[0], b.v128[0]), _mm_xor_ps(a.v128[1], b.v128[1]),
            _mm_xor_ps(a.v128[2], b.v128[2]), _mm_xor_ps(a.v128[3], b.v128[3]));
#endif
    }
    template <>
    inline Simd<128, i64> lnot(const Simd<128, i64> &a) {
#if AXM_SIMD_SSE2
        return Simd<128, i64>(_mm_xor_si128(a.v128, _mm_set1_epi32(~0)));
#else
        return Simd<128, i64>(_mm_xor_ps(a.v128, _mm_set1_ps(~0)));
#endif
    }
    template <>
    inline Simd<256, i64> lnot(const Simd<256, i64> &a) {
#if AXM_SIMD_SSE2
        __m128i ones = _mm_set1_epi32(~0);
        return Simd<256, i64>(_mm_xor_si128(a.v128[0], ones), _mm_xor_si128(a.v128[1], ones));
#else
        __m128 ones = _mm_set_ps1(~0);
        return Simd<256, i64>(_mm_xor_ps(a.v128[0], ones), _mm_xor_ps(a.v128[1], ones));
#endif
    }
    template <>
    inline Simd<512, i64> lnot(const Simd<512, i64> &a) {
#if AXM_SIMD_SSE2
        __m128i ones = _mm_set1_epi32(~0);
        return Simd<512, i64>(
            _mm_xor_si128(a.v128[0], ones), _mm_xor_si128(a.v128[1], ones),
            _mm_xor_si128(a.v128[2], ones), _mm_xor_si128(a.v128[3], ones));
#else
        __m128 ones = _mm_set_ps1(~0);
        return Simd<512, i64>(
            _mm_xor_ps(a.v128[0], ones), _mm_xor_ps(a.v128[1], ones), _mm_xor_ps(a.v128[2], ones),
            _mm_xor_ps(a.v128[3], ones));
#endif
    }
    template <>
    inline Simd<128, i64> landnot(const Simd<128, i64> &a, const Simd<128, i64> &b) {
#if AXM_SIMD_SSE2
        return Simd<128, i64>(_mm_andnot_si128(b.v128, a.v128));
#else
        return Simd<128, i64>(_mm_andnot_ps(b.v128, a.v128));
#endif
    }
    template <>
    inline Simd<256, i64> landnot(const Simd<256, i64> &a, const Simd<256, i64> &b) {
#if AXM_SIMD_SSE2
        return Simd<256, i64>(
            _mm_andnot_si128(b.v128[0], a.v128[0]), _mm_andnot_si128(b.v128[1], a.v128[1]));
#else
        return Simd<256, i64>(
            _mm_andnot_ps(b.v128[0], a.v128[0]), _mm_andnot_ps(b.v128[1], a.v128[1]));
#endif
    }
    template <>
    inline Simd<512, i64> landnot(const Simd<512, i64> &a, const Simd<512, i64> &b) {
#if AXM_SIMD_SSE2
        return Simd<512, i64>(
            _mm_andnot_si128(b.v128[0], a.v128[0]), _mm_andnot_si128(b.v128[1], a.v128[1]),
            _mm_andnot_si128(b.v128[2], a.v128[2]), _mm_andnot_si128(b.v128[3], a.v128[3]));
#else
        return Simd<512, i64>(
            _mm_andnot_ps(b.v128[0], a.v128[0]), _mm_andnot_ps(b.v128[1], a.v128[1]),
            _mm_andnot_ps(b.v128[2], a.v128[2]), _mm_andnot_ps(b.v128[3], a.v128[3]));
#endif
    }

    template <>
    inline Simd<128, i64> shl(const Simd<128, i64> &a, const int count) {
#if AXM_SIMD_SSE2
        return Simd<128, i64>(_mm_slli_epi64(a.v128, count));
#else
        return Simd<128, i64>(a.i[0] << count, a.i[1] << count);
#endif
    }
    template <>
    inline Simd<256, i64> shl(const Simd<256, i64> &a, const int count) {
#if AXM_SIMD_SSE2
        return Simd<256, i64>(_mm_slli_epi64(a.v128[0], count), _mm_slli_epi64(a.v128[1], count));
#else
        return Simd<256, i64>(a.i[0] << count, a.i[1] << count, a.i[2] << count, a.i[3] << count);
#endif
    }
    template <>
    inline Simd<512, i64> shl(const Simd<512, i64> &a, const int count) {
#if AXM_SIMD_SSE2
        return Simd<512, i64>(
            _mm_slli_epi64(a.v128[0], count), _mm_slli_epi64(a.v128[1], count),
            _mm_slli_epi64(a.v128[2], count), _mm_slli_epi64(a.v128[3], count));
#else
        return Simd<512, i64>(
            a.i[0] << count, a.i[1] << count, a.i[2] << count, a.i[3] << count, a.i[4] << count,
            a.i[5] << count, a.i[6] << count, a.i[7] << count);
#endif
    }
    template <>
    inline Simd<128, i64> shr(const Simd<128, i64> &a, const int count) {
#if AXM_SIMD_SSE2
        return Simd<128, i64>(_mm_srli_epi64(a.v128, count));
#else
        return Simd<128, i64>((u32)a.i[0] >> count, (u32)a.i[1] >> count);
#endif
    }
    template <>
    inline Simd<256, i64> shr(const Simd<256, i64> &a, const int count) {
#if AXM_SIMD_SSE2
        return Simd<256, i64>(_mm_srli_epi64(a.v128[0], count), _mm_srli_epi64(a.v128[1], count));
#else
        return Simd<256, i64>(
            (u32)a.i[0] >> count, (u32)a.i[1] >> count, (u32)a.i[2] >> count, (u32)a.i[3] >> count);
#endif
    }
    template <>
    inline Simd<512, i64> shr(const Simd<512, i64> &a, const int count) {
#if AXM_SIMD_SSE2
        return Simd<512, i64>(
            _mm_srli_epi64(a.v128[0], count), _mm_srli_epi64(a.v128[1], count),
            _mm_srli_epi64(a.v128[2], count), _mm_srli_epi64(a.v128[3], count));
#else
        return Simd<512, i64>(
            (u32)a.i[0] >> count, (u32)a.i[1] >> count, (u32)a.i[2] >> count, (u32)a.i[3] >> count,
            (u32)a.i[4] >> count, (u32)a.i[5] >> count, (u32)a.i[6] >> count, (u32)a.i[7] >> count);
#endif
    }
    template <>
    inline Simd<128, i64> sar(const Simd<128, i64> &a, const int count) {
        return Simd<128, i64>(a.i[0] >> count, a.i[1] >> count);
    }
    template <>
    inline Simd<256, i64> sar(const Simd<256, i64> &a, const int count) {
        return Simd<256, i64>(a.i[0] >> count, a.i[1] >> count, a.i[2] >> count, a.i[3] >> count);
    }
    template <>
    inline Simd<512, i64> sar(const Simd<512, i64> &a, const int count) {
        return Simd<512, i64>(
            a.i[0] >> count, a.i[1] >> count, a.i[2] >> count, a.i[3] >> count, a.i[4] >> count,
            a.i[5] >> count, a.i[6] >> count, a.i[7] >> count);
    }

    template <>
    inline Simd<128, i64> mul(const Simd<128, i64> &a, const Simd<128, i64> &b) {
        return Simd<128, i64>(a.i[0] * b.i[0], a.i[1] * b.i[1]);
    }
    template <>
    inline Simd<256, i64> mul(const Simd<256, i64> &a, const Simd<256, i64> &b) {
        return Simd<256, i64>(a.i[0] * b.i[0], a.i[1] * b.i[1], a.i[2] * b.i[2], a.i[3] * b.i[3]);
    }
    template <>
    inline Simd<512, i64> mul(const Simd<512, i64> &a, const Simd<512, i64> &b) {
        return Simd<512, i64>(
            a.i[0] * b.i[0], a.i[1] * b.i[1], a.i[2] * b.i[2], a.i[3] * b.i[3], a.i[4] * b.i[4],
            a.i[5] * b.i[5], a.i[6] * b.i[6], a.i[7] * b.i[7]);
    }

    template <>
    inline Simd<128, i64> cmpEq(const Simd<128, i64> &a, const Simd<128, i64> &b) {
#if AXM_SIMD_SSE41
        return Simd<128, i64>(_mm_cmpeq_epi64(a.v128, b.v128));
#else
        return Simd<128, i64>(a.i[0] == b.i[0] ? ~0 : 0, a.i[1] == b.i[1] ? ~0 : 0);
#endif
    }
    template <>
    inline Simd<256, i64> cmpEq(const Simd<256, i64> &a, const Simd<256, i64> &b) {
#if AXM_SIMD_SSE41
        return Simd<256, i64>(
            _mm_cmpeq_epi64(a.v128[0], b.v128[0]), _mm_cmpeq_epi64(a.v128[1], b.v128[1]));
#else
        return Simd<256, i64>(
            a.i[0] == b.i[0] ? ~0 : 0, a.i[1] == b.i[1] ? ~0 : 0, a.i[2] == b.i[2] ? ~0 : 0,
            a.i[3] == b.i[3] ? ~0 : 0);
#endif
    }
    template <>
    inline Simd<512, i64> cmpEq(const Simd<512, i64> &a, const Simd<512, i64> &b) {
#if AXM_SIMD_SSE41
        return Simd<512, i64>(
            _mm_cmpeq_epi64(a.v128[0], b.v128[0]), _mm_cmpeq_epi64(a.v128[1], b.v128[1]),
            _mm_cmpeq_epi64(a.v128[2], b.v128[2]), _mm_cmpeq_epi64(a.v128[3], b.v128[3]));
#else
        return Simd<512, i64>(
            a.i[0] == b.i[0] ? ~0 : 0, a.i[1] == b.i[1] ? ~0 : 0, a.i[2] == b.i[2] ? ~0 : 0,
            a.i[3] == b.i[3] ? ~0 : 0, a.i[4] == b.i[4] ? ~0 : 0, a.i[5] == b.i[5] ? ~0 : 0,
            a.i[6] == b.i[6] ? ~0 : 0, a.i[7] == b.i[7] ? ~0 : 0);
#endif
    }
    template <>
    inline Simd<128, i64> cmpNe(const Simd<128, i64> &a, const Simd<128, i64> &b) {
#if AXM_SIMD_SSE41
        return Simd<128, i64>(_mm_xor_si128(_mm_cmpeq_epi64(a.v128, b.v128), _mm_set1_epi32(~0)));
#else
        return Simd<128, i64>(a.i[0] != b.i[0] ? ~0 : 0, a.i[1] != b.i[1] ? ~0 : 0);
#endif
    }
    template <>
    inline Simd<256, i64> cmpNe(const Simd<256, i64> &a, const Simd<256, i64> &b) {
#if AXM_SIMD_SSE41
        return Simd<256, i64>(
            _mm_xor_si128(_mm_cmpeq_epi64(a.v128[0], b.v128[0]), _mm_set1_epi32(~0)),
            _mm_xor_si128(_mm_cmpeq_epi64(a.v128[1], b.v128[1]), _mm_set1_epi32(~0)));
#else
        return Simd<256, i64>(
            a.i[0] != b.i[0] ? ~0 : 0, a.i[1] != b.i[1] ? ~0 : 0, a.i[2] != b.i[2] ? ~0 : 0,
            a.i[3] != b.i[3] ? ~0 : 0);
#endif
    }
    template <>
    inline Simd<512, i64> cmpNe(const Simd<512, i64> &a, const Simd<512, i64> &b) {
#if AXM_SIMD_SSE41
        return Simd<512, i64>(
            _mm_xor_si128(_mm_cmpeq_epi64(a.v128[0], b.v128[0]), _mm_set1_epi32(~0)),
            _mm_xor_si128(_mm_cmpeq_epi64(a.v128[1], b.v128[1]), _mm_set1_epi32(~0)),
            _mm_xor_si128(_mm_cmpeq_epi64(a.v128[2], b.v128[2]), _mm_set1_epi32(~0)),
            _mm_xor_si128(_mm_cmpeq_epi64(a.v128[3], b.v128[3]), _mm_set1_epi32(~0)));
#else
        return Simd<512, i64>(
            a.i[0] != b.i[0] ? ~0 : 0, a.i[1] != b.i[1] ? ~0 : 0, a.i[2] != b.i[2] ? ~0 : 0,
            a.i[3] != b.i[3] ? ~0 : 0, a.i[4] != b.i[4] ? ~0 : 0, a.i[5] != b.i[5] ? ~0 : 0,
            a.i[6] != b.i[6] ? ~0 : 0, a.i[7] != b.i[7] ? ~0 : 0);
#endif
    }
    template <>
    inline Simd<128, i64> cmpLt(const Simd<128, i64> &a, const Simd<128, i64> &b) {
#if AXM_SIMD_SSE42
        return Simd<128, i64>(_mm_cmpgt_epi64(b.v128, a.v128));
#else
        return Simd<128, i64>(a.i[0] < b.i[0] ? ~0 : 0, a.i[1] < b.i[1] ? ~0 : 0);
#endif
    }
    template <>
    inline Simd<256, i64> cmpLt(const Simd<256, i64> &a, const Simd<256, i64> &b) {
#if AXM_SIMD_SSE42
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
#if AXM_SIMD_SSE42
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
#else
        return Simd<128, i64>(a.i[0] <= b.i[0] ? ~0 : 0, a.i[1] <= b.i[1] ? ~0 : 0);
#endif
    }
    template <>
    inline Simd<256, i64> cmpLe(const Simd<256, i64> &a, const Simd<256, i64> &b) {
#if AXM_SIMD_SSE42
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
#if AXM_SIMD_SSE42
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
#else
        return Simd<128, i64>(a.i[0] > b.i[0] ? ~0 : 0, a.i[1] > b.i[1] ? ~0 : 0);
#endif
    }
    template <>
    inline Simd<256, i64> cmpGt(const Simd<256, i64> &a, const Simd<256, i64> &b) {
#if AXM_SIMD_SSE42
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
#if AXM_SIMD_SSE42
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
#else
        return Simd<128, i64>(a.i[0] >= b.i[0] ? ~0 : 0, a.i[1] >= b.i[1] ? ~0 : 0);
#endif
    }
    template <>
    inline Simd<256, i64> cmpGe(const Simd<256, i64> &a, const Simd<256, i64> &b) {
#if AXM_SIMD_SSE42
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
#if AXM_SIMD_SSE42
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
#if AXM_SIMD_SSE2
        return (u32)_mm_movemask_epi8(a.v128);
#else
        return (u32)_mm_movemask_ps(a.v128);
#endif
    }
    template <>
    inline u32 movemask(const Simd<256, i64> &a) {
#if AXM_SIMD_SSE2
        return (u32)_mm_movemask_epi8(a.v128[0]) | ((u32)_mm_movemask_epi8(a.v128[1]) << 16);
#else
        return (u32)_mm_movemask_ps(a.v128[0]) | ((u32)_mm_movemask_ps(a.v128[1]) << 16);
#endif
    }
    template <>
    inline u64 movemask(const Simd<512, i64> &a) {
#if AXM_SIMD_SSE2
        return (u64)_mm_movemask_epi8(a.v128[0])
             | ((u64)_mm_movemask_epi8(a.v128[1]) << 16)
             | ((u64)_mm_movemask_epi8(a.v128[2]) << 32)
             | ((u64)_mm_movemask_epi8(a.v128[3]) << 48);
#else
        return (u64)_mm_movemask_ps(a.v128[0])
             | ((u64)_mm_movemask_ps(a.v128[1]) << 16)
             | ((u64)_mm_movemask_ps(a.v128[2]) << 32)
             | ((u64)_mm_movemask_ps(a.v128[3]) << 48);
#endif
    }
}}

#endif
