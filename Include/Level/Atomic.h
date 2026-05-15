/**
 * @file Atomic.h
 * @brief Umbrella header for compiler-specific atomic operation functions.
 *
 * This header selects the appropriate backend based on compiler detection
 * and re-exports a unified set of atomic operation functions for safe
 * concurrent access to shared variables.
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
 *
 * Supported backends:
 * - GCC/Clang: GCC/Atomic.h (__atomic_* builtins)
 * - MSVC: MSVC/Atomic.h (_Interlocked* intrinsics)
 * - Generic: Generic/Atomic.h (C11 stdatomic.h or fallback)
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
