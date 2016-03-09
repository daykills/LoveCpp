/*
136. Single Number
Total Accepted: 113183 Total Submissions: 233510 Difficulty: Medium
Given an array of integers, every element appears twice except for one. Find that single one.

Note:
Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory?
*/

#include <algorithm>
#include <unordered_set>
#include "Common.h"

namespace SingleNumber
{
  static int Test2(vector<int>& nums)
  {
    unordered_set<int> history;
    for (auto num : nums)
    {
      auto it = history.find(num);
      if (it == history.end())
      {
        history.emplace(num);
      }
      else
      {
        history.erase(it);
      }
    }
    return *history.begin();
  }
  static int Test(vector<int>& nums)
  {
    const int n = nums.size();
    if (n == 0) return 0;
    
    auto& singleNumber = nums[0];
    for (int i = 1; i < n; i++)
    {
      singleNumber ^= nums[i];
    }
    return singleNumber;
  }
}