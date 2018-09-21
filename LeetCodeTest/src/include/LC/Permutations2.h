/*
46. Permutations My Submissions Question
Total Accepted: 91404 Total Submissions: 260919 Difficulty: Medium
Given a collection of distinct numbers, return all possible permutations.

For example,
[1,2,3] have the following permutations:
[1,2,3], [1,3,2], [2,1,3], [2,3,1], [3,1,2], and [3,2,1].
*/
#include <iostream>
#include <queue>
#include <algorithm>
#include "Common.h"

namespace Permutations2
{
	void dfs(const unordered_map<int, int>& countMap, const int n, vector<int>& path, vector<vector<int>>& result)
	{
		// base condition: found one complete path
		if ((int)path.size() == n)
		{
			result.emplace_back(path);
			return;
		}
		// for each num in map, find the next possible char
		for (auto it : countMap)
		{
			int count = 0;
			for (auto num : path)
			{
				if (num == it.first) count++;
			}
			if (count < it.second)
			{
				path.emplace_back(it.first);
				dfs(countMap, n, path, result);
				path.pop_back();
			}
		}
	}

	vector<vector<int>> permuteUnique(vector<int>& nums)
	{
		// map stores the number and its occurance
		unordered_map<int, int> map;
		for (auto num : nums) map[num]++;

		// store the so far sub-array
		vector<int> path;
		// result
		vector<vector<int>> result;
		dfs(map, nums.size(), path, result);
		return result;
	}

	void Test()
	{
		vector<int> candidates{ 3, 7, 6, 5 };
		auto result = permuteUnique(candidates);
		cout << "candidates: ";
		for (auto candidate : candidates)
		{
			cout << candidate << " ";
		}
		cout << endl << "Result: " << endl;
		for (auto& combination : result)
		{
			for (auto& num : combination)
			{
				cout << num << " ";
			}
			cout << endl;
		}
	}
}