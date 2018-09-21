#pragma once
/*
120. Triangle My Submissions Question
Total Accepted: 65753 Total Submissions: 220893 Difficulty: Medium
Given a triangle, find the minimum path sum from top to bottom. Each step you may move to adjacent numbers on the row below.

For example, given the following triangle
[
[2],
[3,4],
[6,5,7],
[4,1,8,3]
]
The minimum path sum from top to bottom is 11 (i.e., 2 + 3 + 5 + 1 = 11).
*/

#include <iostream>
#include <queue>
#include <memory>
#include <cassert>
#include <algorithm>
#include <vector>
#include "Common.h"

namespace PascalsTriangle2
{
	vector<int> getRow(int rowIndex)
	{
		vector<int> result(rowIndex + 1, 1);

		for (auto i = 1; i <= rowIndex; i++)
		{
			int nOfRow = i + 1;
			for (auto j = nOfRow - 2; j >= 1; j--)
			{
				result[j] = result[j] + result[j - 1];
			}
		}
		return result;
	}

	void Test()
	{
		auto result = getRow(3);
		for (auto num : result)
		{
			cout << num << " ";
		}
		cout << endl;
	}
}