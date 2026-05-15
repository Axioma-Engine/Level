#ifndef AXM_LVL_SIMD_SSE_F32_H
#define AXM_LVL_SIMD_SSE_F32_H

#include <xmmintrin.h>

#include "../../Types.h"
#include "../Simd.h"

namespace Level { namespace SIMD {
    template <>
    union Simd<128, f32> {
        __m128 v128;
        f32    f[4];
        Simd() {}
        Simd(__m128 a0) { v128 = a0; }
        Simd(f32 a0, f32 a1, f32 a2, f32 a3) {
            f[0] = a0;
            f[1] = a1;
            f[2] = a2;
            f[3] = a3;
        }
    };
    template <>
    union Simd<256, f32> {
        __m128 v128[2];
        f32    f[8];
        Simd() {}
        Simd(__m128 a0, __m128 a1) {
            v128[0] = a0;
            v128[1] = a1;
        }
        Simd(f32 a0, f32 a1, f32 a2, f32 a3, f32 a4, f32 a5, f32 a6, f32 a7) {
            f[0] = a0;
            f[1] = a1;
            f[2] = a2;
            f[3] = a3;
            f[4] = a4;
            f[5] = a5;
            f[6] = a6;
            f[7] = a7;
        }
    };
    template <>
    union Simd<512, f32> {
        __m128 v128[4];
        f32    f[16];
        Simd() {}
        Simd(__m128 a0, __m128 a1, __m128 a2, __m128 a3) {
            v128[0] = a0;
            v128[1] = a1;
            v128[2] = a2;
            v128[3] = a3;
        }
        Simd(
            f32 a0, f32 a1, f32 a2, f32 a3, f32 a4, f32 a5, f32 a6, f32 a7, f32 a8, f32 a9, f32 a10,
            f32 a11, f32 a12, f32 a13, f32 a14, f32 a15) {
            f[0]  = a0;
            f[1]  = a1;
            f[2]  = a2;
            f[3]  = a3;
            f[4]  = a4;
            f[5]  = a5;
            f[6]  = a6;
            f[7]  = a7;
            f[8]  = a8;
            f[9]  = a9;
            f[10] = a10;
            f[11] = a11;
            f[12] = a12;
            f[13] = a13;
            f[14] = a14;
            f[15] = a15;
        }
    };

    template <>
    inline Simd<128, f32> load(const f32* ptr) {
        return Simd<128, f32>(_mm_loadu_ps(ptr));
    }
    template <>
    inline Simd<256, f32> load(const f32* ptr) {
        return Simd<256, f32>(_mm_loadu_ps(ptr), _mm_loadu_ps(ptr + 4));
    }
    template <>
    inline Simd<512, f32> load(const f32* ptr) {
        return Simd<512, f32>(
            _mm_loadu_ps(ptr), _mm_loadu_ps(ptr + 4), _mm_loadu_ps(ptr + 8),
            _mm_loadu_ps(ptr + 12));
    }
    template <>
    inline void store(f32* ptr, const Simd<128, f32> &simd) {
        _mm_storeu_ps(ptr, simd.v128);
    }
    template <>
    inline void store(f32* ptr, const Simd<256, f32> &simd) {
        _mm_storeu_ps(ptr, simd.v128[0]);
        _mm_storeu_ps(ptr + 4, simd.v128[1]);
    }
    template <>
    inline void store(f32* ptr, const Simd<512, f32> &simd) {
        _mm_storeu_ps(ptr, simd.v128[0]);
        _mm_storeu_ps(ptr + 4, simd.v128[1]);
        _mm_storeu_ps(ptr + 8, simd.v128[2]);
        _mm_storeu_ps(ptr + 12, simd.v128[3]);
    }
    template <>
    inline Simd<128, f32> set1(const f32 value) {
        return Simd<128, f32>(_mm_set1_ps(value));
    }
    template <>
    inline Simd<256, f32> set1(const f32 value) {
        __m128 v = _mm_set1_ps(value);
        return Simd<256, f32>(v, v);
    }
    template <>
    inline Simd<512, f32> set1(const f32 value) {
        __m128 v = _mm_set1_ps(value);
        return Simd<512, f32>(v, v, v, v);
    }
    template <>
    inline Simd<128, f32> set(const f32 a0, const f32 a1, const f32 a2, const f32 a3) {
        return Simd<128, f32>(_mm_set_ps(a3, a2, a1, a0));
    }
    template <>
    inline Simd<256, f32>
        set(const f32 a0, const f32 a1, const f32 a2, const f32 a3, const f32 a4, const f32 a5,
            const f32 a6, const f32 a7) {
        return Simd<256, f32>(_mm_set_ps(a3, a2, a1, a0), _mm_set_ps(a7, a6, a5, a4));
    }
    template <>
    inline Simd<512, f32>
        set(const f32 a0, const f32 a1, const f32 a2, const f32 a3, const f32 a4, const f32 a5,
            const f32 a6, const f32 a7, const f32 a8, const f32 a9, const f32 a10, const f32 a11,
            const f32 a12, const f32 a13, const f32 a14, const f32 a15) {
        return Simd<512, f32>(
            _mm_set_ps(a3, a2, a1, a0), _mm_set_ps(a7, a6, a5, a4), _mm_set_ps(a11, a10, a9, a8),
            _mm_set_ps(a15, a14, a13, a12));
    }

