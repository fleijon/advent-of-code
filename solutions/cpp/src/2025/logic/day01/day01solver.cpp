#include "day01solver.h"
#include <algorithm>
#include <iostream>
#include <ranges>
#include <tuple>
#include <vector>

enum Rotation { Right, Left };
using Operation = std::tuple<Rotation, int>;
Operation split(const std::string &value);

long long day01_part1_find_solution(const input_format &input) {

  std::vector<Operation> operations;
  operations.reserve(input.size());
  for (const auto &line : input) {
    operations.push_back(split(line));
  }

  int count = 0;
  int currentPos = 50;

  for (const Operation &oper : operations) {
    auto [rot, times] = oper;

    if (rot == Rotation::Left) {
      currentPos -= times;
    } else {
      currentPos += times;
    }

    // Wrap around 0-99
    if (currentPos > 99 || currentPos < 0) {
      currentPos = ((currentPos % 100) + 100) % 100;
    }

    if (currentPos == 0) {
      count++;
    }

    // Print "Rotation: [R/L], Times: [N], Position: [P]"
    const char rotationChar = (rot == Rotation::Right) ? 'R' : 'L';
    std::cout << "Rotation: " << rotationChar << ", Times: " << times
              << ", Position: " << currentPos << std::endl;
  }

  return count;
}

long long day01_part2_find_solution(const input_format &) {
  // TODO: Implement Day 1 Part 2 solution
  return 0;
}

Operation split(const std::string &value) {

  const char rotation = value.at(0);
  const int moves = std::stoi(value.substr(1));

  const Rotation direction =
      (rotation == 'R') ? Rotation::Right : Rotation::Left;

  return {direction, moves};
}
