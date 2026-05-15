#ifndef AXM_LVL_SIMD_GENERIC_I64_H
#define AXM_LVL_SIMD_GENERIC_I64_H

#include "../../Types.h"
#include "../Simd.h"

namespace Level { namespace SIMD {
    template <>
    union Simd<128, i64> {
        i64 i[2];
        Simd() {}
        Simd(i64 a0, i64 a1) {
            i[0] = a0;
            i[1] = a1;
        }
    };
    template <>
    union Simd<256, i64> {
        i64 i[4];
        Simd() {}
        Simd(i64 a0, i64 a1, i64 a2, i64 a3) {
            i[0] = a0;
            i[1] = a1;
            i[2] = a2;
            i[3] = a3;
        }
    };
    template <>
    union Simd<512, i64> {
        i64 i[8];
        Simd() {}
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
        return Simd<128, i64>(ptr[0], ptr[1]);
    }
    template <>
    inline Simd<256, i64> load(const i64* ptr) {
        return Simd<256, i64>(ptr[0], ptr[1], ptr[2], ptr[3]);
    }
    template <>
    inline Simd<512, i64> load(const i64* ptr) {
        return Simd<512, i64>(ptr[0], ptr[1], ptr[2], ptr[3], ptr[4], ptr[5], ptr[6], ptr[7]);
    }
    template <>
    inline void store(i64* ptr, const Simd<128, i64> &simd) {
        ptr[0] = simd.i[0];
        ptr[1] = simd.i[1];
    }
    template <>
    inline void store(i64* ptr, const Simd<256, i64> &simd) {
        ptr[0] = simd.i[0];
        ptr[1] = simd.i[1];
        ptr[2] = simd.i[2];
        ptr[3] = simd.i[3];
    }
    template <>
    inline void store(i64* ptr, const Simd<512, i64> &simd) {
        ptr[0] = simd.i[0];
        ptr[1] = simd.i[1];
        ptr[2] = simd.i[2];
        ptr[3] = simd.i[3];
        ptr[4] = simd.i[4];
        ptr[5] = simd.i[5];
        ptr[6] = simd.i[6];
        ptr[7] = simd.i[7];
    }
    template <>
    inline Simd<128, i64> set1(const i64 value) {
        return Simd<128, i64>(value, value);
    }
    template <>
    inline Simd<256, i64> set1(const i64 value) {
        return Simd<256, i64>(value, value, value, value);
    }
    template <>
    inline Simd<512, i64> set1(const i64 value) {
        return Simd<512, i64>(value, value, value, value, value, value, value, value);
    }
    template <>
    inline Simd<128, i64> set(const i64 a0, const i64 a1) {
        return Simd<128, i64>(a0, a1);
    }
    template <>
    inline Simd<256, i64> set(const i64 a0, const i64 a1, const i64 a2, const i64 a3) {
        return Simd<256, i64>(a0, a1, a2, a3);
    }
    template <>
    inline Simd<512, i64>
        set(const i64 a0, const i64 a1, const i64 a2, const i64 a3, const i64 a4, const i64 a5,
            const i64 a6, const i64 a7) {
        return Simd<512, i64>(a0, a1, a2, a3, a4, a5, a6, a7);
    }

