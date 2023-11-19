#pragma once
#include <vector>
#include <array>
#include "../utils/load.h"

template <class T>
inline void hash_combine(std::size_t & s, const T & v)
{
  std::hash<T> h;
  s^= h(v) + 0x9e3779b9 + (s<< 6) + (s>> 2);
}

struct Position {
	int X;
	int Y;

	bool operator==(const Position& other) const = default;
};

template <class T>
class MyHash;

template<>
struct MyHash<Position>
{
    std::size_t operator()(Position const& s) const 
    {
        std::size_t res = 0;
		hash_combine(res,s.X);
		hash_combine(res,s.Y);
        return res;
    }
};

struct Move
{
	Move(int dx, int dy, int times) : dX(dx), dY(dy), Times(times) { }

	int dX;
	int dY;
	int Times;
};

struct BoardState
{
	BoardState(const std::vector<Position>& positions) : Positions(positions){}
	std::vector<Position> Positions;
};

bool get_moves(const input_format& input, std::vector<Move>& movesOut);

size_t calculate_number_of_unique_visits(const std::vector<Move>& moves, BoardState& state);
