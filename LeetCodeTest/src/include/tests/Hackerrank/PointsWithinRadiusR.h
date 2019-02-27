#pragma once
/*
Draw circle at (0, 0) with radius r.
How many points with integer coordinates will fall into the circle? If r = 1, then point (0, 0), (1, 0), (0, 1), (0, -1), (-1, 0) will. Return 5.
r is [0, 20000]
*/

#include <iostream>
#include <queue>
#include <algorithm>
#include "Common.h"

namespace PointsWithinRadiusR
{
	int numPointsWithinRadiusR(int r)
	{
		// calculate the squares of 0 ~ r
		vector<int> squares(r + 1, 0);
		// in the quadrant, for each i, there is j = sqrt(r^2 - i^2) points
		int count = 1;
		for (auto i = 1; i <= r; i++)
		{
			count += 4 * (int)(sqrt(r * r - i * i) + 1);
		}
		return count;
	}

	void Test()
	{
		int r = 2;
		cout << "R: " << r << " Num of points: " << numPointsWithinRadiusR(r) << endl;
	}
}