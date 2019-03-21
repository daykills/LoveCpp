/*
88. Merge Sorted Array
Total Accepted: 86584 Total Submissions: 291349 Difficulty: Easy
Given two sorted integer arrays nums1 and nums2, merge nums2 into nums1 as one sorted array.

Note:
You may assume that nums1 has enough space (size that is greater or equal to m + n) to hold additional elements from nums2. The number of elements initialized in nums1 and nums2 are m and n respectively.
*/

#include <algorithm>
#include "Common.h"

namespace MergeSortedArray
{
  void merge(vector<int>& nums1, int m, vector<int>& nums2, int n)
  {
    int i1 = m - 1, i2 = n - 1;
    // start from m + n -1, get biggest elements one by one
    int j = m + n - 1;
    while (i2 >= 0)
    {
      if (i1 >= 0 && nums1[i1] > nums2[i2])
      {
        nums1[j--] = nums1[i1--];
      }
      else
      {
        nums1[j--] = nums2[i2--];
      }
    }
  }

  static bool Test()
  {
    vector<int> nums1{ 1, 4, 5, 11, 12, 13, -1, -1, -1, -1, -1 };
    vector<int> nums2{ 1, 2, 2, 6, 12 };

    for (auto i : nums1)
      cout << " " << i;
    cout << endl;

    for (auto i : nums2)
      cout << " " << i;
    cout << endl;

    merge(nums1, 6, nums2, 5);
    for (auto i : nums1)
      cout << " " << i;
    cout << endl;

    return false;
  }
}