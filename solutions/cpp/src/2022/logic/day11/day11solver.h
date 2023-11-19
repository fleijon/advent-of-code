#pragma once

#include <vector>
#include <functional>
#include "../utils/load.h"

using operation = std::function<int(int)>;
using monkeySelectorFunction = std::function<int(int)>;

struct Monkey
{
	explicit Monkey(const std::vector<int>& items, const operation& operation_, const monkeySelectorFunction& throwToFunction)
		: Items(items), Operation(operation_), MonkeySelector(throwToFunction) {}

	std::vector<int> Items;
	operation Operation;
	monkeySelectorFunction MonkeySelector;
};

bool ParseInput(const input_format& input, std::vector<Monkey>& monkeys);
int CalculateMonkeyBusiness(std::vector<Monkey>& monkeys);
