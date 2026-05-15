# Level Library

**Version:** 1.1.0  
**Language:** C++ (C++98 and later)  
**Type:** Header-only Plugin for Axiom Framework

## Overview

The **Level** library is a comprehensive, header-only C++ utility library designed as a plugin for the Axiom framework. It provides portable, low-level abstractions for system detection, compiler-specific features, atomic operations, bit manipulation, and SIMD vectorization. Level enables developers to write high-performance, cross-platform C++ code by encapsulating compiler and architecture-specific details behind unified, easy-to-use macros and utilities.

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
  - Language standard level detection (C++98, C++11, C++14, C++17, C++20, etc.)
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
- **Core operations:**
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

All operations located in `Level::Atomic::` namespace.

### 5. **Bit Operations** (`BitOperations.h`)
Common bit-manipulation helpers in the `Level::Bits::` namespace with compiler-optimized implementations:

- **Count trailing zeros:** `ctz32(u32)`, `ctz64(u64)` - Returns 32/64 for zero input
- **Count leading zeros:** `clz32(u32)`, `clz64(u64)` - Returns 32/64 for zero input
- **Population count:** `popcount32(u32)`, `popcount64(u64)` - Counts the number of set bits
- **Byte swapping:** `swap16(u16)`, `swap32(u32)`, `swap64(u64)`
- **Host-to-little-endian:** `htole16(u16)`, `htole32(u32)`, `htole64(u64)`
- **Little-endian-to-host:** `letoh16(u16)`, `letoh32(u32)`, `letoh64(u64)`
- **Host-to-big-endian:** `htobe16(u16)`, `htobe32(u32)`, `htobe64(u64)`
- **Big-endian-to-host:** `betoh16(u16)`, `betoh32(u32)`, `betoh64(u64)`

All functions are static inline and available in the `Level::Bits::` namespace.

**Compiler-specific backends:**
- GCC/Clang: Uses compiler builtins (`__builtin_ctz`, `__builtin_popcount`, etc.) with portable fallbacks
- MSVC: Uses MSVC intrinsics (`_BitScanForward`, `__popcnt`, `_byteswap_*`, etc.)
- Generic: Portable C implementations using De Bruijn sequences and efficient algorithms

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

### 7. **SIMD Vectorization** (`Simd.h` + `SIMD/*.h`)
Portable, templated SIMD abstractions for efficient vector operations.

**Supported backends:**
- AVX/AVX2 (256-bit vectors)
- SSE/SSE2 (128-bit vectors)
- NEON (ARM 128-bit vectors)
- Scalar fallback (portable C implementation)

The current SIMD API uses a small, consistent set of templated functions and a
`Simd<N, T>` union type under the `Level::SIMD` namespace. `N` is the bit
count and `T` is the element type (e.g., `f32`, `i32`). Backends provide
specializations that map these templates to the most efficient intrinsics
available for the target platform.

Primary interface (declared in `Simd.h`):

- `template<usize N, typename T> union Simd;` — vector storage type
- `load< N, T >(const T* ptr)` / `store< N, T >(T* ptr, const Simd<N,T>&)`
- `set< N, T >(...)` — several overloads for constructing vectors from scalars
- Arithmetic: `add< N, T >`, `sub< N, T >`, `mul< N, T >`, `div< N, T >`
- Unary: `abs< N, T >`, `neg< N, T >`, `sqrt`, `rsqrt`, `reciprocal`
- Bitwise/logical: `land`, `lor`, `lxor`, `lnot`, `landnot`
- Shifts: `shl`, `shr`, `sar`
- Min/Max: `min< N, T >`, `max< N, T >`
- Comparisons: `cmpEq`, `cmpNe`, `cmpLt`, `cmpLe`, `cmpGt`, `cmpGe`
- Utilities: `movemask(const Simd<N,T>&)` — extract lane masks

All functions are declared as `inline` templates and implemented in the
backend headers (`SIMD/AVX`, `SIMD/SSE`, `SIMD/NEON`, `SIMD/Scalar`).

Example usage:

```cpp
#include <Level/Simd.h>
using namespace Level::SIMD;

// 4-wide float vectors
using Vec4f = Simd<128, f32>;

f32 dataA[4] = {1,2,3,4};
f32 dataB[4] = {5,6,7,8};

Vec4f a = load<128, f32>(dataA);
Vec4f b = load<128, f32>(dataB);
Vec4f sum = add<128, f32>(a, b);
store<4, f32>(dataA, sum); // writes 6,8,10,12 back to dataA

// Construct directly
Vec4f c = set<128, f32>(1.0f, 2.0f, 3.0f, 4.0f);

// Mask and comparisons
auto m = cmpGt<128, f32>(sum, c);        // per-lane greater-than mask
u32 mask = movemask<128, f32>(m);        // platform-independent lane mask
```

