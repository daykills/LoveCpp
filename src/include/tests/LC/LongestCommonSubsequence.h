/*
Longest Common Subsequence

Given two strings, find the longest common subsequence (LCS).

Your code should return the length of LCS.

Example
For "ABCD" and "EDCA", the LCS is "A" (or "D", "C"), return 1.

For "ABCD" and "EACB", the LCS is "AC", return 2.

*/
#include <string>
#include <iostream>
#include <algorithm>
#include "Common.h"

namespace LongestCommonSubsequence
{
	/**
	* @param A, B: Two strings.
	* @return: The length of longest common subsequence of A and B.
	*/
	int longestCommonSubsequence(string A, string B) {
		// write your code here
		int n1 = A.length(), n2 = B.length();
		// dp[i][j] is the LCS for the first i of A and the first j ob B
		vector<vector<int>> dp(n1 + 1, vector<int>(n2 + 1, 0));

		// dp[i][j] = ?
		for (auto i = 1; i <= n1; i++)
		{
			for (auto j = 1; j <= n2; j++)
			{
				// for the first i of A and first j of B
				if (A[i - 1] == B[j - 1])
				{
					// make use of the last ch of A and B
					dp[i][j] = dp[i - 1][j - 1] + 1;
				}
				else
				{
					// since two last chars of A and B can't be used at the same time
					dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
				}
			}
		}
		return dp[n1][n2];
	}

	static int Test()
	{
		string str1("bedaacbade");
		string str2("dccaeedbeb");
		auto result = longestCommonSubsequence(str1, str2);
		cout << str1 << " " << str2 << ": " << result << endl;
		return 0;
	}
}