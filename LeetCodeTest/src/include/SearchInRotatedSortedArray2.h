/*
81. Search in Rotated Sorted Array II
Total Accepted: 56158 Total Submissions: 177519 Difficulty: Medium
Follow up for "Search in Rotated Sorted Array":
What if duplicates are allowed?

Would this affect the run-time complexity? How and why?

Write a function to determine if a given target is in the array.
*/

#include <algorithm>
#include <cassert>
#include "Common.h"

namespace SearchInRotatedSortedArray2
{
  // 
  int search(vector<int>& nums, int target)
  {
    const int n = nums.size();
    if (n == 0) return -1;
    int lo = 0;
    int hi = n - 1;
    while (lo < hi)
    {
      // there is always one half that's sorted. we can reduce within that sorted half
      int mid = (lo + hi) >> 1;

      if (nums[mid] == target) return mid;

      if (nums[lo] < nums[mid])
      {
        // left half is sorted
        if (target < nums[lo] || nums[mid] < target)
        {
          lo = mid + 1;
        }
        else if (nums[lo] <= target && target < nums[mid])
        {
          hi = mid;
        }
      }
      else if (nums[lo] > nums[mid])
      {
        // right half is sorted
        if (target < nums[mid] || nums[hi] < target)
        {
          hi = mid;
        }
        else if (nums[mid] < target && target <= nums[hi])
        {
          lo = mid + 1;
        }
      }
      else // nums[lo] == nums[mid]
      {
        // duplicate may exists
        lo++;
        if (nums[mid] == nums[hi]) hi--;
      }
    }
    return (nums[lo] == target) ? lo : -1;
  }

  ///////////////////////////////////////////////////////////////////////////////////////
  int findTurnPoint(vector<int>& nums)
  {
    int n = nums.size();
    if (n <= 1) return 0;  // no turning point

    int lo = 0;
    int hi = n - 1;
    // narrow down the unsorted half
    while (lo < hi - 1)
    {
      int mid = (lo + hi) >> 1;
      if (nums[lo] < nums[hi])
      {
        return (hi + 1) % n;
      }
      if (nums[lo] < nums[mid])
      {
        // left half is sorted
        lo = mid; // should not +1 as mid is needed to identify dis-order
      }
      else if (nums[lo] > nums[mid])
      {
        hi = mid;
      }
      else // (nums[lo] == nums[mid])
      {
        // duplicates exist
        lo++;
        if (nums[hi] == nums[mid]) hi--;        
      }
    }
    return (nums[lo] < nums[hi]) ? (hi + 1) % n : hi;
  }

  // find turning point, and then start binary search
  int search2(vector<int>& nums, int target)
  {
    const int n = nums.size();
    if (n == 0) return -1;

    int iTurn = findTurnPoint(nums);

    int lo = iTurn;
    int hi = (lo + n - 1) % n;
    while (lo != hi)
    {
      // when lo is bigger than hi, move hi to the high end
      auto mid = (lo > hi) ? ((lo + hi + n) >> 1) % n : (lo + hi) >> 1;
      if (nums[mid] < target)
      {
        lo = (mid + 1) % n;
      }
      else if (nums[mid] > target)
      {
        hi = mid;
      }
      else return mid;
    }
    return (nums[lo] == target) ? lo : -1;
  }

  bool search3(vector<int>& nums, int target)
  {
    int i = search(nums, target);
    return i != -1;
  }

  //////////////////////////////////////////////////////////////////////////////

  static int Test(vector<int>& nums)
  {
    for (auto num : nums)
    {
      cout << num << " ";
    }
    cout << endl;

    return search3(nums, 0);
  }
}