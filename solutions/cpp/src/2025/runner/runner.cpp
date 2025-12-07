#include <filesystem>
#include <functional>
#include <iostream>
#include <sstream>

#include "day01/day01solver.h"
#include "utils/preprocess.h"

/// <summary>
/// Run a solver function for a specific day and part.
/// This template function loads the input file, calls the solver,
/// and displays the result.
/// </summary>
template <class T>
void RunSolver(const std::function<T(const input_format &)> &solver,
               const std::string &day_id, const std::string &separator = "\n") {
  // Construct path to input file
  // The executable is at: cmake_build_clang-linux-debug/bin/runner
  // From there, go up 4 levels to reach the project root where resources/ is
  // located Then navigate to: resources/2025/DD/input.1.txt

  std::stringstream ss;
  ss << "../../../../resources/2025/" << day_id << "/input.1.txt";
  std::string filepath = ss.str();

  input_format input;

  // Convert to absolute path to handle different working directories
  auto abs_path = std::filesystem::absolute(filepath);

  std::cout << "Attempting to load: " << abs_path << std::endl;

  if (!LoadInput(abs_path.string(), separator, input)) {
    std::cout << "Failed to read input file for day " << day_id << ": "
              << abs_path << std::endl;
    return;
  }

  std::cout << "Day " << day_id << " result: " << solver(input) << std::endl;
}

int main() {
  std::cout << "=== Advent of Code 2025 ===" << std::endl;

  // Example: Run Day 1
  // Uncomment and update this when you have implemented the solver
  RunSolver<int>(day01_part1_find_solution, "01");
  // RunSolver<int>(day01_part2_find_solution, "01");

  return 0;
}
