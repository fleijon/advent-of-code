#include "day03solver.h"
#include <vector>
#include <functional>
#include <algorithm>
#include <ranges>
#include <array>
#include <iostream>
#include <regex>

int mul(const std::string& mulCmd)
{
    auto pattern = R"(^mul\((\d*),(\d*)\))";
	std::regex mulRegex(pattern);
	auto mBegin = std::sregex_iterator(mulCmd.begin(), mulCmd.end(), mulRegex);
    auto mEnd = std::sregex_iterator();

    int product = 0;
    bool active = false;
    for (std::sregex_iterator i = mBegin; i != mEnd; ++i)
    {
        std::smatch match = *i;
        for (size_t j = 1; j < match.size(); j++)
        {
            if (!active)
            {
                product = 1;
                active = true;
            }
			std::string match_str = match[j];
			auto val = std::stoi(match_str);
			product *= val;
        }
    }

    return product;
}

int day03_part1_find_solution(const input_format& input)
{
    auto prodSum = 0;
    for (size_t i = 0; i < input.size(); i++)
    {
        for (size_t k = 0; k < input[i].size(); k++)
        {
			const auto& row = input[i][k];
			auto cIdx = 0;
			auto in = false;
			for (size_t j = 0; j < row.size(); j++)
			{
				if (row[j] == 'm')
				{
					cIdx = j;
					in = true;
				}
				else if (in && row[j] == ')')
				{
					auto substring = row.substr(cIdx, j-cIdx+1);
					auto prod = mul(substring);

					prodSum += prod;
					in = false;
				}
			}
        }
    }

    return prodSum;
}

int day03_part2_find_solution(const input_format& input)
{
    auto prodSum = 0;
	auto isDo = true;
    for (size_t i = 0; i < input.size(); i++)
    {
        for (size_t k = 0; k < input[i].size(); k++)
        {
			const auto& row = input[i][k];
			auto cIdx = 0;
			auto in = false;
			for (size_t j = 0; j < row.size(); j++)
			{
				if (row[j] == 'd') {
					if (row.substr(j, 4) == "do()") {
						isDo = true;
					}
					else if (row.substr(j, 7) == "don't()")
					{
						isDo = false;
					}
				}
				else if (row[j] == 'm')
				{
					cIdx = j;
					in = true;
				}
				else if (in && row[j] == ')')
				{
					in = false;
					if (isDo)
					{
						auto substring = row.substr(cIdx, j-cIdx+1);
						auto prod = mul(substring);

						if (prod != 0) {
							std::cout << substring << " " << prod << std::endl;
						}

						prodSum += prod;
					}
				}
			}
        }
    }

	return prodSum;
}
