/**
 * @file Atomic.h (MSVC backend)
 * @brief MSVC _Interlocked* intrinsic wrapper functions.
 *
 * This header wraps MSVC's _Interlocked* intrinsics into a unified
 * atomic operation interface compatible with the Level library.
 * Note that MSVC does not directly support fine-grained memory ordering,
 * so all operations use sequential consistency.
 *
 * Namespace hierarchy:
 * - Level::Atomic:: : Memory ordering constants and atomic operations
 *   - RELAXED, CONSUME, ACQUIRE, RELEASE, ACQ_REL, SEQ_CST
 *
 * - Level::Atomic::pause() : Pause instruction for spin-wait loops
 *
 * - Level::Atomic::load<T>(ptr, seq)
 * - Level::Atomic::store<T>(ptr, value, seq)
 * - Level::Atomic::exchange<T>(ptr, value, seq)
 * - Level::Atomic::compareExchange<T>(ptr, expected, desired, success_seq, failure_seq)
 * - Level::Atomic::fetchAdd<T>(ptr, value, seq)
 * - Level::Atomic::fetchSub<T>(ptr, value, seq)
 * - Level::Atomic::fetchAnd<T>(ptr, value, seq)
 * - Level::Atomic::fetchOr<T>(ptr, value, seq)
 * - Level::Atomic::fetchXor<T>(ptr, value, seq)
 */

#ifndef AXM_LVL_MSVC_ATOMIC_H
#define AXM_LVL_MSVC_ATOMIC_H

#include <intrin.h>

#include "../Types.h"
#include "Attributes.h"

namespace Level { namespace Atomic {

    static const AXM_CONSTEXPR i32 RELAXED = 0;
    static const AXM_CONSTEXPR i32 CONSUME = 1;
    static const AXM_CONSTEXPR i32 ACQUIRE = 2;
    static const AXM_CONSTEXPR i32 RELEASE = 3;
    static const AXM_CONSTEXPR i32 ACQ_REL = 4;
    static const AXM_CONSTEXPR i32 SEQ_CST = 5;

    static inline void pause() { _mm_pause(); }

    template <typename T>
    static inline T load(T* ptr, i32 seq = 5) {
        return *ptr;
    }
    template <typename T>
    static inline void store(T* ptr, T value, i32 seq = 5) {
        *ptr = value;
    }
    template <typename T>
    static inline T exchange(T* ptr, T value, i32 seq = 5) {
        return _InterlockedExchange(reinterpret_cast<long*>(ptr), static_cast<long>(value));
    }
    template <typename T>
    static inline b8
        compareExchange(T* ptr, T* expected, T desired, i32 success_seq = 5, i32 failure_seq = 0) {
        long result = _InterlockedCompareExchange(
            reinterpret_cast<long*>(ptr),
            static_cast<long>(desired),
            *reinterpret_cast<long*>(expected));
        if (result == static_cast<long>(*expected)) return 1;
        *expected = static_cast<T>(result);
        return 0;
    }
    template <typename T>
    static inline T fetchAdd(T* ptr, T value, i32 seq = 5) {
        return _InterlockedExchangeAdd(reinterpret_cast<long*>(ptr), static_cast<long>(value));
    }
    template <typename T>
    static inline T fetchSub(T* ptr, T value, i32 seq = 5) {
        return _InterlockedExchangeAdd(reinterpret_cast<long*>(ptr), -static_cast<long>(value));
    }
    template <typename T>
    static inline T fetchAnd(T* ptr, T value, i32 seq = 5) {
        return _InterlockedAnd(reinterpret_cast<long*>(ptr), static_cast<long>(value));
    }
    template <typename T>
    static inline T fetchOr(T* ptr, T value, i32 seq = 5) {
        return _InterlockedOr(reinterpret_cast<long*>(ptr), static_cast<long>(value));
    }
    template <typename T>
    static inline T fetchXor(T* ptr, T value, i32 seq = 5) {
        return _InterlockedXor(reinterpret_cast<long*>(ptr), static_cast<long>(value));
    }
}}

#endif
