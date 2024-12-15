#include "pch.h"
#include "utils/preprocess.h"
#include "day01/day01solver.h"
#include "day02/day02solver.h"
#include "day03/day03solver.h"

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

TEST(day02, part1) {
	const std::string filepath = "../../../../../../../../resources/2024/02/example.1.txt";
	input_format loadedInput;
	if (!LoadInput(filepath, " ", loadedInput))
	{
		return;
	}
	auto result = day02_part1_find_solution(loadedInput);
	EXPECT_EQ(result, 2);
}

TEST(day02, part2) {
	const std::string filepath = "../../../../../../../../resources/2024/02/example.1.txt";
	input_format loadedInput;
	if (!LoadInput(filepath, " ", loadedInput))
	{
		return;
	}
	auto result = day02_part2_find_solution(loadedInput);
	EXPECT_EQ(result, 4);
}

TEST(day02, is_report_safe_with_damper) {
	std::vector<std::string> values = { "28", "31", "34", "35", "38", "39", "43"};
	auto result = is_report_safe_with_damper(values);

	EXPECT_EQ(result, true);
}

TEST(day03, mul) {

	auto mulCmd = "mul(2,3)";
	auto result = mul(mulCmd);

	EXPECT_EQ(result, 6);

	mulCmd = "mul(20,3)";
	result = mul(mulCmd);

	EXPECT_EQ(result, 60);
}

TEST(day03, part1) {
	const std::string filepath = "../../../../../../../../resources/2024/03/example.1.txt";
	input_format loadedInput;
	if (!LoadInput(filepath, " ", loadedInput))
	{
		return;
	}
	auto result = day03_part1_find_solution(loadedInput);
	EXPECT_EQ(result, 161);
}

TEST(day03, part2) {
	const std::string filepath = "../../../../../../../../resources/2024/03/example.2.txt";
	input_format loadedInput;
	if (!LoadInput(filepath, " ", loadedInput))
	{
		return;
	}
	auto result = day03_part2_find_solution(loadedInput);
	EXPECT_EQ(result, 48);
}