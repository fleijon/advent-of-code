#include "pch.h"

#include "CppUnitTest.h"
#include "./day04/day04solver.h"
#include <variant>
#include <array>
#include <filesystem>
#include <iostream>
#include <fstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace logictests
{

	TEST_CLASS(day04tests)
	{


	public:

		TEST_METHOD(Should_Solve_sample_part1)
		{
			// arrange
			const std::string filepath = "../../../../../../../../resources/2023/04/example.1.txt";
			auto abs = std::filesystem::absolute(filepath);

			input_format input;

			auto result = LoadInput(filepath, ':', input);

			Assert::IsTrue(result);

			// act
			auto solution = SolveDay04Part1(input);

			// assert

			Assert::AreEqual(13, solution);
		}

		TEST_METHOD(Should_Solve_sample_part2)
		{
			// arrange
			const std::string filepath = "../../../../../../../../resources/2023/04/example.1.txt";
			auto abs = std::filesystem::absolute(filepath);

			input_format input;

			auto result = LoadInput(filepath, ':', input);

			Assert::IsTrue(result);

			// act
			auto solution = SolveDay04Part2(input);

			// assert

			Assert::AreEqual(30, solution);
		}
	};
}