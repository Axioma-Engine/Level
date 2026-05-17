/**
 * @file Atomic.h (Generic backend)
 * @brief Generic atomic operation wrapper functions.
 *
 * This header provides a portable wrapper for atomic operations used by the
 * Quark library. When the platform provides <stdatomic.h> the functions
 * wrap the C11 atomic API (atomic_load_explicit, atomic_store_explicit, etc.).
 * If <stdatomic.h> is not available the functions fall back to simple
 * non-atomic operations to preserve API compatibility (but without atomicity).
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

#ifndef AXM_QRK_GENERIC_ATOMIC_H
#define AXM_QRK_GENERIC_ATOMIC_H

#include "../Types.h"
#include "Attributes.h"

#if AXM_HAS_INCLUDE(<stdatomic.h>)
#    include <stdatomic.h> // IWYU pragma: export

namespace Quark { namespace Atomic {

    static const AXM_CONSTEXPR i32 RELAXED = memory_order_relaxed;
    static const AXM_CONSTEXPR i32 CONSUME = memory_order_consume;
    static const AXM_CONSTEXPR i32 ACQUIRE = memory_order_acquire;
    static const AXM_CONSTEXPR i32 RELEASE = memory_order_release;
    static const AXM_CONSTEXPR i32 ACQ_REL = memory_order_acq_rel;
    static const AXM_CONSTEXPR i32 SEQ_CST = memory_order_seq_cst;

    static inline void pause() {
        // No-op for generic backend
    }

    template <typename T>
    static inline T load(T* ptr, i32 seq = memory_order_seq_cst) {
        return atomic_load_explicit(reinterpret_cast<_Atomic(T)*>(ptr), seq);
    }
    template <typename T>
    static inline void store(T* ptr, T value, i32 seq = memory_order_seq_cst) {
        atomic_store_explicit(reinterpret_cast<_Atomic(T)*>(ptr), value, seq);
    }
    template <typename T>
    static inline T exchange(T* ptr, T value, i32 seq = memory_order_seq_cst) {
        return atomic_exchange_explicit(reinterpret_cast<_Atomic(T)*>(ptr), value, seq);
    }
    template <typename T>
    static inline b8 compareExchange(
        T* ptr, T* expected, T desired, i32 success_seq = memory_order_seq_cst,
        i32 failure_seq = memory_order_relaxed) {
        return atomic_compare_exchange_strong_explicit(
            reinterpret_cast<_Atomic(T)*>(ptr), expected, desired, success_seq, failure_seq);
    }
    template <typename T>
    static inline T fetchAdd(T* ptr, T value, i32 seq = memory_order_seq_cst) {
        return atomic_fetch_add_explicit(reinterpret_cast<_Atomic(T)*>(ptr), value, seq);
    }
    template <typename T>
    static inline T fetchSub(T* ptr, T value, i32 seq = memory_order_seq_cst) {
        return atomic_fetch_sub_explicit(reinterpret_cast<_Atomic(T)*>(ptr), value, seq);
    }
    template <typename T>
    static inline T fetchAnd(T* ptr, T value, i32 seq = memory_order_seq_cst) {
        return atomic_fetch_and_explicit(reinterpret_cast<_Atomic(T)*>(ptr), value, seq);
    }
    template <typename T>
    static inline T fetchOr(T* ptr, T value, i32 seq = memory_order_seq_cst) {
        return atomic_fetch_or_explicit(reinterpret_cast<_Atomic(T)*>(ptr), value, seq);
    }
    template <typename T>
    static inline T fetchXor(T* ptr, T value, i32 seq = memory_order_seq_cst) {
        return atomic_fetch_xor_explicit(reinterpret_cast<_Atomic(T)*>(ptr), value, seq);
    }
}}

#else

namespace Quark { namespace Atomic {

    static const AXM_CONSTEXPR i32 RELAXED = 0;
    static const AXM_CONSTEXPR i32 CONSUME = 1;
    static const AXM_CONSTEXPR i32 ACQUIRE = 2;
    static const AXM_CONSTEXPR i32 RELEASE = 3;
    static const AXM_CONSTEXPR i32 ACQ_REL = 4;
    static const AXM_CONSTEXPR i32 SEQ_CST = 5;

    static inline void pause() {
        // No-op for generic backend
    }

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
        T old = *ptr;
        *ptr  = value;
        return old;
    }
    template <typename T>
    static inline b8
        compareExchange(T* ptr, T* expected, T desired, i32 success_seq = 5, i32 failure_seq = 0) {
        if (*ptr == *expected) {
            *ptr = desired;
            return 1;
        }
        *expected = *ptr;
        return 0;
    }
    template <typename T>
    static inline T fetchAdd(T* ptr, T value, i32 seq = 5) {
        T old  = *ptr;
        *ptr  += value;
        return old;
    }
    template <typename T>
    static inline T fetchSub(T* ptr, T value, i32 seq = 5) {
        T old  = *ptr;
        *ptr  -= value;
        return old;
    }
    template <typename T>
    static inline T fetchAnd(T* ptr, T value, i32 seq = 5) {
        T old  = *ptr;
        *ptr  &= value;
        return old;
    }
    template <typename T>
    static inline T fetchOr(T* ptr, T value, i32 seq = 5) {
        T old  = *ptr;
        *ptr  |= value;
        return old;
    }
    template <typename T>
    static inline T fetchXor(T* ptr, T value, i32 seq = 5) {
        T old  = *ptr;
        *ptr  ^= value;
        return old;
    }
}}

#    pragma message "AXM: Generic Atomics are very unsafe."
#    pragma message("AXM: Generic Atomics are very unsafe.")

#endif

#endif
