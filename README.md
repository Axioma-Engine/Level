# Level Plugin

A lightweight, header-only C++98 library plugin for the Axiom project that provides portable type definitions, cross-platform atomic operations, and comprehensive system/environment detection macros.

## Version

**1.0.1**

## Overview

Level is a foundational plugin that abstracts platform-specific complexities and provides a unified interface for:

- **Portable Type Aliases** – Fixed-width integer types, pointer-sized integers, floating-point types, booleans, and character types optimized for clarity and consistency across platforms
- **Atomic Operations** – Cross-platform atomic operation macros with explicit memory ordering semantics (Relaxed, Consume, Acquire, Release, ACQ_REL, SEQ_CST)
- **System Detection** – Compile-time detection of CPU architecture, compiler, C++ language level, endianness, operating system, runtime sanitizers, and SIMD capabilities
- **Compiler Attributes** – Unified attribute support across GCC, Clang, and MSVC
- **Feature Detection** – C++ feature availability detection

## Features

### Type System

The `Types.h` header provides concise, portable type aliases:

- **Fixed-width integers**: `u8`, `u16`, `u32`, `u64`, `i8`, `i16`, `i32`, `i64`
- **Pointer-sized integers**: `iptr`, `uptr`, `intptr`, `uintptr`
- **Floating-point types**: `f32`, `f64`
- **Boolean and character**: `bool8`, `char8`, `char16`, `char32`

### Atomic Operations

The `Atomic.h` header provides unified atomic macros across compiler backends:

**Memory Ordering Levels:**
- `AXM_LVL_ATOMIC_SEQ_RELAXED` – No synchronization, relaxed ordering
- `AXM_LVL_ATOMIC_SEQ_CONSUME` – Consume semantics
- `AXM_LVL_ATOMIC_SEQ_ACQUIRE` – Acquire semantics
- `AXM_LVL_ATOMIC_SEQ_RELEASE` – Release semantics
- `AXM_LVL_ATOMIC_SEQ_ACQ_REL` – Acquire-release semantics
- `AXM_LVL_ATOMIC_SEQ_SEQ_CST` – Sequentially-consistent (strictest)

**Supported Operations:**
- Load, Store, Exchange
- Compare-and-exchange (CAS)
- Fetch-add, Fetch-sub
- Fetch-and, Fetch-or, Fetch-xor

**Compiler Support:**
- GCC/Clang: `__atomic_*` builtins
- MSVC: `_Interlocked*` intrinsics
- Generic fallback: C11 `stdatomic.h`

### System Detection

The `System.h` umbrella header provides compile-time detection macros:

- `AXM_ARCH_*` – CPU architecture and pointer-width (x86, x64, ARM, etc.)
- `AXM_COMPILER_*` – Compiler identification (GCC, Clang, MSVC) and version
- `AXM_LANGUAGE_CXX` – C++ language marker and standard feature level
- `AXM_ENDIAN_*` – Byte-order detection (little-endian, big-endian)
- `AXM_OS_*` – Operating system detection (Windows, Linux, macOS, POSIX)
- `AXM_SANITIZER_*` – Runtime sanitizer detection (ASan, MSan, UBSan, TSan)
- `AXM_SIMD_*` – SIMD and vector instruction detection (SSE, AVX, Neon, etc.)

**Build Configuration:**
- `AXM_BUILD_DEBUG` – Defined when NDEBUG is not set
- `AXM_BUILD_RELEASE` – Defined when NDEBUG is set

### Compiler Attributes

The `Attributes.h` header provides unified attribute syntax across GCC, Clang, and MSVC for function/type annotations like deprecated, visibility, alignment, and other compiler-specific features.

## Directory Structure

```
Include/Level/          # Public API headers
├── Types.h             # Portable type aliases
├── Atomic.h            # Cross-platform atomic operations
├── System.h            # System/environment detection umbrella
├── Attributes.h        # Compiler attribute wrappers
├── Features.h          # C++ feature detection
├── System/             # Implementation details for detection
│   ├── Arch.h          # Architecture detection
│   ├── Compiler.h      # Compiler detection
│   ├── Cpp.h           # C++ standard detection
│   ├── Endian.h        # Endianness detection
│   ├── Os.h            # OS detection
│   ├── Sanitizer.h     # Sanitizer detection
│   └── Simd.h          # SIMD detection
├── GCC/                # GCC/Clang specific implementations
├── MSVC/               # MSVC specific implementations
└── Generic/            # Standard C/C++ fallback implementations
```

## Usage

### Include the Library

```cpp
#include <Level/System.h>    // System detection (includes all detection macros)
#include <Level/Types.h>     // Portable type aliases
#include <Level/Atomic.h>    // Atomic operations
```

### Portable Integer Types

```cpp
#include <Level/Types.h>

namespace AXM {
    // Use fixed-width types for binary formats
    struct FileHeader {
        u32 magic;
        u32 version;
        u64 timestamp;
    };

    // Use fast types for performance-critical code
    void process_data(u32f count) {
        // ...
    }
}
```

### Platform Detection

```cpp
#include <Level/System.h>

#if defined(AXM_OS_WINDOWS)
    // Windows-specific code
#elif defined(AXM_OS_LINUX)
    // Linux-specific code
#endif

#if defined(AXM_COMPILER_GCC)
    // GCC/Clang specific code
#elif defined(AXM_COMPILER_MSVC)
    // MSVC specific code
#endif

#if AXM_ARCH_BITS == 64
    // 64-bit architecture code
#endif
```

### Atomic Operations

```cpp
#include <Level/Atomic.h>

// Thread-safe increment with sequential consistency
volatile u32 counter = 0;
AXM_LVL_ATOMIC_FETCH_ADD(&counter, 1);

// Load with acquire semantics
u32 value = AXM_LVL_ATOMIC_LOAD_SEQ(&counter, AXM_LVL_ATOMIC_SEQ_ACQUIRE);

// Compare-and-exchange
u32 expected = 5, desired = 10;
AXM_LVL_ATOMIC_COMPARE_EXCHANGE(&counter, expected, desired);
```

## Building

The library is header-only and requires no compilation:

```bash
# Configure
cmake -B Build -DCMAKE_BUILD_TYPE=Release

# Install
cmake --install Build
```

## Supported Platforms

- Windows (x86, x64)
- Linux (x86, x64, ARM)
- macOS (x64, ARM64)
- POSIX-compliant systems

## Integration with Axiom

Level is registered as an Axiom plugin and integrates with the Axiom build system:

- Automatic configuration via `AxiomFunctions` module
- Install target with plugin metadata
- Header-only distribution
- CMake config files for downstream projects

## Dependencies

- None (standard library only: `<stdint.h>`, `<stddef.h>`, `<float.h>`)

## Contributing

Level provides low-level portability abstractions. When extending:

- Maintain C++98 compatibility
- Add platform-specific implementations in `GCC/`, `MSVC/`, or `Generic/` folders
- Document detection macros clearly
- Test across supported compilers and platforms
- Update Doxygen comments for new public APIs

---