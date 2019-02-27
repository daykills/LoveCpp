/*
52. N-Queens II My Submissions Question
Total Accepted: 42106 Total Submissions: 108386 Difficulty: Hard
Follow up for N-Queens problem.

Now, instead outputting board configurations, return the total number of distinct solutions.
*/
#include <iostream>
#include <queue>
#include <algorithm>
#include "Common.h"

namespace NQueens2
{
	void dfs(int n, vector<int>& cols, int& totalSolutions)
	{
		int nQueens = cols.size();
		// base condition
		if (nQueens == n)
		{
			totalSolutions++;
			return;
		}

		// find possible position for next queen
		int curRow = nQueens;
		for (auto col = 0; col < n; col++)
		{
			bool colIsValid = true;
			for (auto row = 0; row < nQueens; row++)
			{
				// validate curRow and col
				if (cols[row] == col || abs(col - cols[row]) == curRow - row)
				{
					colIsValid = false;
					break;
				}
			}
			if (!colIsValid) continue;
			cols.emplace_back(col);
			dfs(n, cols, totalSolutions);
			cols.pop_back();
		}
	}

	int totalNQueens(int n)
	{
		int totalSolutions = 0;
		vector<int> cols;
		dfs(n, cols, totalSolutions);
		return totalSolutions;
	}

	void Test()
	{
		int n = 6;
		auto result = totalNQueens(n);
		cout << "Number of queens: " << n << endl;
		cout << endl << "Result: " << result << endl;
	}
}