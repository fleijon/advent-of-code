#pragma once
#include <string>
#include <vector>
#include <memory>
#include "../utils/load.h"

struct CycleState
{
	int cycle;
	int value;
};

struct Instruction
{
	Instruction() = default;

	virtual ~Instruction() = default;

	virtual std::vector<CycleState> Do(const CycleState& currentState) = 0;
};

struct AddX : public Instruction
{
	int addValue;
	explicit AddX(int value);
	~AddX() final;

	std::vector<CycleState> Do(const CycleState& currentState) final;
};

struct noop : public Instruction
{
	~noop() final;
	std::vector<CycleState> Do(const CycleState& currentState) final;
};

bool LoadInstructions(const input_format& input, std::vector<std::unique_ptr<Instruction>>& target);

bool ApplyInstructions(const std::vector<std::unique_ptr<Instruction>>& instructions, std::vector<CycleState>& cycles);

int CalculateSignalStrength(const std::vector<int>& aCycles, const std::vector<CycleState>& cycles);

std::string CreateCRTOutput(const std::vector<CycleState>& cycles);
