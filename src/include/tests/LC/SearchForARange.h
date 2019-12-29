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

vector<int> searchRange(vector<int>& nums, int target)
{
    int n = nums.size();
    if (n == 0) return vector<int> {-1, -1};
    
    // binary search to find the target
    int lo = 0, hi = n - 1;
    while (lo < hi)
    {
        auto mid = (lo + hi) / 2;
        if (nums[mid] == target)
        {
            lo = hi = mid;
            break;
        }
        else if (nums[mid] < target)
        {
            lo = mid + 1;
        }
        else
        {
            hi = mid;
        }
    }
    int iTarget = (nums[lo] == target) ? lo : -1;
    if (iTarget == -1) return vector<int> {-1, -1};
    
    // binary search for high end
    lo = 0, hi = iTarget;
    // make sure there is always a target
    while (lo < hi)
    {
        auto mid = (lo + hi) / 2;
        if (nums[mid] < target && nums[mid + 1] == target)
        {
            lo = hi = mid + 1;
            break;
        }
        
        if (nums[mid] < target)
        {
            lo = mid + 1;
        }
        else // meaning nums[mid] == target
        {
            hi = mid;
        }
    }
    int lowEnd = lo;
    
    // binary search for high end
    lo = iTarget, hi = n - 1;
    while (lo < hi)
    {
        auto mid = (lo + hi + 1) / 2;
        if (nums[mid] == target && nums[mid + 1] > target)
        {
            lo = hi = mid;
            break;
        }
        else if (nums[mid] > target)
        {
            hi = mid - 1;
        }
        else // meaning nums[mid] == target
        {
            lo = mid;
        }
    }
    int highEnd = lo;
    
    return vector<int> {lowEnd, highEnd};
}

vector<int> searchRange(vector<int>& nums, int target) {
    auto lower = lower_bound(nums.begin(), nums.end(), target);
    if (lower == nums.end() || *lower != target)
        return { -1, -1 };
    auto upper = upper_bound(nums.begin(), nums.end(), target);
    vector<int> range = { lower - nums.begin(), upper - nums.begin() - 1 };
    return range;
}

int Test()
{
    vector<int> nums{ 2, 2 };
    for (auto num : nums)
    {
        cout << num << " ";
    }
    cout << endl;
    
    auto result = searchRange(nums, 1);
    for (auto num : result)
    {
        cout << num << " ";
    }
    cout << endl;
    return 0;
}
}
