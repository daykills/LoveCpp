/*
34. Search for a Range
Total Accepted: 72911 Total Submissions: 255449 Difficulty: Medium
Given a sorted array of integers, find the starting and ending position of a given target value.

Your algorithm's runtime complexity must be in the order of O(log n).

If the target is not found in the array, return [-1, -1].

For example,
Given [5, 7, 7, 8, 8, 10] and target value 8,
return [3, 4].
*/

#include <algorithm>
#include "Common.h"

namespace SearchForARange
{
  int findFirstNotLessThanTarget(vector<int>& nums, int target)
  {
    int lo = 0;
    int hi = nums.size() - 1;
    while (lo != hi)
    {
      int iMedian = (lo + hi) >> 1; // lo to hi-1
      if (nums[iMedian] < target)
      {
        lo = iMedian + 1;
      }
      else
      {
        hi = iMedian;
      }
    }
    return (nums[lo] >= target) ? lo : lo + 1;  // return could be n
  }

  int findLastNotGreaterThanTarget(vector<int>& nums, int target)
  {
    int lo = 0;
    int hi = nums.size() - 1;
    while (lo != hi)
    {
      int iMedian = (lo + hi) >> 1; // lo to hi-1
      if (nums[iMedian] <= target)
      {
        lo = iMedian + 1;
      }
      else
      {
        hi = iMedian;
      }
    }
    return (nums[lo] <= target) ? lo : lo - 1;  // return could be -1
  }

  vector<int> searchRange(vector<int>& nums, int target) {
    vector<int> result(2, -1);
    auto left = findFirstNotLessThanTarget(nums, target);
    if (left == nums.size() || nums[left] != target) return result;
    auto right = findLastNotGreaterThanTarget(nums, target);
    result[0] = left;
    result[1] = right;
    return result;
  }

  int Test(vector<int>& nums)
  {
    for (auto num : nums)
    {
      cout << num << " ";
    }
    cout << endl;

    auto result = searchRange(nums, 0);
    for (auto num : result)
    {
      cout << num << " ";
    }
    cout << endl;
    return 0;
  }
}