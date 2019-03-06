/*
4. Median of Two Sorted Arrays
 There are two sorted arrays nums1 and nums2 of size m and n respectively.
 
 Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).
 
 You may assume nums1 and nums2 cannot be both empty.
 
 Example 1:
 
 nums1 = [1, 3]
 nums2 = [2]
 
 The median is 2.0
 Example 2:
 
 nums1 = [1, 2]
 nums2 = [3, 4]
 
 The median is (2 + 3)/2 = 2.5
*/
#include <cassert>
#include "Common.h"

namespace MedianOfTwoSortedArrays
{
  // find the k-th number of the merged array, k = 1 ~ m+n
  int findKthNumber(vector<int>& nums1, int lo1, int hi1, vector<int>& nums2, int lo2, int hi2, int k)
  {
    // array length
    const int len1 = hi1 - lo1 + 1;
    const int len2 = hi2 - lo2 + 1;
    assert(k <= len1 + len2 );

    // make sure the shorter one is nums1
    if (len1 > len2) return findKthNumber(nums2, lo2, hi2, nums1, lo1, hi1, k);

    assert(k > 0);

    // if nums1 is empty
    if (len1 == 0)
    {
      return nums2[lo2 + k - 1];
    }

    // looking for the first number; len1 and len2 are guaranteed to be > 0
    if (k == 1)
    {
      return min(nums1[lo1], nums2[lo2]);
    }    
    
    // compare the first k1 of nums1 and first k2 of nums2 (k1 + k2 <= k); exclude the smaller.
    const int k1 = min(k >> 1, len1);
    const int k2 = k - k1;  // k - k1 must be less than len2

    if (nums1[lo1 + k1 - 1] < nums2[lo2 + k2 - 1])
    {
      // if k1 is smaller, exclude those k1 numbers
      return findKthNumber(nums1, lo1 + k1, hi1, nums2, lo2, hi2, k - k1);
    }
    else
    {
      // if k2 is smaller, exclude those k2 numbers
      return findKthNumber(nums1, lo1, hi1, nums2, lo2 + k2, hi2, k - k2);
    }
  }

  double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2)
  {
    int m = nums1.size();
    int n = nums2.size();
    if (m == 0 && n == 0)
    {
      return 0;
    }
    else if (m == 0)
    {
      return(nums2[(n - 1) / 2] + nums2[n / 2]) * 0.5;
    }
    else if (n == 0)
    {
      return(nums1[(m - 1) / 2] + nums1[m / 2]) * 0.5;
    }

    if (m + n & 0x1)
    {
      // find the middle number
      return findKthNumber(nums1, 0, m - 1, nums2, 0, n - 1, (m + n + 1) / 2);
    }
    else
    {
      // return the average of the middle two numbers
      return (findKthNumber(nums1, 0, m - 1, nums2, 0, n - 1, (m + n) / 2)
        + findKthNumber(nums1, 0, m - 1, nums2, 0, n - 1, (m + n) / 2 + 1)) * 0.5;
    }

    return 0;
  }
  static double Test(vector<int>& nums)
  {
    vector<int> nums1;
    vector<int> nums2;

    int n = nums.size();
    nums1.insert(nums1.begin(), nums.begin(), nums.begin() + n / 2);
    nums2.insert(nums2.begin(), nums.begin() + n / 2, nums.end());

    for (auto num : nums1)
    {
      cout << num << " ";
    }
    cout << endl;

    for (auto num : nums2)
    {
      cout << num << " ";
    }
    cout << endl;

    return findMedianSortedArrays(nums1, nums2);
  }
}
