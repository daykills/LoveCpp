/*
https://leetcode.com/problems/longest-increasing-subsequence/

300. Longest Increasing Subsequence

Given an unsorted array of integers, find the length of longest increasing subsequence.

For example,
Given [10, 9, 2, 5, 3, 7, 101, 18],
The longest increasing subsequence is [2, 3, 7, 101], therefore the length is 4. Note that there may be more than one LIS combination, it is only necessary for you to return the length.

Your algorithm should run in O(n2) complexity.

Follow up: Could you improve it to O(n log n) time complexity?

*/

#include <string>
#include <iostream>
#include "Common.h"

namespace LongestIncreasingSubsequence
{
int lengthOfLISDP(vector<int>& nums) {
    if (nums.empty()) return 0;
    // dp[i] is the length of LIS ending at i
    vector<int> dp(nums.size(), 1);
    int ans = 0;
    for (auto i = 0; i < nums.size(); i++) {
        for (auto j = 0; j < i; j++) {
            if (nums[j] >= nums[i]) continue;
            dp[i] = max(dp[i], dp[j] + 1);
        }
        ans = max(ans, dp[i]);
    }
    return ans;
}

// https://www.geeksforgeeks.org/longest-monotonically-increasing-subsequence-size-n-log-n/
int lengthOfLIS(vector<int>& nums) {
    vector<int> res;
    for(int i=0; i<nums.size(); i++) {
        auto it = std::lower_bound(res.begin(), res.end(), nums[i]);
        if(it==res.end())
            res.push_back(nums[i]);
        else *it = nums[i];
    }
    return res.size();
}

static void Test()
{
    vector<int> nums = {2, 5, 3, 1, 2, 3, 4,};
    std::cout << lengthOfLIS(nums) << std::endl;
}

}
