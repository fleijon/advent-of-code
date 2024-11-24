#include "pch.h"

#include "CppUnitTest.h"
#include <filesystem>
#include "../../logic/day11/day11solver.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace logictests
{
	TEST_CLASS(day11tests)
	{

		TEST_METHOD(Should_Parse_Sample_Input)
		{
			std::string filepath = "../../../../../../../../resources/2022/11/example.1.txt";
			input_format input;

			auto abs = std::filesystem::absolute(filepath);
			auto canLoadInput = LoadInput(abs.string(), ' ', input);
			Assert::IsTrue(canLoadInput);

			std::vector<Monkey> monkeys;
			auto canParseInput = ParseInput(input, monkeys);
			Assert::IsTrue(canParseInput);
		}

		TEST_METHOD(Should_Solve_Example) {
			std::string filepath = "../../../../../../../../resources/2022/11/example.1.txt";
			input_format input;

			auto abs = std::filesystem::absolute(filepath);
			auto canLoadInput = LoadInput(abs.string(), ' ', input);
			Assert::IsTrue(canLoadInput);

			std::vector<Monkey> monkeys;
			auto canParseInput = ParseInput(input, monkeys);
			Assert::IsTrue(canParseInput);

			auto result = CalculateMonkeyBusiness(monkeys);

			Assert::AreEqual(10605, result);
		}

	};
}