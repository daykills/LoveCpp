/*
55. Jump Game My Submissions Question
Total Accepted: 72280 Total Submissions: 257839 Difficulty: Medium
Given an array of non-negative integers, you are initially positioned at the first index of the array.

Each element in the array represents your maximum jump length at that position.

Determine if you are able to reach the last index.

For example:
A = [2,3,1,1,4], return true.

A = [3,2,1,0,4], return false.
*/

#include <iostream>
#include "Common.h"

namespace JumpGame
{
  bool canJump1(vector<int>& nums)
  {
    int n = nums.size();
    if (n == 1) return true;

    int maxReach = 0;
    for (auto i = 0; i < n; i++)
    {
      // if maxReach can reach i, update maxReach
      if (maxReach >= i) maxReach = max(maxReach, i + nums[i]);
      else return false; // no possible to go any further
      if (maxReach >= n - 1) return true;
    }
    return false;
  }

  bool canJump(vector<int>& nums)
  {
    int n = nums.size();
    if (n == 1) return true;

    int remainingSteps = nums[0];
    for (auto i = 1; i < n; i++)
    {
      // consumed one step coming from i-1 to i
      remainingSteps--;
      if (remainingSteps < 0) return false;
      remainingSteps = max(nums[i], remainingSteps);
    }

    return true;
  }

  static bool Test()
  {
    vector<int> nums{ 3, 1, 2, 2, 1, 2 };
    for (auto i : nums)
      cout << " " << i;
    cout << endl;

    cout << "Best profit: " << canJump(nums) << endl;

    return false;
  }
}