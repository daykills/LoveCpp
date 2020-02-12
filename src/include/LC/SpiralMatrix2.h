/*
59. Spiral Matrix II My Submissions Question
Total Accepted: 49573 Total Submissions: 143810 Difficulty: Medium
Given an integer n, generate a square matrix filled with elements from 1 to n2 in spiral order.

For example,
Given n = 3,

You should return the following matrix:
[
[ 1, 2, 3 ],
[ 8, 9, 4 ],
[ 7, 6, 5 ]
]
*/

#include <iostream>
#include <queue>
#include <memory>
#include <cassert>
#include <algorithm>
#include "Common.h"

namespace SpiralMatrix2
{
	// direction is the increment of i/j; num is the current number to fill
	void dfs(int i, int j, const vector<pair<int, int>>& directions, int iDirection, int num, vector<vector<int>>& matrix)
	{
		matrix[i][j] = num;

		int n = matrix.size();
		for (int index = 0; index < (int)directions.size(); index++)
		{
			int newI = directions[iDirection].first + i;
			int newJ = directions[iDirection].second + j;
			// if reach boundary or value is already set, turn right
			if (newI < 0 || newI >= n || newJ < 0 || newJ >= n || matrix[newI][newJ] > 0)
			{
				iDirection = (iDirection + 1) % directions.size();
			}
			else
			{
				dfs(newI, newJ, directions, iDirection, num + 1, matrix);
				return;
			}
		}
		// all directions are set.
		return;
	}

	vector<vector<int>> generateMatrix(int n)
	{
		if (n == 0) return vector<vector<int>>();

		vector<vector<int>> matrix(n, vector<int>(n, -1));
		const vector<pair<int, int>>directions{
			{ 0, 1 },{ 1, 0 },{ 0, -1 },{ -1, 0 }
		};

		dfs(0, 0, directions, 0, 1, matrix);
		return matrix;
	}

	void Test()
	{
		auto matrix = generateMatrix(7);

		for (auto& line : matrix)
		{
			for (auto num : line)
			{
				cout << num << " ";
			}
			cout << endl;
		}
	}
}