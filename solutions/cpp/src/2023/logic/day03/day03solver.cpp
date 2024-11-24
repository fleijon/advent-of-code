
#include "day03solver.h"
#include <map>
#include <memory>
#include <cmath>
#include <string>
#include <format>
#include <iostream>
#include <numeric>

struct NumberCoord {
	int xFrom;
	int xTo;
	int y;
	int value;
	bool isAdjacent;
};

void get_coords(std::string_view row, std::vector<NumberCoord>& coords, int y, const input_format& input);

int get_value(std::string_view row, int from, int take);

void get_partial_sum_back(int i, const std::string& row, std::vector<int>& parts)
{
	if (i > 0 && isdigit(row[i - 1]))
	{
		get_partial_sum_back(i-1, row, parts);
	}

	parts.push_back(row[i] - '0');
}

void get_partial_sum_forward(int i, const std::string& row, std::vector<int>& parts)
{
	parts.push_back(row[i] - '0');

	if (i < row.size() - 1 && isdigit(row[i+1]))
	{
		get_partial_sum_forward(i+1, row, parts);
	}
}

void get_partial_sum(int i, const std::string& row, std::vector<int>& parts)
{
	if (i > 0 && isdigit(row[i - 1]))
	{
		get_partial_sum_back(i-1, row, parts);
	}

	get_partial_sum_forward(i, row, parts);
}

void get_partial_sums(int i, int j, const input_format& input, std::vector<int>& partialSums)
{
	auto width = input[0][0].size();
	auto heigth = input.size();

	auto toX = i < width - 1 ? i + 1 : i;
	auto toY = j < heigth - 1 ? j + 1 : j;
	for (auto a = i > 0 ? i - 1 : 0; a < toX + 1; a++)
	{
		for (auto b = j > 0 ? j - 1 : 0 ; b < toY + 1; b++)
		{
			auto row = input[b][0];

			if (isdigit(row[a]))
			{
				std::vector<int> parts;
				get_partial_sum(a, row, parts);
				auto partSum = 0;

				for (auto k = 0; k < parts.size(); k++)
				{
					auto r = (parts.size()-1) - k;
					partSum += std::pow(10, r) * parts[k];
				}

				partialSums.push_back(partSum);
			}
		}
	}
}

void get_uniques(const std::vector<int>& source, std::vector<int>& target)
{
	for (auto ele : source)
	{
		if (std::ranges::find(target.cbegin(), target.cend(), ele) == target.cend()) {
			target.push_back(ele);
		}
	}
}

int SolveDay03Part2(const input_format& input)
{
	auto sum = 0;

	for (auto j = 0; j < input.size(); j++)
	{
		const auto& entry = input[j][0];

		for (auto i = 0; i < entry.length(); i++)
		{
			if (entry[i] == '*')
			{
				std::vector<int> partialSums{};
				get_partial_sums(i, j, input, partialSums);
				std::vector<int> uniqueSums;
				get_uniques(partialSums, uniqueSums);

				if (uniqueSums.size() == 2)
				{
					sum += uniqueSums[0] * uniqueSums[1];
				}

			}
		}
	}

	return sum;
}

bool is_symbol(char c) {
	return !isdigit(c) && c != '.';
}

int SolveDay03Part1(const input_format& input)
{
	auto sum = 0;
	auto y = 0;

	for (const auto& row : input)
	{
		const auto& entry = row[0];
		std::vector<NumberCoord> coords;

		get_coords(entry, coords, y, input);

		for (const auto& cord : coords)
		{
			if(cord.isAdjacent)
			{
				sum += cord.value;
			}
		}

		y++;
	}

	return sum;
}


bool is_adjacent(int x, int y, const input_format& input)
{
	auto max = input[0][0].length() - 1;
	auto maxY = input.size() - 1;

	for (int i = x - 1; i < x + 2; i ++) {
		if (i < 0 || i > max) {
			continue;
		}

		for (int j = y - 1; j < y + 2; j++)
		{
			if (j < 0 || j > maxY) {
				continue;
			}
			auto l = input[j][0][i];
			if (is_symbol(l))
			{
				return true;
			}
		}
	}

	return false;
}

void get_coords(std::string_view row, std::vector<NumberCoord>& coords, int y, const input_format& input)
{
	auto i = 0;
	auto startx = -1;
	auto endx = -1;
	auto isAdj = false;
	while (i < row.length())
	{
		if (isdigit(row[i]))
		{
			if (startx == -1)
			{
				startx = i;
				isAdj = isAdj || is_adjacent(i, y, input);
			}
			else
			{
				endx = i;
				isAdj = isAdj || is_adjacent(i, y, input);
			}
		}
		else
		{
			if (startx != -1)
			{
				endx = endx == -1 ? startx : endx;
				auto value = get_value(row, startx, endx-startx+1);
				NumberCoord a{ startx, endx, y, value };

				a.isAdjacent = isAdj;

				coords.push_back(a);

				startx = -1;
				endx = -1;
				isAdj = false;
			}
		}

		i++;
	}

	if (startx != -1)
	{
		endx = endx == -1 ? startx : endx;
		auto value = get_value(row, startx, endx-startx+1);
		NumberCoord a{ startx, endx, y, value };

		a.isAdjacent = isAdj;

		coords.push_back(a);
	}
}

int get_value(std::string_view row, int from, int take)
{
	auto res = 0;
	for (auto i = 0; i < take; i++) {
		auto j = (from+take-1) - i;
		auto k = row[j];
		res += std::pow(10, i) * (k - '0');
	}

	return res;
}

