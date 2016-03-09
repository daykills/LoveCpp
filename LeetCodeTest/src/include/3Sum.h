/*
15. 3Sum
Total Accepted: 97791 Total Submissions: 541755 Difficulty: Medium
Given an array S of n integers, are there elements a, b, c in S such that a + b + c = 0? Find all unique triplets in the array which gives the sum of zero.

Note:
Elements in a triplet (a,b,c) must be in non-descending order. (ie, a ¡Ü b ¡Ü c)
The solution set must not contain duplicate triplets.
For example, given array S = {-1 0 1 2 -1 -4},

A solution set is:
(-1, 0, 1)
(-1, -1, 2)
*/
#include <iostream>
#include <queue>
#include <algorithm>
#include "Common.h"

namespace ThreeSum
{
  // find all unique triplets in the nums with index >= start_index
  void search(const vector<int>& sortedNums, int start_index, int target, vector<vector<int>>& result)
  {
    int high = sortedNums.size() - 1;
    int low = start_index;
    while (high > low)
    {
      auto lowVal = sortedNums[low];
      auto highVal = sortedNums[high];
      auto sum = lowVal + highVal;
      if (sum > target)
      {
        while (high > low && highVal == sortedNums[high - 1]) high--;
        high--;
      }
      else
      {
        if (sum == target)
        {
          result.emplace_back(vector<int> { -target, lowVal, highVal });
        }
        while (high > low && lowVal == sortedNums[low + 1]) low++;
        low++;
      }
    }
  }
  vector<vector<int>> threeSum(vector<int>& nums)
  {
    vector<vector<int>> results;
    int n = nums.size();
    if (n == 0) return results;
    sort(nums.begin(), nums.end());
    // target is set as -num[i].
    for(auto i = 0; i < n - 2; i++)
    {
      search(nums, i + 1, -nums[i], results);
      // find next element that's not equal to nums[i]; nextI cann't be n - 2 or bigger.
      while (i < n - 2 && nums[i] == nums[i + 1]) i++;
    }
    return results;
  }

  int Test(vector<int>& nums)
  {
    for (auto i : nums)
      cout << " " << i;
    cout << endl;
    auto results = threeSum(nums);
    for (auto result : results)
    {
      for (auto i : result)
        cout << " " << i;
      cout << endl;
    }    
    return 0;
  }
}