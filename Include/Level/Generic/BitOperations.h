/**
 * @file BitOperations.h
 * @brief Generic/portable bit-operation implementation.
 *
 * @details
 * This backend provides portable software implementations of bit-manipulation
 * primitives using only standard C, with no compiler intrinsics or builtins.
 * All functions use efficient algorithms (De Bruijn sequences, Hamming weight)
 * that compile to good code on any C++ compiler.
 *
 * @par Functions in Level::Bits:: namespace
 * - ctz32, ctz64 : Count trailing zeros
 * - clz32, clz64 : Count leading zeros
 * - popcount32, popcount64 : Population count (count set bits)
 * - swap16, swap32, swap64 : Byte swap / endian conversion
 * - htole16/32/64, letoh16/32/64 : Host-to/from little-endian conversion
 * - htobe16/32/64, betoh16/32/64 : Host-to/from big-endian conversion
 */
#ifndef AXM_LVL_GENERIC_BITOPERATIONS_H
#define AXM_LVL_GENERIC_BITOPERATIONS_H

#include "../System/Endian.h"
#include "../Types.h"

namespace Level { namespace Bits {
    static inline u32 ctz32(u32 value) {
        if (value == 0) return sizeof(u32) * 8;

        static const u32 debruijn_index[32] = { 0,  1,  28, 2,  29, 14, 24, 3,  30, 22, 20,
                                                15, 25, 17, 4,  8,  31, 27, 13, 23, 21, 19,
                                                16, 7,  26, 12, 18, 6,  11, 5,  10, 9 };

        const u32 isolated = value & -value;
        const u32 index    = (isolated * 0x077CB531) >> 27;
        return debruijn_index[index];
    }

    static inline u32 ctz64(u64 value) {
        if (value == 0) return sizeof(u64) * 8;

        static const u32 debruijn_index[64] = { 0,  1,  2,  53, 3,  7,  54, 27, 4,  38, 41, 8,  34,
                                                55, 48, 28, 62, 5,  39, 46, 44, 42, 22, 9,  24, 35,
                                                59, 56, 49, 18, 29, 11, 63, 52, 6,  26, 37, 40, 33,
                                                47, 61, 45, 43, 21, 23, 58, 17, 10, 51, 25, 36, 32,
                                                60, 20, 57, 16, 50, 31, 19, 15, 30, 14, 13, 12 };

        const u64 debruijn = 0x022FDD63CC95386D;
        const u64 isolated = value & -value;
        const u32 index    = (isolated * debruijn) >> 58;
        return debruijn_index[index];
    }

    static inline u32 clz32(u32 value) {
        if (value == 0) return sizeof(u32) * 8;

        static const u32 debruijn_msb_index[32] = { 0,  9,  1,  10, 13, 21, 2,  29, 11, 14, 16,
                                                    18, 22, 25, 3,  30, 8,  12, 20, 28, 15, 17,
                                                    24, 7,  19, 27, 23, 6,  26, 5,  4,  31 };

        value |= value >> 1;
        value |= value >> 2;
        value |= value >> 4;
        value |= value >> 8;
        value |= value >> 16;

        const u32 index = (value * 0x07C4ACDD) >> 27;
        return 31 - debruijn_msb_index[index];
    }

    static inline u32 clz64(u64 value) {
        if (value == 0) return sizeof(u64) * 8;

        const u32 high = value >> 32;
        if (high != 0) return clz32(high);

        const u32 low = value & 0xFFFFFFFF;
        return 32 + clz32(low);
    }

    static inline u32 popcount32(u32 value) {
        value = value - ((value >> 1) & 0x55555555);
        value = (value & 0x33333333) + ((value >> 2) & 0x33333333);
        value = (value + (value >> 4)) & 0x0F0F0F0F;
        value = value + (value >> 8);
        value = value + (value >> 16);
        return value & 0x3F;
    }

    static inline u32 popcount64(u64 value) {
        const u32 low  = value & 0xFFFFFFFF;
        const u32 high = value >> 32;
        return popcount32(low) + popcount32(high);
    }

    static inline u16 swap16(u16 value) { return (value >> 8) | (value << 8); }

    static inline u32 swap32(u32 value) {
        return ((value & 0x000000FF) << 24)
             | ((value & 0x0000FF00) << 8)
             | ((value & 0x00FF0000) >> 8)
             | ((value & 0xFF000000) >> 24);
    }

    static inline u64 swap64(u64 value) {
        const u64 m1 = (u64)0x000000FF << 32;
        const u64 m2 = (u64)0x0000FF00 << 32;
        const u64 m3 = (u64)0x00FF0000 << 32;
        const u64 m4 = (u64)0xFF000000 << 32;

        return ((value & 0x00000000000000FF) << 56)
             | ((value & 0x000000000000FF00) << 40)
             | ((value & 0x0000000000FF0000) << 24)
             | ((value & 0x00000000FF000000) << 8)
             | ((value & m1) >> 8)
             | ((value & m2) >> 24)
             | ((value & m3) >> 40)
             | ((value & m4) >> 56);
    }

    static inline u16 htole16(u16 value) {
#if AXM_LITTLE_ENDIAN
        return value;
#else
        return swap16(value);
#endif
    }
    static inline u32 htole32(u32 value) {
#if AXM_LITTLE_ENDIAN
        return value;
#else
        return swap32(value);
#endif
    }
    static inline u64 htole64(u64 value) {
#if AXM_LITTLE_ENDIAN
        return value;
#else
        return swap64(value);
#endif
    }

    static inline u16 letoh16(u16 value) {
#if AXM_LITTLE_ENDIAN
        return value;
#else
        return swap16(value);
#endif
    }
    static inline u32 letoh32(u32 value) {
#if AXM_LITTLE_ENDIAN
        return value;
#else
        return swap32(value);
#endif
    }
    static inline u64 letoh64(u64 value) {
#if AXM_LITTLE_ENDIAN
        return value;
#else
        return swap64(value);
#endif
    }

    static inline u16 htobe16(u16 value) {
#if AXM_LITTLE_ENDIAN
        return swap16(value);
#else
        return value;
#endif
    }
    static inline u32 htobe32(u32 value) {
#if AXM_LITTLE_ENDIAN
        return swap32(value);
#else
        return value;
#endif
    }
    static inline u64 htobe64(u64 value) {
#if AXM_LITTLE_ENDIAN
        return swap64(value);
#else
        return value;
#endif
    }

    static inline u16 betoh16(u16 value) {
#if AXM_LITTLE_ENDIAN
        return swap16(value);

#else
        return value;
#endif
    }
    static inline u32 betoh32(u32 value) {
#if AXM_LITTLE_ENDIAN
        return swap32(value);
#else
        return value;
#endif
    }
    static inline u64 betoh64(u64 value) {
#if AXM_LITTLE_ENDIAN
        return swap64(value);
#else
        return value;
#endif
    }
}}

#endif
