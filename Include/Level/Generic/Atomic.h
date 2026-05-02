/**
 * @file Atomic.h (Generic backend)
 * @brief Generic atomic operation macros using <stdatomic.h> when available.
 *
 * This header provides a portable wrapper for atomic operations used by the
 * Level library. When the platform provides <stdatomic.h> the macros map to
 * the C11 atomic API (atomic_load_explicit, atomic_store_explicit, etc.).
 * If <stdatomic.h> is not available the header falls back to simple
 * non-atomic operations to preserve API compatibility (but without atomicity).
 *
 * Macro hierarchy:
 * - AXM_LVL_ATOMIC_SEQ_* : Memory ordering constants (for API compatibility)
 *   - AXM_LVL_ATOMIC_SEQ_RELAXED
 *   - AXM_LVL_ATOMIC_SEQ_CONSUME
 *   - AXM_LVL_ATOMIC_SEQ_ACQUIRE
 *   - AXM_LVL_ATOMIC_SEQ_RELEASE
 *   - AXM_LVL_ATOMIC_SEQ_ACQ_REL
 *   - AXM_LVL_ATOMIC_SEQ_SEQ_CST
 *
 * - AXM_LVL_ATOMIC_*_SEQ : Sequentially-explicit operations
 *   - LOAD_SEQ, STORE_SEQ, EXCHANGE_SEQ, COMPARE_EXCHANGE_SEQ
 *   - FETCH_ADD_SEQ, FETCH_SUB_SEQ, FETCH_AND_SEQ, FETCH_OR_SEQ, FETCH_XOR_SEQ
 *
 * - AXM_LVL_ATOMIC_* : Default operations (use sequentially-consistent ordering)
 *   - LOAD, STORE, EXCHANGE, COMPARE_EXCHANGE
 *   - FETCH_ADD, FETCH_SUB, FETCH_AND, FETCH_OR, FETCH_XOR
 */

#ifndef AXM_LVL_GENERIC_ATOMIC_H
#define AXM_LVL_GENERIC_ATOMIC_H

#include "../Features.h"

#if AXM_HAS_INCLUDE(<stdatomic.h>)
#    include <stdatomic.h>

// Memory ordering constants
#    define AXM_LVL_ATOMIC_SEQ_RELAXED memory_order_relaxed
#    define AXM_LVL_ATOMIC_SEQ_CONSUME memory_order_consume
#    define AXM_LVL_ATOMIC_SEQ_ACQUIRE memory_order_acquire
#    define AXM_LVL_ATOMIC_SEQ_RELEASE memory_order_release
#    define AXM_LVL_ATOMIC_SEQ_ACQ_REL memory_order_acq_rel
#    define AXM_LVL_ATOMIC_SEQ_SEQ_CST memory_order_seq_cst

// Sequentially-explicit atomic operations
#    define AXM_LVL_ATOMIC_LOAD_SEQ(ptr, seq)         atomic_load_explicit((ptr), (seq))
#    define AXM_LVL_ATOMIC_STORE_SEQ(ptr, value, seq) atomic_store_explicit((ptr), (value), (seq))
#    define AXM_LVL_ATOMIC_EXCHANGE_SEQ(ptr, value, seq)                                           \
        atomic_exchange_explicit((ptr), (value), (seq))
#    define AXM_LVL_ATOMIC_COMPARE_EXCHANGE_SEQ(ptr, expected, desired, success_seq, failure_seq)  \
        atomic_compare_exchange_strong_explicit(                                                   \
            (ptr), (expected), (desired), (success_seq), (failure_seq))
#    define AXM_LVL_ATOMIC_FETCH_ADD_SEQ(ptr, value, seq)                                          \
        atomic_fetch_add_explicit((ptr), (value), (seq))
#    define AXM_LVL_ATOMIC_FETCH_SUB_SEQ(ptr, value, seq)                                          \
        atomic_fetch_sub_explicit((ptr), (value), (seq))
#    define AXM_LVL_ATOMIC_FETCH_AND_SEQ(ptr, value, seq)                                          \
        atomic_fetch_and_explicit((ptr), (value), (seq))
#    define AXM_LVL_ATOMIC_FETCH_OR_SEQ(ptr, value, seq)                                           \
        atomic_fetch_or_explicit((ptr), (value), (seq))
#    define AXM_LVL_ATOMIC_FETCH_XOR_SEQ(ptr, value, seq)                                          \
        atomic_fetch_xor_explicit((ptr), (value), (seq))

// Default atomic operations
#    define AXM_LVL_ATOMIC_LOAD(ptr)            atomic_load((ptr))
#    define AXM_LVL_ATOMIC_STORE(ptr, value)    atomic_store((ptr), (value))
#    define AXM_LVL_ATOMIC_EXCHANGE(ptr, value) atomic_exchange((ptr), (value))
#    define AXM_LVL_ATOMIC_COMPARE_EXCHANGE(ptr, expected, desired)                                \
        atomic_compare_exchange_strong((ptr), (expected), (desired))
