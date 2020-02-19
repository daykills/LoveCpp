/*
 410. Split Array Largest Sum

 Given an array which consists of non-negative integers and an integer m, you can split the array into m non-empty continuous subarrays. Write an algorithm to minimize the largest sum among these m subarrays.

 Note:
 If n is the length of array, assume the following constraints are satisfied:

 1 ≤ n ≤ 1000
 1 ≤ m ≤ min(50, n)
 Examples:

 Input:
 nums = [7,2,5,10,8]
 m = 2

 Output:
 18

 Explanation:
 There are four ways to split nums into two subarrays.
 The best way is to split it into [7,2,5] and [10,8],
 where the largest sum among the two subarrays is only 18.
 
 */

#include <iostream>
#include <queue>
#include <algorithm>
#include "Common.h"

namespace SplitArrayLargestSum
{
// get the min split sum for nums in [start, n - 1], with m splits
long dfs(vector<int>& nums, vector<long>& accum, int m, int start, vector<vector<int>>& visited) {
    assert(start >= 0 && start < nums.size());
    if (m == 1)
        return accum.back() - accum[start];
    // memorization for speed
    if (visited[m][start])
        return visited[m][start];
    
    long minMaxSum = LONG_MAX;
    
    for (auto next = start + 1; next < nums.size(); next++) {
        long leftSum = accum[next] - accum[start];
        long rightMinMaxSum = dfs(nums, accum, m - 1, next, visited);
        auto maxSplitSum = max(leftSum, rightMinMaxSum);
        minMaxSum = min(minMaxSum, maxSplitSum);
    }
    visited[m][start] = minMaxSum;
    return minMaxSum;
}

int splitArray(vector<int>& nums, int m) {
    auto n = nums.size();
    assert(n > 0 && m < n);
    
    // sum of first i elements
    vector<long> accum(n + 1, 0);
    for (auto i = 1; i <= n; i++)
        accum[i] = accum[i - 1] + nums[i - 1];
    
    vector<vector<int>> visited(m + 1, vector<int>(n, 0));
    
    return dfs(nums, accum, m, 0, visited);
}

////////////////////////////////////////////////////////////////////////////////////
void Test()
{
    vector<int> nums = {7,2,5,10,8};
    cout << splitArray(nums, 2) << endl;
}
}
