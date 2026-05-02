/**
 * @file Atomic.h (MSVC backend)
 * @brief MSVC _Interlocked* intrinsic wrapper macros.
 *
 * This header wraps MSVC's _Interlocked* intrinsics into a unified atomic
 * operation interface compatible with the Level library. Note that MSVC
 * does not directly support fine-grained memory ordering, so all operations
 * use sequential consistency.
 *
 * Macro hierarchy:
 * - AXM_LVL_ATOMIC_SEQ_* : Memory ordering constants (for API compatibility)
 *   - AXM_LVL_ATOMIC_SEQ_RELAXED -> 0
 *   - AXM_LVL_ATOMIC_SEQ_CONSUME -> 1
 *   - AXM_LVL_ATOMIC_SEQ_ACQUIRE -> 2
 *   - AXM_LVL_ATOMIC_SEQ_RELEASE -> 3
 *   - AXM_LVL_ATOMIC_SEQ_ACQ_REL -> 4
 *   - AXM_LVL_ATOMIC_SEQ_SEQ_CST -> 5
 *
 * - AXM_LVL_ATOMIC_*_SEQ : Sequentially-explicit operations
 *   - LOAD_SEQ, STORE_SEQ, EXCHANGE_SEQ, COMPARE_EXCHANGE_SEQ
 *   - FETCH_ADD_SEQ, FETCH_SUB_SEQ, FETCH_AND_SEQ, FETCH_OR_SEQ, FETCH_XOR_SEQ
 *
 * - AXM_LVL_ATOMIC_* : Default operations
 *   - LOAD, STORE, EXCHANGE, COMPARE_EXCHANGE
 *   - FETCH_ADD, FETCH_SUB, FETCH_AND, FETCH_OR, FETCH_XOR
 */

#ifndef AXM_LVL_MSVC_ATOMIC_H
#define AXM_LVL_MSVC_ATOMIC_H

#include <intrin.h>

// Memory ordering constants (enum-like for API compatibility; MSVC ignores these)
#define AXM_LVL_ATOMIC_SEQ_RELAXED 0
#define AXM_LVL_ATOMIC_SEQ_CONSUME 1
#define AXM_LVL_ATOMIC_SEQ_ACQUIRE 2
#define AXM_LVL_ATOMIC_SEQ_RELEASE 3
#define AXM_LVL_ATOMIC_SEQ_ACQ_REL 4
#define AXM_LVL_ATOMIC_SEQ_SEQ_CST 5

// Sequentially-explicit atomic operations via MSVC _Interlocked* intrinsics
#define AXM_LVL_ATOMIC_LOAD_SEQ(ptr, seq)            (*(ptr))
#define AXM_LVL_ATOMIC_STORE_SEQ(ptr, value, seq)    (*(ptr) = (value))
#define AXM_LVL_ATOMIC_EXCHANGE_SEQ(ptr, value, seq) _InterlockedExchange((ptr), (value))
#define AXM_LVL_ATOMIC_COMPARE_EXCHANGE_SEQ(ptr, expected, desired, success_seq, failure_seq)      \
    (_InterlockedCompareExchange((ptr), (desired), *(expected)) == *(expected)                     \
         ? 1                                                                                       \
         : (*(expected) = _InterlockedCompareExchange((ptr), (desired), *(expected)), 0))
#define AXM_LVL_ATOMIC_FETCH_ADD_SEQ(ptr, value, seq) _InterlockedExchangeAdd((ptr), (value))
#define AXM_LVL_ATOMIC_FETCH_SUB_SEQ(ptr, value, seq) _InterlockedExchangeAdd((ptr), -(value))
#define AXM_LVL_ATOMIC_FETCH_AND_SEQ(ptr, value, seq) _InterlockedAnd((ptr), (value))
#define AXM_LVL_ATOMIC_FETCH_OR_SEQ(ptr, value, seq)  _InterlockedOr((ptr), (value))
#define AXM_LVL_ATOMIC_FETCH_XOR_SEQ(ptr, value, seq) _InterlockedXor((ptr), (value))

// Default atomic operations via MSVC _Interlocked* intrinsics
#define AXM_LVL_ATOMIC_LOAD(ptr)            (*(ptr))
#define AXM_LVL_ATOMIC_STORE(ptr, value)    (*(ptr) = (value))
#define AXM_LVL_ATOMIC_EXCHANGE(ptr, value) _InterlockedExchange((ptr), (value))
#define AXM_LVL_ATOMIC_COMPARE_EXCHANGE(ptr, expected, desired)                                    \
    (_InterlockedCompareExchange((ptr), (desired), *(expected)) == *(expected)                     \
         ? 1                                                                                       \
         : (*(expected) = _InterlockedCompareExchange((ptr), (desired), *(expected)), 0))
#define AXM_LVL_ATOMIC_FETCH_ADD(ptr, value) _InterlockedExchangeAdd((ptr), (value))
#define AXM_LVL_ATOMIC_FETCH_SUB(ptr, value) _InterlockedExchangeAdd((ptr), -(value))
#define AXM_LVL_ATOMIC_FETCH_AND(ptr, value) _InterlockedAnd((ptr), (value))
#define AXM_LVL_ATOMIC_FETCH_OR(ptr, value)  _InterlockedOr((ptr), (value))
#define AXM_LVL_ATOMIC_FETCH_XOR(ptr, value) _InterlockedXor((ptr), (value))

#endif
