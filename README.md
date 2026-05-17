# Quark Library

**Version:** 1.1.0
**Language:** C++ (C++98 and later)
**Type:** Header-only Plugin for Axiom Framework

## Overview

The **Quark** library is a comprehensive, header-only C++ utility library designed as a plugin for the Axiom framework. It provides portable, low-level abstractions for system detection, compiler-specific features, atomic operations, bit manipulation, and SIMD vectorization. Quark enables developers to write high-performance, cross-platform C++ code by encapsulating compiler and architecture-specific details behind unified, easy-to-use macros and utilities.

## Key Features

### 1. **System Detection** (`System.h` + `System/*.h`)
Comprehensive environment detection macros that allow code to adapt to different platforms:

- **Architecture Detection** (`System/Arch.h`)
  - CPU architecture identification (x86, x86_64, ARM, etc.)
  - Pointer width and alignment information
  - Endianness detection

- **Compiler Detection** (`System/Compiler.h`)
  - Compiler identification (GCC, Clang, MSVC, etc.)
  - Compiler family classification (GCC-like, MSVC-like)
  - Version information for conditional compilation

- **C++ Standard Detection** (`System/Cpp.h`)
  - Language standard quark detection (C++98, C++11, C++14, C++17, C++20, etc.)
  - Feature availability queries (constexpr, threading, etc.)

- **Endianness Detection** (`System/Endian.h`)
  - Byte order identification (little-endian, big-endian)

- **Operating System Detection** (`System/Os.h`)
  - OS identification (Linux, Windows, macOS, BSD, etc.)

- **Sanitizer Detection** (`System/Sanitizer.h`)
  - Runtime sanitizer identification (ASAN, UBSAN, TSAN, MSAN, etc.)

- **SIMD Feature Detection** (`System/Simd.h`)
  - SIMD instruction set support (AVX, AVX2, SSE, SSE2, NEON, etc.)
  - Vector capability queries

### 2. **Feature Detection** (`Features.h`)
Portable compiler feature-probing helpers that normalize access to compiler capabilities:

- `AXM_HAS_ATTRIBUTE(x)` - Check for compiler attributes
- `AXM_HAS_BUILTIN(x)` - Check for compiler builtins
- `AXM_HAS_FEATURE(x)` - Check for language/compiler features
- `AXM_HAS_EXTENSION(x)` - Check for compiler extensions
- `AXM_HAS_CPP_ATTRIBUTE(x)` - Check for standard C++ attributes
- `AXM_HAS_INCLUDE(x)` - Check for header availability
- `AXM_HAS_DECLSPEC(x)` - Check for declspec attributes

All feature checks provide conservative defaults (returning 0) when unavailable, allowing callers to implement portable fallbacks.

### 3. **Type Aliases** (`Types.h`)
Lightweight, portable type aliases for fixed-width and convenience use:

- **Fixed-width unsigned integers:** `u8`, `u16`, `u32`, `u64`
- **Fixed-width signed integers:** `i8`, `i16`, `i32`, `i64`
- **Fast integer types:** `i8f`, `i16f`, `i32f`, `i64f` (at least N bits, performance-oriented)
- **Fast integer types:** `i8l`, `i16l`, `i32l`, `i64l` (at least N bits, size-oriented)
- **Pointer-sized integers:** `vptr`, `usize`, `isize`, `uptr`, `iptr`
- **Floating-point types:** `f32`, `f64`, `f80`
- **Boolean and character:** `b8`, `b32`, `c8`, `c16`, `c32`, `wc`

These aliases improve code clarity and ensure portability across 32-bit and 64-bit platforms.

### 4. **Atomic Operations** (`Atomic.h`)
Safe concurrent access primitives with memory ordering guarantees:

- **Memory ordering constants:** `RELAXED`, `CONSUME`, `ACQUIRE`, `RELEASE`, `ACQ_REL`, `SEQ_CST`
- **Quark operations:**
  - `load<T>()` - Atomic load
  - `store<T>()` - Atomic store
  - `exchange<T>()` - Atomic exchange
  - `compareExchange<T>()` - Compare-and-swap (CAS)
  - `fetchAdd<T>()` - Atomic add-and-return
  - `fetchSub<T>()` - Atomic subtract-and-return
  - `fetchAnd<T>()` - Atomic bitwise AND
  - `fetchOr<T>()` - Atomic bitwise OR
  - `fetchXor<T>()` - Atomic bitwise XOR
  - `pause()` - Pause instruction for spin-wait loops

