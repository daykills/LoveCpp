/*
 540. Single Element in a Sorted Array

 You are given a sorted array consisting of only integers where every element appears exactly twice, except for one element which appears exactly once. Find this single element that appears only once.

 Example 1:
 
 Input: [1,1,2,3,3,4,4,8,8]
 Output: 2
 Example 2:
 
 Input: [3,3,7,7,10,11,11]
 Output: 10
 
 Note: Your solution should run in O(log n) time and O(1) space.
*/

#include <algorithm>
#include <unordered_set>
#include "Common.h"

namespace SingleNonDuplicate
{
int singleNonDuplicate(vector<int>& nums) {
    auto lo = 0;
    auto hi = nums.size() - 1;
    while (lo < hi) {
        auto mid = (lo + hi) / 2;
        if (mid % 2 == 0) {
            if (nums[mid] == nums[mid + 1]) {
                // single number is on high side
                lo = mid + 1;
            } else {
                if (mid == 0 || nums[mid - 1] != nums[mid])
                    return nums[mid];
                hi = mid;
            }
        } else {
            assert(mid > 0);
            if (nums[mid] == nums[mid - 1]) {
                lo = mid + 1;
            } else {
                hi = mid;
            }
        }
    }
    return nums[lo];
}

void Test() {
    vector<int> nums = { 1,1,2,3,3,4,4,8,8 };
    cout << singleNonDuplicate(nums) << endl;
}
}
