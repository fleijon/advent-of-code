#include "pch.h"

#include "CppUnitTest.h"
#include "./day03/day03solver.h"
#include <variant>
#include <array>
#include <filesystem>
#include <iostream>
#include <fstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace logictests
{

	TEST_CLASS(day03tests)
	{


	public:

		TEST_METHOD(Should_Solve_sample_part1)
		{
			// arrange
			const std::string filepath = "../../../../../../../../resources/2023/03/example.1.txt";
			auto abs = std::filesystem::absolute(filepath);

			input_format input;

			auto result = LoadInput(filepath, ':', input);

			Assert::IsTrue(result);

			// act
			auto solution = SolveDay03Part1(input);

			// assert

			Assert::AreEqual(4361, solution);
		}

		TEST_METHOD(Should_Solve_sample_part2)
		{
			// arrange
			const std::string filepath = "../../../../../../../../resources/2023/03/example.1.txt";
			auto abs = std::filesystem::absolute(filepath);

			input_format input;

			auto result = LoadInput(filepath, ':', input);

			Assert::IsTrue(result);

			// act
			auto solution = SolveDay03Part2(input);

			// assert

			Assert::AreEqual(467835, solution);
		}
	};
}