Notes:
- Implementations are backend-driven; adding new backends (e.g., SVE, RVV)
    can be done by providing specializations in `Include/Level/SIMD/`.

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
Level/
├── Include/Level/
│   ├── Atomic.h              # Atomic operations facade
│   ├── Attributes.h          # Compiler attributes facade
│   ├── BitOperations.h       # Bit manipulation facade
│   ├── Features.h            # Feature detection macros
│   ├── Simd.h                # SIMD backend selector
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
│   │   └── BitOperations.h   # __builtin_* functions
│   ├── MSVC/                 # MSVC-specific implementations
│   │   ├── Atomic.h          # _Interlocked* intrinsics
│   │   ├── Attributes.h      # declspec and pragmas
│   │   └── BitOperations.h   # _BitScan*, __popcnt, etc.
│   ├── Generic/              # Portable fallbacks
│   │   ├── Atomic.h          # C11 or safe fallback
│   │   ├── Attributes.h      # Minimal fallbacks
│   │   └── BitOperations.h   # Pure C implementations
│   └── SIMD/                 # SIMD backends
│       ├── AVX.h             # AVX/AVX2 intrinsics
│       ├── SSE.h             # SSE/SSE2 intrinsics
│       ├── NEON.h            # ARM NEON intrinsics
│       └── Scalar.h          # Portable scalar fallback
├── CMakeLists.txt            # Build configuration
├── Testing.cpp               # Testing driver (generates compile_commands.json)
└── README.md                 # This file
```

## Usage

### Basic Inclusion

```cpp
// Include everything
#include <Level/System.h>
#include <Level/Types.h>
#include <Level/Attributes.h>
#include <Level/BitOperations.h>
#include <Level/Atomic.h>
#include <Level/Simd.h>
#include <Level/Utils.h>

// Or include specific headers as needed
#include <Level/Features.h>  // Feature detection only
```

### Example: System Detection

```cpp
#include <Level/System.h>

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
#include <Level/Types.h>

// Portable fixed-width types
Level::u8 byte = 255;           // Exactly 8 bits
Level::u32 color = 0xFF0000FF;  // Exactly 32 bits
Level::i64 timestamp = 123456;  // Exactly 64 bits

// Platform-dependent but optimized
Level::uptr address = (Level::uptr)&some_var;  // Word-sized unsigned
Level::f32 value = 3.14f;                      // 32-bit float
Level::iptr offset = some_ptr - other_ptr;    // Signed pointer-sized integer
```

### Example: Atomic Operations

```cpp
#include <Level/Atomic.h>

// Atomic flag for thread synchronization
volatile int ready = 0;

// Thread 1: Signal readiness
Level::Atomic::store<int>(&ready, 1, Level::Atomic::RELEASE);

// Thread 2: Wait for signal
while (Level::Atomic::load<int>(&ready, Level::Atomic::ACQUIRE) == 0) {
    Level::Atomic::pause();  // Yield CPU
}
```

### Example: Bit Operations

```cpp
#include <Level/BitOperations.h>
using namespace Level::Bits;

u32 value = 0x80000000;
int leading_zeros = clz32(value);      // 0
int trailing_zeros = ctz32(value);     // 31
int pop_count = popcount32(0xFF00FF);  // 16

// Endianness conversion
u32 host_value = 0x12345678;
u32 big_endian = htobe32(host_value);
u32 little_endian = htole32(host_value);

// 64-bit operations
u64 large_value = 0x8000000000000000ULL;
int clz64_result = clz64(large_value);  // 0
int ctz64_result = ctz64(large_value);  // 63
```

### Example: Compiler Attributes

```cpp
#include <Level/Attributes.h>

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

### Example: SIMD Operations

```cpp
#include <Level/Simd.h>

// Add four 32-bit integers using SIMD (or scalar fallback)
Level::V128I32 a = /* ... */;
Level::V128I32 b = /* ... */;
Level::V128I32 result = AXM::v128i32Add(a, b);

// Store result back
AXM::v128i32Store(&output_array[0], result);
```

### Example: Feature Detection

```cpp
#include <Level/Features.h>

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

Level uses a **facade pattern** with compiler-specific backends:

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
# Clone or navigate to the Level directory
cd Level

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
#include <Level/System.h>

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
#include <Level/Features.h>

#if AXM_HAS_CPP_ATTRIBUTE(carries_dependency)
#    define AXM_CARRIES_DEPENDENCY [[carries_dependency]]
#elif AXM_HAS_ATTRIBUTE(carries_dependency)
#    define AXM_CARRIES_DEPENDENCY __attribute__((carries_dependency))
#else
#    define AXM_CARRIES_DEPENDENCY
#endif
```

### Safe Fallback Implementation

```cpp
#include <Level/BitOperations.h>
using namespace Level::Bits;

// Automatically uses fastest available implementation
// GCC: __builtin_clz, Clang: __builtin_clz, MSVC: _BitScanReverse, Other: portable algorithm
u32 value = 0x80000000;
int leading_zeros = clz32(value);
int trailing_zeros = ctz32(value);
int set_bits = popcount32(0xFF00FF);

// Endianness conversions automatically adapt to platform
u32 network_order = htobe32(local_value);
u32 back_to_local = betoh32(network_order);
```

## Troubleshooting

### Issue: Undefined symbols in Level::Bits namespace
- **Cause:** Level headers not in include path or namespace not used
- **Solution:** Add `Include/` to compiler include paths and use `#include <Level/BitOperations.h>` with `using namespace Level::Bits;` or call functions as `Level::Bits::ctz32(value)`

### Issue: Incorrect endianness conversion results
- **Cause:** Not including system detection headers or platform detection failing
- **Solution:** Include `Level/System.h` which detects platform endianness, or check that `AXM_LITTLE_ENDIAN` or `AXM_BIG_ENDIAN` are properly defined

### Issue: Getting compiler errors in bit operations
- **Cause:** Potentially incompatible compiler or architecture not fully supported
- **Solution:** The generic fallback should work on any platform. Check that compiler is C++98 compatible at minimum
