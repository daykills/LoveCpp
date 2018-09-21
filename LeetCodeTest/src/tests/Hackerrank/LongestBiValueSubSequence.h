#pragma once
/*

*/

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

namespace LongestBiValueSubSequence
{
	int findLongestBiValueSubSequence(vector<int> &nums)
	{
		// write your code in C++11 (g++ 4.8.2)
		int n = nums.size();
		if (n <= 2) return n;

		vector<int> biValue(2);
		vector<int> firstPos(2);
		biValue[0] = nums[0], biValue[1] = nums[1];
		int startPos = 0;
		int maxLen = 2;
		for (auto i = 2; i < n; i++)
		{
			// the current substr is still bi-valued
			if (nums[i] == biValue[0] || nums[i] == biValue[1])
			{
				maxLen = max(maxLen, i - startPos + 1);
				continue;
			}
			// startPos becomes the first A[i - 1] location
			startPos = i - 1;
			while (startPos > 0 && nums[startPos - 1] == nums[i - 1]) startPos--;
			// update the bi values
			biValue[0] = nums[i], biValue[1] = nums[i - 1];
			maxLen = max(maxLen, i - startPos + 1);
		}
		return maxLen;
	}
	void Test()
	{
		vector<int> nums{ 1, 1, 2, 3, 2, 3, 1, 4, 5, 4, 5 };
		auto result = findLongestBiValueSubSequence(nums);
		cout << result << endl;
	}
}