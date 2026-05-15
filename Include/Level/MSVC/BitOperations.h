/**
 * @file BitOperations.h
 * @brief MSVC bit-operation implementation.
 *
 * @details
 * This backend wraps MSVC intrinsics for bit-manipulation primitives,
 * using _BitScanForward/_BitScanReverse for leading/trailing zero counts,
 * __popcnt/__popcnt64 for population counts, and _byteswap_* intrinsics
 * for endianness conversion.
 *
 * @par Functions in Level::Bits:: namespace
 * - ctz32, ctz64 : Count trailing zeros
 * - clz32, clz64 : Count leading zeros
 * - popcount32, popcount64 : Population count (count set bits)
 * - swap16, swap32, swap64 : Byte swap / endian conversion
 * - htole16/32/64, letoh16/32/64 : Host-to/from little-endian conversion
 * - htobe16/32/64, betoh16/32/64 : Host-to/from big-endian conversion
 */
#ifndef AXM_LVL_MSVC_BITOPERATIONS_H
#define AXM_LVL_MSVC_BITOPERATIONS_H

#include <intrin.h>

#include "../System/Endian.h"
#include "../Types.h"

namespace Level { namespace Bits {
    static inline u32 ctz32(u32 value) {
        if (value == 0) return sizeof(u32) * 8;

        unsigned long index = 0;
        _BitScanForward(&index, value);
        return index;
    }

    static inline u32 ctz64(u64 value) {
        if (value == 0) return sizeof(u64) * 8;

#if defined(_M_X64) || defined(_M_ARM64) || defined(_M_ARM64EC)
        unsigned long index = 0;
        _BitScanForward64(&index, value);
        return index;
#else
        unsigned long index = 0;
        u32           low   = value & 0xFFFFFFFF;
        if (low != 0) {
            _BitScanForward(&index, low);
            return index;
        }

        u32 high = value >> 32;
        _BitScanForward(&index, high);
        return index + 32;
#endif
    }

    static inline u32 clz32(u32 value) {
        if (value == 0) return sizeof(u32) * 8;

        unsigned long index = 0;
        _BitScanReverse(&index, value);
        return (sizeof(u32) * 8 - 1) - index;
    }

    static inline u32 clz64(u64 value) {
        if (value == 0) return sizeof(u64) * 8;

#if defined(_M_X64) || defined(_M_ARM64) || defined(_M_ARM64EC)
        unsigned long index = 0;
        _BitScanReverse64(&index, value);
        return (sizeof(u64) * 8 - 1) - index;
#else
        unsigned long index = 0;
        u32           high  = value >> 32;
        if (high != 0) {
            _BitScanReverse(&index, high);
            return 63 - (index + 32);
        }

        u32 low = value & 0xFFFFFFFF;
        _BitScanReverse(&index, low);
        return 31 - index + 32;
#endif
    }

    static inline u32 popcount32(u32 value) { return __popcnt(value); }

    static inline u32 popcount64(u64 value) {
#if defined(_M_X64) || defined(_M_ARM64) || defined(_M_ARM64EC)
        return __popcnt64(value);
#else
        return __popcnt(value & 0xFFFFFFFF) + __popcnt(value >> 32);
#endif
    }

    static inline u16 swap16(u16 value) { return _byteswap_ushort(value); }

    static inline u32 swap32(u32 value) { return _byteswap_ulong(value); }

    static inline u64 swap64(u64 value) { return _byteswap_uint64(value); }

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