    template <>
    inline Simd<128, f32> add(const Simd<128, f32> &a, const Simd<128, f32> &b) {
        return Simd<128, f32>(_mm_add_ps(a.v128, b.v128));
    }
    template <>
    inline Simd<256, f32> add(const Simd<256, f32> &a, const Simd<256, f32> &b) {
        return Simd<256, f32>(_mm_add_ps(a.v128[0], b.v128[0]), _mm_add_ps(a.v128[1], b.v128[1]));
    }
    template <>
    inline Simd<512, f32> add(const Simd<512, f32> &a, const Simd<512, f32> &b) {
        return Simd<512, f32>(
            _mm_add_ps(a.v128[0], b.v128[0]), _mm_add_ps(a.v128[1], b.v128[1]),
            _mm_add_ps(a.v128[2], b.v128[2]), _mm_add_ps(a.v128[3], b.v128[3]));
    }
    template <>
    inline Simd<128, f32> sub(const Simd<128, f32> &a, const Simd<128, f32> &b) {
        return Simd<128, f32>(_mm_sub_ps(a.v128, b.v128));
    }
    template <>
    inline Simd<256, f32> sub(const Simd<256, f32> &a, const Simd<256, f32> &b) {
        return Simd<256, f32>(_mm_sub_ps(a.v128[0], b.v128[0]), _mm_sub_ps(a.v128[1], b.v128[1]));
    }
    template <>
    inline Simd<512, f32> sub(const Simd<512, f32> &a, const Simd<512, f32> &b) {
        return Simd<512, f32>(
            _mm_sub_ps(a.v128[0], b.v128[0]), _mm_sub_ps(a.v128[1], b.v128[1]),
            _mm_sub_ps(a.v128[2], b.v128[2]), _mm_sub_ps(a.v128[3], b.v128[3]));
    }
    template <>
    inline Simd<128, f32> abs(const Simd<128, f32> &a) {
        __m128 mask = _mm_set_ps1(0x7FFFFFFF);
        return Simd<128, f32>(_mm_and_ps(a.v128, mask));
    }
    template <>
    inline Simd<256, f32> abs(const Simd<256, f32> &a) {
        __m128 mask = _mm_set_ps1(0x7FFFFFFF);
        return Simd<256, f32>(_mm_and_ps(a.v128[0], mask), _mm_and_ps(a.v128[1], mask));
    }
    template <>
    inline Simd<512, f32> abs(const Simd<512, f32> &a) {
        __m128 mask = _mm_set_ps1(0x7FFFFFFF);
        return Simd<512, f32>(
            _mm_and_ps(a.v128[0], mask), _mm_and_ps(a.v128[1], mask), _mm_and_ps(a.v128[2], mask),
            _mm_and_ps(a.v128[3], mask));
    }
    template <>
    inline Simd<128, f32> neg(const Simd<128, f32> &a) {
        return Simd<128, f32>(_mm_xor_ps(a.v128, _mm_set_ps1(-0.0f)));
    }
    template <>
    inline Simd<256, f32> neg(const Simd<256, f32> &a) {
        __m128 mask = _mm_set_ps1(-0.0f);
        return Simd<256, f32>(_mm_xor_ps(a.v128[0], mask), _mm_xor_ps(a.v128[1], mask));
    }
    template <>
    inline Simd<512, f32> neg(const Simd<512, f32> &a) {
        __m128 mask = _mm_set_ps1(-0.0f);
        return Simd<512, f32>(
            _mm_xor_ps(a.v128[0], mask), _mm_xor_ps(a.v128[1], mask), _mm_xor_ps(a.v128[2], mask),
            _mm_xor_ps(a.v128[3], mask));
    }
    template <>
    inline Simd<128, f32> min(const Simd<128, f32> &a, const Simd<128, f32> &b) {
        return Simd<128, f32>(_mm_min_ps(a.v128, b.v128));
    }
    template <>
    inline Simd<256, f32> min(const Simd<256, f32> &a, const Simd<256, f32> &b) {
        return Simd<256, f32>(_mm_min_ps(a.v128[0], b.v128[0]), _mm_min_ps(a.v128[1], b.v128[1]));
    }
    template <>
    inline Simd<512, f32> min(const Simd<512, f32> &a, const Simd<512, f32> &b) {
        return Simd<512, f32>(
            _mm_min_ps(a.v128[0], b.v128[0]), _mm_min_ps(a.v128[1], b.v128[1]),
            _mm_min_ps(a.v128[2], b.v128[2]), _mm_min_ps(a.v128[3], b.v128[3]));
    }
    template <>
    inline Simd<128, f32> max(const Simd<128, f32> &a, const Simd<128, f32> &b) {
        return Simd<128, f32>(_mm_max_ps(a.v128, b.v128));
    }
    template <>
    inline Simd<256, f32> max(const Simd<256, f32> &a, const Simd<256, f32> &b) {
        return Simd<256, f32>(_mm_max_ps(a.v128[0], b.v128[0]), _mm_max_ps(a.v128[1], b.v128[1]));
    }
    template <>
    inline Simd<512, f32> max(const Simd<512, f32> &a, const Simd<512, f32> &b) {
        return Simd<512, f32>(
            _mm_max_ps(a.v128[0], b.v128[0]), _mm_max_ps(a.v128[1], b.v128[1]),
            _mm_max_ps(a.v128[2], b.v128[2]), _mm_max_ps(a.v128[3], b.v128[3]));
    }

