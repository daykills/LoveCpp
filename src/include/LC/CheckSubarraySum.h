/*
 523. Continuous Subarray Sum
 
 Given a list of non-negative numbers and a target integer k, write a function to check if the array has a continuous subarray of size at least 2 that sums up to a multiple of k, that is, sums up to n*k where n is also an integer.
 
 Example 1:
 
 Input: [23, 2, 4, 6, 7],  k=6
 Output: True
 Explanation: Because [2, 4] is a continuous subarray of size 2 and sums up to 6.
 Example 2:
 
 Input: [23, 2, 6, 4, 7],  k=6
 Output: True
 Explanation: Because [23, 2, 6, 4, 7] is an continuous subarray of size 5 and sums up to 42.
 
 Note:
 
 The length of the array won't exceed 10,000.
 You may assume the sum of all the numbers is in the range of a signed 32-bit integer.
*/

#include <iostream>
#include <stack>
#include <algorithm>
#include "Common.h"

namespace CheckSubarraySum
{
bool checkSubarraySum(vector<int>& nums, int k) {
    if (nums.empty()) return false;
    if (k == 0) {
        for (auto i = 1; i < nums.size(); i++) {
            if (nums[i] == 0 && nums[i - 1] == 0) return true;
        }
        return false;
    }
    unordered_map<int, int> rem;
    rem.emplace(0, -1);
    int accum = 0;
    for (auto i = 0; i < nums.size(); i++) {
        auto num = nums[i];
        accum = (accum + num) % k;
        auto it = rem.find(accum);
        // if one of the previous accumulated sums has same remainder
        if (it == rem.end()) {
            rem.emplace(accum, i);
            continue;
        };
        auto preInd = it->second;
        if (preInd + 1 < i) return true;
    }
    return false;
}

int Test()
{
    vector<int> nums = { 1, 0 };
    cout << checkSubarraySum(nums, 2) << endl;
return 0;
}
}
