#include "pch.h"
#include "day11solver.h"
#include <algorithm>

bool replace(std::string& str, const std::string& from, const std::string& to) {
    size_t start_pos = str.find(from);
    if(start_pos == std::string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}

bool ParseInput(const input_format& input, std::vector<Monkey>& monkeys)
{
	for (int i = 0; i < input.size(); i++)
	{
		if (!input[i].empty() && input[i][0].starts_with("Monkey"))
		{
			int monkey = std::stoi(input[i][1]);
			std::vector<int> items;

			i++;
			// items
			for (int j = 4; j < input[i].size(); j++) // Why 4? Should not the iteration start at 3, if we count the first item in list as empty string? Or do we start with two empty strings
			{
				auto value = input[i][j];
				const auto c = replace(value, ",", "");
				items.emplace_back(std::stoi(value));
			}
			i++;

			// operation
			static constexpr int opIdx = 6;
			static constexpr int opValueIdx = 7;
			const auto op = input[i][opIdx];
			const auto opValueStr = input[i][opValueIdx];

			operation operationFunction;
			if (opValueStr == "old")
			{
				if (op == "*") {
					operationFunction = [](int arg) { return arg * arg; };
				}
				else {
					operationFunction = [](int arg) { return arg + arg; };
				}
			}
			else {
				const auto opValue = std::stoi(opValueStr);
				if (op == "*") {
					operationFunction = [opValue](int arg) { return arg * opValue; };
				}
				else {
					operationFunction = [opValue](int arg) { return arg + opValue; };
				}

			}

			// Next row
			i++;

			// Throw operation
			static constexpr int divIdx = 5;
			static constexpr int monkeyIdx = 9;
			const auto divValue = std::stoi(input[i][divIdx]);

			i++;

			const auto monkeyTrueValue = std::stoi(input[i][monkeyIdx]);

			i++;
			const auto monkeyFalseValue = std::stoi(input[i][monkeyIdx]);

			monkeySelectorFunction throwFunction = [divValue, monkeyTrueValue, monkeyFalseValue](int arg) {
				if (arg % divValue == 0) {
					return monkeyTrueValue;
				}

				return monkeyFalseValue;
			};

			monkeys.emplace_back(items, operationFunction, throwFunction);
		}
	}

	return true;
}

int CalculateMonkeyBusiness(std::vector<Monkey>& monkeys)
{
	std::vector<int> inspectCount(monkeys.size(), 0);

	for (int i = 0; i < 20; i++)
	{
		for (int m = 0; m < monkeys.size(); m++)
		{
			auto& monkey = monkeys[m];
			for (auto item : monkey.Items)
			{
				auto newItemValue = monkey.Operation(item)/3;
				auto passToMonkey = monkey.MonkeySelector(newItemValue);

				if (passToMonkey == m)
				{
					throw new std::domain_error("Did not expect monkey to throw to himself");
				}

				monkeys[passToMonkey].Items.emplace_back(newItemValue);

				++inspectCount[m];
			}
			monkey.Items.clear();
		}

	}

	std::ranges::sort(inspectCount.begin(), inspectCount.end(), [](int a, int b) {return a > b; });

	return inspectCount[0] * inspectCount[1];
}
