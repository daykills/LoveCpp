/*
(4)two sum
是leetcode two sum的小变形，要求返回的是count
*/
#include <iostream>
#include <queue>
#include <algorithm>
#include "Common.h"

namespace TwoSumWithCount
{
  // find all unique triplets in the nums with index >= start_index
  int twoSum(vector<int>& sortedNums, int target)
  {
    int n = sortedNums.size();
    if (n == 0) return 0;

    sort(sortedNums.begin(), sortedNums.end());
    int count = 0;
    int high = sortedNums.size() - 1;
    int low = 0;
    while (low < high)
    {
      auto lowVal = sortedNums[low];
      auto highVal = sortedNums[high];
      auto sum = lowVal + highVal;
      if (sum > target)
      {
        // exclude duplicates
        //while (high > low && highVal == sortedNums[high - 1]) high--;
        high--;
      }
      else
      {
        if (sum == target)
        {
          count++;
        }
        // exclude duplicates
        //while (high > low && lowVal == sortedNums[low + 1]) low++;
        low++;
      }
    }
    return count;
  }

  int Test()
  {
    vector<int> nums{ 0, 2, 3, 5, 4, 1, 1 };

    for (auto i : nums)
      cout << " " << i;
    cout << endl;
    auto result = twoSum(nums, 5);
    return result;
  }
}