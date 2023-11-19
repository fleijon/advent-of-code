#include "pch.h"

#include "CppUnitTest.h"
#include <filesystem>
#include "../../logic/day08/day08solver.h"
#include "../../logic/utils/load.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace logictests
{
	TEST_CLASS(day08tests)
	{

	public:

		TEST_METHOD(Should_Create_Matrix)
		{
			auto matrix = Matrix(5, 4);

			Assert::AreEqual(5, (int)matrix.values.size());
			Assert::AreEqual(4, (int)matrix.values[0].size());
		}

		TEST_METHOD(Should_Solve_Sample) {

			std::string filepath = "../../../../../../../../resources/2022/08/example.1.txt";
			input_format input;

			auto abs = std::filesystem::absolute(filepath);
			auto canLoadInput = LoadInput(filepath, ' ', input);
			Assert::IsTrue(canLoadInput);

			auto matrix = CreateMatrix(input);

			Assert::AreEqual(5, (int)matrix->values.size());

			auto result = calculate_number_of_visible_trees(matrix.get());

			Assert::AreEqual(21, result);
		}

		TEST_METHOD(Should_Solve_Part2_Sample) {

			std::string filepath = "../../../../../../../../resources/2022/08/example.1.txt";
			input_format input;

			auto abs = std::filesystem::absolute(filepath);
			auto canLoadInput = LoadInput(filepath, ' ', input);
			Assert::IsTrue(canLoadInput);

			auto matrix = CreateMatrix(input);

			Assert::AreEqual(5, (int)matrix->values.size());

			auto result = calculate_highest_scenic_score(matrix.get());

			Assert::AreEqual(8, result);
		}


	};
}