    template <>
    inline Simd<128, i64> add(const Simd<128, i64> &a, const Simd<128, i64> &b) {
        return Simd<128, i64>(a.i[0] + b.i[0], a.i[1] + b.i[1]);
    }
    template <>
    inline Simd<256, i64> add(const Simd<256, i64> &a, const Simd<256, i64> &b) {
        return Simd<256, i64>(a.i[0] + b.i[0], a.i[1] + b.i[1], a.i[2] + b.i[2], a.i[3] + b.i[3]);
    }
    template <>
    inline Simd<512, i64> add(const Simd<512, i64> &a, const Simd<512, i64> &b) {
        return Simd<512, i64>(
            a.i[0] + b.i[0], a.i[1] + b.i[1], a.i[2] + b.i[2], a.i[3] + b.i[3], a.i[4] + b.i[4],
            a.i[5] + b.i[5], a.i[6] + b.i[6], a.i[7] + b.i[7]);
    }
    template <>
    inline Simd<128, i64> sub(const Simd<128, i64> &a, const Simd<128, i64> &b) {
        return Simd<128, i64>(a.i[0] - b.i[0], a.i[1] - b.i[1]);
    }
    template <>
    inline Simd<256, i64> sub(const Simd<256, i64> &a, const Simd<256, i64> &b) {
        return Simd<256, i64>(a.i[0] - b.i[0], a.i[1] - b.i[1], a.i[2] - b.i[2], a.i[3] - b.i[3]);
    }
    template <>
    inline Simd<512, i64> sub(const Simd<512, i64> &a, const Simd<512, i64> &b) {
        return Simd<512, i64>(
            a.i[0] - b.i[0], a.i[1] - b.i[1], a.i[2] - b.i[2], a.i[3] - b.i[3], a.i[4] - b.i[4],
            a.i[5] - b.i[5], a.i[6] - b.i[6], a.i[7] - b.i[7]);
    }
    template <>
    inline Simd<128, i64> abs(const Simd<128, i64> &a) {
        return Simd<128, i64>(a.i[0] < 0 ? -a.i[0] : a.i[0], a.i[1] < 0 ? -a.i[1] : a.i[1]);
    }
    template <>
    inline Simd<256, i64> abs(const Simd<256, i64> &a) {
        return Simd<256, i64>(
            a.i[0] < 0 ? -a.i[0] : a.i[0], a.i[1] < 0 ? -a.i[1] : a.i[1],
            a.i[2] < 0 ? -a.i[2] : a.i[2], a.i[3] < 0 ? -a.i[3] : a.i[3]);
    }
    template <>
    inline Simd<512, i64> abs(const Simd<512, i64> &a) {
        return Simd<512, i64>(
            a.i[0] < 0 ? -a.i[0] : a.i[0], a.i[1] < 0 ? -a.i[1] : a.i[1],
            a.i[2] < 0 ? -a.i[2] : a.i[2], a.i[3] < 0 ? -a.i[3] : a.i[3],
            a.i[4] < 0 ? -a.i[4] : a.i[4], a.i[5] < 0 ? -a.i[5] : a.i[5],
            a.i[6] < 0 ? -a.i[6] : a.i[6], a.i[7] < 0 ? -a.i[7] : a.i[7]);
    }
    template <>
    inline Simd<128, i64> neg(const Simd<128, i64> &a) {
        return Simd<128, i64>(-a.i[0], -a.i[1]);
    }
    template <>
    inline Simd<256, i64> neg(const Simd<256, i64> &a) {
        return Simd<256, i64>(-a.i[0], -a.i[1], -a.i[2], -a.i[3]);
    }
    template <>
    inline Simd<512, i64> neg(const Simd<512, i64> &a) {
        return Simd<512, i64>(
            -a.i[0], -a.i[1], -a.i[2], -a.i[3], -a.i[4], -a.i[5], -a.i[6], -a.i[7]);
    }
    template <>
    inline Simd<128, i64> min(const Simd<128, i64> &a, const Simd<128, i64> &b) {
        return Simd<128, i64>(a.i[0] < b.i[0] ? a.i[0] : b.i[0], a.i[1] < b.i[1] ? a.i[1] : b.i[1]);
    }
    template <>
    inline Simd<256, i64> min(const Simd<256, i64> &a, const Simd<256, i64> &b) {
        return Simd<256, i64>(
            a.i[0] < b.i[0] ? a.i[0] : b.i[0], a.i[1] < b.i[1] ? a.i[1] : b.i[1],
            a.i[2] < b.i[2] ? a.i[2] : b.i[2], a.i[3] < b.i[3] ? a.i[3] : b.i[3]);
    }
    template <>
    inline Simd<512, i64> min(const Simd<512, i64> &a, const Simd<512, i64> &b) {
        return Simd<512, i64>(
            a.i[0] < b.i[0] ? a.i[0] : b.i[0], a.i[1] < b.i[1] ? a.i[1] : b.i[1],
            a.i[2] < b.i[2] ? a.i[2] : b.i[2], a.i[3] < b.i[3] ? a.i[3] : b.i[3],
            a.i[4] < b.i[4] ? a.i[4] : b.i[4], a.i[5] < b.i[5] ? a.i[5] : b.i[5],
            a.i[6] < b.i[6] ? a.i[6] : b.i[6], a.i[7] < b.i[7] ? a.i[7] : b.i[7]);
    }
    template <>
    inline Simd<128, i64> max(const Simd<128, i64> &a, const Simd<128, i64> &b) {
        return Simd<128, i64>(a.i[0] > b.i[0] ? a.i[0] : b.i[0], a.i[1] > b.i[1] ? a.i[1] : b.i[1]);
    }
    template <>
    inline Simd<256, i64> max(const Simd<256, i64> &a, const Simd<256, i64> &b) {
        return Simd<256, i64>(
            a.i[0] > b.i[0] ? a.i[0] : b.i[0], a.i[1] > b.i[1] ? a.i[1] : b.i[1],
            a.i[2] > b.i[2] ? a.i[2] : b.i[2], a.i[3] > b.i[3] ? a.i[3] : b.i[3]);
    }
    template <>
    inline Simd<512, i64> max(const Simd<512, i64> &a, const Simd<512, i64> &b) {
        return Simd<512, i64>(
            a.i[0] > b.i[0] ? a.i[0] : b.i[0], a.i[1] > b.i[1] ? a.i[1] : b.i[1],
            a.i[2] > b.i[2] ? a.i[2] : b.i[2], a.i[3] > b.i[3] ? a.i[3] : b.i[3],
            a.i[4] > b.i[4] ? a.i[4] : b.i[4], a.i[5] > b.i[5] ? a.i[5] : b.i[5],
            a.i[6] > b.i[6] ? a.i[6] : b.i[6], a.i[7] > b.i[7] ? a.i[7] : b.i[7]);
    }