    template <>
    inline Simd<128, f32> land(const Simd<128, f32> &a, const Simd<128, f32> &b) {
        return Simd<128, f32>(_mm_and_ps(a.v128, b.v128));
    }
    template <>
    inline Simd<256, f32> land(const Simd<256, f32> &a, const Simd<256, f32> &b) {
        return Simd<256, f32>(_mm_and_ps(a.v128[0], b.v128[0]), _mm_and_ps(a.v128[1], b.v128[1]));
    }
    template <>
    inline Simd<512, f32> land(const Simd<512, f32> &a, const Simd<512, f32> &b) {
        return Simd<512, f32>(
            _mm_and_ps(a.v128[0], b.v128[0]), _mm_and_ps(a.v128[1], b.v128[1]),
            _mm_and_ps(a.v128[2], b.v128[2]), _mm_and_ps(a.v128[3], b.v128[3]));
    }
    template <>
    inline Simd<128, f32> lor(const Simd<128, f32> &a, const Simd<128, f32> &b) {
        return Simd<128, f32>(_mm_or_ps(a.v128, b.v128));
    }
    template <>
    inline Simd<256, f32> lor(const Simd<256, f32> &a, const Simd<256, f32> &b) {
        return Simd<256, f32>(_mm_or_ps(a.v128[0], b.v128[0]), _mm_or_ps(a.v128[1], b.v128[1]));
    }
    template <>
    inline Simd<512, f32> lor(const Simd<512, f32> &a, const Simd<512, f32> &b) {
        return Simd<512, f32>(
            _mm_or_ps(a.v128[0], b.v128[0]), _mm_or_ps(a.v128[1], b.v128[1]),
            _mm_or_ps(a.v128[2], b.v128[2]), _mm_or_ps(a.v128[3], b.v128[3]));
    }
    template <>
    inline Simd<128, f32> lxor(const Simd<128, f32> &a, const Simd<128, f32> &b) {
        return Simd<128, f32>(_mm_xor_ps(a.v128, b.v128));
    }
    template <>
    inline Simd<256, f32> lxor(const Simd<256, f32> &a, const Simd<256, f32> &b) {
        return Simd<256, f32>(_mm_xor_ps(a.v128[0], b.v128[0]), _mm_xor_ps(a.v128[1], b.v128[1]));
    }
    template <>
    inline Simd<512, f32> lxor(const Simd<512, f32> &a, const Simd<512, f32> &b) {
        return Simd<512, f32>(
            _mm_xor_ps(a.v128[0], b.v128[0]), _mm_xor_ps(a.v128[1], b.v128[1]),
            _mm_xor_ps(a.v128[2], b.v128[2]), _mm_xor_ps(a.v128[3], b.v128[3]));
    }
    template <>
    inline Simd<128, f32> lnot(const Simd<128, f32> &a) {
        return Simd<128, f32>(_mm_xor_ps(a.v128, _mm_set_ps1(~0)));
    }
    template <>
    inline Simd<256, f32> lnot(const Simd<256, f32> &a) {
        __m128 ones = _mm_set_ps1(~0);
        return Simd<256, f32>(_mm_xor_ps(a.v128[0], ones), _mm_xor_ps(a.v128[1], ones));
    }
    template <>
    inline Simd<512, f32> lnot(const Simd<512, f32> &a) {
        __m128 ones = _mm_set_ps1(~0);
        return Simd<512, f32>(
            _mm_xor_ps(a.v128[0], ones), _mm_xor_ps(a.v128[1], ones), _mm_xor_ps(a.v128[2], ones),
            _mm_xor_ps(a.v128[3], ones));
    }
    template <>
    inline Simd<128, f32> landnot(const Simd<128, f32> &a, const Simd<128, f32> &b) {
        return Simd<128, f32>(_mm_andnot_ps(b.v128, a.v128));
    }
    template <>
    inline Simd<256, f32> landnot(const Simd<256, f32> &a, const Simd<256, f32> &b) {
        return Simd<256, f32>(
            _mm_andnot_ps(b.v128[0], a.v128[0]), _mm_andnot_ps(b.v128[1], a.v128[1]));
    }
    template <>
    inline Simd<512, f32> landnot(const Simd<512, f32> &a, const Simd<512, f32> &b) {
        return Simd<512, f32>(
            _mm_andnot_ps(b.v128[0], a.v128[0]), _mm_andnot_ps(b.v128[1], a.v128[1]),
            _mm_andnot_ps(b.v128[2], a.v128[2]), _mm_andnot_ps(b.v128[3], a.v128[3]));
    }

