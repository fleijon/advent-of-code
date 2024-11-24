#pragma once

#include "../utils/preprocess.h"

struct Game
{
	int Blue;
	int Red;
	int Green;
};

int solve_day02_part1(const input_format& input, Game proposalGame);
int solve_day02_part2(const input_format& input);
