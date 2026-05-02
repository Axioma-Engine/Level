/**
 * @file Atomic.h
 * @brief Umbrella header for compiler-specific atomic operation macros.
 *
 * This header selects the appropriate backend based on compiler detection
 * and re-exports a unified set of AXM_LVL_ATOMIC_* macros for safe
 * concurrent access to shared variables.
 *
 * Macro hierarchy:
 * - AXM_LVL_ATOMIC_SEQ_* : Memory ordering semantics
 *   - AXM_LVL_ATOMIC_SEQ_RELAXED
 *   - AXM_LVL_ATOMIC_SEQ_CONSUME
 *   - AXM_LVL_ATOMIC_SEQ_ACQUIRE
 *   - AXM_LVL_ATOMIC_SEQ_RELEASE
 *   - AXM_LVL_ATOMIC_SEQ_ACQ_REL
 *   - AXM_LVL_ATOMIC_SEQ_SEQ_CST
 *
 * - AXM_LVL_ATOMIC_*_SEQ : Sequentially-explicit atomic operations
 *   - AXM_LVL_ATOMIC_LOAD_SEQ(ptr, seq)
 *   - AXM_LVL_ATOMIC_STORE_SEQ(ptr, value, seq)
 *   - AXM_LVL_ATOMIC_EXCHANGE_SEQ(ptr, value, seq)
 *   - AXM_LVL_ATOMIC_COMPARE_EXCHANGE_SEQ(ptr, expected, desired, success_seq, failure_seq)
 *   - AXM_LVL_ATOMIC_FETCH_ADD_SEQ(ptr, value, seq)
 *   - AXM_LVL_ATOMIC_FETCH_SUB_SEQ(ptr, value, seq)
 *   - AXM_LVL_ATOMIC_FETCH_AND_SEQ(ptr, value, seq)
 *   - AXM_LVL_ATOMIC_FETCH_OR_SEQ(ptr, value, seq)
 *   - AXM_LVL_ATOMIC_FETCH_XOR_SEQ(ptr, value, seq)
 *
 * - AXM_LVL_ATOMIC_* : Sequentially-consistent atomic operations (default)
 *   - AXM_LVL_ATOMIC_LOAD(ptr)
 *   - AXM_LVL_ATOMIC_STORE(ptr, value)
 *   - AXM_LVL_ATOMIC_EXCHANGE(ptr, value)
 *   - AXM_LVL_ATOMIC_COMPARE_EXCHANGE(ptr, expected, desired)
 *   - AXM_LVL_ATOMIC_FETCH_ADD(ptr, value)
 *   - AXM_LVL_ATOMIC_FETCH_SUB(ptr, value)
 *   - AXM_LVL_ATOMIC_FETCH_AND(ptr, value)
 *   - AXM_LVL_ATOMIC_FETCH_OR(ptr, value)
 *   - AXM_LVL_ATOMIC_FETCH_XOR(ptr, value)
 *
 * Supported backends:
 * - GCC/Clang: GCC/Atomic.h (__atomic_* builtins)
 * - MSVC: MSVC/Atomic.h (_Interlocked* intrinsics)
 * - Generic: Generic/Atomic.h (C11 stdatomic.h)
 */

#ifndef AXM_LVL_ATOMIC_H
#define AXM_LVL_ATOMIC_H

#include "System/Compiler.h"

// IWYU pragma: begin_exports
#if AXM_COMPILER_GCC_LIKE
#    include "GCC/Atomic.h"
#elif AXM_COMPILER_MSVC_LIKE
#    include "MSVC/Atomic.h"
#else
#    include "Generic/Atomic.h"
#endif
// IWYU pragma: end_exports

#endif
