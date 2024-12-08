#include "pch.h"

#include "CppUnitTest.h"
#include <variant>
#include <array>
#include <filesystem>
#include <iostream>
#include <fstream>
#include "../logic/utils/preprocess.h"
#include "../logic/day05/day05solver.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace logictests
{

	TEST_CLASS(day05tests)
	{


	public:

		TEST_METHOD(Should_Solve_sample_part1)
		{
			// arrange
			const std::string filepath = "../../../../../../../../resources/2023/05/example.1.txt";
			auto abs = std::filesystem::absolute(filepath);
			input_format input;
			auto result = LoadInput(filepath, ' ', input);
			Assert::IsTrue(result);

			// act
			auto min = SolveDay05Part1(input);

			// assert
			Assert::AreEqual(35, min);
		}

		TEST_METHOD(Should_Solve_sample_part2)
		{
			// arrange
			const std::string filepath = "../../../../../../../../resources/2023/05/example.1.txt";
			auto abs = std::filesystem::absolute(filepath);
			input_format input;
			auto result = LoadInput(filepath, ':', input);
			Assert::IsTrue(result);

			// act

			// assert
		}
	};
}