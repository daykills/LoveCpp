/*
18. 4Sum My Submissions Question
Total Accepted: 65798 Total Submissions: 281701 Difficulty: Medium
Given an array S of n integers, are there elements a, b, c, and d in S such that a + b + c + d = target?
Find all unique quadruplets in the array which gives the sum of target.

Note:
Elements in a quadruplet (a,b,c,d) must be in non-descending order. (ie, a ≤ b ≤ c ≤ d)
The solution set must not contain duplicate quadruplets.
For example, given array S = {1 0 -1 0 -2 2}, and target = 0.

A solution set is:
(-1,  0, 0, 1)
(-2, -1, 1, 2)
(-2,  0, 0, 2)
*/
#include <iostream>
#include <queue>
#include <algorithm>
#include "Common.h"

namespace FourSum
{
  vector<vector<int>> fourSum(vector<int>& nums, int target)
  {
    vector<vector<int>> result;
    int n = nums.size();
    if (n == 0) return result;
    // sort the array at cost O(n * log(n))
    sort(nums.begin(), nums.end());
    // enumerate i,j as the first two numbers
    for (int i = 0; i < n - 3; i++)
    {
      for (int j = i + 1; j < n - 2; j++)
      {
        int lo = j + 1, hi = n - 1;
        while (lo < hi)
        {
          auto sum = nums[i] + nums[j] + nums[lo] + nums[hi];
          if (sum <= target)
          {
            // find a quadruplet
            if (sum == target)
            {
              result.emplace_back(vector<int> { nums[i], nums[j], nums[lo], nums[hi] });
            }
            // move to next different number
            while (lo < hi && nums[lo + 1] == nums[lo]) lo++;
            lo++;
          }
          else
          {
            // move to next different number
            while (lo < hi && nums[hi - 1] == nums[hi]) hi--;
            hi--;
          }
        }
        // move j to next different number
        while (j < n - 2 && nums[j + 1] == nums[j]) j++;
      }
      // move i to next different number
      while (i < n - 3 && nums[i + 1] == nums[i]) i++;
    }
    return result;
  }

  int Test()
  {
    vector<int> nums{ 1, 0, -1, 0, -2, 2 };
    for (auto i : nums)
      cout << " " << i;
    cout << endl;
    auto results = fourSum(nums, 4);
    for (auto result : results)
    {
      for (auto i : result)
        cout << " " << i;
      cout << endl;
    }
    return 0;
  }
}