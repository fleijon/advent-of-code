#include "../logic/day07/day07solver.h"
#include <filesystem>
#include <iostream>
#include "../logic/day08/day08solver.h"
#include "../logic/day09/day09solver.h"
#include "../logic/day10/day10solver.h"
#include <functional>
#include "../logic/day11/day11solver.h"

using solution = std::function<void(const input_format&)>;

void Run(const solution& solution, std::string id)
{
	std::string filepath = std::format("../../../../../resources/2022/{}/input.1.txt", id);
	input_format input;

	auto abs = std::filesystem::absolute(filepath);
	if (auto canLoad = LoadInput(filepath, ' ', input); !canLoad) {

		std::cout << "Failed to read file input for day 07!" << std::endl;
		return;
	}

	solution(input);
}

void solve_day07_part2(const input_format& input) {
	const int totDiskSpace = 70000000;
	const int requireDiskSpace = 30000000;

	std::shared_ptr<Directory> nullRoot;
	auto root_s = std::make_shared<Directory>("root", nullRoot);

	build_directory_tree(root_s, input);

	int sizeToFree = free_space(root_s, totDiskSpace, requireDiskSpace);

	std::cout << "Solution day 07 part2: " << sizeToFree << std::endl;
}


void solve_day07_part(const input_format& input) {
	std::shared_ptr<Directory> nullRoot;
	auto root_s = std::make_shared<Directory>("root", nullRoot);

	build_directory_tree(root_s, input);

	int total = calculate_total_size_with_max(root_s, 100000);

	std::cout << "Solution day 07 part1: " << total << std::endl;
}

void solve_day08_part1(const input_format& input) {
	auto matrix = CreateMatrix(input);
	auto result = calculate_number_of_visible_trees(matrix.get());

	std::cout << "Solution day 08 part1: " << result << std::endl;
}

void solve_day08_part2(const input_format& input) {
	auto matrix = CreateMatrix(input);

	auto result = calculate_highest_scenic_score(matrix.get());

	std::cout << "Solution day 08 part2: " << result << std::endl;
}

void solve_day09_part1(const input_format& input)
{
	std::vector<Move> moves;
	auto canLoadMoves = get_moves(input, moves);

	BoardState state{ {Position(0, 0), Position(0, 0)} };
	auto visits = calculate_number_of_unique_visits(moves, state);

	std::cout << "Solution day 09 part1: " << visits << std::endl;
}

void solve_day09_part2(const input_format& input)
{
	std::vector<Move> moves;

	auto canLoadMoves = get_moves(input, moves);

	BoardState state{
		{
			Position(0, 0), 
			Position(0, 0),
			Position(0, 0),
			Position(0, 0),
			Position(0, 0),
			Position(0, 0),
			Position(0, 0),
			Position(0, 0),
			Position(0, 0),
			Position(0, 0),
		}
	};
	auto visits = calculate_number_of_unique_visits(moves, state);

	std::cout << "Solution day 09 part2: " << visits << std::endl;
}

void solve_day10_part1(const input_format& input)
{
	std::vector<std::unique_ptr<Instruction>> instructions;
	auto canGetInstructions = LoadInstructions(input, instructions);

	std::vector<CycleState> cycles;
	cycles.emplace_back(1, 1); // Init state

	auto canApplyInstructions = ApplyInstructions(instructions, cycles);

	std::vector<int> cycleValues{20, 60, 100, 140, 180, 220};
	int totalStrength = CalculateSignalStrength(cycleValues, cycles);

	std::cout << "Solution day 10 part1: " << totalStrength << std::endl;
}



void solve_day10_part2(const input_format& input)
{
	std::vector<std::unique_ptr<Instruction>> instructions;
	auto canGetInstructions = LoadInstructions(input, instructions);

	std::vector<CycleState> cycles;
	cycles.emplace_back(1, 1); // Init state

	auto canApplyInstructions = ApplyInstructions(instructions, cycles);

	const auto crt = CreateCRTOutput(cycles);

	std::cout << "Solution day 10 part2:" << std::endl;

	int row = 0;
	for (int i = 1; i < 241; i++)
	{
		std::cout << crt[i-1];
		const auto expectedRow = (int)(i / 40);
		if (row != expectedRow) {
			row = expectedRow;
			std::cout << std::endl;
		}
	}
}

void solve_day11_part1(const input_format& input)
{
	std::vector<Monkey> monkeys;
	ParseInput(input, monkeys);

	auto result = CalculateMonkeyBusiness(monkeys);

	std::cout << "Solutions day 11 part 1: " << result << std::endl;
}

void main() {
	Run(solve_day07_part, "07");
	Run(solve_day07_part2, "07");
	Run(solve_day08_part1, "08");
	Run(solve_day08_part2, "08");
	Run(solve_day09_part1, "09");
	Run(solve_day09_part2, "09");
	Run(solve_day10_part1, "10");
	Run(solve_day10_part2, "10");
	Run(solve_day11_part1, "11");
	std::cin.get();
}