#include "../utils/preprocess.h"
#include "day05solver.h"
#include <algorithm>

using point = unsigned int;

struct Range
{
	point From;
	unsigned int To;
	Range(point from, point to) : From(from), To(to)
	{
	}

	bool IsInside(point value) const
	{
		return value >= From && value <= To;
	}
};

struct Map
{
	Range From;
	Range To;

	explicit Map(Range from, Range to) : From(from), To(to)
	{
	}

	bool CanMap(point point) const
	{
		return From.IsInside(point);
	}
};

struct Mapper
{
	std::vector<Map> Maps;

	explicit Mapper(const std::vector<Map>& maps) : Maps(maps)
	{
	}

	point Map(point point) const
	{
		for (const auto& map : Maps)
		{
			if (map.CanMap(point))
			{
				const auto basePoint = map.From;
				const auto inc = point - basePoint.From;
				return map.To.From + inc;
			}
		}

		return point; // default to 1-1 mapping
	}
};

std::vector<Map> ProcessMappings(const input_format& input, size_t& i, const size_t max);

std::vector<Mapper> LoadInstructions(const input_format& input, std::vector<point>& seeds)
{
	std::vector<Mapper> mappers;

	size_t max = input.size();

	for (size_t i = 0; i < max; i++)
	{
		const auto& row = input[i];

		if (row.empty()) {
			continue;
		}

		if (row[0] == "seeds:")
		{
			std::vector<std::string> seeds_str;
			std::ranges::for_each(std::next(row.cbegin()), row.cend(),
				[&](const std::string& seed_str) {
					seeds.emplace_back(utils::stoui(seed_str));
				}
				);
		}
		else if(row[0] == "seed-to-soil")
		{
			mappers.emplace_back(ProcessMappings(input, i, max));
		}
		else if (row[0] == "soil-to-fertilizer")
		{
			mappers.emplace_back(ProcessMappings(input, i, max));
		}
		else if (row[0] == "fertilizer-to-water")
		{
			mappers.emplace_back(ProcessMappings(input, i, max));
		}
		else if ("water-to-light")
		{
			mappers.emplace_back(ProcessMappings(input, i, max));
		}
		else if ("light-to-temperature")
		{
			mappers.emplace_back(ProcessMappings(input, i, max));
		}
		else if ("temperature-to-humidity")
		{
			mappers.emplace_back(ProcessMappings(input, i, max));
		}
		else if ("humidity-to-location")
		{
			mappers.emplace_back(ProcessMappings(input, i, max));
		}
	}

	return mappers;
}

std::vector<Map> ProcessMappings(const input_format& input, size_t& i, const size_t max)
{
	i++;
	std::vector<Map> mappings;
	for (; i < max; i++)
	{
		const auto& row = input[i];
		if (row.empty())
		{
			return mappings;
		}
		const auto dest = utils::stoui(row[0]);
		const auto source = utils::stoui(row[1]);
		const auto len = utils::stoui(row[2]);

		mappings.emplace_back(Map(Range(source, source+len), Range(dest, dest+len)));
	}

	return mappings;
}

int SolveDay05Part1(const input_format& input)
{
	std::vector<point> seeds;
	const auto instructions = LoadInstructions(input, seeds);

	point min(UINT_MAX);
	for (const auto& seed : seeds)
	{
		point curr = seed;
		for (const auto& instr : instructions)
		{
			curr = instr.Map(curr);
		}

		if (curr < min)
		{
			min = curr;
		}
	}

	return min;
}

int SolveDay05Part2(const input_format& input)
{
	return 0;
}
