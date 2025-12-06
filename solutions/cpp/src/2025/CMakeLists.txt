# CMakeLists.txt for AoC 2025 - Root Project Configuration
# This is the main build configuration file for the Advent of Code 2025 C++ project.
# It sets up project-wide compiler settings, includes Google Test via FetchContent,
# and orchestrates builds for the logic library, tests, and console runner.

cmake_minimum_required(VERSION 3.20)  # 3.20 introduces better presets support

# Project declaration
project(AoC2025 
    VERSION 2025.1.0
    DESCRIPTION "Advent of Code 2025 - C++ Solutions"
    LANGUAGES CXX)

# Set C++ standard to C++23 for modern features (modules, ranges, std::print, etc.)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)  # Disable compiler-specific extensions for portability

# Output directories - organize built artifacts by configuration
# CMAKE_BUILD_TYPE is set by CMakePresets.json
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

# Compiler-specific settings
# This improves warnings and error messages across different compilers
if(MSVC)
    # Microsoft Visual C++ compiler settings (Windows)
    add_compile_options(/W4 /WX)  # Warning level 4, treat warnings as errors
    add_compile_options(/permissive-)  # Stricter C++ standards conformance
else()
    # Clang/GCC compiler settings (Linux, macOS)
    add_compile_options(-Wall -Wextra -Wpedantic)  # Enable many warnings
    add_compile_options(-Werror)  # Treat warnings as errors
endif()

# ============================================================================
# Google Test Integration via FetchContent (Added in CMake 3.11)
# FetchContent automatically downloads and builds dependencies as needed
# ============================================================================
include(FetchContent)

# Declare the Google Test dependency
# This will download gtest during the CMake configure step
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP ON  # Avoid timestamp checks for reproducible builds
)

# Set options to disable GTest building its own tests
# We only need the test framework itself
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)  # Use shared runtime on Windows

# Make the gtest content available
# This populates googletest_SOURCE_DIR and googletest_BINARY_DIR variables
FetchContent_MakeAvailable(googletest)

# ============================================================================
# Enable Testing
# This makes CTest available for discovering and running tests
# ============================================================================
enable_testing()

# ============================================================================
# Add Subdirectories
# Each subdirectory contains its own CMakeLists.txt that defines specific targets
# ============================================================================

# logic/ - Core solver library
add_subdirectory(logic)

# logic.tests/ - Google Test test suite
add_subdirectory(logic.tests)

# runner/ - Console application
add_subdirectory(runner)

# ============================================================================
# Print Configuration Summary
# Useful for debugging and understanding the build configuration
# ============================================================================
message(STATUS "========== AoC 2025 Configuration ==========")
message(STATUS "CMake Version: ${CMAKE_VERSION}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Generator: ${CMAKE_GENERATOR}")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "Source Dir: ${CMAKE_SOURCE_DIR}")
message(STATUS "Binary Dir: ${CMAKE_BINARY_DIR}")
message(STATUS "============================================")
