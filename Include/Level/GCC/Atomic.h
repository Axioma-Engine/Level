/**
 * @file Atomic.h (GCC backend)
 * @brief GCC/Clang __atomic_* builtin wrapper macros.
 *
 * This header wraps GCC and Clang's __atomic_* builtins into a unified
 * atomic operation interface compatible with the Level library.
 *
 * Macro hierarchy:
 * - AXM_LVL_ATOMIC_SEQ_* : Memory ordering constants
 *   - AXM_LVL_ATOMIC_SEQ_RELAXED -> __ATOMIC_RELAXED
 *   - AXM_LVL_ATOMIC_SEQ_CONSUME -> __ATOMIC_CONSUME
 *   - AXM_LVL_ATOMIC_SEQ_ACQUIRE -> __ATOMIC_ACQUIRE
 *   - AXM_LVL_ATOMIC_SEQ_RELEASE -> __ATOMIC_RELEASE
 *   - AXM_LVL_ATOMIC_SEQ_ACQ_REL -> __ATOMIC_ACQ_REL
 *   - AXM_LVL_ATOMIC_SEQ_SEQ_CST -> __ATOMIC_SEQ_CST
 *
 * - AXM_LVL_ATOMIC_*_SEQ : Sequentially-explicit operations
 *   - LOAD_SEQ, STORE_SEQ, EXCHANGE_SEQ, COMPARE_EXCHANGE_SEQ
 *   - FETCH_ADD_SEQ, FETCH_SUB_SEQ, FETCH_AND_SEQ, FETCH_OR_SEQ, FETCH_XOR_SEQ
 *
 * - AXM_LVL_ATOMIC_* : Default sequentially-consistent operations
 *   - LOAD, STORE, EXCHANGE, COMPARE_EXCHANGE
 *   - FETCH_ADD, FETCH_SUB, FETCH_AND, FETCH_OR, FETCH_XOR
 */

#ifndef AXM_LVL_GCC_ATOMIC_H
#define AXM_LVL_GCC_ATOMIC_H

// Memory ordering semantics as GCC __ATOMIC_* constants
#define AXM_LVL_ATOMIC_SEQ_RELAXED __ATOMIC_RELAXED
#define AXM_LVL_ATOMIC_SEQ_CONSUME __ATOMIC_CONSUME
#define AXM_LVL_ATOMIC_SEQ_ACQUIRE __ATOMIC_ACQUIRE
#define AXM_LVL_ATOMIC_SEQ_RELEASE __ATOMIC_RELEASE
#define AXM_LVL_ATOMIC_SEQ_ACQ_REL __ATOMIC_ACQ_REL
#define AXM_LVL_ATOMIC_SEQ_SEQ_CST __ATOMIC_SEQ_CST

// Sequentially-explicit atomic operations via __atomic_* builtins
#define AXM_LVL_ATOMIC_LOAD_SEQ(ptr, seq)            __atomic_load_n((ptr), (seq))
#define AXM_LVL_ATOMIC_STORE_SEQ(ptr, value, seq)    __atomic_store_n((ptr), (value), (seq))
#define AXM_LVL_ATOMIC_EXCHANGE_SEQ(ptr, value, seq) __atomic_exchange_n((ptr), (value), (seq))
#define AXM_LVL_ATOMIC_COMPARE_EXCHANGE_SEQ(ptr, expected, desired, success_seq, failure_seq)      \
    __atomic_compare_exchange_n((ptr), (expected), (desired), 0, (success_seq), (failure_seq))
#define AXM_LVL_ATOMIC_FETCH_ADD_SEQ(ptr, value, seq) __atomic_fetch_add((ptr), (value), (seq))
#define AXM_LVL_ATOMIC_FETCH_SUB_SEQ(ptr, value, seq) __atomic_fetch_sub((ptr), (value), (seq))
#define AXM_LVL_ATOMIC_FETCH_AND_SEQ(ptr, value, seq) __atomic_fetch_and((ptr), (value), (seq))
#define AXM_LVL_ATOMIC_FETCH_OR_SEQ(ptr, value, seq)  __atomic_fetch_or((ptr), (value), (seq))
#define AXM_LVL_ATOMIC_FETCH_XOR_SEQ(ptr, value, seq) __atomic_fetch_xor((ptr), (value), (seq))

// Sequentially-consistent atomic operations (default memory ordering)
#define AXM_LVL_ATOMIC_LOAD(ptr)            __atomic_load_n((ptr), AXM_LVL_ATOMIC_SEQ_SEQ_CST)
#define AXM_LVL_ATOMIC_STORE(ptr, value)    __atomic_store_n((ptr), (value), __ATOMIC_SEQ_CST)
#define AXM_LVL_ATOMIC_EXCHANGE(ptr, value) __atomic_exchange_n((ptr), (value), __ATOMIC_SEQ_CST)
#define AXM_LVL_ATOMIC_COMPARE_EXCHANGE(ptr, expected, desired)                                    \
    __atomic_compare_exchange_n(                                                                   \
        (ptr), (expected), (desired), __ATOMIC_SEQ_CST, AXM_LVL_ATOMIC_SEQ_SEQ_CST)
#define AXM_LVL_ATOMIC_FETCH_ADD(ptr, value) __atomic_fetch_add((ptr), (value), __ATOMIC_SEQ_CST)
#define AXM_LVL_ATOMIC_FETCH_SUB(ptr, value) __atomic_fetch_sub((ptr), (value), __ATOMIC_SEQ_CST)
#define AXM_LVL_ATOMIC_FETCH_AND(ptr, value) __atomic_fetch_and((ptr), (value), __ATOMIC_SEQ_CST)
#define AXM_LVL_ATOMIC_FETCH_OR(ptr, value)  __atomic_fetch_or((ptr), (value), __ATOMIC_SEQ_CST)
#define AXM_LVL_ATOMIC_FETCH_XOR(ptr, value) __atomic_fetch_xor((ptr), (value), __ATOMIC_SEQ_CST)

#endif
