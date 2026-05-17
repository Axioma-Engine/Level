/**
 * @file Atomic.h (GCC backend)
 * @brief GCC/Clang __atomic_* builtin wrapper functions.
 *
 * This header wraps GCC and Clang's __atomic_* builtins into a unified
 * atomic operation interface compatible with the Quark library.
 *
 * Namespace hierarchy:
 * - Quark::Atomic:: : Memory ordering constants and atomic operations
 *   - RELAXED, CONSUME, ACQUIRE, RELEASE, ACQ_REL, SEQ_CST
 *
 * - Quark::Atomic::pause() : Pause instruction for spin-wait loops
 *
 * - Quark::Atomic::load<T>(ptr, seq)
 * - Quark::Atomic::store<T>(ptr, value, seq)
 * - Quark::Atomic::exchange<T>(ptr, value, seq)
 * - Quark::Atomic::compareExchange<T>(ptr, expected, desired, success_seq, failure_seq)
 * - Quark::Atomic::fetchAdd<T>(ptr, value, seq)
 * - Quark::Atomic::fetchSub<T>(ptr, value, seq)
 * - Quark::Atomic::fetchAnd<T>(ptr, value, seq)
 * - Quark::Atomic::fetchOr<T>(ptr, value, seq)
 * - Quark::Atomic::fetchXor<T>(ptr, value, seq)
 */

#ifndef AXM_QRK_GCC_ATOMIC_H
#define AXM_QRK_GCC_ATOMIC_H

#include "../Types.h"
#include "Attributes.h"

namespace Quark { namespace Atomic {

    static const AXM_CONSTEXPR i32 RELAXED = __ATOMIC_RELAXED;
    static const AXM_CONSTEXPR i32 CONSUME = __ATOMIC_CONSUME;
    static const AXM_CONSTEXPR i32 ACQUIRE = __ATOMIC_ACQUIRE;
    static const AXM_CONSTEXPR i32 RELEASE = __ATOMIC_RELEASE;
    static const AXM_CONSTEXPR i32 ACQ_REL = __ATOMIC_ACQ_REL;
    static const AXM_CONSTEXPR i32 SEQ_CST = __ATOMIC_SEQ_CST;

    static inline void pause() {
#if defined(__i386__) || defined(__x86_64__)
        __builtin_ia32_pause();
#elif defined(__arm__) || defined(__aarch64__)
        __asm__ volatile("yield" ::: "memory");
#elif defined(__powerpc__) || defined(__ppc__)
        __builtin_ppc_yield();
#elif defined(__riscv)
        __asm__ volatile("pause" ::: "memory");
#else
        __asm__ volatile("" ::: "memory");
#endif
    }

    template <typename T>
    static inline T load(T* ptr, i32 seq = __ATOMIC_SEQ_CST) {
        return __atomic_load_n(ptr, seq);
    }
    template <typename T>
    static inline void store(T* ptr, T value, i32 seq = __ATOMIC_SEQ_CST) {
        __atomic_store_n(ptr, value, seq);
    }
    template <typename T>
    static inline T exchange(T* ptr, T value, i32 seq = __ATOMIC_SEQ_CST) {
        return __atomic_exchange_n(ptr, value, seq);
    }
    template <typename T>
    static inline b8 compareExchange(
        T*  ptr,
        T*  expected,
        T   desired,
        i32 success_seq = __ATOMIC_SEQ_CST,
        i32 failure_seq = __ATOMIC_RELAXED) {
        return __atomic_compare_exchange_n(ptr, expected, desired, 0, success_seq, failure_seq);
    }
    template <typename T>
    static inline T fetchAdd(T* ptr, T value, i32 seq = __ATOMIC_SEQ_CST) {
        return __atomic_fetch_add(ptr, value, seq);
    }
    template <typename T>
    static inline T fetchSub(T* ptr, T value, i32 seq = __ATOMIC_SEQ_CST) {
        return __atomic_fetch_sub(ptr, value, seq);
    }
    template <typename T>
    static inline T fetchAnd(T* ptr, T value, i32 seq = __ATOMIC_SEQ_CST) {
        return __atomic_fetch_and(ptr, value, seq);
    }
    template <typename T>
    static inline T fetchOr(T* ptr, T value, i32 seq = __ATOMIC_SEQ_CST) {
        return __atomic_fetch_or(ptr, value, seq);
    }
    template <typename T>
    static inline T fetchXor(T* ptr, T value, i32 seq = __ATOMIC_SEQ_CST) {
        return __atomic_fetch_xor(ptr, value, seq);
    }
}}

#endif
