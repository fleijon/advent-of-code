
#include "day02solver.h"
#include <vector>
#include <algorithm>

inline Game GetGame(const std::vector<std::string>& row);

inline bool IsPossibleGame(const Game& actualGame, const Game& proposalGame);

inline int GetGamePower(const std::vector<std::string>& row);

void GetTokens(std::string gameScript, std::vector<std::string>& tokens);

int solve_day02_part1(const input_format& input, Game proposalGame)
{
	int sum = 0;

	for (size_t i = 0; i < input.size(); i++)
	{
		const auto game = GetGame(input[i]);

		if (IsPossibleGame(game, proposalGame))
			sum += i+1;
	}

	return sum;
}

int solve_day02_part2(const input_format& input)
{
	int sum = 0;
	auto s = [&sum] (const std::vector<std::string>& row)
	{
		sum += GetGamePower(row);
	};

	std::ranges::for_each(input, s);

	return sum;
}

int GetGamePower(const std::vector<std::string>& row)
{
	Game game;
	game.Blue = 0;
	game.Red = 0;
	game.Green = 0;

	std::vector<std::string> tokens;

	auto& gameScript = row[1];
	GetTokens(gameScript, tokens);

	auto i = 0;
	auto value = 0;
	while (i < tokens.size())
	{
		std::string current = tokens[i];

		if (isdigit(current[0]))
		{
			value = std::stoi(current);
		}

		if (current == "blue" && value > game.Blue) game.Blue = value;
		if (current == "red" && value > game.Red) game.Red = value;
		if (current == "green" && value > game.Green) game.Green = value;

		i++;
	}

	return game.Blue * game.Red * game.Green;
}


void GetTokens(std::string gameScript, std::vector<std::string>& tokens)
{
	size_t from = 0;
	size_t i = 0; 
	for (;i < gameScript.size(); i++)
	{
		if (gameScript[i] == ',' || gameScript[i] == ';' || gameScript[i] == ' ')
		{
			auto token = gameScript.substr(from, (i-from));
			tokens.push_back(token);
			from = i+1;
		}
	}

	// inlcude last token before newline
	auto token = gameScript.substr(from, (i-from));
	tokens.push_back(token);
}

Game GetGame(const std::vector<std::string>& row)
{
	Game game;
	game.Blue = 0;
	game.Red = 0;
	game.Green = 0;

	std::vector<std::string> tokens;

	auto& gameScript = row[1];
	GetTokens(gameScript, tokens);

	auto i = 0;
	auto value = 0;
	while (i < tokens.size())
	{
		std::string current = tokens[i];

		if (isdigit(current[0]))
		{
			value = std::stoi(current);
		}

		if (current == "blue" && value > game.Blue) game.Blue = value;
		if (current == "red" && value > game.Red) game.Red = value;
		if (current == "green" && value > game.Green) game.Green = value;

		i++;
	}

	return game;
}

bool IsPossibleGame(const Game& actualGame, const Game& proposalGame)
{
	return actualGame.Blue <= proposalGame.Blue &&
		actualGame.Green <= proposalGame.Green &&
		actualGame.Red <= proposalGame.Red;
}

