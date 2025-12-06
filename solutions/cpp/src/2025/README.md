# Advent of Code 2025 - C++ Solutions (CMake Edition)

A modern C++ project for solving Advent of Code 2025 challenges using CMake for cross-platform builds. This project is designed to work on **Ubuntu/Linux with clang** and **Windows with MSVC**, with full Visual Studio Code integration including debugging and testing.

## Project Structure

```
2025/
├── CMakeLists.txt              # Root CMake configuration
├── CMakePresets.json           # Build presets for different platforms/configurations
├── README.md                   # This file
├── .gitignore                  # Git ignore patterns
├── .vscode/
│   ├── settings.json           # VS Code editor and CMake settings
│   ├── tasks.json              # Build, test, and run tasks
│   └── launch.json             # Debugger configurations
├── logic/
│   ├── CMakeLists.txt          # Logic library build configuration
│   ├── day01/
│   │   ├── day01solver.h       # Day 1 solver declarations
│   │   └── day01solver.cpp     # Day 1 solver implementation
│   ├── day02/                  # (To be created as you progress)
│   │   └── ...
│   └── utils/
│       ├── preprocess.h        # Utility functions for file I/O and string parsing
│       └── preprocess.cpp
├── logic.tests/
│   ├── CMakeLists.txt          # Test runner build configuration
│   ├── pch.h                   # Precompiled header for tests
│   ├── pch.cpp                 # Precompiled header implementation
│   └── test.cpp                # Google Test test cases
└── runner/
    ├── CMakeLists.txt          # Console app build configuration
    └── runner.cpp              # Main console application
```

### Key Components

