# CMakeLists.txt for console runner
# Defines the main console application that runs solvers and displays results

# Create an executable target named "runner"
# This is the main console application users will run
add_executable(runner)

# ============================================================================
# Target Sources
# Source files to compile into the runner executable
# ============================================================================

target_sources(runner PRIVATE
    runner.cpp  # Main console application
)

# ============================================================================
# Target Include Directories
# ============================================================================

# PRIVATE includes are only needed when compiling this target
target_include_directories(runner PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/..  # Access to logic/ and utils/
)

# ============================================================================
# Target Link Libraries
# ============================================================================

# Link against the logic library containing solver functions
target_link_libraries(runner PRIVATE logic)

# ============================================================================
# Post-Build Information
# Print helpful information after building
# ============================================================================

add_custom_command(TARGET runner POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo ""
    COMMAND ${CMAKE_COMMAND} -E echo "=== Runner Build Complete ==="
    COMMAND ${CMAKE_COMMAND} -E echo "Executable location: $<TARGET_FILE:runner>"
    COMMAND ${CMAKE_COMMAND} -E echo "To run: $<TARGET_FILE:runner>"
    COMMAND ${CMAKE_COMMAND} -E echo ""
)

message(STATUS "Runner application configured")
