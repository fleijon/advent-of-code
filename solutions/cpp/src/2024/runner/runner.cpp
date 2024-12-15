#include <iostream>
#include <functional>
#include <filesystem>

#include "./utils/preprocess.h"
#include "./day01/day01solver.h"
#include "./day02/day02solver.h"
#include "./day03/day03solver.h"

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
	std::string filepath = std::format("../../../../../resources/2024/{}/input.1.txt", id);
	input_format input;

	auto abs = std::filesystem::absolute(filepath);
	if (auto canLoad = LoadInput(abs.string(), sep, input); !canLoad) {

		std::cout << "Failed to read file input for day " << id << std::endl;
		return;
	}

	solution(input);
}

template<class T>
void Run(const std::function<T(const input_format&)>& solution, std::string id, const std::string& sep = " ")
{
	std::string filepath = std::format("../../../../../resources/2024/{}/input.1.txt", id);
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
	std::cout << "Solution day " << day << " part " << part << ":\n";
	std::cout << solution << "\n\n";
}

void solveDay01(const input_format& input)
{
	auto solution = day01_part1_find_solution(input);
	print_solution("1", "1", solution);

	auto solution2 = day01_part2_find_solution(input);
	print_solution("1", "2", solution2);
}

void solveDay02(const input_format& input)
{
	auto solution = day02_part1_find_solution(input);
	print_solution("2", "1", solution);

	auto solution2 = day02_part2_find_solution(input);
	print_solution("2", "2", solution2);
}

void solveDay03(const input_format& input)
{
	auto solution = day03_part1_find_solution(input);
	print_solution("3", "1", solution);

	auto solution2 = day03_part2_find_solution(input);
	print_solution("3", "2", solution2);
}

int main()
{
	Run<void>(solveDay01, "01", "   ");
	Run<void>(solveDay02, "02", " ");
	Run<void>(solveDay03, "03", " ");

	std::cout << "Allocation Count " << s_AllocationCount << std::endl;
	std::cout << "Allocation size " << s_AllocationSize << " bytes" << std::endl;
}