**Compiler-specific backends:**
- GCC/Clang: Uses `__atomic_*` builtins
- MSVC: Uses `_Interlocked*` intrinsics
- Generic: Falls back to C11 `<stdatomic.h>` or unsafe fallbacks

All operations located in `Quark::Atomic::` namespace.

### 6. **Attributes & Compiler Directives** (`Attributes.h`)
Unified macros for compiler-specific features and optimizations:

- **Standard C++ attributes:** `AXM_NORETURN`, `AXM_NODISCARD`, `AXM_MAYBE_UNUSED`, `AXM_FALLTHROUGH`
- **Control flow/exceptions:** `AXM_NOEXCEPT`, `AXM_ASSUME`, `AXM_UNREACHABLE`
- **Deprecation:** `AXM_DEPRECATED`, `AXM_DEPRECATED_MSG`
- **Visibility/linkage:** `AXM_EXPORT`, `AXM_IMPORT`, `AXM_LOCAL`, `AXM_API`
- **Inlining:** `AXM_FORCE_INLINE`, `AXM_NO_INLINE`
- **Optimization hints:** `AXM_LIKELY`, `AXM_UNLIKELY`, `AXM_HOT`, `AXM_COLD`
- **Function properties:** `AXM_PURE`, `AXM_CONST`, `AXM_MALLOC`, `AXM_ALLOC_SIZE`, `AXM_RETURNS_NONNULL`
- **Format checking:** `AXM_FORMAT_PRINTF`, `AXM_FORMAT_SCANF`
- **Memory/layout:** `AXM_PACKED_BEGIN`, `AXM_PACKED_END`, `AXM_PACKED`, `AXM_RESTRICT`, `AXM_MAY_ALIAS`
- **Language feature shims:** `AXM_CONSTEXPR`, `AXM_THREAD_LOCAL`, `AXM_ALIGNAS`, `AXM_NULLPTR`
- **Diagnostics:** `AXM_DEBUG_TRAP`, `AXM_FUNC_NAME`, `AXM_FUNC_SIG`, `AXM_LINE`

**Compiler-specific backends:**
- GCC/Clang: Full support via `__attribute__` syntax
- MSVC: Support via declspec and pragmas
- Generic: Minimal fallbacks for unsupported compilers

### 8. **Utilities** (`Utils.h`)
Common utility macros and helpers:

- **Token concatenation:** `AXM_CONCAT`, `AXM_CONCAT3`
- **Unused variable suppression:** `AXM_UNUSED`
- **Memory size helpers:** `AXM_KB`, `AXM_MB`, `AXM_GB`, `AXM_TB`
- **Type aliasing:** `AXM_ALIAS` (uses C++11 `using` or C++98 `typedef`)
- **Buffer alignment:** `AXM_ALIGNBUF`
- **Debug messaging:** `AXM_DEBUG_MESSAGE`, `AXM_DEBUG_MESSAGE_ARGS`
- **Assertions:** `AXM_ASSERT`, `AXM_ASSERT_MSG` (active in debug builds only)

## Directory Structure

