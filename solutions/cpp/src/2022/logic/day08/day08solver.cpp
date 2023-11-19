#include "pch.h"

#include "day08solver.h"
#include <algorithm>
#include <memory>
#include <iostream>

std::unique_ptr<Matrix> CreateMatrix(const input_format& input) {
	auto size = (int)input.size();
	if (size == 0)
	{
		std::cout << "Given input length was of size 0";
		return std::make_unique<Matrix>(0, 0);
	}

	if (auto width = (int)input[0].size(); width != 1)
	{
		std::cout << "Given input width was not of size 1";
		return std::make_unique<Matrix>(0, 0);
	}

	auto wordSize = input[0][0].length();

	auto mat_ptr = std::make_unique<Matrix>(size, wordSize);

	for (size_t i = 0; i < input.size(); i++)
	{
		auto& row = input[i][0]; // Assume only one entry per row
		std::vector<char> elements(row.begin(), row.end());

		for (size_t j = 0; j < elements.size(); j++)
		{
			if (isdigit(elements[j])) {
				mat_ptr->values[i][j] = elements[j] - '0';
			}
			else {
				std::cout << "All of the given input could not be parsed as int";
				return std::make_unique<Matrix>(0, 0);
			}
		}

	}

	return mat_ptr;
}

int Matrix::scenic_score(int x, int y, int currentTreeHeight) const
{
	auto l = 0;
	auto u = 0;
	auto r = 0;
	auto d = 0;

	// Check left
	for (int i = x-1; i > -1; i--)
	{
		if (auto curr = values[y][i]; curr < currentTreeHeight)
		{
			l++;
		}
		else if (curr >= currentTreeHeight) {
			l++;
			break;
		}
		else {
			break;
		}
	}

	// Check upp
	for (int i = y-1; i > -1; i--)
	{
		if (auto curr = values[i][x]; curr < currentTreeHeight)
		{
			u++;
		}
		else if (curr >= currentTreeHeight) {
			u++;
			break;
		}
		else {
			break;
		}
	}

	// Check rigth
	for (int i = x+1; i < _m; i++)
	{
		if (auto curr = values[y][i]; curr < currentTreeHeight)
		{
			r++;
		}
		else if (curr >= currentTreeHeight) {
			r++;
			break;
		}
		else {
			break;
		}

	}

	// Check down
	for (int i = y+1; i < _n; i++)
	{
		if (auto curr = values[i][x]; curr < currentTreeHeight)
		{
			d++;
		}
		else if (curr >= currentTreeHeight) {
			d++;
			break;
		}
		else {
			break;
		}
	}

	return l * u * r * d;
}

std::array<int, 4> Matrix::getAdjacent(int x, int y) const
{
	auto l = -1;
	auto u = -1;
	auto r = -1;
	auto d = -1;

	// Check left
	for (size_t i = 0; i < x; i++)
	{
		if (auto curr = values[y][i]; l < curr)
		{
			l = curr;
		}
	}

	// Check upp
	for (size_t i = 0; i < y; i++)
	{
		if (auto curr = values[i][x]; u < curr)
		{
			u = curr;
		}
	}

	// Check rigth
	for (size_t i = x+1; i < _m; i++)
	{
		if (auto curr = values[y][i]; r < curr)
		{
			r = curr;
		}
	}

	// Check down
	for (size_t i = y+1; i < _n; i++)
	{
		if (auto curr = values[i][x]; d < curr)
		{
			d = curr;
		}
	}

	return std::array<int, 4>({ l, u, r, d });
}

inline bool any_of_not_size(const std::vector<std::vector<int>>& target, size_t size) {
	return std::ranges::any_of(target.cbegin(), target.cend(), [size](const std::vector<int>& row) { return row.size() != size; });
}

inline bool isVisible(const Matrix& treeGrid, int x, int y)
{
	auto treeHeight = treeGrid.values[y][x];
	auto result = treeGrid.getAdjacent(x, y);

	return std::ranges::any_of(result.cbegin(), result.cend(), [treeHeight](int heigth) { return heigth < treeHeight;});
}

int calculate_highest_scenic_score(Matrix const * const treeGrid) {
	if (auto m = treeGrid->values.size(); m == 0)
		return 0;

	if (auto n = treeGrid->values[0].size(); any_of_not_size(treeGrid->values, n)) // Make sure matrix is equal size
	{
		return 0;
	}

	int max = -1;
	for (size_t i = 0; i < treeGrid->values.size(); i++)
	{
		for (size_t j = 0; j < treeGrid->values[i].size(); j++)
		{
			auto heigth = treeGrid->values[i][j];
			auto score = treeGrid->scenic_score((int)j, (int)i, heigth);
			if (score > max) {
				max = score;
			}
		}
	}

	return max;
}

int calculate_number_of_visible_trees(Matrix const * const treeGrid)
{
	if (auto m = treeGrid->values.size(); m == 0)
		return 0;

	if (auto n = treeGrid->values[0].size(); any_of_not_size(treeGrid->values, n)) // Make sure matrix is equal size
	{
		return 0;
	}

	int visibleTrees = 0;
	for (size_t i = 0; i < treeGrid->values.size(); i++)
	{
		for (size_t j = 0; j < treeGrid->values[i].size(); j++)
		{
			if (isVisible(*treeGrid, (int)j, (int)i)) {
				visibleTrees++;
			}
		}
	}

	return visibleTrees;
}


