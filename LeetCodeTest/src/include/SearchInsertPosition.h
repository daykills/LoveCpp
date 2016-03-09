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
  int searchInsert(vector<int>& nums, int target)
  {
    int lo = 0;
    int hi = nums.size() - 1; // median is calculated as (hi + lo) >> 1, so hi will never be taken as median
    while (lo < hi)
    {
      int n = hi - lo + 1;
      int iMedian = (hi + lo) >> 1;    // range from lo to hi-1  
      if (nums[iMedian] < target)
      {
        lo = iMedian + 1;
      }
      else if (nums[iMedian] > target)
      {
        hi = iMedian; // should not "-1"
      }
      else
      {
        return iMedian;
      }
    }
    // need a final judge for lo
    return (target <= nums[lo]) ? lo : lo + 1;
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