```
Quark/
├── Include/Quark/
│   ├── Atomic.h              # Atomic operations facade
│   ├── Attributes.h          # Compiler attributes facade
│   ├── Features.h            # Feature detection macros
│   ├── System.h              # System detection umbrella header
│   ├── Types.h               # Type aliases
│   ├── Utils.h               # Utility macros
│   ├── System/               # System detection headers
│   │   ├── Arch.h            # Architecture detection
│   │   ├── Compiler.h        # Compiler detection
│   │   ├── Cpp.h             # C++ standard detection
│   │   ├── Endian.h          # Endianness detection
│   │   ├── Os.h              # OS detection
│   │   ├── Sanitizer.h       # Sanitizer detection
│   │   └── Simd.h            # SIMD feature detection
│   ├── GCC/                  # GCC/Clang implementations
│   │   ├── Atomic.h          # __atomic_* builtins
│   │   ├── Attributes.h      # __attribute__ directives
│   ├── MSVC/                 # MSVC-specific implementations
│   │   ├── Atomic.h          # _Interlocked* intrinsics
│   │   ├── Attributes.h      # declspec and pragmas
│   ├── Generic/              # Portable fallbacks
│   │   ├── Atomic.h          # C11 or safe fallback
│   │   ├── Attributes.h      # Minimal fallbacks
├── CMakeLists.txt            # Build configuration
├── Testing.cpp               # Testing driver (generates compile_commands.json)
└── README.md                 # This file
```

## Usage

### Basic Inclusion

```cpp
// Include everything
#include <Quark/System.h>
#include <Quark/Types.h>
#include <Quark/Attributes.h>
#include <Quark/Atomic.h>
#include <Quark/Utils.h>

// Or include specific headers as needed
#include <Quark/Features.h>  // Feature detection only
```

### Example: System Detection

```cpp
#include <Quark/System.h>

// Query platform at compile time
#if AXM_COMPILER_GCC_LIKE
    // GCC/Clang-specific code
#elif AXM_COMPILER_MSVC_LIKE
    // MSVC-specific code
#endif

#if AXM_BUILD_DEBUG
    // Debug build
#elif AXM_BUILD_RELEASE
    // Release build
#endif

// Endianness queries
#if AXM_ENDIAN_BIG
    // Big-endian platform
#else
    // Little-endian platform
#endif

// SIMD capability queries
#if AXM_SIMD_AVX2
    // AVX2 available
#elif AXM_SIMD_SSE2
    // SSE2 available
#endif
```

### Example: Using Type Aliases

```cpp
#include <Quark/Types.h>

// Portable fixed-width types
Quark::u8 byte = 255;           // Exactly 8 bits
Quark::u32 color = 0xFF0000FF;  // Exactly 32 bits
Quark::i64 timestamp = 123456;  // Exactly 64 bits

// Platform-dependent but optimized
Quark::uptr address = (Quark::uptr)&some_var;  // Word-sized unsigned
Quark::f32 value = 3.14f;                      // 32-bit float
Quark::iptr offset = some_ptr - other_ptr;    // Signed pointer-sized integer
```

### Example: Atomic Operations

```cpp
#include <Quark/Atomic.h>

// Atomic flag for thread synchronization
volatile int ready = 0;

// Thread 1: Signal readiness
Quark::Atomic::store<int>(&ready, 1, Quark::Atomic::RELEASE);

// Thread 2: Wait for signal
while (Quark::Atomic::load<int>(&ready, Quark::Atomic::ACQUIRE) == 0) {
    Quark::Atomic::pause();  // Yield CPU
}
```

### Example: Compiler Attributes

```cpp
#include <Quark/Attributes.h>

// Force inlining for performance-critical code
AXM_FORCE_INLINE int hot_path(int x) {
    return x * 2;
}

// Mark as pure (no side effects, only depends on arguments)
AXM_PURE int compute_hash(const char* str);

// Mark obsolete function
AXM_DEPRECATED void old_function() {
    // Implementation
}

// Add likely/unlikely hints for branch prediction
if (AXM_LIKELY(size > 0)) {
    process_items();
}
```

### Example: Feature Detection

```cpp
#include <Quark/Features.h>

// Conditional code based on compiler capabilities
#if AXM_HAS_ATTRIBUTE(__noreturn__)
    #define MY_NORETURN __attribute__((__noreturn__))
#else
    #define MY_NORETURN
#endif

// Check if particular builtin is available
#if AXM_HAS_BUILTIN(__builtin_expect)
    #define PREDICT(cond, val) __builtin_expect(cond, val)
#else
    #define PREDICT(cond, val) (cond)
#endif
```

## Build Integration

### CMake

The library uses CMake with Axiom framework integration. Key build commands:

