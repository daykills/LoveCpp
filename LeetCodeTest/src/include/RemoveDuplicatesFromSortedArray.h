/*
26. Remove Duplicates from Sorted Array
Total Accepted: 110002 Total Submissions: 336956 Difficulty: Easy
Given a sorted array, remove the duplicates in place such that each element appear only once and return the new length.

Do not allocate extra space for another array, you must do this in place with constant memory.

For example,
Given input array nums = [1,1,2],

Your function should return length = 2, with the first two elements of nums being 1 and 2 respectively. It doesn't matter what you leave beyond the new length.
*/

#include <algorithm>
#include "Common.h"

namespace RemoveDuplicatesFromSortedArray
{
  static int Test(vector<int>& nums)
  {
    int n = nums.size();
    if (n <= 1) return n;
    int index = 0, i = 0;
    while (i < n)
    {
      while (i < n - 1 && nums[i] == nums[i + 1]) i++;
      nums[index++] = nums[i++];
    }
    return index;
  }
}