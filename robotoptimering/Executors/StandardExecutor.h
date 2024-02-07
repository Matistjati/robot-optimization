#pragma once
#include "Executor.h"
#include "programs/Program.h"

class StandardExecutor : public Executor
{
public:
	StandardExecutor(Grid& grid, Program& p) : Executor(grid, p) {}
	int maxitscurr = int(1e3);
	const int maxits = int(9980010);


	int distcutoff = 100;
	bool execute() override
	{
		maxitscurr = maxits;

		int p = program.findmain();
		p2& goal = grid.goal;
		p2& pos = grid.start.position;
		Direction dir = grid.start.dir;
		p2 dirv;
		UpdateDir(dirv, dir);

		int prgramsize = program.instructions.size();
		int it = -1;
		while (it< maxitscurr)
		{
			it++;
			if (pos==goal)
			{
				return true;
			}

			if (it==maxitscurr-1)
			{
				if (distanceto(pos, grid.start.position) >= distcutoff)
				{
					maxitscurr = maxits;
				}
			}

			if (p >= prgramsize)
			{
				die();
				return false;
			}
			Instruction& nextins = program.instructions[p];

			switch (nextins.instruction)
			{
			case Instructiontype::forward:
				//cout << "forward\n";
				pos.first += dirv.first;
				pos.second += dirv.second;
				if (grid.isblocked(pos))
				{
					pos.first -= dirv.first;
					pos.second -= dirv.second;
				}
				break;
			case Instructiontype::rleft:
				//cout << "left\n";
				dir = rotateleft(dir);
				UpdateDir(dirv, dir);
				break;
			case Instructiontype::rright:
				//cout << "right\n";
				dir = rotateright(dir);
				UpdateDir(dirv, dir);
				break;
			case jump:
				p = nextins.target;
				goto endloop;
			case gotoblocked:
				if (grid.isblocked(p2(pos.first + dirv.first, pos.second + dirv.second)))
				{
					p = nextins.target;
					goto endloop;
				}
				break;
			case loop:
				if (nextins.counter == -1) nextins.counter = nextins.target;
				else nextins.counter--;
				break;
			case closeloop:
				if (program.instructions[nextins.target].counter != -1)
				{
					p = nextins.target;
					goto endloop;
				}
			default:
				break;
			}
			p++;
		endloop:;
		}
		return false;
	}
};