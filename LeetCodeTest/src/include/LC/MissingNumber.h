/*
268. Missing Number My Submissions QuestionEditorial Solution
Total Accepted: 46457 Total Submissions: 116513 Difficulty: Medium
Given an array containing n distinct numbers taken from 0, 1, 2, ..., n, find the one that is missing from the array.

For example,
Given nums = [0, 1, 3] return 2.

Note:
Your algorithm should run in linear runtime complexity. Could you implement it using only constant extra space complexity?
*/
#include <iostream>
#include <queue>
#include <algorithm>
#include "Common.h"

namespace MissingNumber
{
	int missingNumber(vector<int>& nums)
	{
		int n = nums.size();
		int num = 0;
		for (auto i = 1; i <= n; i++)
		{
			num ^= i;
			num ^= nums[i - 1];
		}
		return num;
	}

	void Test()
	{
		vector<int> nums{ 0, 1, 3 };
		for(auto num : nums)
			cout << num << " ";
		
		cout << endl << missingNumber(nums) << endl;
	}
}