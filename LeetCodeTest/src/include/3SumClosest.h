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
  int closestToTarget(vector<int>& sortedNums, int startIndex, int target)
  {
    int low = startIndex;
    int high = sortedNums.size() - 1;
    int smallestDiff = INT_MAX;
    while (low < high)
    {
      auto diff = sortedNums[low] + sortedNums[high] - target;
      // perfect match
      if (diff == 0) return target;
      // if abs(diff) increases, then last diff is the closest
      if (abs(diff) < abs(smallestDiff))
      {
        smallestDiff = diff;
      }
      
      // go to the direction that makes abs(diff) smaller; skip duplicate numbers
      if (diff > 0)
      {
        while (high > low && sortedNums[high] == sortedNums[high - 1]) high--;
        high--;
      }
      else
      {
        while (high > low && sortedNums[low] == sortedNums[low + 1]) low++;
        low++;
      }
    }
    return smallestDiff + target;
  }

  int threeSumClosest(vector<int>& nums, int target)
  {
    int n = nums.size();
    if (n == 0) return 0;
    int diff = INT_MAX;
    int closest = 0;
    sort(nums.begin(), nums.end());
    for (int i = 0; i < n - 2; i++)
    {
      int targetTemp = target - nums[i];
      auto newClosest = closestToTarget(nums, i + 1, targetTemp);
      auto newDiff = abs(newClosest - targetTemp);
      if (newDiff < diff)
      {
        diff = newDiff;
        closest = newClosest + nums[i];
      }
      // skip duplicate numbers
      while (i < n - 2 && nums[i] == nums[i + 1]) i++;
    }
    return closest;
  }

  int Test(vector<int>& nums)
  {
    for (auto i : nums)
      cout << " " << i;
    cout << endl;
    return threeSumClosest(nums, -289);
  }
}