```bash
# Debug build
cmake -B Build/Debug -S . -DCMAKE_BUILD_TYPE=Debug
cmake --build Build/Debug

# Release build
cmake -B Build/Release -S . -DCMAKE_BUILD_TYPE=Release
cmake --build Build/Release

# Generate compile_commands.json
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON <build_dir>
```

### Compiler Support

- **Primary:** GCC, Clang
- **Secondary:** MSVC (with partial fallbacks)
- **Fallback:** Generic/portable C implementations for unsupported compilers

### C++ Standard

- **Minimum:** C++98
- **Recommended:** C++11 or later (for optimized implementations)
- Detects and adapts to higher standards (C++14, C++17, C++20, etc.)

## Architecture

Quark uses a **facade pattern** with compiler-specific backends:

1. **Public headers** (e.g., `Atomic.h`, `BitOperations.h`) act as stable facades
2. Each facade selects a backend at compile time based on `AXM_COMPILER_*` macros
3. **Three-tier fallback strategy:**
   - GCC/Clang optimized implementation (best performance)
   - MSVC optimized implementation (good performance on Windows)
   - Generic portable C implementation (maximum compatibility)

This design ensures:
- **Portability:** Code works across compilers and platforms
- **Performance:** Compiler-specific optimizations are always used when available
- **Maintainability:** Platform-specific code is isolated and centralized
- **Reliability:** Conservative fallbacks prevent silent failures

## Building from Source

### Prerequisites
- CMake >= 3.21
- C++ compiler (GCC, Clang, or MSVC)
- Axiom framework CMake modules (in `~/.axiom/CMake`)

### Build Steps

```bash
# Clone or navigate to the Quark directory
cd Quark

# Create and configure build directory
mkdir -p Build/Debug
cd Build/Debug
cmake ../.. -DCMAKE_BUILD_TYPE=Debug

# Build
cmake --build .

# (Optional) Create release build
cd ../Release
cmake ../.. -DCMAKE_BUILD_TYPE=Release
cmake --build .
```

## Performance Considerations

- **Header-only:** No compilation overhead; all optimizations are inlined
- **Zero runtime cost:** Wrapper macros compile down to direct compiler calls/intrinsics
- **SIMD support:** Automatic selection of fastest available instruction set
- **Bit operations:** Compiler builtins ensure efficient codegen (single CPU instruction)
- **Atomic operations:** Lock-free on supporting platforms; memory barriers only where needed

## License & Attribution

Part of the **Axiom framework** plugin ecosystem. Consult the Axiom documentation and licensing for additional information.

## Common Patterns

### Compile-Time Platform Selection

```cpp
#include <Quark/System.h>

#if AXM_COMPILER_GCC_LIKE
    // GCC/Clang specific
#elif AXM_COMPILER_MSVC_LIKE
    // MSVC specific
#else
    #error "Unsupported compiler"
#endif
```

### Conditional Feature Use

```cpp
#include <Quark/Features.h>

#if AXM_HAS_CPP_ATTRIBUTE(carries_dependency)
#    define AXM_CARRIES_DEPENDENCY [[carries_dependency]]
#elif AXM_HAS_ATTRIBUTE(carries_dependency)
#    define AXM_CARRIES_DEPENDENCY __attribute__((carries_dependency))
#else
#    define AXM_CARRIES_DEPENDENCY
#endif
```

## Troubleshooting

### Issue: Undefined symbols in Quark::BitOps namespace
- **Cause:** Quark headers not in include path or namespace not used
- **Solution:** Add `Include/` to compiler include paths and use `#include <Quark/BitOperations.h>` with `using namespace Quark::BitOps;` or call functions as `Quark::BitOps::ctz32(value)`

### Issue: Incorrect endianness conversion results
- **Cause:** Not including system detection headers or platform detection failing
- **Solution:** Include `Quark/System.h` which detects platform endianness, or check that `AXM_LITTLE_ENDIAN` or `AXM_BIG_ENDIAN` are properly defined

### Issue: Getting compiler errors in bit operations
- **Cause:** Potentially incompatible compiler or architecture not fully supported
- **Solution:** The generic fallback should work on any platform. Check that compiler is C++98 compatible at minimum
