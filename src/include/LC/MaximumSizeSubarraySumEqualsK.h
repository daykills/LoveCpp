/*
325. Maximum Size Subarray Sum Equals k
Medium

812

29

Add to List

Share
Given an array nums and a target value k, find the maximum length of a subarray that sums to k. If there isn't one, return 0 instead.

Note:
The sum of the entire nums array is guaranteed to fit within the 32-bit signed integer range.

Example 1:

Input: nums = [1, -1, 5, -2, 3], k = 3
Output: 4
Explanation: The subarray [1, -1, 5, -2] sums to 3 and is the longest.
Example 2:

Input: nums = [-2, -1, 2, 1], k = 1
Output: 2
Explanation: The subarray [-1, 2] sums to 1 and is the longest.
Follow Up:
Can you do it in O(n) time?
*/

#include "Common.h"

namespace MaximumSizeSubarraySumEqualsK
{

class Solution {
public:
    int maxSubArrayLen(vector<int>& nums, int k) {
        // sum -> lowest localtion
        unordered_map<int, int> hist { { 0, -1 } };
        int maxLen = 0;
        int sum = 0;
        for (auto i = 0; i < nums.size(); i++) {
            sum += nums[i];
            auto target = sum - k;
            // a prvious sum is equal to target
            if (hist.count(target)) {
                maxLen = max(maxLen, i - hist[target]);
            }
            if (!hist.count(sum))
                hist[sum] = i;
        }
        return maxLen;
    }
};

static void Test()
{
    vector<int> nums = { -2,-1,2,1 };
    Solution s;
    std::cout << s.maxSubArrayLen(nums, 1) << std::endl;
}
}
