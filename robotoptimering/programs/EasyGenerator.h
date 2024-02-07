#pragma once
#include "ProgramGenerator.h"

class EasyGenerator : public ProgramGenerator
{
	vector<Instructiontype> types;
public:
	EasyGenerator()
	{
		types.push_back(Instructiontype::forward);
		types.push_back(Instructiontype::rleft);
		types.push_back(Instructiontype::rright);
		types.push_back(Instructiontype::label);
		//types.push_back(Instructiontype::jump);
		types.push_back(Instructiontype::gotoblocked);
		types.push_back(Instructiontype::loop);
		types.push_back(Instructiontype::closeloop);
	}

	Program Generate() override
	{
		Program p;

		int len = 4 + randint(0, 5);
		int loophi = int(50);

		p.instructions.emplace_back(Instruction(label, 0));
		vi labelpos;
		labelpos.push_back(0);
		int labelind = 1;
		vi unclosedloops;
		rep(i, len)
		{
			Instructiontype t = randel(types);
			switch (t)
			{
			case Instructiontype::forward:
			case rright:
			case rleft:
				p.instructions.emplace_back(Instruction(t));
				break;

			case loop:
				unclosedloops.push_back(p.instructions.size());
				p.instructions.emplace_back(Instruction(t, randint(2, loophi), -1));
				break;
			case closeloop:
				if (unclosedloops.empty()) goto skipped;
				p.instructions.emplace_back(Instruction(t, unclosedloops.back()));
				unclosedloops.pop_back();
				break;

			case gotoblocked:
			case jump:
				p.instructions.emplace_back(Instruction(t, labelpos[randint(0, labelind - 1)]));
				break;
			case label:
				if (unclosedloops.size()) goto skipped;
				labelpos.push_back(p.instructions.size());
				p.instructions.emplace_back(Instruction(t, labelind++));
				break;
			default:
				break;
			}

			skipped:;
		}

		while (unclosedloops.size())
		{
			p.instructions.emplace_back(Instruction(closeloop, unclosedloops.back()));
			unclosedloops.pop_back();
		}
		p.instructions.emplace_back(Instruction(jump, labelpos[randint(0,labelind-1)]));

		p.reset();
		return p;
	}
};
