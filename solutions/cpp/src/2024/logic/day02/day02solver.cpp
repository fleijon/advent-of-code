#include "day02solver.h"
#include <vector>
#include <functional>
#include <algorithm>
#include <ranges>
#include <array>
#include <iostream>

int day02_part1_find_solution(const input_format& input)
{
	int sum = 0;
	for(auto& row:input)
	{
		int direction = 0;
		int previous = -1;
		for (auto& entry : row)
		{
			auto val = std::stoi(entry);
			if (previous != -1)
			{
				auto diff = previous - val;
				if (diff == 0)
				{
					direction = 0;
					break;
				}
				else if (abs(diff) > 3)
				{
					direction = 0;
					break;
				}
				auto newDirection = diff < 0 ? -1 : 1;
				if (direction == 0)
				{
					direction = newDirection;
				}
				else if (newDirection != direction)
				{
					direction = 0;
					break;
				}
			}

			previous = val;
		}

		if (direction != 0) {
			sum++;
		}
	}

	return sum;
}

bool is_report_safe(const std::vector<std::string>& report)
{
	int direction = 0;
	int previous = -1;
	for (size_t i = 0; i < report.size(); i++)
	{
		const auto val = std::stoi(report[i]);
		if (previous != -1)
		{
			const auto diff = val - previous;
			if (abs(diff) > 3)
			{
				return false;
			}
			else if (diff == 0)
			{
				return false;
			}

			auto newDirection = diff < 0 ? -1 : 1;
			if (direction == 0) {
				direction = newDirection;
			}
			else if (newDirection != direction){
				return false;
			}
		}

		previous = val;
	}
}

template<typename T>
std::vector<T> ExludeByIndex(const std::vector<std::string>& original, size_t index)
{
	std::vector<std::string> out = {};
	for (size_t i = 0; i < original.size(); i++)
	{
		if (i != index)
		{
			out.emplace_back(original[i]);
		}
	}

	return out;
}

bool is_report_safe_with_damper(const std::vector<std::string>& report)
{
	if (!is_report_safe(report))
	{
		std::vector<std::string> truncatedReport = {};
		for (auto i = 0; i  < report.size(); i++)
		{
			truncatedReport = ExludeByIndex<std::string>(report, i);
			if (is_report_safe(truncatedReport))
			{
				return true;
			}
		}

		return false;
	}

	return true;
}

int day02_part2_find_solution(const input_format& input)
{
	int sum = 0;
	for (size_t i = 0; i < input.size(); i++)
	{
		const auto& report = input[i];
		if (is_report_safe_with_damper(report))
		{
			sum++;
		}
	}

	return sum;
}
