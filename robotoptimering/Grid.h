#pragma once
#include "template.h"
#include "Position.h"

struct Grid
{
	string name;
	int n, m;
	vvi blocked;
	Position start;
	p2 goal;

	Grid() {}

	inline bool isblocked(const p2& p)
	{
		return !ValidPos(p) || blocked[p.first][p.second];
	}

	inline bool ValidPos(const p2& p)
	{
		return (p.first >= 0 && p.second >= 0 && p.first < n&& p.second < m);
	}

	void read()
	{
		cin >> name;
		cin >> n >> m;
		blocked.resize(n, vi(m));
		rep(i, n)
		{
			string row;
			cin >> row;
			rep(j, m) blocked[i][j] = (row[j] == '#');
			rep(j, m)
			{
				if (row[j] == '<' || row[j] == '>' || row[j] == 'v' || row[j] == '^')
				{
					start.position = p2(i, j);
					start.dir = fromChar(row[j]);
				}
				if (row[j] == 'M') goal = p2(i, j);
			}
		}
	}
};