    template <>
    inline Simd<128, f32> mul(const Simd<128, f32> &a, const Simd<128, f32> &b) {
        return Simd<128, f32>(_mm_mul_ps(a.v128, b.v128));
    }
    template <>
    inline Simd<256, f32> mul(const Simd<256, f32> &a, const Simd<256, f32> &b) {
        return Simd<256, f32>(_mm_mul_ps(a.v128[0], b.v128[0]), _mm_mul_ps(a.v128[1], b.v128[1]));
    }
    template <>
    inline Simd<512, f32> mul(const Simd<512, f32> &a, const Simd<512, f32> &b) {
        return Simd<512, f32>(
            _mm_mul_ps(a.v128[0], b.v128[0]), _mm_mul_ps(a.v128[1], b.v128[1]),
            _mm_mul_ps(a.v128[2], b.v128[2]), _mm_mul_ps(a.v128[3], b.v128[3]));
    }
    template <>
    inline Simd<128, f32> div(const Simd<128, f32> &a, const Simd<128, f32> &b) {
        return Simd<128, f32>(_mm_div_ps(a.v128, b.v128));
    }
    template <>
    inline Simd<256, f32> div(const Simd<256, f32> &a, const Simd<256, f32> &b) {
        return Simd<256, f32>(_mm_div_ps(a.v128[0], b.v128[0]), _mm_div_ps(a.v128[1], b.v128[1]));
    }
    template <>
    inline Simd<512, f32> div(const Simd<512, f32> &a, const Simd<512, f32> &b) {
        return Simd<512, f32>(
            _mm_div_ps(a.v128[0], b.v128[0]), _mm_div_ps(a.v128[1], b.v128[1]),
            _mm_div_ps(a.v128[2], b.v128[2]), _mm_div_ps(a.v128[3], b.v128[3]));
    }
    template <>
    inline Simd<128, f32> sqrt(const Simd<128, f32> &a) {
        return Simd<128, f32>(_mm_sqrt_ps(a.v128));
    }
    template <>
    inline Simd<256, f32> sqrt(const Simd<256, f32> &a) {
        return Simd<256, f32>(_mm_sqrt_ps(a.v128[0]), _mm_sqrt_ps(a.v128[1]));
    }
    template <>
    inline Simd<512, f32> sqrt(const Simd<512, f32> &a) {
        return Simd<512, f32>(
            _mm_sqrt_ps(a.v128[0]), _mm_sqrt_ps(a.v128[1]), _mm_sqrt_ps(a.v128[2]),
            _mm_sqrt_ps(a.v128[3]));
    }
    template <>
    inline Simd<128, f32> rsqrt(const Simd<128, f32> &a) {
        return Simd<128, f32>(_mm_rsqrt_ps(a.v128));
    }
    template <>
    inline Simd<256, f32> rsqrt(const Simd<256, f32> &a) {
        return Simd<256, f32>(_mm_rsqrt_ps(a.v128[0]), _mm_rsqrt_ps(a.v128[1]));
    }
    template <>
    inline Simd<512, f32> rsqrt(const Simd<512, f32> &a) {
        return Simd<512, f32>(
            _mm_rsqrt_ps(a.v128[0]), _mm_rsqrt_ps(a.v128[1]), _mm_rsqrt_ps(a.v128[2]),
            _mm_rsqrt_ps(a.v128[3]));
    }
    template <>
    inline Simd<128, f32> reciprocal(const Simd<128, f32> &a) {
        return Simd<128, f32>(_mm_rcp_ps(a.v128));
    }
    template <>
    inline Simd<256, f32> reciprocal(const Simd<256, f32> &a) {
        return Simd<256, f32>(_mm_rcp_ps(a.v128[0]), _mm_rcp_ps(a.v128[1]));
    }
    template <>
    inline Simd<512, f32> reciprocal(const Simd<512, f32> &a) {
        return Simd<512, f32>(
            _mm_rcp_ps(a.v128[0]), _mm_rcp_ps(a.v128[1]), _mm_rcp_ps(a.v128[2]),
            _mm_rcp_ps(a.v128[3]));
    }

