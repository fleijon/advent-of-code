# CMakeLists.txt for logic library
# Defines the core solver library containing all Advent of Code solution logic

# Create a static library target named "logic"
# STATIC means the library will be compiled into .a (Linux) or .lib (Windows) files
add_library(logic STATIC)

# ============================================================================
# Target Sources
# These are the source files that will be compiled into the library
# ============================================================================

target_sources(logic PRIVATE
    # Day 1 solutions
    day01/day01solver.cpp
    
    # Add more days here as you implement them:
    # day02/day02solver.cpp
    # day03/day03solver.cpp
    # etc.
    
    # Utility functions
    utils/preprocess.cpp
)

# ============================================================================
# Precompiled Headers (PCH)
# Precompiled headers significantly speed up compilation by pre-compiling
# frequently included headers (like the entire standard library).
# This is optional but recommended for larger projects.
# ============================================================================

# Define a precompiled header for the logic library
# Note: PCH support is automatic on MSVC; on clang/GCC it's automatic with CMake 3.16+
# We'll create a simple precompiled header that includes common headers
target_precompile_headers(logic PRIVATE
    <vector>
    <string>
    <map>
    <algorithm>
    <iostream>
)

# ============================================================================
# Target Include Directories
# These directories contain header files needed by this target
# ============================================================================

# PUBLIC includes are visible to targets that link against "logic"
# This allows the test runner and runner app to include headers from these directories
target_include_directories(logic PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}  # Makes <day01/day01solver.h> and <utils/preprocess.h> available
)

# ============================================================================
# Optional: Per-file Properties
# For advanced scenarios (like enabling PCH for specific files on specific compilers)
# ============================================================================

# If you want even more aggressive optimization or specific compiler flags,
# you can set properties on individual source files:
# set_source_files_properties(day01/day01solver.cpp PROPERTIES COMPILE_FLAGS "-O3")

message(STATUS "Logic library configured")