    template <>
    inline Simd<128, i64> land(const Simd<128, i64> &a, const Simd<128, i64> &b) {
        return Simd<128, i64>(a.i[0] & b.i[0], a.i[1] & b.i[1]);
    }
    template <>
    inline Simd<256, i64> land(const Simd<256, i64> &a, const Simd<256, i64> &b) {
        return Simd<256, i64>(a.i[0] & b.i[0], a.i[1] & b.i[1], a.i[2] & b.i[2], a.i[3] & b.i[3]);
    }
    template <>
    inline Simd<512, i64> land(const Simd<512, i64> &a, const Simd<512, i64> &b) {
        return Simd<512, i64>(
            a.i[0] & b.i[0], a.i[1] & b.i[1], a.i[2] & b.i[2], a.i[3] & b.i[3], a.i[4] & b.i[4],
            a.i[5] & b.i[5], a.i[6] & b.i[6], a.i[7] & b.i[7]);
    }
    template <>
    inline Simd<128, i64> lor(const Simd<128, i64> &a, const Simd<128, i64> &b) {
        return Simd<128, i64>(a.i[0] | b.i[0], a.i[1] | b.i[1]);
    }
    template <>
    inline Simd<256, i64> lor(const Simd<256, i64> &a, const Simd<256, i64> &b) {
        return Simd<256, i64>(a.i[0] | b.i[0], a.i[1] | b.i[1], a.i[2] | b.i[2], a.i[3] | b.i[3]);
    }
    template <>
    inline Simd<512, i64> lor(const Simd<512, i64> &a, const Simd<512, i64> &b) {
        return Simd<512, i64>(
            a.i[0] | b.i[0], a.i[1] | b.i[1], a.i[2] | b.i[2], a.i[3] | b.i[3], a.i[4] | b.i[4],
            a.i[5] | b.i[5], a.i[6] | b.i[6], a.i[7] | b.i[7]);
    }
    template <>
    inline Simd<128, i64> lxor(const Simd<128, i64> &a, const Simd<128, i64> &b) {
        return Simd<128, i64>(a.i[0] ^ b.i[0], a.i[1] ^ b.i[1]);
    }
    template <>
    inline Simd<256, i64> lxor(const Simd<256, i64> &a, const Simd<256, i64> &b) {
        return Simd<256, i64>(a.i[0] ^ b.i[0], a.i[1] ^ b.i[1], a.i[2] ^ b.i[2], a.i[3] ^ b.i[3]);
    }
    template <>
    inline Simd<512, i64> lxor(const Simd<512, i64> &a, const Simd<512, i64> &b) {
        return Simd<512, i64>(
            a.i[0] ^ b.i[0], a.i[1] ^ b.i[1], a.i[2] ^ b.i[2], a.i[3] ^ b.i[3], a.i[4] ^ b.i[4],
            a.i[5] ^ b.i[5], a.i[6] ^ b.i[6], a.i[7] ^ b.i[7]);
    }
    template <>
    inline Simd<128, i64> lnot(const Simd<128, i64> &a) {
        return Simd<128, i64>(~a.i[0], ~a.i[1]);
    }
    template <>
    inline Simd<256, i64> lnot(const Simd<256, i64> &a) {
        return Simd<256, i64>(~a.i[0], ~a.i[1], ~a.i[2], ~a.i[3]);
    }
    template <>
    inline Simd<512, i64> lnot(const Simd<512, i64> &a) {
        return Simd<512, i64>(
            ~a.i[0], ~a.i[1], ~a.i[2], ~a.i[3], ~a.i[4], ~a.i[5], ~a.i[6], ~a.i[7]);
    }
    template <>
    inline Simd<128, i64> landnot(const Simd<128, i64> &a, const Simd<128, i64> &b) {
        return Simd<128, i64>(a.i[0] & ~b.i[0], a.i[1] & ~b.i[1]);
    }
    template <>
    inline Simd<256, i64> landnot(const Simd<256, i64> &a, const Simd<256, i64> &b) {
        return Simd<256, i64>(
            a.i[0] & ~b.i[0], a.i[1] & ~b.i[1], a.i[2] & ~b.i[2], a.i[3] & ~b.i[3]);
    }
    template <>
    inline Simd<512, i64> landnot(const Simd<512, i64> &a, const Simd<512, i64> &b) {
        return Simd<512, i64>(
            a.i[0] & ~b.i[0], a.i[1] & ~b.i[1], a.i[2] & ~b.i[2], a.i[3] & ~b.i[3],
            a.i[4] & ~b.i[4], a.i[5] & ~b.i[5], a.i[6] & ~b.i[6], a.i[7] & ~b.i[7]);
    }

