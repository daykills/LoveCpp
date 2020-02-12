/*
16. 3Sum Closest
Total Accepted: 66107 Total Submissions: 233809 Difficulty: Medium
Given an array S of n integers, find three integers in S such that the sum is closest to a given number, target. Return the sum of the three integers. You may assume that each input would have exactly one solution.

For example, given array S = {-1 2 1 -4}, and target = 1.

The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).

A solution set is:
(-1, 0, 1)
(-1, -1, 2)
*/
#include <iostream>
#include <queue>
#include <algorithm>
#include "Common.h"

namespace ThreeSumClosest
{
  int threeSumClosest(vector<int>& nums, int target)
  {
    int n = nums.size();
    // sort the array
    sort(nums.begin(), nums.end());
    // the result, cloest; minimum distance, abs(closest)
    int closestSum, minDist = INT_MAX;
    // the first number at i, find the other two (after i) to match (target - nums[i])
    for (auto i = 0; i < n - 2; i++)
    {
      // search for good pair between lo and hi
      int lo = i + 1, hi = n - 1;
      while (lo < hi)
      {
        auto sum = nums[i] + nums[lo] + nums[hi];
        auto dist = abs(sum - target);
        // find closer sum, update
        if (dist < minDist)
        {
          closestSum = sum, minDist = dist;
        }
        if (sum == target)
        {
          return target;
        }
        else if (sum > target)
        {
          // decrease by move hi to low
          hi--;
        }
        else
        {
          // increase by move lo to high
          lo++;
        }
      }
    }
    return closestSum;
  }

  int Test()
  {
    vector<int> nums{ 23, 33, 12, 3, 14, 6 };
    for (auto i : nums)
      cout << " " << i;
    cout << endl;
    return threeSumClosest(nums, 22);
  }
}