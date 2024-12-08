#include "pch.h"
#include "utils/preprocess.h"
#include "day01/day01solver.h"

TEST(day01, part1) {
	const std::string filepath = "../../../../../../../../resources/2024/01/example.1.txt";
	input_format loadedInput;
	if (!LoadInput(filepath, "   ", loadedInput))
	{
		return;
	}
	auto result = day01_part1_find_solution(loadedInput);
	EXPECT_EQ(result, 11);
}

TEST(day01, part2) {
	const std::string filepath = "../../../../../../../../resources/2024/01/example.1.txt";
	input_format loadedInput;
	if (!LoadInput(filepath, "   ", loadedInput))
	{
		return;
	}
	auto result = day01_part2_find_solution(loadedInput);
	EXPECT_EQ(result, 31);
}