#include "pch.h"

#include "CppUnitTest.h"
#include "./day02/day02solver.h"
#include <variant>
#include <array>
#include <filesystem>
#include <iostream>
#include <fstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace logictests
{

	TEST_CLASS(day02tests)
	{


	public:

		TEST_METHOD(Should_Solve_sample_part1)
		{
			// arrange
			Game proposalGame;
			proposalGame.Blue = 14;
			proposalGame.Red = 12;
			proposalGame.Green = 13;

			const std::string filepath = "../../../../../../../../resources/2023/02/example.1.txt";
			auto abs = std::filesystem::absolute(filepath);

			input_format input;

			auto result = LoadInput(filepath, ':', input);

			Assert::IsTrue(result);

			// act
			auto solution = solve_day02_part1(input, proposalGame);

			// assert
			Assert::AreEqual(8, solution);
		}

		TEST_METHOD(Should_Solve_sample_part2)
		{
			// arrange
			const std::string filepath = "../../../../../../../../resources/2023/02/example.1.txt";
			auto abs = std::filesystem::absolute(filepath);

			input_format input;

			auto result = LoadInput(filepath, ':', input);

			Assert::IsTrue(result);

			// act
			auto solution = solve_day02_part2(input);

			// assert
			Assert::AreEqual(2286, solution);
		}
	};
}