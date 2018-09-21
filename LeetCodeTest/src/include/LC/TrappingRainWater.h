/*
135. Candy My Submissions Question
Total Accepted: 47846 Total Submissions: 218577 Difficulty: Hard
There are N children standing in a line. Each child is assigned a rating value.

You are giving candies to these children subjected to the following requirements:

Each child must have at least one candy.
Children with a higher rating get more candies than their neighbors.
What is the minimum candies you must give?
*/

#include <iostream>
#include <queue>
#include <algorithm>
#include "Common.h"

namespace TrappingRainWater
{
	int trap(vector<int>& height)
	{
		int n = height.size();
		if (n < 2) return 0;

		// find the highest
		int iHighest = 0;
		for (int i = 1; i <n; i++)
		{
			if (height[i] > height[iHighest]) iHighest = i;
		}

		// for left part
		int water = 0;
		int lastHigh = height[0];
		for (auto i = 1; i < iHighest; i++)
		{
			if (height[i] >= lastHigh)
			{
				lastHigh = height[i];
			}
			else
			{
				water += lastHigh - height[i];
			}
		}
		// for right part
		lastHigh = height[n - 1];
		for (auto i = n - 2; i > iHighest; i--)
		{
			if (height[i] >= lastHigh)
			{
				lastHigh = height[i];
			}
			else
			{
				water += lastHigh - height[i];
			}
		}
		return water;
	}

	static void Test()
	{
		vector<int> heights { 2, 4, 3, 5, 2, 3, 1 };
		for (auto i : heights)
			cout << " " << i;
		cout << endl;
		cout << "result: " << trap(heights) << endl;
	}
}