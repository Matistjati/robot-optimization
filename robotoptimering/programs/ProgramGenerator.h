#pragma once
#include "Program.h"

class ProgramGenerator
{
public:
	virtual Program Generate()
	{
		assert(0);
		return Program();
	}
};
