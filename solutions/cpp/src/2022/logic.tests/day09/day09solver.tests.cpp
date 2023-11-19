#include "pch.h"

#include "CppUnitTest.h"
#include <filesystem>
#include "../../logic/day09/day09solver.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace logictests
{
	TEST_CLASS(day09tests)
	{
	public:

		TEST_METHOD(Should_Create_Moves)
		{
			std::string filepath = "../../../../../../../../resources/2022/09/example.1.txt";
			input_format input;

			auto abs = std::filesystem::absolute(filepath);
			auto canLoadInput = LoadInput(filepath, ' ', input);
			Assert::IsTrue(canLoadInput);

			std::vector<Move> moves;
			auto result = get_moves(input, moves);

			Assert::IsTrue(result);
			Assert::AreEqual(8, (int)moves.size());
		}

		TEST_METHOD(Should_Solve_Example_Part1)
		{
			std::string filepath = "../../../../../../../../resources/2022/09/example.1.txt";
			input_format input;

			auto abs = std::filesystem::absolute(filepath);
			auto canLoadInput = LoadInput(filepath, ' ', input);
			Assert::IsTrue(canLoadInput);

			std::vector<Move> moves;
			auto canLoadMoves = get_moves(input, moves);
			Assert::IsTrue(canLoadMoves);

			BoardState state{ {Position(0, 0), Position(0, 0)} };
			auto visits = calculate_number_of_unique_visits(moves, state);

			Assert::AreEqual(13, (int)visits);
		}
	};
}
