
#include "day01solver.h"
#include <vector>
#include <functional>
#include <algorithm>

int day01_part1_find_solution(const input_format& input)
{
	auto sum = 0;
	for (const auto& row : input)
	{
		const auto& entry = row[0];
		auto first = std::ranges::find_if(entry.cbegin(), entry.cend(), [](char c) { return isdigit(c); });
		auto last = std::ranges::find_if(std::reverse_iterator(entry.cend()), std::reverse_iterator(entry.cbegin()), [](char c) { return isdigit(c); });

		if (first != entry.cend() && last != std::reverse_iterator(entry.cbegin()))
		{
			std::string v{*first, *last};

			sum += std::stoi(v);
		}

	}

	return sum;
}

struct number {
	std::string name;
	char charValue;
};

const number one{ "one", '1' };
const number two{ "two", '2' };
const number three{ "three", '3' };
const number four{ "four", '4' };
const number five{ "five", '5' };
const number six{ "six", '6' };
const number seven{ "seven", '7' };
const number eight{ "eight", '8' };
const number nine{ "nine", '9' };

const std::vector<number> numbers
{
	one,
	two,
	three,
	four,
	five,
	six,
	seven,
	eight,
	nine,
};

inline bool is_match(const number& number, std::string_view view)
{
	return view.starts_with(number.name);
}

char find_first(std::string_view);
char find_last(std::string_view);

int day01_part2_find_solution(const input_format& input)
{
	auto sum = 0;

	for (const auto& row : input)
	{
		const auto& entry = row[0];
		std::string_view span{ entry };
		char first = find_first(span);
		char last = find_last(span);
		
		std::string v{first, last};

		auto parsed = std::stoi(v);
		sum += parsed;
	}

	return sum;
}

char find_first(std::string_view entry)
{
	for (auto i = 0; i < entry.length(); i++)
	{
		for (number n : numbers)
		{
			auto subString = entry.substr(i, entry.length() - i);
			if (is_match(n, subString) || entry[i] == n.charValue)
			{
				return n.charValue;
			}
		}
	}

	return '0';
}

char find_last(std::string_view entry)
{
	for (auto i = entry.length(); i --> 0;)
	{
		for (number n : numbers)
		{
			auto subString = entry.substr(i, entry.length() - i);
			if (is_match(n, subString) || entry[i] == n.charValue)
			{
				return n.charValue;
			}
		}
	}

	return '0';
}
