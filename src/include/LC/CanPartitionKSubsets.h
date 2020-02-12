/*
 698. Partition to K Equal Sum Subsets

 Given an array of integers nums and a positive integer k, find whether it's possible to divide this array into k non-empty subsets whose sums are all equal.
 
 Example 1:
 
 Input: nums = [4, 3, 2, 3, 5, 2, 1], k = 4
 Output: True
 Explanation: It's possible to divide it into 4 subsets (5), (1, 4), (2,3), (2,3) with equal sums.
 
 Note:
 
 1 <= k <= len(nums) <= 16.
 0 < nums[i] < 10000.
*/

#include <algorithm>
#include <unordered_set>
#include "Common.h"

namespace CanPartitionKSubsets
{
bool dfs(vector<int>& nums, int k, int subSum, int startInd, vector<bool>& visited, int curSum) {
    // all slots filled
    if (k == 0) return true;
    // fill one slot; move on to next slot
    if (curSum == subSum) {
        return dfs(nums, k - 1, subSum, 0, visited, 0);
    }
    for (auto i = startInd; i < nums.size(); i++) {
        if (visited[i])
            continue;
        auto num = nums[i];
        visited[i] = true;
        bool success = dfs(nums, k, subSum, i + 1, visited, curSum + num);
        if (success)
            return true;
        visited[i] = false;
    }
    return false;
}

bool canPartitionKSubsets(vector<int>& nums, int k) {
    const int kTotal = std::accumulate(nums.begin(), nums.end(), 0);
    if (kTotal % k) return false;
    const int kSubSum = kTotal / k;
    vector<bool> visited(nums.size(), false);
    return dfs(nums, k, kSubSum, 0, visited, 0);
}

void Test() {
    vector<int> nums = { 4, 3, 2, 3, 5, 2, 1 };
    cout << canPartitionKSubsets(nums, 4) << endl;
}
}
