#pragma once
#include "Position.h"
#include "Grid.h"
#include "programs/Program.h"

class Executor
{
public:
	Position position;
	Grid& grid;
	Program& program;

	bool invalidProgram = false;

	Executor(Grid& grid, Program& program) : grid(grid), program(program), position(grid.start) {}

	virtual bool execute()
	{
		assert(0);
		return false;
	};


	void die()
	{
		invalidProgram = true;
	}
};
