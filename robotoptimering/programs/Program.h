#pragma once
#include "template.h"

enum Instructiontype
{
	forward,
	rright,
	rleft,
	loop,
	closeloop,
	call,
	ret,
	gotoblocked,
	jump,
	label
};

struct Instruction
{
	Instructiontype instruction;
	int target;
	int counter;

	Instruction(Instructiontype instruction) : instruction(instruction) {}
	Instruction(Instructiontype instruction, int t) : instruction(instruction), target(t) {}
	Instruction(Instructiontype instruction, int t, int c) : instruction(instruction), target(t), counter(c) {}
};

struct Program
{
	vector<Instruction> instructions;
	vi looplevel;

	int findmain()
	{
		rep(i, sz(instructions))
		{
			Instruction& inst = instructions[i];
			if (inst.instruction==label&&inst.target==0) // main is 0
			{
				return i;
			}
		}
		assert(0);
	}

	int GetLen()
	{
		int cost = 0;

		repe(inst, instructions)
		{
			if (inst.instruction == closeloop || inst.instruction == label || inst.instruction == jump) continue;
			cost++;
		}
		return cost;
	}

	void reset()
	{
		int level = 0;
		rep(i, instructions.size())
		{
			if (instructions[i].instruction == loop) level++;
			if (instructions[i].instruction == closeloop) level--;
			looplevel.push_back(level);
		}
		assert(looplevel.size() == instructions.size());
	}

	void add(Instructiontype t)
	{
		instructions.push_back(Instruction(t));
	}
	void add(Instructiontype t, int ta)
	{
		instructions.push_back(Instruction(t, ta));
	}

};
