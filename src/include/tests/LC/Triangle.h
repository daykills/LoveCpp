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

namespace Triangle
{
	void dfs(const vector<vector<int>>& triangle, int preRow, int preCol, int sum, int& minSum)
	{
		int m = triangle.size();
		// base condition
		if (preRow == m - 1)
		{
			minSum = min(minSum, sum);
			return;
		}
		auto row = preRow + 1;
		auto& rowData = triangle[row];
		int n = rowData.size();
		for (auto col = preCol; col <= preCol + 1; col++)
		{
			dfs(triangle, row, col, sum + rowData[col], minSum);
		}
	}

	int minimumTotalDfs(vector<vector<int>>& triangle)
	{
		int minSum = 0;
		dfs(triangle, 0, 0, 0, minSum);
		return minSum;
	}

	int minimumTotal(vector<vector<int>>& triangle)
	{
		int n = triangle.size();
		if (n == 0) return 0;
		// minimum distance to reach each cell of current row
		vector<int> minDist(n, 0);
		minDist[0] = triangle[0][0];
		for (auto row = 1; row < n; row++)
		{
			for (auto col = row; col >= 0; col--)
			{
				if (col == row) minDist[col] = minDist[col - 1] + triangle[row][col];
				else if (col == 0) minDist[col] = minDist[0] + triangle[row][col];
				else
				{
					minDist[col] = min(minDist[col], minDist[col - 1]) + triangle[row][col];
				}
			}
		}
		int result = minDist[0];
		for (auto i = 1; i < n; i++)
			result = min(result, minDist[i]);
		return result;
	}

	void Test()
	{
		vector<vector<int>> tri{ {-1},{2, 3},{1, -1, -1} };
		cout << minimumTotal(tri) << endl;
	}
}