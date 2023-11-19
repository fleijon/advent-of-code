#include "pch.h"

#include "CppUnitTest.h"
#include <filesystem>
#include "../../logic/day10/day10solver.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace logictests
{
	TEST_CLASS(day10tests)
	{
		TEST_METHOD(Should_Create_Instructions)
		{
			std::string filepath = "../../../../../../../../resources/2022/10/example.1.txt";
			input_format input;

			auto abs = std::filesystem::absolute(filepath);
			auto canLoadInput = LoadInput(filepath, ' ', input);
			Assert::IsTrue(canLoadInput);

			std::vector<std::unique_ptr<Instruction>> instructions;
			auto canGetInstructions = LoadInstructions(input, instructions);
			Assert::IsTrue(canGetInstructions);
		}

		TEST_METHOD(Should_Apply_Instructions)
		{
			std::string filepath = "../../../../../../../../resources/2022/10/example.1.txt";
			input_format input;

			auto abs = std::filesystem::absolute(filepath);
			auto canLoadInput = LoadInput(filepath, ' ', input);
			Assert::IsTrue(canLoadInput);

			std::vector<std::unique_ptr<Instruction>> instructions;
			auto canGetInstructions = LoadInstructions(input, instructions);
			Assert::IsTrue(canGetInstructions);

			std::vector<CycleState> cycles;
			cycles.emplace_back(1, 1);

			auto canApplyInstructions = ApplyInstructions(instructions, cycles);
			Assert::IsTrue(canApplyInstructions);

			Assert::AreEqual(220, cycles[219].cycle);
			Assert::AreEqual(18, cycles[219].value);
		}

		TEST_METHOD(Should_Calculate_Signal_Strength)
		{
			std::string filepath = "../../../../../../../../resources/2022/10/example.1.txt";
			input_format input;

			auto abs = std::filesystem::absolute(filepath);
			auto canLoadInput = LoadInput(filepath, ' ', input);

			std::vector<std::unique_ptr<Instruction>> instructions;
			auto canGetInstructions = LoadInstructions(input, instructions);

			std::vector<CycleState> cycles;
			cycles.emplace_back(1, 1); // Init state

			auto canApplyInstructions = ApplyInstructions(instructions, cycles);

			std::vector<int> cycleValues{20, 60, 100, 140, 180, 220};
			int totalStrength = CalculateSignalStrength(cycleValues, cycles);

			Assert::AreEqual(13140, totalStrength);
		}

		TEST_METHOD(Should_Create_CRT_Of_Example)
		{
			std::string filepath = "../../../../../../../../resources/2022/10/example.1.txt";
			input_format input;

			auto abs = std::filesystem::absolute(filepath);
			auto canLoadInput = LoadInput(filepath, ' ', input);

			std::vector<std::unique_ptr<Instruction>> instructions;
			auto canGetInstructions = LoadInstructions(input, instructions);

			std::vector<CycleState> cycles;
			cycles.emplace_back(1, 1); // Init state

			auto canApplyInstructions = ApplyInstructions(instructions, cycles);

			auto result = CreateCRTOutput(cycles);
			const auto start10 = result.substr(0, 10);
			std::string expectedFirst10 = "##..##..##";

			Assert::AreEqual(expectedFirst10, start10);
		}
	};
}