    template <>
    inline Simd<128, i64> shl(const Simd<128, i64> &a, const int count) {
        return Simd<128, i64>(a.i[0] << count, a.i[1] << count);
    }
    template <>
    inline Simd<256, i64> shl(const Simd<256, i64> &a, const int count) {
        return Simd<256, i64>(a.i[0] << count, a.i[1] << count, a.i[2] << count, a.i[3] << count);
    }
    template <>
    inline Simd<512, i64> shl(const Simd<512, i64> &a, const int count) {
        return Simd<512, i64>(
            a.i[0] << count, a.i[1] << count, a.i[2] << count, a.i[3] << count, a.i[4] << count,
            a.i[5] << count, a.i[6] << count, a.i[7] << count);
    }
    template <>
    inline Simd<128, i64> shr(const Simd<128, i64> &a, const int count) {
        return Simd<128, i64>((u32)a.i[0] >> count, (u32)a.i[1] >> count);
    }
    template <>
    inline Simd<256, i64> shr(const Simd<256, i64> &a, const int count) {
        return Simd<256, i64>(
            (u32)a.i[0] >> count, (u32)a.i[1] >> count, (u32)a.i[2] >> count, (u32)a.i[3] >> count);
    }
    template <>
    inline Simd<512, i64> shr(const Simd<512, i64> &a, const int count) {
        return Simd<512, i64>(
            (u32)a.i[0] >> count, (u32)a.i[1] >> count, (u32)a.i[2] >> count, (u32)a.i[3] >> count,
            (u32)a.i[4] >> count, (u32)a.i[5] >> count, (u32)a.i[6] >> count, (u32)a.i[7] >> count);
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
        return Simd<128, i64>(a.i[0] == b.i[0] ? ~0 : 0, a.i[1] == b.i[1] ? ~0 : 0);
    }
    template <>
    inline Simd<256, i64> cmpEq(const Simd<256, i64> &a, const Simd<256, i64> &b) {
        return Simd<256, i64>(
            a.i[0] == b.i[0] ? ~0 : 0, a.i[1] == b.i[1] ? ~0 : 0, a.i[2] == b.i[2] ? ~0 : 0,
            a.i[3] == b.i[3] ? ~0 : 0);
    }
    template <>
    inline Simd<512, i64> cmpEq(const Simd<512, i64> &a, const Simd<512, i64> &b) {
        return Simd<512, i64>(
            a.i[0] == b.i[0] ? ~0 : 0, a.i[1] == b.i[1] ? ~0 : 0, a.i[2] == b.i[2] ? ~0 : 0,
            a.i[3] == b.i[3] ? ~0 : 0, a.i[4] == b.i[4] ? ~0 : 0, a.i[5] == b.i[5] ? ~0 : 0,
            a.i[6] == b.i[6] ? ~0 : 0, a.i[7] == b.i[7] ? ~0 : 0);
    }
    template <>
    inline Simd<128, i64> cmpNe(const Simd<128, i64> &a, const Simd<128, i64> &b) {
        return Simd<128, i64>(a.i[0] != b.i[0] ? ~0 : 0, a.i[1] != b.i[1] ? ~0 : 0);
    }
    template <>
    inline Simd<256, i64> cmpNe(const Simd<256, i64> &a, const Simd<256, i64> &b) {
        return Simd<256, i64>(
            a.i[0] != b.i[0] ? ~0 : 0, a.i[1] != b.i[1] ? ~0 : 0, a.i[2] != b.i[2] ? ~0 : 0,
            a.i[3] != b.i[3] ? ~0 : 0);
    }
    template <>
    inline Simd<512, i64> cmpNe(const Simd<512, i64> &a, const Simd<512, i64> &b) {
        return Simd<512, i64>(
            a.i[0] != b.i[0] ? ~0 : 0, a.i[1] != b.i[1] ? ~0 : 0, a.i[2] != b.i[2] ? ~0 : 0,
            a.i[3] != b.i[3] ? ~0 : 0, a.i[4] != b.i[4] ? ~0 : 0, a.i[5] != b.i[5] ? ~0 : 0,
            a.i[6] != b.i[6] ? ~0 : 0, a.i[7] != b.i[7] ? ~0 : 0);
    }
    template <>
    inline Simd<128, i64> cmpLt(const Simd<128, i64> &a, const Simd<128, i64> &b) {
        return Simd<128, i64>(a.i[0] < b.i[0] ? ~0 : 0, a.i[1] < b.i[1] ? ~0 : 0);
    }
    template <>
    inline Simd<256, i64> cmpLt(const Simd<256, i64> &a, const Simd<256, i64> &b) {
        return Simd<256, i64>(
            a.i[0] < b.i[0] ? ~0 : 0, a.i[1] < b.i[1] ? ~0 : 0, a.i[2] < b.i[2] ? ~0 : 0,
            a.i[3] < b.i[3] ? ~0 : 0);
    }
    template <>
    inline Simd<512, i64> cmpLt(const Simd<512, i64> &a, const Simd<512, i64> &b) {
        return Simd<512, i64>(
            a.i[0] < b.i[0] ? ~0 : 0, a.i[1] < b.i[1] ? ~0 : 0, a.i[2] < b.i[2] ? ~0 : 0,
            a.i[3] < b.i[3] ? ~0 : 0, a.i[4] < b.i[4] ? ~0 : 0, a.i[5] < b.i[5] ? ~0 : 0,
            a.i[6] < b.i[6] ? ~0 : 0, a.i[7] < b.i[7] ? ~0 : 0);
    }
    template <>
    inline Simd<128, i64> cmpLe(const Simd<128, i64> &a, const Simd<128, i64> &b) {
        return Simd<128, i64>(a.i[0] <= b.i[0] ? ~0 : 0, a.i[1] <= b.i[1] ? ~0 : 0);
    }
    template <>
    inline Simd<256, i64> cmpLe(const Simd<256, i64> &a, const Simd<256, i64> &b) {
        return Simd<256, i64>(
            a.i[0] <= b.i[0] ? ~0 : 0, a.i[1] <= b.i[1] ? ~0 : 0, a.i[2] <= b.i[2] ? ~0 : 0,
            a.i[3] <= b.i[3] ? ~0 : 0);
    }
    template <>
    inline Simd<512, i64> cmpLe(const Simd<512, i64> &a, const Simd<512, i64> &b) {
        return Simd<512, i64>(
            a.i[0] <= b.i[0] ? ~0 : 0, a.i[1] <= b.i[1] ? ~0 : 0, a.i[2] <= b.i[2] ? ~0 : 0,
            a.i[3] <= b.i[3] ? ~0 : 0, a.i[4] <= b.i[4] ? ~0 : 0, a.i[5] <= b.i[5] ? ~0 : 0,
            a.i[6] <= b.i[6] ? ~0 : 0, a.i[7] <= b.i[7] ? ~0 : 0);
    }
    template <>
    inline Simd<128, i64> cmpGt(const Simd<128, i64> &a, const Simd<128, i64> &b) {
        return Simd<128, i64>(a.i[0] > b.i[0] ? ~0 : 0, a.i[1] > b.i[1] ? ~0 : 0);
    }
    template <>
    inline Simd<256, i64> cmpGt(const Simd<256, i64> &a, const Simd<256, i64> &b) {
        return Simd<256, i64>(
            a.i[0] > b.i[0] ? ~0 : 0, a.i[1] > b.i[1] ? ~0 : 0, a.i[2] > b.i[2] ? ~0 : 0,
            a.i[3] > b.i[3] ? ~0 : 0);
    }
    template <>
    inline Simd<512, i64> cmpGt(const Simd<512, i64> &a, const Simd<512, i64> &b) {
        return Simd<512, i64>(
            a.i[0] > b.i[0] ? ~0 : 0, a.i[1] > b.i[1] ? ~0 : 0, a.i[2] > b.i[2] ? ~0 : 0,
            a.i[3] > b.i[3] ? ~0 : 0, a.i[4] > b.i[4] ? ~0 : 0, a.i[5] > b.i[5] ? ~0 : 0,
            a.i[6] > b.i[6] ? ~0 : 0, a.i[7] > b.i[7] ? ~0 : 0);
    }
    template <>
    inline Simd<128, i64> cmpGe(const Simd<128, i64> &a, const Simd<128, i64> &b) {
        return Simd<128, i64>(a.i[0] >= b.i[0] ? ~0 : 0, a.i[1] >= b.i[1] ? ~0 : 0);
    }
    template <>
    inline Simd<256, i64> cmpGe(const Simd<256, i64> &a, const Simd<256, i64> &b) {
        return Simd<256, i64>(
            a.i[0] >= b.i[0] ? ~0 : 0, a.i[1] >= b.i[1] ? ~0 : 0, a.i[2] >= b.i[2] ? ~0 : 0,
            a.i[3] >= b.i[3] ? ~0 : 0);
    }
    template <>
    inline Simd<512, i64> cmpGe(const Simd<512, i64> &a, const Simd<512, i64> &b) {
        return Simd<512, i64>(
            a.i[0] >= b.i[0] ? ~0 : 0, a.i[1] >= b.i[1] ? ~0 : 0, a.i[2] >= b.i[2] ? ~0 : 0,
            a.i[3] >= b.i[3] ? ~0 : 0, a.i[4] >= b.i[4] ? ~0 : 0, a.i[5] >= b.i[5] ? ~0 : 0,
            a.i[6] >= b.i[6] ? ~0 : 0, a.i[7] >= b.i[7] ? ~0 : 0);
    }


