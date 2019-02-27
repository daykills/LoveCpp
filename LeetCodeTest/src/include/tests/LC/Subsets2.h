/*
90. Subsets II My Submissions Question
Total Accepted: 63290 Total Submissions: 209940 Difficulty: Medium
Given a collection of integers that might contain duplicates, nums, return all possible subsets.

Note:
Elements in a subset must be in non-descending order.
The solution set must not contain duplicate subsets.
For example,
If nums = [1,2,2], a solution is:

[
[2],
[1],
[1,2,2],
[2,2],
[1,2],
[]
]
*/

#include <iostream>
#include <queue>
#include <memory>
#include <cassert>
#include <algorithm>
#include <vector>
#include "Common.h"

namespace Subsets2
{
	// index means
	void dfsSearch(const vector<int>& nums, int index, vector<int>& subset, vector<vector<int>>& result)
	{
		// add new subset
		result.emplace_back(subset);

		int n = nums.size();
		// base condition
		if (n == index) return;

		// with different step, try dfs search
		for (auto i = index; i < n; i++)
		{
			// insert number
			subset.emplace_back(nums[i]);
			dfsSearch(nums, i + 1, subset, result);
			subset.pop_back();
			while (i < n - 1 && nums[i + 1] == nums[i]) i++;
		}
	}

	vector<vector<int>> subsetsWithDup(vector<int>& nums)
	{
		sort(nums.begin(), nums.end());
		vector<vector<int>> result;
		vector<int> subset;
		dfsSearch(nums, 0, subset, result);
		return result;
	}

	void Test()
	{
		vector<int> nums{ 1, 4, 4 };
		auto result = subsetsWithDup(nums);

		cout << "nums: ";
		for (auto num : nums)
			cout << num << " ";

		cout << endl << "subsets: ";
		for (auto& subset : result)
		{
			for (auto num : subset)
				cout << num << " ";
			cout << endl;
		}
	}
}