#pragma once
/*
140. Word Break II My Submissions Question
Total Accepted: 53041 Total Submissions: 272210 Difficulty: Hard
Given a string s and a dictionary of words dict, add spaces in s to construct a sentence where each word is a valid dictionary word.

Return all such possible sentences.

For example, given
s = "catsanddog",
dict = ["cat", "cats", "and", "sand", "dog"].

A solution is ["cats and dog", "cat sand dog"].
*/

#include <iostream>
#include <queue>
#include <memory>
#include <cassert>
#include <algorithm>
#include <vector>
#include "Common.h"

namespace WordBreak2
{
	///////////////////////////////////////////////////////
	// dfs is too slow
	void dfsSearch(const string& s, int start, const unordered_set<string>& wordDict, vector<string>& sentence, vector<string>& result)
	{
		int n = s.length();
		// base condition: s is complete, add sentence to result
		if (start == n)
		{
			// empty sentence, do nothing
			if (sentence.empty()) return;
			// add space between words
			string str = sentence[0];
			for (auto i = 1; i < (int)sentence.size(); i++)
			{
				str.append(" ");
				str.append(sentence[i]);
			}
			result.emplace_back(str);
			return;
		}
		// add next word to sentence for search
		for (auto wordLen = 1; wordLen <= n - start; wordLen++)
		{
			string word = s.substr(start, wordLen);
			// if word is valid, go on search
			if (wordDict.find(word) != wordDict.end())
			{
				sentence.emplace_back(move(word));
				dfsSearch(s, start + wordLen, wordDict, sentence, result);
				sentence.pop_back();
			}
		}
	}

	vector<string> wordBreakDfs(string s, unordered_set<string>& wordDict)
	{
		vector<string> result;
		vector<string> sentence;
		dfsSearch(s, 0, wordDict, sentence, result);
		return result;
	}
	/////////////////////////////////////////////////////
	// use dp to boost
	void dfsSearch(const string& s, int start, const unordered_set<string>& wordDict,
		const vector<bool>& dp, vector<string>& sentence, vector<string>& result)
	{
		int n = s.length();
		// base condition: sentence is formed
		if (n == start)
		{
			string str = sentence[0];
			for (auto i = 1; i < (int)sentence.size(); i++)
			{
				str.append(" ");
				str.append(sentence[i]);
			}
			result.emplace_back(move(str));
			return;
		}

		for (auto end = start; end < n; end++)
		{
			// check whther end is usable
			if (!dp[end + 1]) continue;
			// check whther word is a word
			string word = s.substr(start, end - start + 1);
			if (wordDict.find(word) == wordDict.end()) continue;
			sentence.emplace_back(move(word));
			dfsSearch(s, end + 1, wordDict, dp, sentence, result);
			sentence.pop_back();
		}
	}
	vector<string> wordBreak(string s, unordered_set<string>& wordDict)
	{
		vector<string> result;
		int n = s.length();
		if (n == 0) return result;
		// dp[i] means whether first i letters can form a sentence.
		vector<bool> dp(n + 1, false);
		dp[0] = true;
		// populate dp[i] 
		for (auto i = 1; i <= n; i++)
		{
			for (auto j = i - 1; j >= 0; j--)
			{
				dp[i] = dp[j] && wordDict.find(s.substr(j, i - j)) != wordDict.end();
				if (dp[i]) break;
			}
		}
		// no sentence is possible
		if (dp[n] == false) return result;

		vector<string> sentence;
		dfsSearch(s, 0, wordDict, dp, sentence, result);
		return result;
	}

	void Test()
	{
		string s("hipangpang");
		unordered_set<string> wordDict{ "hi", "pang", "hip", "ang" };
		cout << "input: " << s << endl;
		cout << "result: " << endl;
		auto result = wordBreak(s, wordDict);
		for(auto& sentence : result)
			cout << sentence << endl;
	}
}