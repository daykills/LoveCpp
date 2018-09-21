#pragma once

/*
Encircular
Posted on January 12, 2016 by angshukutu
We are given a string consisting of letters- F,L,R. ?which is the instruction a robot follows

G - goes forward by one step.
L - turn left.
R - turn right.

String length can be upto 2500 characters.
*/

#include <iostream>
#include <queue>
#include <algorithm>
#include "Common.h"

namespace Encircular
{
	string doesCircleExists(string commands)
	{
		// directions in order of counter-clockwise
		vector<pair<int, int>> directions{ { 1, 0 },{ 0, 1 },{ -1, 0 },{ 0, -1 } };
		// assume initial direction is (1, 0)
		auto iDirect = 0;
		// position of the bot
		int i = 0, j = 0;
		// run through one command and find the end condition
		for (auto ch : commands)
		{
			if (ch == 'L')
			{
				iDirect = (iDirect + 1) % 4;
			}
			else if (ch == 'R')
			{
				iDirect = (iDirect - 1 + 4) % 4;
			}
			else if (ch == 'G')
			{
				const auto& direct = directions[iDirect];
				i += direct.first;
				j += direct.second;
			}
			else return "NO";
		}
		// deltaI deltaJ and deltaDirection are the end status of one command
		auto deltaI = i, deltaJ = j, deltaDirection = iDirect;
		// no movement
		if (deltaI == 0 && deltaJ == 0) return "YES";
		// set initial condition
		i = 0, j = 0, iDirect = 0;
		// run command for 4 times
		for (auto it = 0; it < 4; it++)
		{
			if (iDirect == 0)
			{
				i += deltaI, j += deltaJ;
			}
			else if (iDirect == 1)
			{
				i -= deltaJ, j += deltaI;
			}
			else if (iDirect == 2)
			{
				i -= deltaI, j -= deltaJ;
			}
			else // iDirect == 3
			{
				i += deltaJ, j -= deltaI;
			}
			iDirect = (iDirect + deltaDirection) % 4;
		}

		if (i == 0 && i == 0) return "YES";

		return "NO";
	}
}