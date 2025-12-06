# CMakeLists.txt for test runner
# Defines the test executable using Google Test framework

# Create an executable target named "logic.tests"
# This will be the test runner program
add_executable(logic.tests)

# ============================================================================
# Target Sources
# Test files to compile into the test executable
# ============================================================================

target_sources(logic.tests PRIVATE
    pch.cpp  # Precompiled header implementation
    test.cpp # Test cases
)

# ============================================================================
# Precompiled Headers for Tests
# Tests use a different PCH than the library since they include gtest
# ============================================================================

# Set the precompiled header file for the test target
# This must be done BEFORE other target_precompile_headers calls
target_precompile_headers(logic.tests PRIVATE pch.h)

# ============================================================================
# Target Include Directories
# ============================================================================

# PRIVATE includes are only used when compiling this target
# Tests need to include the logic library headers and preprocess utilities
target_include_directories(logic.tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/..  # Access to logic/ and logic/utils/
)

# ============================================================================
# Target Link Libraries
# Link against libraries this target depends on
# ============================================================================

# Link against the logic library (our custom library)
target_link_libraries(logic.tests PRIVATE logic)

# Link against Google Test framework
# gtest_main provides the main() function for the test executable
target_link_libraries(logic.tests PRIVATE gtest_main gtest)

# ============================================================================
# Register Tests with CTest
# This makes the tests discoverable by the CTest framework in VS Code
# ============================================================================

# Enable CTest discovery for this executable
# This allows running tests with: cmake --build . --target RUN_TESTS
# Or from VS Code: CMake: Run Tests
add_test(
    NAME logic.tests
    COMMAND logic.tests
)

message(STATUS "Test runner configured")
