#pragma once
/*
PalindromePartitioning2.h
132. Palindrome Partitioning II My Submissions Question
Total Accepted: 47617 Total Submissions: 222032 Difficulty: Hard
Given a string s, partition s such that every substring of the partition is a palindrome.

Return the minimum cuts needed for a palindrome partitioning of s.

For example, given s = "aab",
Return 1 since the palindrome partitioning ["aa","b"] could be produced using 1 cut.
*/

#include <iostream>
#include <queue>
#include <memory>
#include <cassert>
#include <algorithm>
#include <vector>
#include "Common.h"

namespace PalindromePartitioning2
{
	bool isPalindrome(const string& s, int lo, int hi)
	{
		while (lo < hi)
		{
			if (s[lo] != s[hi]) return false;
			lo++, hi--;
		}
		return true;
	}
	int bfsSearch(const string& s)
	{
		int len = s.length();
		// q to store partial partitionings
		queue<int> q;
		vector<bool> visited(len, false);
		// first cut is set at -1.
		q.push(-1);
		// min cuts to split the whole string
		int cuts = 0;
		while (!q.empty())
		{
			// number of posibilities of the same cut
			int n = q.size();
			for (int i = 0; i < n; i++)
			{
				auto lastCutAt = q.front();
				q.pop();

				for (int startSubstr = lastCutAt + 1, endSubstr = len - 1; endSubstr >= startSubstr; endSubstr--)
				{
					// between lastCust and nextCut, if the substr is palindrome, we add it to the queue
					if (!visited[endSubstr] && isPalindrome(s, startSubstr, endSubstr))
					{
						if (endSubstr == len - 1) return cuts;
						q.push(endSubstr);
						visited[endSubstr] = true;
					}
				}
			}
			cuts++;
		}
		return 0;
	}
	///////////////////////////////////////////////////////////////////////////////
	int dpSolution(const string& s)
	{
		int n = s.length();
		if (n < 2) return 0;
		vector<vector<bool>> p(n, vector<bool>(n, false));
		for (int i = 0; i < n; i++) p[i][i] = true;

		// minCuts[i] is the minCuts of s[0:i - 1]
		vector<int> minCuts(n + 1, 0);
		minCuts[0] = -1, minCuts[1] = 0;
		for (auto i = 1; i < n; i++)
		{
			// calculate minCuts[i + 1] -> s[0:i]
			int minTmp = INT_MAX;
			// if s[j:i] is palindrome, minCuts[i + 1] <= minCuts[j] + 1
			for (auto j = 0; j <= i; j++)
			{
				if (i - j <= 1) p[j][i] = (s[i] == s[j]);
				else
				{
					p[j][i] = (s[i] == s[j]) && p[j + 1][i - 1];
				}
				if (p[j][i])
					minTmp = min(minTmp, minCuts[j] + 1);
			}
			minCuts[i + 1] = minTmp;
		}
		return minCuts[n];
	}
	///////////////////////////////////////////////////////////////////////////////
	int minCut(string s)
	{
		//return bfsSearch(s);
		return dpSolution(s);
	}

	void Test()
	{
		string input("aabaa");
		cout << "input: " << input << endl;
		cout << "result: " << minCut(input) << endl;

	}
}

