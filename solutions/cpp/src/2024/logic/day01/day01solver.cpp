#include "day01solver.h"
#include <vector>
#include <functional>
#include <algorithm>
#include <ranges>
#include <array>

std::vector<int> StringVToIntV(const std::vector<std::vector<std::string>>& stringV, int indx)
{
	std::vector<int> result;
	std::ranges::for_each(stringV.cbegin(), stringV.cend(), [indx, &result](const std::vector<std::string>& val) {
		auto const& firstVal = val[indx];
		result.emplace_back(std::stoi(firstVal));
	});

	return result;
}

int day01_part1_find_solution(const input_format& input)
{
	auto first = StringVToIntV(input, 0);
	auto second = StringVToIntV(input, 1);
	int sum = 0;
	namespace ranges = std::ranges;
	ranges::sort(first);
	ranges::sort(second);
	for (size_t i = 0; i < first.size(); i++)
	{
		sum += abs(first[i] - second[i]);
	}

	return sum;
}

int day01_part2_find_solution(const input_format& input)
{
	auto first = StringVToIntV(input, 0);
	auto second = StringVToIntV(input, 1);

	int prod = 0;
	for (size_t i = 0; i < first.size(); i++)
	{
		int val = first[i];
		auto sum = std::ranges::count(second.cbegin(), second.cend(), val);
		prod += val * sum;
	}

	return prod;
}