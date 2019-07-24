/*
 33. Search in Rotated Sorted Array
 Total Accepted: 89767 Total Submissions: 301338 Difficulty: Hard
 Suppose a sorted array is rotated at some pivot unknown to you beforehand.
 
 (i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).
 
 You are given a target value to search. If found in the array return its index, otherwise return -1.
 
 You may assume no duplicate exists in the array.
 */

#include <algorithm>
#include <cassert>
#include "Common.h"

namespace SearchInRotatedSortedArray
{
    //
    int search2(vector<int>& nums, int target)
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
            
            if (nums[lo] <= nums[mid])
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
            else
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
        }
        return (nums[lo] == target) ? lo : -1;
    }
    
    int search(vector<int>& nums, int target) {
        int n = nums.size();
        if (n == 0)
            return -1;
        int lo = 0;
        int hi = n - 1;
        int iMin = (lo + hi) / 2;
        while (lo < hi) {
            // if [lo, hi] is in order, iMin = lo
            if (nums[lo] <= nums[hi]) {
                iMin = lo;
                break;
            }
            iMin = (lo + hi) / 2;
            if (nums[iMin] >= nums[lo])
                lo = iMin + 1;
            else // nums[iMin] <= nums[hi]
                hi = iMin;
        }
        
        // assume the array is offset by iMin
        auto getValue = [&nums, n, iMin](int i) {
            assert(i < n && i >= 0);
            return nums[(i + iMin) % n];
        };
        lo = 0;
        hi = n - 1;
        while (lo < hi) {
            auto mid = (lo + hi) / 2;
            auto midValue = getValue(mid);
            if (midValue == target)
                return (mid + iMin) % n;
            if (midValue > target) {
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }
        return (getValue(lo) == target) ? (lo + iMin) % n : -1;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    
    static void Test()
    {
        vector<int> nums = { 3, 1 };
        for (auto num : nums)
        {
            cout << num << " ";
        }
        cout << endl;
        
        cout << "Result: " << search(nums, 1) << std::endl;
    }
}

