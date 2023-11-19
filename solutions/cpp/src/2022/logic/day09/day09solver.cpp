#include "pch.h"

#include "day09solver.h"
#include <string>
#include <unordered_set>

bool get_moves(const input_format& input, std::vector<Move>& movesOut) {
	for (auto& row: input)
	{
		if (row.size() != 2)
			return false;

		int dX = 0;
		int dY = 0;

		if (row[0] == "R")
		{
			dX = 1;
		}
		else if (row[0] == "L") {

			dX = -1;
		}
		else if (row[0] == "D") {
			dY = -1;
		}
		else if (row[0] == "U") {
			dY = 1;
		}
		auto times = stoi(row[1]);
		movesOut.emplace_back(dX, dY, times);
	}

	return true;
}

void step(BoardState& state, Move move, std::unordered_set<Position, MyHash<Position>>& visits) {

	for (size_t k = 0; k < move.Times; k++)
	{
		// Move Head
		auto head = &state.Positions[0];
		auto tail = &state.Positions[0];

		head->X = head->X + move.dX;
		head->Y = head->Y + move.dY;

		for (int i = 1; i < state.Positions.size(); i++)
		{
			head = &state.Positions[i - 1];
			tail = &state.Positions[i];

			// Update Tail to follow Head
			auto xDiff = head->X - tail->X;
			auto yDiff = head->Y - tail->Y;

			if (abs(xDiff) > 1 && abs(yDiff) == 1)
			{
				// Special move
				tail->Y = head->Y;
			}
			
			if (abs(yDiff) > 1 && abs(xDiff) == 1)
			{
				// Special move
				tail->X = head->X;
			}

			if (abs(xDiff) > 1)
			{
				tail->X = tail->X + (xDiff > 0 ? xDiff - 1 : xDiff + 1) ;
			}

			if (abs(yDiff) > 1)
			{
				tail->Y = tail->Y + (yDiff > 0 ? yDiff - 1 : yDiff + 1) ;
			}

		}

		visits.insert(Position{tail->X, tail->Y});
	}
}

size_t calculate_number_of_unique_visits(const std::vector<Move>& moves, BoardState& state)
{
	std::unordered_set<Position, MyHash<Position>> visits;

	for (const auto& move: moves) {
		step(state, move, visits);

	}

	return visits.size();
}
