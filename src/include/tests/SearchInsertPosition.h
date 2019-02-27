/*
35. Search Insert Position
Total Accepted: 92799 Total Submissions: 252565 Difficulty: Medium
Given a sorted array and a target value, return the index if the target is found. If not, return the index where it would be if it were inserted in order.

You may assume no duplicates in the array.

Here are few examples.
[1,3,5,6], 5 ¡ú 2
[1,3,5,6], 2 ¡ú 1
[1,3,5,6], 7 ¡ú 4
[1,3,5,6], 0 ¡ú 0

*/
#include <algorithm>
#include "Common.h"

namespace SearchInsertPosition
{
  int findFirstNoLessThanTarget(vector<int>& nums, int target)
  {
    int n = nums.size();
    if (n == 0) return 0;

    int lo = 0, hi = n - 1;

    while (lo < hi)
    {
      auto mid = (lo + hi) / 2;
      if (nums[mid] == target) return mid;
      if (nums[mid] < target) lo = mid + 1;
      else hi = mid;
    }
    return nums[lo] >= target ? lo : lo + 1;
  }

  int searchInsert(vector<int>& nums, int target) {
    // find the first location of the first no less than target number
    return findFirstNoLessThanTarget(nums, target);
  }

  static int Test(vector<int>& nums)
  {
    for (auto num : nums)
    {
      cout << num << " ";
    }
    cout << endl;

    return searchInsert(nums, 0);
  }
}