    template <>
    inline u32 movemask(const Simd<128, i64> &a) {
        i64 mask = 0;

        mask |= ((a.i[0] >> 7) & 1) << 0;
        mask |= ((a.i[0] >> 15) & 1) << 1;
        mask |= ((a.i[0] >> 23) & 1) << 2;
        mask |= ((a.i[0] >> 31) & 1) << 3;

        mask |= ((a.i[1] >> 7) & 1) << 4;
        mask |= ((a.i[1] >> 15) & 1) << 5;
        mask |= ((a.i[1] >> 23) & 1) << 6;
        mask |= ((a.i[1] >> 31) & 1) << 7;

        mask |= ((a.i[2] >> 7) & 1) << 8;
        mask |= ((a.i[2] >> 15) & 1) << 9;
        mask |= ((a.i[2] >> 23) & 1) << 10;
        mask |= ((a.i[2] >> 31) & 1) << 11;

        mask |= ((a.i[3] >> 7) & 1) << 12;
        mask |= ((a.i[3] >> 15) & 1) << 13;
        mask |= ((a.i[3] >> 23) & 1) << 14;
        mask |= ((a.i[3] >> 31) & 1) << 15;

        return (u32)mask;
    }
    template <>
    inline u32 movemask(const Simd<256, i64> &a) {
        i64 mask = 0;

        mask |= ((a.i[0] >> 7) & 1) << 0;
        mask |= ((a.i[0] >> 15) & 1) << 1;
        mask |= ((a.i[0] >> 23) & 1) << 2;
        mask |= ((a.i[0] >> 31) & 1) << 3;

        mask |= ((a.i[1] >> 7) & 1) << 4;
        mask |= ((a.i[1] >> 15) & 1) << 5;
        mask |= ((a.i[1] >> 23) & 1) << 6;
        mask |= ((a.i[1] >> 31) & 1) << 7;

        mask |= ((a.i[2] >> 7) & 1) << 8;
        mask |= ((a.i[2] >> 15) & 1) << 9;
        mask |= ((a.i[2] >> 23) & 1) << 10;
        mask |= ((a.i[2] >> 31) & 1) << 11;

        mask |= ((a.i[3] >> 7) & 1) << 12;
        mask |= ((a.i[3] >> 15) & 1) << 13;
        mask |= ((a.i[3] >> 23) & 1) << 14;
        mask |= ((a.i[3] >> 31) & 1) << 15;

        mask |= ((a.i[4] >> 7) & 1) << 16;
        mask |= ((a.i[4] >> 15) & 1) << 17;
        mask |= ((a.i[4] >> 23) & 1) << 18;
        mask |= ((a.i[4] >> 31) & 1) << 19;

        mask |= ((a.i[5] >> 7) & 1) << 20;
        mask |= ((a.i[5] >> 15) & 1) << 21;
        mask |= ((a.i[5] >> 23) & 1) << 22;
        mask |= ((a.i[5] >> 31) & 1) << 23;

        mask |= ((a.i[6] >> 7) & 1) << 24;
        mask |= ((a.i[6] >> 15) & 1) << 25;
        mask |= ((a.i[6] >> 23) & 1) << 26;
        mask |= ((a.i[6] >> 31) & 1) << 27;

        mask |= ((a.i[7] >> 7) & 1) << 28;
        mask |= ((a.i[7] >> 15) & 1) << 29;
        mask |= ((a.i[7] >> 23) & 1) << 30;
        mask |= ((a.i[7] >> 31) & 1) << 31;

        return (u32)mask;
    }
    template <>
    inline u64 movemask(const Simd<512, i64> &a) {
        u64 mask = 0;

        mask |= ((a.i[0] >> 7) & 1) << 0;
        mask |= ((a.i[0] >> 15) & 1) << 1;
        mask |= ((a.i[0] >> 23) & 1) << 2;
        mask |= ((a.i[0] >> 31) & 1) << 3;

        mask |= ((a.i[1] >> 7) & 1) << 4;
        mask |= ((a.i[1] >> 15) & 1) << 5;
        mask |= ((a.i[1] >> 23) & 1) << 6;
        mask |= ((a.i[1] >> 31) & 1) << 7;

        mask |= ((a.i[2] >> 7) & 1) << 8;
        mask |= ((a.i[2] >> 15) & 1) << 9;
        mask |= ((a.i[2] >> 23) & 1) << 10;
        mask |= ((a.i[2] >> 31) & 1) << 11;

        mask |= ((a.i[3] >> 7) & 1) << 12;
        mask |= ((a.i[3] >> 15) & 1) << 13;
        mask |= ((a.i[3] >> 23) & 1) << 14;
        mask |= ((a.i[3] >> 31) & 1) << 15;

        mask |= ((a.i[4] >> 7) & 1) << 16;
        mask |= ((a.i[4] >> 15) & 1) << 17;
        mask |= ((a.i[4] >> 23) & 1) << 18;
        mask |= ((a.i[4] >> 31) & 1) << 19;

        mask |= ((a.i[5] >> 7) & 1) << 20;
        mask |= ((a.i[5] >> 15) & 1) << 21;
        mask |= ((a.i[5] >> 23) & 1) << 22;
        mask |= ((a.i[5] >> 31) & 1) << 23;
        mask |= ((a.i[6] >> 7) & 1) << 24;
        mask |= ((a.i[6] >> 15) & 1) << 25;
        mask |= ((a.i[6] >> 23) & 1) << 26;
        mask |= ((a.i[6] >> 31) & 1) << 27;
        mask |= ((a.i[7] >> 7) & 1) << 28;
        mask |= ((a.i[7] >> 15) & 1) << 29;
        mask |= ((a.i[7] >> 23) & 1) << 30;
        mask |= ((a.i[7] >> 31) & 1) << 31;
        mask |= ((a.i[8] >> 7) & 1) << 32;
        mask |= ((a.i[8] >> 15) & 1) << 33;
        mask |= ((a.i[8] >> 23) & 1) << 34;
        mask |= ((a.i[8] >> 31) & 1) << 35;
        mask |= ((a.i[9] >> 7) & 1) << 36;
        mask |= ((a.i[9] >> 15) & 1) << 37;
        mask |= ((a.i[9] >> 23) & 1) << 38;
        mask |= ((a.i[9] >> 31) & 1) << 39;
        mask |= ((a.i[10] >> 7) & 1) << 40;
        mask |= ((a.i[10] >> 15) & 1) << 41;
        mask |= ((a.i[10] >> 23) & 1) << 42;
        mask |= ((a.i[10] >> 31) & 1) << 43;
        mask |= ((a.i[11] >> 7) & 1) << 44;
        mask |= ((a.i[11] >> 15) & 1) << 45;
        mask |= ((a.i[11] >> 23) & 1) << 46;
        mask |= ((a.i[11] >> 31) & 1) << 47;
        mask |= ((a.i[12] >> 7) & 1) << 48;
        mask |= ((a.i[12] >> 15) & 1) << 49;
        mask |= ((a.i[12] >> 23) & 1) << 50;
        mask |= ((a.i[12] >> 31) & 1) << 51;
        mask |= ((a.i[13] >> 7) & 1) << 52;
        mask |= ((a.i[13] >> 15) & 1) << 53;
        mask |= ((a.i[13] >> 23) & 1) << 54;
        mask |= ((a.i[13] >> 31) & 1) << 55;
        mask |= ((a.i[14] >> 7) & 1) << 56;
        mask |= ((a.i[14] >> 15) & 1) << 57;
        mask |= ((a.i[14] >> 23) & 1) << 58;
        mask |= ((a.i[14] >> 31) & 1) << 59;
        mask |= ((a.i[15] >> 7) & 1) << 60;
        mask |= ((a.i[15] >> 15) & 1) << 61;
        mask |= ((a.i[15] >> 23) & 1) << 62;
        mask |= ((a.i[15] >> 31) & 1) << 63;

        return mask;
    }
}}

#endif
