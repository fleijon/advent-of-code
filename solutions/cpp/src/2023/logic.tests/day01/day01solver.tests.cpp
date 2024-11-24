#include "pch.h"

#include "CppUnitTest.h"
#include "./day01/day01solver.h"
#include <variant>
#include <array>
#include <filesystem>
#include <iostream>
#include <fstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace logictests
{

	TEST_CLASS(day01tests)
	{


	public:

		TEST_METHOD(Should_Solve_sample_part1)
		{
			// arrange
			const std::string filepath = "../../../../../../../../resources/2023/01/example.1.txt";
			auto abs = std::filesystem::absolute(filepath);

			input_format input;

			auto result = LoadInput(filepath, ' ', input);

			Assert::IsTrue(result);

			// act
			auto solution = day01_part1_find_solution(input);

			// assert
			Assert::AreEqual(142, solution);
		}

		TEST_METHOD(Should_Solve_sample_part2)
		{
			// arrange
			const std::string filepath = "../../../../../../../../resources/2023/01/example.2.txt";
			auto abs = std::filesystem::absolute(filepath);

			input_format input;

			auto result = LoadInput(filepath, ' ', input);

			Assert::IsTrue(result);

			// act
			auto solution = day01_part2_find_solution(input);

			// assert
			Assert::AreEqual(281, solution);
		}
	};
}