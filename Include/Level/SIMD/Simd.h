#ifndef AXM_LVL_SIMD_SIMD_H
#define AXM_LVL_SIMD_SIMD_H

#include "../Types.h"

namespace Level { namespace SIMD {
    template <usize N, typename T>
    union Simd;

    template <usize N, typename T>
    inline Simd<N, T> load(const T* ptr);
    template <usize N, typename T>
    inline void store(T* ptr, const Simd<N, T> &simd);
    template <usize N, typename T>
    inline Simd<N, T> set1(const T value);
    template <usize N, typename T>
    inline Simd<N, T> set(const T a0, const T a1);
    template <usize N, typename T>
    inline Simd<N, T> set(const T a0, const T a1, const T a2, const T a3);
    template <usize N, typename T>
    inline Simd<N, T>
        set(const T a0, const T a1, const T a2, const T a3, const T a4, const T a5, const T a6,
            const T a7);
    template <usize N, typename T>
    inline Simd<N, T>
        set(const T a0, const T a1, const T a2, const T a3, const T a4, const T a5, const T a6,
            const T a7, const T a8, const T a9, const T a10, const T a11, const T a12, const T a13,
            const T a14, const T a15);

    template <usize N, typename T>
    inline Simd<N, T> add(const Simd<N, T> &a, const Simd<N, T> &b);
    template <usize N, typename T>
    inline Simd<N, T> sub(const Simd<N, T> &a, const Simd<N, T> &b);
    template <usize N, typename T>
    inline Simd<N, T> abs(const Simd<N, T> &a);
    template <usize N, typename T>
    inline Simd<N, T> neg(const Simd<N, T> &a);
    template <usize N, typename T>
    inline Simd<N, T> min(const Simd<N, T> &a, const Simd<N, T> &b);
    template <usize N, typename T>
    inline Simd<N, T> max(const Simd<N, T> &a, const Simd<N, T> &b);

    template <usize N, typename T>
    inline Simd<N, T> land(const Simd<N, T> &a, const Simd<N, T> &b);
    template <usize N, typename T>
    inline Simd<N, T> lor(const Simd<N, T> &a, const Simd<N, T> &b);
    template <usize N, typename T>
    inline Simd<N, T> lxor(const Simd<N, T> &a, const Simd<N, T> &b);
    template <usize N, typename T>
    inline Simd<N, T> lnot(const Simd<N, T> &a);
    template <usize N, typename T>
    inline Simd<N, T> landnot(const Simd<N, T> &a, const Simd<N, T> &b);

    template <usize N, typename T>
    inline Simd<N, T> shl(const Simd<N, T> &a, int count);
    template <usize N, typename T>
    inline Simd<N, T> shr(const Simd<N, T> &a, int count);
    template <usize N, typename T>
    inline Simd<N, T> sar(const Simd<N, T> &a, int count);

    template <usize N, typename T>
    inline Simd<N, T> mul(const Simd<N, T> &a, const Simd<N, T> &b);
    template <usize N, typename T>
    inline Simd<N, T> div(const Simd<N, T> &a, const Simd<N, T> &b);
    template <usize N, typename T>
    inline Simd<N, T> sqrt(const Simd<N, T> &a);
    template <usize N, typename T>
    inline Simd<N, T> rsqrt(const Simd<N, T> &a);
    template <usize N, typename T>
    inline Simd<N, T> reciprocal(const Simd<N, T> &a);

    template <usize N, typename T>
    inline Simd<N, T> cmpEq(const Simd<N, T> &a, const Simd<N, T> &b);
    template <usize N, typename T>
    inline Simd<N, T> cmpNe(const Simd<N, T> &a, const Simd<N, T> &b);
    template <usize N, typename T>
    inline Simd<N, T> cmpLt(const Simd<N, T> &a, const Simd<N, T> &b);
    template <usize N, typename T>
    inline Simd<N, T> cmpLe(const Simd<N, T> &a, const Simd<N, T> &b);
    template <usize N, typename T>
    inline Simd<N, T> cmpGt(const Simd<N, T> &a, const Simd<N, T> &b);
    template <usize N, typename T>
    inline Simd<N, T> cmpGe(const Simd<N, T> &a, const Simd<N, T> &b);

    template <usize N, typename T>
    inline u32 movemask(const Simd<N, T> &a);
    template <typename T>
    inline u64 movemask(const Simd<512, T> &a);
}}

#endif