1. **logic/** - Core solver library
   - Contains day-by-day solver implementations
   - Compiled as a static library (`liblogic.a` on Linux, `logic.lib` on Windows)
   - Shared by tests and runner application

2. **logic.tests/** - Unit test suite
   - Uses Google Test framework (automatically fetched by CMake)
   - Tests solver correctness against example inputs
   - Can be run independently or as part of the build

3. **runner/** - Console application
   - Main entry point for solving puzzles
   - Loads input files and calls solver functions
   - Displays results

## Prerequisites

### Ubuntu/Linux with Clang

**Note**: C++23 support requires recent compiler versions. Ubuntu 24.04 (Noble) or newer recommended.

```bash
# Update package manager
sudo apt update

# Install build tools (with C++23 support)
sudo apt install -y \
    cmake \
    clang \
    clang++ \
    ninja-build \
    gdb

# Optional but recommended
sudo apt install -y clang-format clang-tidy
```

### Windows with MSVC

- **Visual Studio 2022** (or newer) with C++ workload installed
- **CMake 3.20+** (install from https://cmake.org)
- **Visual Studio 2022 version 17.4+** (for C++23 support)
- **Git Bash** or **Windows Terminal** for command-line usage

## Building the Project

### Configure

The first step prepares the build directory and generates build files for your platform:

```bash
# Linux with Clang (Debug)
cmake --preset clang-linux-debug

# Linux with Clang (Release - optimized)
cmake --preset clang-linux-release

# Windows with MSVC (Debug)
cmake --preset msvc-windows-debug

# Windows with MSVC (Release)
cmake --preset msvc-windows-release
```

**What this does:**
- Creates a `cmake_build_<preset-name>/` directory with all build files
- For Linux: Generates Unix Makefiles or Ninja build files
- For Windows: Generates Visual Studio project files (.vcxproj)
- Downloads and builds Google Test automatically

### Build

```bash
# Build all targets (debug configuration on Linux)
cmake --build cmake_build_clang-linux-debug

# Build all targets (release configuration on Windows)
cmake --build cmake_build_msvc-windows-release

# Build specific target
cmake --build cmake_build_clang-linux-debug --target logic.tests

# Build with parallel jobs (4 jobs)
cmake --build cmake_build_clang-linux-debug -j 4
```

**Output locations:**
- Executables: `cmake_build_<preset>/bin/` (or `.../bin/Debug/` on Windows)
- Libraries: `cmake_build_<preset>/lib/`

### Run Tests

```bash
# Run all tests (Linux)
cd cmake_build_clang-linux-debug && ctest

# Or using CMake directly
cmake --build cmake_build_clang-linux-debug --target RUN_TESTS

# Run a specific test (once built)
./cmake_build_clang-linux-debug/bin/logic.tests
```

### Run Solver

```bash
# Run the main console application
./cmake_build_clang-linux-debug/bin/runner

# On Windows
.\cmake_build_msvc-windows-debug\bin\Debug\runner.exe
```

## Visual Studio Code Setup

### Extensions

Install these extensions in VS Code for optimal development experience:

1. **C/C++ Extension Pack** (Microsoft)
   - Provides IntelliSense, debugging, and code browsing
   - ID: `ms-vscode.cpptools-extension-pack`

2. **CMake Tools** (Microsoft)
   - Provides CMake integration and build support
   - ID: `ms-vscode.cmake-tools`

3. **CMake** (Twxs) - Optional
   - Provides CMake syntax highlighting
   - ID: `twxs.cmake`

### First-Time Setup

1. Open the workspace folder in VS Code:
   ```bash
   code solutions/cpp/src/2025
   ```

2. VS Code will detect CMake and ask to install the CMake Tools extension if not already installed

3. Select your preferred CMake preset when prompted:
   - Linux users: `clang-linux-debug`
   - Windows users: `msvc-windows-debug`

4. Configure the project (Cmd+Shift+P → "CMake: Configure")

### Building in VS Code

- **Default build**: Press `Ctrl+Shift+B` (runs CMake: Build task)
- **Alternative**: Cmd+Shift+P → "CMake: Build"

### Running Tests in VS Code

- **Cmd+Shift+P** → "CMake: Run Tests"
- Or run the task: `Ctrl+Shift+B` → select "CMake: Test"

### Debugging in VS Code

1. **Set a breakpoint** by clicking in the left margin of any .cpp or .h file

2. **Start debugging**:
   - Press `F5`, or
   - Cmd+Shift+P → "Debug: Start Debugging"
   - Select the appropriate configuration:
     - `GDB: Debug Tests (Linux)` for tests
     - `GDB: Debug Runner (Linux)` for main app

3. **Debug controls**:
   - Step Over: `F10`
   - Step Into: `F11`
   - Continue: `F5`
   - Stop: `Shift+F5`

**Note**: Ensure you've configured debugging prerequisites:
- **Linux**: Install GDB with `sudo apt install gdb`
- **Windows**: MSVC debugger comes with Visual Studio

## Adding New Days

When you start a new day:

1. **Create a new day folder**:
   ```bash
   mkdir logic/day02
   ```

2. **Create solver files**:
   ```cpp
   // logic/day02/day02solver.h
   #pragma once
   #include "../utils/preprocess.h"
   
   long long day02_part1_find_solution(const input_format& input);
   long long day02_part2_find_solution(const input_format& input);
   ```

   ```cpp
   // logic/day02/day02solver.cpp
   #include "day02solver.h"
   
   long long day02_part1_find_solution(const input_format& input) {
       // TODO: Implement solution
       return 0;
   }
   
   long long day02_part2_find_solution(const input_format& input) {
       // TODO: Implement solution
       return 0;
   }
   ```

3. **Update `logic/CMakeLists.txt`**:
   - Add `day02/day02solver.cpp` to the `target_sources()` list

4. **Add tests in `logic.tests/test.cpp`**:
   ```cpp
   #include "day02/day02solver.h"
   
   TEST(day02, part1_example) {
       const std::string filepath = "../../../../resources/2025/02/example.1.txt";
       input_format loadedInput;
       
       if (!LoadInput(filepath, "\n", loadedInput)) {
           GTEST_SKIP() << "Example input file not found";
       }
       
       auto result = day02_part1_find_solution(loadedInput);
       EXPECT_EQ(result, expected_value);
   }
   ```

5. **Add solver calls in `runner/runner.cpp`**:
   ```cpp
   RunSolver(day02_part1_find_solution, "02");
   RunSolver(day02_part2_find_solution, "02");
   ```

6. **Place input files** in the `resources/2025/02/` directory:
   - `example.1.txt` - Example input for testing
   - `input.1.txt` - Actual puzzle input

7. **Rebuild** with `Ctrl+Shift+B`

## Understanding the Build System

### CMake Basics

**CMake** is a meta-build system that generates platform-specific build files:
- **On Linux**: Generates Makefiles or Ninja build files
- **On Windows**: Generates Visual Studio project files

**Key terms:**
- **Target**: A build artifact (executable or library)
- **Source file**: .cpp, .h files that are compiled
- **Presets**: Predefined configurations that specify compiler, flags, and directories

### CMakePresets.json

Defines platform and configuration-specific build settings:
- `clang-linux-debug` - Debug build with clang on Linux
- `clang-linux-release` - Optimized release build with clang
- `msvc-windows-debug` - Debug build with MSVC on Windows
- `msvc-windows-release` - Optimized release build with MSVC

Each preset:
- Specifies the C++ compiler to use
- Sets build directory location
- Defines optimization levels (Debug = none, Release = -O3 on Linux)
- Inherits common settings from `default-base` preset

### Precompiled Headers (PCH)

**What are precompiled headers?**
Precompiled headers pre-compile frequently included headers once, then reuse the compiled form across many translation units, significantly speeding up compilation.

**How it works in this project:**
- `logic.tests/pch.h` includes Google Test and common STL headers
- `logic.tests/pch.cpp` is the PCH implementation file
- CMake automatically links PCH into the test target
- On MSVC: Automatic handling
- On Clang/GCC: Handled transparently by CMake 3.16+

**When PCH rebuilds:**
- Any change to `pch.h` triggers recompilation of all test files
- Editing other headers (e.g., `preprocess.h`) does NOT trigger PCH rebuild

### Linking and Dependencies

**Target Linking** (CMakeLists.txt):
```cmake
target_link_libraries(logic.tests PRIVATE logic gtest_main gtest)
```
This tells the linker:
- `logic` - Link the logic library (our solvers)
- `gtest_main` - Google Test's main() function
- `gtest` - Google Test framework

**Public vs Private**:
- `PUBLIC`: Visible to targets linking against this target
- `PRIVATE`: Only used internally

## Troubleshooting

### "CMake not found"
```bash
# Install CMake
sudo apt install cmake
# Or verify it's in PATH
cmake --version
```

### "clang++ not found"
```bash
sudo apt install clang
which clang++
```

### Build failures with "gtest not found"
```bash
# Ensure FetchContent downloaded gtest
rm -rf cmake_build_clang-linux-debug
cmake --preset clang-linux-debug
cmake --build cmake_build_clang-linux-debug
```

### Tests not found
```bash
# Verify tests were compiled
ls cmake_build_clang-linux-debug/bin/logic.tests

# Run with verbose output
./cmake_build_clang-linux-debug/bin/logic.tests --verbose
```

### Debugging not working
- **Linux**: Verify GDB is installed: `which gdb`
- **Windows**: Verify VS 2022 is properly installed with C++ workload
- Ensure executable was compiled with debug symbols (Debug preset)

### Input files not found at runtime
- Verify `resources/2025/01/example.1.txt` exists
- Check relative path in test: It assumes you're running from project root
- For runner: Check path format uses forward slashes on all platforms

## Useful Commands

```bash
# Create a clean build from scratch
rm -rf cmake_build_clang-linux-debug
cmake --preset clang-linux-debug
cmake --build cmake_build_clang-linux-debug

# Run with verbose output (see exact commands)
cmake --build cmake_build_clang-linux-debug -- VERBOSE=1

# Generate compile_commands.json for advanced tools
cmake --preset clang-linux-debug
# Find it at: cmake_build_clang-linux-debug/compile_commands.json

# Run specific test
./cmake_build_clang-linux-debug/bin/logic.tests --gtest_filter=day01.*

# See CMake configuration variables
cmake -N -L cmake_build_clang-linux-debug | head -30
```

## Learning Resources

- **CMake Documentation**: https://cmake.org/cmake/help/latest/
- **Modern CMake**: https://cliutils.gitlab.io/modern-cmake/
- **Google Test Primer**: https://github.com/google/googletest/blob/main/docs/primer.md
- **C++ Standard**: https://en.cppreference.com/w/cpp

## Project Configuration Reference

### CMakeLists.txt (Root)

Key CMake commands used:

| Command | Purpose |
|---------|---------|
| `cmake_minimum_required()` | Specifies minimum CMake version required |
| `project()` | Declares the project and version |
| `set()` | Sets CMake variables |
| `add_library()` | Defines a library target |
| `add_executable()` | Defines an executable target |
| `target_sources()` | Adds source files to a target |
| `target_include_directories()` | Specifies include paths for a target |
| `target_link_libraries()` | Links dependencies to a target |
| `target_precompile_headers()` | Enables PCH for a target |
| `add_subdirectory()` | Includes subdirectory CMakeLists.txt |
| `FetchContent_Declare()` | Declares external dependency |
| `FetchContent_MakeAvailable()` | Downloads and makes dependency available |
| `enable_testing()` | Enables CTest for test discovery |
| `add_test()` | Registers a test with CTest |

### Compiler Flags

**Linux (Clang)**:
- `-Wall -Wextra -Wpedantic` - Enable strict warnings
- `-Werror` - Treat warnings as errors
- `-O0` (Debug) or `-O3` (Release) - Optimization levels

**Windows (MSVC)**:
- `/W4` - Warning level 4 (equivalent to GCC's -Wall)
- `/WX` - Treat warnings as errors
- `/permissive-` - Stricter C++ standards conformance

## Contributing to Your Own Projects

When you add new challenges:

1. **Keep solver files small** - One solver per day for clarity
2. **Use meaningful variable names** - Your future self will thank you
3. **Add tests early** - Test against examples before running on real input
4. **Document complex logic** - Add comments explaining algorithms
5. **Follow C++23 standards** - Use modern C++ features (ranges, modules, std::print, etc.)

## License

Personal project for learning purposes.

---

**Last Updated**: December 2025
