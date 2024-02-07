#pragma once
#include "template.h"

enum Direction
{
	up,
	down,
	left,
	right,
	invalid,
};

Direction fromChar(char c)
{
	switch (c)
	{
	case 'v':
		return down;
	case '^':
		return up;
	case '<':
		return Direction::left;
	case '>':
		return Direction::right;
	default:
		assert(0);
		break;
	}
}

inline Direction rotateleft(Direction dir)
{
	switch (dir)
	{
	case up:
		return Direction::left;
	case Direction::left:
		return down;
	case down:
		return Direction::right;
	case Direction::right:
		return up;
	default:
		assert(0);
		break;
	}
}

inline Direction rotateright(Direction dir)
{
	switch (dir)
	{
	case up:
		return Direction::right;
	case Direction::right:
		return down;
	case down:
		return Direction::left;
	case Direction::left:
		return up;
	default:
		assert(0);
		break;
	}
}

void UpdateDir(p2& dir, Direction dirc)
{
	switch (dirc)
	{
	case up:
		dir.first = -1;
		dir.second = 0;
		break;
	case down:
		dir.first = 1;
		dir.second = 0;
		break;
	case Direction::left:
		dir.first = 0;
		dir.second = -1;
		break;
	case Direction::right:
		dir.first = 0;
		dir.second = 1;
		break;
	case invalid:
		break;
	default:
		assert(0);
	}
}

int distanceto(p2 a, p2 b)
{
	return abs(a.first - b.first) + abs(a.second - b.second);
}

struct Position
{
	p2 position;
	Direction dir;
	Position(p2 p, Direction dir) : position(p), dir(dir) {}
	Position(p2 p, char dir) : position(p), dir(fromChar(dir)) {}
	Position() : position(p2(-1,-1)), dir(invalid) {}

	
};