    template <>
    inline Simd<128, f32> cmpEq(const Simd<128, f32> &a, const Simd<128, f32> &b) {
        return Simd<128, f32>(_mm_cmpeq_ps(a.v128, b.v128));
    }
    template <>
    inline Simd<256, f32> cmpEq(const Simd<256, f32> &a, const Simd<256, f32> &b) {
        return Simd<256, f32>(
            _mm_cmpeq_ps(a.v128[0], b.v128[0]), _mm_cmpeq_ps(a.v128[1], b.v128[1]));
    }
    template <>
    inline Simd<512, f32> cmpEq(const Simd<512, f32> &a, const Simd<512, f32> &b) {
        return Simd<512, f32>(
            _mm_cmpeq_ps(a.v128[0], b.v128[0]), _mm_cmpeq_ps(a.v128[1], b.v128[1]),
            _mm_cmpeq_ps(a.v128[2], b.v128[2]), _mm_cmpeq_ps(a.v128[3], b.v128[3]));
    }
    template <>
    inline Simd<128, f32> cmpNe(const Simd<128, f32> &a, const Simd<128, f32> &b) {
        return Simd<128, f32>(_mm_cmpneq_ps(a.v128, b.v128));
    }
    template <>
    inline Simd<256, f32> cmpNe(const Simd<256, f32> &a, const Simd<256, f32> &b) {
        return Simd<256, f32>(
            _mm_cmpneq_ps(a.v128[0], b.v128[0]), _mm_cmpneq_ps(a.v128[1], b.v128[1]));
    }
    template <>
    inline Simd<512, f32> cmpNe(const Simd<512, f32> &a, const Simd<512, f32> &b) {
        return Simd<512, f32>(
            _mm_cmpneq_ps(a.v128[0], b.v128[0]), _mm_cmpneq_ps(a.v128[1], b.v128[1]),
            _mm_cmpneq_ps(a.v128[2], b.v128[2]), _mm_cmpneq_ps(a.v128[3], b.v128[3]));
    }
    template <>
    inline Simd<128, f32> cmpLt(const Simd<128, f32> &a, const Simd<128, f32> &b) {
        return Simd<128, f32>(_mm_cmplt_ps(a.v128, b.v128));
    }
    template <>
    inline Simd<256, f32> cmpLt(const Simd<256, f32> &a, const Simd<256, f32> &b) {
        return Simd<256, f32>(
            _mm_cmplt_ps(a.v128[0], b.v128[0]), _mm_cmplt_ps(a.v128[1], b.v128[1]));
    }
    template <>
    inline Simd<512, f32> cmpLt(const Simd<512, f32> &a, const Simd<512, f32> &b) {
        return Simd<512, f32>(
            _mm_cmplt_ps(a.v128[0], b.v128[0]), _mm_cmplt_ps(a.v128[1], b.v128[1]),
            _mm_cmplt_ps(a.v128[2], b.v128[2]), _mm_cmplt_ps(a.v128[3], b.v128[3]));
    }
    template <>
    inline Simd<128, f32> cmpLe(const Simd<128, f32> &a, const Simd<128, f32> &b) {
        return Simd<128, f32>(_mm_cmple_ps(a.v128, b.v128));
    }
    template <>
    inline Simd<256, f32> cmpLe(const Simd<256, f32> &a, const Simd<256, f32> &b) {
        return Simd<256, f32>(
            _mm_cmple_ps(a.v128[0], b.v128[0]), _mm_cmple_ps(a.v128[1], b.v128[1]));
    }
    template <>
    inline Simd<512, f32> cmpLe(const Simd<512, f32> &a, const Simd<512, f32> &b) {
        return Simd<512, f32>(
            _mm_cmple_ps(a.v128[0], b.v128[0]), _mm_cmple_ps(a.v128[1], b.v128[1]),
            _mm_cmple_ps(a.v128[2], b.v128[2]), _mm_cmple_ps(a.v128[3], b.v128[3]));
    }
    template <>
    inline Simd<128, f32> cmpGt(const Simd<128, f32> &a, const Simd<128, f32> &b) {
        return Simd<128, f32>(_mm_cmpgt_ps(a.v128, b.v128));
    }
    template <>
    inline Simd<256, f32> cmpGt(const Simd<256, f32> &a, const Simd<256, f32> &b) {
        return Simd<256, f32>(
            _mm_cmpgt_ps(a.v128[0], b.v128[0]), _mm_cmpgt_ps(a.v128[1], b.v128[1]));
    }
    template <>
    inline Simd<512, f32> cmpGt(const Simd<512, f32> &a, const Simd<512, f32> &b) {
        return Simd<512, f32>(
            _mm_cmpgt_ps(a.v128[0], b.v128[0]), _mm_cmpgt_ps(a.v128[1], b.v128[1]),
            _mm_cmpgt_ps(a.v128[2], b.v128[2]), _mm_cmpgt_ps(a.v128[3], b.v128[3]));
    }
    template <>
    inline Simd<128, f32> cmpGe(const Simd<128, f32> &a, const Simd<128, f32> &b) {
        return Simd<128, f32>(_mm_cmpge_ps(a.v128, b.v128));
    }
    template <>
    inline Simd<256, f32> cmpGe(const Simd<256, f32> &a, const Simd<256, f32> &b) {
        return Simd<256, f32>(
            _mm_cmpge_ps(a.v128[0], b.v128[0]), _mm_cmpge_ps(a.v128[1], b.v128[1]));
    }
    template <>
    inline Simd<512, f32> cmpGe(const Simd<512, f32> &a, const Simd<512, f32> &b) {
        return Simd<512, f32>(
            _mm_cmpge_ps(a.v128[0], b.v128[0]), _mm_cmpge_ps(a.v128[1], b.v128[1]),
            _mm_cmpge_ps(a.v128[2], b.v128[2]), _mm_cmpge_ps(a.v128[3], b.v128[3]));
    }

    template <>
    inline u32 movemask(const Simd<128, f32> &a) {
        return _mm_movemask_ps(a.v128);
    }
    template <>
    inline u32 movemask(const Simd<256, f32> &a) {
        return _mm_movemask_ps(a.v128[0]) | (_mm_movemask_ps(a.v128[1]) << 16);
    }
    template <>
    inline u64 movemask(const Simd<512, f32> &a) {
        return (u64)_mm_movemask_ps(a.v128[0])
             | ((u64)_mm_movemask_ps(a.v128[1]) << 16)
             | ((u64)_mm_movemask_ps(a.v128[2]) << 32)
             | ((u64)_mm_movemask_ps(a.v128[3]) << 48);
    }
}}
#endif