#    define AXM_LVL_ATOMIC_FETCH_ADD(ptr, value) atomic_fetch_add((ptr), (value))
#    define AXM_LVL_ATOMIC_FETCH_SUB(ptr, value) atomic_fetch_sub((ptr), (value))
#    define AXM_LVL_ATOMIC_FETCH_AND(ptr, value) atomic_fetch_and((ptr), (value))
#    define AXM_LVL_ATOMIC_FETCH_OR(ptr, value)  atomic_fetch_or((ptr), (value))
#    define AXM_LVL_ATOMIC_FETCH_XOR(ptr, value) atomic_fetch_xor((ptr), (value))
#else

// Memory ordering constants
#    define AXM_LVL_ATOMIC_SEQ_RELAXED                   0
#    define AXM_LVL_ATOMIC_SEQ_CONSUME                   1
#    define AXM_LVL_ATOMIC_SEQ_ACQUIRE                   2
#    define AXM_LVL_ATOMIC_SEQ_RELEASE                   3
#    define AXM_LVL_ATOMIC_SEQ_ACQ_REL                   4
#    define AXM_LVL_ATOMIC_SEQ_SEQ_CST                   5

// Sequentially-explicit atomic operations
#    define AXM_LVL_ATOMIC_LOAD_SEQ(ptr, seq)            (*(ptr))
#    define AXM_LVL_ATOMIC_STORE_SEQ(ptr, value, seq)    ((void)((*(ptr)) = (value)))
#    define AXM_LVL_ATOMIC_EXCHANGE_SEQ(ptr, value, seq) ((*(ptr)) = (value))
#    define AXM_LVL_ATOMIC_COMPARE_EXCHANGE_SEQ(ptr, expected, desired, success_seq, failure_seq)  \
        (((*(ptr)) == *(expected)) ? ((*(ptr)) = (desired), 1) : ((*(expected)) = (*(ptr)), 0))
#    define AXM_LVL_ATOMIC_FETCH_ADD_SEQ(ptr, value, seq) ((*(ptr)) += (value))
#    define AXM_LVL_ATOMIC_FETCH_SUB_SEQ(ptr, value, seq) ((*(ptr)) -= (value))
#    define AXM_LVL_ATOMIC_FETCH_AND_SEQ(ptr, value, seq) ((*(ptr)) &= (value))
#    define AXM_LVL_ATOMIC_FETCH_OR_SEQ(ptr, value, seq)  ((*(ptr)) |= (value))
#    define AXM_LVL_ATOMIC_FETCH_XOR_SEQ(ptr, value, seq) ((*(ptr)) ^= (value))

// Default atomic operations
#    define AXM_LVL_ATOMIC_LOAD(ptr) AXM_LVL_ATOMIC_LOAD_SEQ((ptr), AXM_LVL_ATOMIC_SEQ_SEQ_CST)
#    define AXM_LVL_ATOMIC_STORE(ptr, value)                                                       \
        AXM_LVL_ATOMIC_STORE_SEQ((ptr), (value), AXM_LVL_ATOMIC_SEQ_SEQ_CST)
#    define AXM_LVL_ATOMIC_EXCHANGE(ptr, value)                                                    \
        AXM_LVL_ATOMIC_EXCHANGE_SEQ((ptr), (value), AXM_LVL_ATOMIC_SEQ_SEQ_CST)
#    define AXM_LVL_ATOMIC_COMPARE_EXCHANGE(ptr, expected, desired)                                \
        AXM_LVL_ATOMIC_COMPARE_EXCHANGE_SEQ(                                                       \
            (ptr), (expected), (desired), AXM_LVL_ATOMIC_SEQ_SEQ_CST, AXM_LVL_ATOMIC_SEQ_SEQ_CST)
#    define AXM_LVL_ATOMIC_FETCH_ADD(ptr, value)                                                   \
        AXM_LVL_ATOMIC_FETCH_ADD_SEQ((ptr), (value), AXM_LVL_ATOMIC_SEQ_SEQ_CST)
#    define AXM_LVL_ATOMIC_FETCH_SUB(ptr, value)                                                   \
        AXM_LVL_ATOMIC_FETCH_SUB_SEQ((ptr), (value), AXM_LVL_ATOMIC_SEQ_SEQ_CST)
#    define AXM_LVL_ATOMIC_FETCH_AND(ptr, value)                                                   \
        AXM_LVL_ATOMIC_FETCH_AND_SEQ((ptr), (value), AXM_LVL_ATOMIC_SEQ_SEQ_CST)
#    define AXM_LVL_ATOMIC_FETCH_OR(ptr, value)                                                    \
        AXM_LVL_ATOMIC_FETCH_OR_SEQ((ptr), (value), AXM_LVL_ATOMIC_SEQ_SEQ_CST)
#    define AXM_LVL_ATOMIC_FETCH_XOR(ptr, value)                                                   \
        AXM_LVL_ATOMIC_FETCH_XOR_SEQ((ptr), (value), AXM_LVL_ATOMIC_SEQ_SEQ_CST)

#    pragma message "AXM: Generic Atomics on old platforms are very unsafe."
#    pragma message("AXM: Generic Atomics on old platforms are very unsafe.")

#endif

#endif
