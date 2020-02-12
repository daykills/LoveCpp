/*
 33. Search in Rotated Sorted Array

 Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.
 
 (i.e., [0,1,2,4,5,6,7] might become [4,5,6,7,0,1,2]).
 
 You are given a target value to search. If found in the array return its index, otherwise return -1.
 
 You may assume no duplicate exists in the array.
 
 Your algorithm's runtime complexity must be in the order of O(log n).
 
 Example 1:
 
 Input: nums = [4,5,6,7,0,1,2], target = 0
 Output: 4
 Example 2:
 
 Input: nums = [4,5,6,7,0,1,2], target = 3
 Output: -1
 */

#include <algorithm>
#include <cassert>
#include "Common.h"

namespace SearchInRotatedSortedArray
{
int searchOld(vector<int>& nums, int target) {
    int n = nums.size();
    if (n == 0)
        return -1;
    auto lo = 0;
    auto hi = n - 1;
    while (lo < hi) {
        auto mid = (lo + hi) / 2;
        // iMin on upper side
        if (nums[mid] > nums[hi]) lo = mid + 1;
        else hi = mid;
    }
    assert(lo == hi);
    auto iMin = lo;
    
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

int search(vector<int>& nums, int target) {
    int n = nums.size();
    if (n == 0)
        return -1;
    auto lo = 0;
    auto hi = n - 1;
    while (lo < hi) {
        auto mid = (lo + hi) / 2;
        // iMin on upper side
        if (nums[mid] > nums[hi]) lo = mid + 1;
        else hi = mid;
    }
    assert(lo == hi);
    auto iMin = lo;
    
    vector<int> newNums(n, 0);
    for (auto i = 0; i < n; i++)
        newNums[i] = nums[(i + iMin) % n];
    auto lower = lower_bound(newNums.begin(), newNums.end(), target);
    return (lower != newNums.end() && *lower == target) ?
        (distance(newNums.begin(), lower) + iMin) % n : -1;
}

static void Test()
{
    vector<int> nums = { 4,5,6,7,0,1,2 };
    for (auto num : nums)
    {
        cout << num << " ";
    }
    cout << endl;
    
    cout << "Result: " << search(nums, 1) << std::endl;
}

}

