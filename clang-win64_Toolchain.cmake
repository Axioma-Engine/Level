cmake_minimum_required(VERSION 3.21)

set(CMAKE_SYSTEM_NAME      Windows)
set(CMAKE_SYSTEM_PROCESSOR x86_64)
set(CMAKE_C_COMPILER_TARGET   "x86_64-w64-mingw32")
set(CMAKE_CXX_COMPILER_TARGET "x86_64-w64-mingw32")

set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_WORKS 1)

set(CMAKE_C_COMPILER   "clang.exe")
set(CMAKE_CXX_COMPILER "clang++.exe")
set(CMAKE_RC_COMPILER  "llvm-rc.exe")
set(CMAKE_AR     "llvm-ar.exe")
set(CMAKE_LINKER "ld.lld.exe")
set(CMAKE_RANLIB "llvm-ranlib.exe")
set(CMAKE_STRIP  "llvm-strip.exe")

add_link_options(-fuse-ld=lld)
