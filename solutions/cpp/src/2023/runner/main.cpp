#include <iostream>
#include <functional>
#include <filesystem>
#include "./utils/preprocess.h"
#include "./day01/day01solver.h"
#include "./day02/day02solver.h"
#include "./day03/day03solver.h"
#include "./day04/day04solver.h"
#include <iostream>

static int s_AllocationCount = 0;
static int s_AllocationSize = 0;

void* operator new(size_t size)
{
	s_AllocationCount++;
	s_AllocationSize += size;
	return malloc(size);
}

template<class T>
void Run(const std::function<T(const input_format&)>& solution, std::string id, char sep = ' ')
{
	std::string filepath = std::format("../../../../../resources/2023/{}/input.1.txt", id);
	input_format input;

	auto abs = std::filesystem::absolute(filepath);
	if (auto canLoad = LoadInput(abs.string(), sep, input); !canLoad) {

		std::cout << "Failed to read file input for day " << id << std::endl;
		return;
	}

	solution(input);
}

void print_solution(const std::string& day, const std::string& part, int solution)
{
	std::cout << "Solution day " << day << "part" << part << ": " << std::endl;
	std::cout << solution << std::endl;
}

void solveDay01(const input_format& input)
{
	auto solution = day01_part1_find_solution(input);
	print_solution("1", "1", solution);
}

void solveDay01Part2(const input_format& input)
{
	auto solution = day01_part2_find_solution(input);
	print_solution("1", "2", solution);
}

void solveDay02Part1(const input_format& input)
{
	Game proposalGame;
	proposalGame.Blue = 14;
	proposalGame.Red = 12;
	proposalGame.Green = 13;

	auto solution = solve_day02_part1(input, proposalGame);
	print_solution("2", "1", solution);
}

void solveDay02Part2(const input_format& input)
{
	auto solution = solve_day02_part2(input);
	print_solution("2", "2", solution);
}

void solveDay03Part1(const input_format& input)
{
	auto solution = SolveDay03Part1(input);
	print_solution("3", "1", solution);
}

void solveDay03Part2(const input_format& input)
{
	auto solution = SolveDay03Part2(input);
	print_solution("3", "2", solution);
}

void solveDay04Part1(const input_format& input)
{
	auto solution = SolveDay04Part1(input);
	print_solution("4", "1", solution);
}

void main()
{
	Run<void>(solveDay01, "01");
	Run<void>(solveDay01Part2, "01");
	Run<void>(solveDay02Part1, "02", ':');
	Run<void>(solveDay02Part2, "02", ':');
	Run<void>(solveDay03Part1, "03", ' ');
	Run<void>(solveDay03Part2, "03", ' ');
	Run<void>(solveDay04Part1, "04", ':');

	std::cout << "Allocation Count " << s_AllocationCount << std::endl;
	std::cout << "Allocation size " << s_AllocationSize << " bytes" << std::endl;
}
