#pragma once
#include <vector>
#include <array>
#include "../utils/load.h"

struct Matrix {

	Matrix(int m, int n) : _m(m), _n(n) {

		values.resize(m);

		for (int j = 0; j < n; j++)
		{
			values[j].resize(n);
		}
	}

	int _m;
	int _n;

	std::array<int, 4> getAdjacent(int x, int y) const;
	int scenic_score(int x, int y, int currentTreeHeigth) const;

	std::vector<std::vector<int>> values;
};

std::unique_ptr<Matrix> CreateMatrix(const input_format& input);

int calculate_number_of_visible_trees(Matrix const* const treeGrid);
int calculate_highest_scenic_score(Matrix const* const treeGrid);
