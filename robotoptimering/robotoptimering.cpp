#include <bits/stdc++.h>
using namespace std;
#include "template.h"
#include "Grid.h"
#include "programs/ProgramGenerator.h"
#include "programs/EasyGenerator.h";
#include "Executors/StandardExecutor.h"
#include "Executors/Executor.h"

Grid grid;

signed main()
{
	fast();

#if 1
	ifstream in("C:\\Users\\Matis\\desktop\\robot\\robot_diagonal.in");
	cin.rdbuf(in.rdbuf());
#endif

	grid.read();
	assert(grid.start.position.first != -1);

	ProgramGenerator* generator = new EasyGenerator();

	int its = 0;
	vector<pair<Instruction,bool>> check;
	auto add = [&](Instructiontype t)
	{
		check.emplace_back(Instruction(t), false);
	};
	auto addexact = [&](Instructiontype t, int ta)
	{
		check.emplace_back(Instruction(t, ta), 1);
	};
	add(label);
	add(rright);
	add(label);
	addexact(gotoblocked, 0);
	add(Instructiontype::forward);
	add(rleft);
	addexact(jump, 2);

	Program prog;
	prog.add(label, 0);
	prog.add(rright);
	prog.add(label);
	prog.add(gotoblocked, 0);
	prog.add(Instructiontype::forward);
	prog.add(rleft);
	prog.add(jump, 2);
	prog.reset();

	Executor* executor = new StandardExecutor(grid, prog);
	executor->execute();


	while (true)
	{
		its++;
		Program p = generator->Generate();

		bool ok = 1;
		if (0)
		{
			bool w = 0;
			if (p.instructions.size() >= check.size())
			{
				w = 1;
				
				rep(i, check.size())
				{
					w &= p.instructions[i].instruction == check[i].first.instruction;
					if (check[i].second) w &= p.instructions[i].target == check[i].first.target;
				}
			}
			if (w)
			{
				deb
			}
		}

		Executor* executor = new StandardExecutor(grid, p);

		if (ok&&executor->execute())
		{
			cout << "WIN " << p.GetLen() << "\n";
		}
		delete executor;
		if (elapsedmillis()>10*1000)
		{
			cerr << its << "\n";
			resettimer();
			its = 0;
		}
	}

	return 0;
}
