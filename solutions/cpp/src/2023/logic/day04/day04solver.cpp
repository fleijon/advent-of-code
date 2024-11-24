#include "day04solver.h"

struct Card
{
	std::vector<int> WinningNumbers;
	std::vector<int> MyNumbers;
};

std::vector<int> ToIntList(const std::string& input)
{
	std::vector<std::string> target;
	split(input, ' ', target);

	std::vector<int> output;
	for (auto i = 0; i < target.size(); i++)
	{
		if (!target[i].empty() && isdigit(target[i][0]))
		{
			output.push_back(std::stoi(target[i]));
		}
	}

	return output;
}

void FillCards(const input_format& input, std::vector<Card>& cards)
{
	for (auto i = 0; i < input.size(); i++)
	{
		const auto& row = input[i][1];
		std::vector<std::string> target;
		split(row, '|', target);
		const auto& winnings = target[0];
		const auto& my = target[1];

		cards.emplace_back(ToIntList(winnings), ToIntList(my));
	}
}

int score(const Card& card)
{
	auto res = 0;
	for (const auto w : card.WinningNumbers)
	{
		if (std::ranges::find(card.MyNumbers.cbegin(), card.MyNumbers.cend(), w) != card.MyNumbers.cend())
		{
			res = res == 0 ? 1 : res * 2;
		}
	}

	return res;
}

int score2(const Card& card)
{
	auto res = 0;
	for (const auto w : card.WinningNumbers)
	{
		if (std::ranges::find(card.MyNumbers.cbegin(), card.MyNumbers.cend(), w) != card.MyNumbers.cend())
		{
			res++;
		}
	}

	return res;

}

int SolveDay04Part1(const input_format& input)
{
	auto sum = 0;

	std::vector<Card> cards;
	FillCards(input, cards);

	for (const auto& card : cards)
	{
		sum += score(card);
	}

	return sum;
}

void fillScores(const std::vector<Card>& cards, std::vector<int>& cardScores)
{
	for (auto i = 0; i < cards.size(); i++)
	{
		cardScores[i] = score2(cards[i]);
	}
}

void fillCardCounts(int i, const std::vector<int>& cardScores, std::vector<int>& cardCounts)
{
	auto max = cardScores.size();
	for (; i < max; i++)
	{
		for (auto j = i + 1; j < max && j < i + cardScores[i] + 1; j++)
		{
			fillCardCounts(j, cardScores, cardCounts);
			cardCounts[j]++;
		}
	}
}

int SolveDay04Part2(const input_format& input)
{
	auto sum = 0;

	std::vector<Card> cards;
	FillCards(input, cards);

	std::vector<int> countCard(cards.size(), 1);
	std::vector<int> cardScores(cards.size(), 0);

	fillScores(cards, cardScores);
	fillCardCounts(0, cardScores, countCard);

	for (auto i = 0; i < cards.size(); i++)
	{
		sum += cardScores[i] * countCard[i];
	}

	return sum;
}
