#include "pch.h"

#include "day10solver.h"
#include "../utils/load.h"


AddX::AddX(int value) : addValue(value) {};

AddX::~AddX() = default;

std::vector<CycleState> AddX::Do(const CycleState& currentState)
{
	auto startCycle = currentState.cycle;
	auto registerValue = currentState.value;
	std::vector<CycleState> outTarget{
		{++startCycle, registerValue},
		{++startCycle, registerValue + addValue },
	};

	return outTarget;
}

noop::~noop() = default;

std::vector<CycleState> noop::Do(const CycleState& currentState)
{
	auto startCycle = currentState.cycle;
	auto registerValue = currentState.value;
	return std::vector<CycleState> { {++startCycle, registerValue}};
}

bool LoadInstructions(const input_format& input, std::vector<std::unique_ptr<Instruction>>& target) 
{
	for (const auto& line: input)
	{
		if (line.size() == 1 && line[0] == "noop") {
			target.push_back(std::make_unique<noop>());
		}
		else if (line.size() == 2 && line[0] == "addx")
		{
			const bool isNegative = line[1].substr(0, 1) == "-";
			const auto value = isNegative ? line[1].substr(1) : line[1];
			const auto intValue = std::stoi(value);
			const auto signedValue = isNegative ? -intValue : intValue;

			target.push_back(std::make_unique<AddX>(signedValue));
		}
		else
		{
			return false;
		}
	}

	return true;
}

bool ApplyInstructions(const std::vector<std::unique_ptr<Instruction>>& instructions, std::vector<CycleState>& cycles) 
{
	if (cycles.empty())
		return false;

	for (const auto& instruction : instructions) 
	{
		const auto currentState = cycles[cycles.size()-1];
		const auto newCycles = instruction->Do(currentState);

		for (const auto& cycle : newCycles) {
			cycles.push_back(cycle);
		}
	}

	return true;
}

int CalculateSignalStrength(const std::vector<int>& aCycles, const std::vector<CycleState>& cycles)
{
	int total = 0;
	for (int cycleNumber: aCycles) {
		const auto& cycle = cycles[cycleNumber - 1];
		total += cycle.cycle * cycle.value;
	}

	return total;
}

char GetPixel(int beamPosition, int spritePosition)
{
	if (abs(spritePosition - beamPosition) < 2)
		return '#';

	return '.';
}

std::string CreateCRTOutput(const std::vector<CycleState>& cycles)
{
	std::string out;
	int beamPosition = 0;
	for (const auto& cycle: cycles) 
	{
		char pixel = GetPixel(beamPosition, cycle.value);

		out += pixel;
		beamPosition++;
		if (beamPosition == 40)
		{
			beamPosition = 0;
		}
	}

	return out;
}

