#include "day01/day01solver.h"
#include "pch.h"
#include "utils/preprocess.h"

// Example test for Day 1 Part 1
TEST(day01, part1_example) {
  const std::string filepath = "../../../../resources/2025/01/example.1.txt";
  input_format loadedInput;

  // Note: This test will fail until you create the example input file
  // and implement the solver logic
  if (!LoadInput(filepath, "\n", loadedInput)) {
    GTEST_SKIP() << "Example input file not found: " << filepath;
  }

  [[maybe_unused]] auto result = day01_part1_find_solution(loadedInput);
  EXPECT_EQ(result, 3);
}

// Example test for Day 1 Part 2
TEST(day01, part2_example) {
  const std::string filepath = "../../../../resources/2025/01/example.1.txt";
  input_format loadedInput;

  if (!LoadInput(filepath, "\n", loadedInput)) {
    GTEST_SKIP() << "Example input file not found: " << filepath;
  }

  [[maybe_unused]] auto result = day01_part2_find_solution(loadedInput);
  // EXPECT_EQ(result, expected_value);
}
