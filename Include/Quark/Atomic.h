/**
 * @file Atomic.h
 * @brief Umbrella header for compiler-specific atomic operation functions.
 *
 * This header selects the appropriate backend based on compiler detection
 * and re-exports a unified set of atomic operation functions for safe
 * concurrent access to shared variables.
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
 *
 * Supported backends:
 * - GCC/Clang: GCC/Atomic.h (__atomic_* builtins)
 * - MSVC: MSVC/Atomic.h (_Interlocked* intrinsics)
 * - Generic: Generic/Atomic.h (C11 stdatomic.h or fallback)
 */

#ifndef AXM_QRK_ATOMIC_H
#define AXM_QRK_ATOMIC_H

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
