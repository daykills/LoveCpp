/*
80. Remove Duplicates from Sorted Array II
Total Accepted: 65608 Total Submissions: 205355 Difficulty: Medium
Follow up for "Remove Duplicates":
What if duplicates are allowed at most twice?

For example,
Given sorted array nums = [1,1,1,2,2,3],

Your function should return length = 5, with the first five elements of nums being 1, 1, 2, 2 and 3. It doesn't matter what you leave beyond the new length.
*/

#include <algorithm>
#include "Common.h"

namespace RemoveDuplicatesFromSortedArray2
{
  static int Test(vector<int>& nums)
  {
    int n = nums.size();
    if (n <= 1) return n;
    int index = 0, i = 0;
    while (i < n)
    {
      int dupCount = 0;
      while (i < n - 1 && nums[i] == nums[i + 1])
      {
        i++;
        if (dupCount++ < 1)
        {
          nums[index++] = nums[i];
        }
      }
      nums[index++] = nums[i++];
    }
    return index;
  }
}