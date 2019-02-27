#pragma once
/*
139. Word Break My Submissions Question
Total Accepted: 81270 Total Submissions: 326846 Difficulty: Medium
Given a string s and a dictionary of words dict, determine if s can be segmented into a space-separated sequence of one or more dictionary words.

For example, given
s = "leetcode",
dict = ["leet", "code"].

Return true because "leetcode" can be segmented as "leet code".
*/

#include <iostream>
#include <queue>
#include <memory>
#include <cassert>
#include <algorithm>
#include <vector>
#include "Common.h"

namespace WordBreak
{
	bool wordBreak(string s, unordered_set<string>& wordDict)
	{
		int n = s.length();
		if (n == 0) return true;

		// dp[i] means first i letters can form a sentence
		vector<bool> dp(n + 1, false);

		dp[0] = true;
		for (auto i = 1; i <= n; i++)
		{
			// dp[i] = true if dp[j] is true, and s[j : i] forms a word
			for (auto j = i - 1; j >= 0; j--)
			{
				dp[i] = dp[j] && wordDict.find(s.substr(j, i - j)) != wordDict.end();
				if (dp[i]) break;
			}
		}
		return dp[n];
	}

	void Test()
	{
		string s("hipangpang");
		unordered_set<string> wordDict{ "hi", "pang" };
		cout << "input: " << s << endl;
		cout << "result: " << wordBreak(s, wordDict) << endl;

	}
}