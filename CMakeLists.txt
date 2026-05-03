cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD          98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(TO_CMAKE_PATH "$ENV{HOME}" _HOME_PATH)
file(TO_CMAKE_PATH "$ENV{USERPROFILE}" _USERPROFILE_PATH)
list(APPEND CMAKE_MODULE_PATH
    "${_HOME_PATH}/.axiom/CMake"
    "${_USERPROFILE_PATH}/.axiom/CMake"
)
include(AxiomFunctions REQUIRED)
Axiom_UseToolchain("${CMAKE_SOURCE_DIR}/clang-gnu_Toolchain.cmake")
Axiom_RegisterNativeBuildType()

project(Level LANGUAGES CXX VERSION 1.0.1)
add_library(Level INTERFACE
)
Axiom_DetectCompiler()
Axiom_SetupProject(Level HEADER_ONLY TYPE PLUGIN)
Axiom_SetupCompileCommands(SYMLINK)
Axiom_SetupInstall(Level TYPE PLUGIN VERSION 1.0.1 HEADER_ONLY)
