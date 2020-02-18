/*
 416. Partition Equal Subset Sum
 
 Given a non-empty array containing only positive integers, find if the array can be partitioned into two subsets such that the sum of elements in both subsets is equal.
 
 Note:
 
 Each of the array element will not exceed 100.
 The array size will not exceed 200.
 
 
 Example 1:
 
 Input: [1, 5, 11, 5]
 
 Output: true
 
 Explanation: The array can be partitioned as [1, 5, 5] and [11].
 
 
 Example 2:
 
 Input: [1, 2, 3, 5]
 
 Output: false
 
 Explanation: The array cannot be partitioned into equal sum subsets.
 */

#include "Common.h"

namespace PartitionEqualSubsetSum
{
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = std::accumulate(nums.begin(), nums.end(), 0);
        if (sum & 1) return false;
        
        sum /= 2;
        
        // dp[i]: times that i has been reached
        vector<uint8_t> dp(sum + 1, 0);
        // 0 is always reachable
        dp[0] = 1;
        // dpPre is the state after processing last number
        vector<uint8_t> dpPre = dp;
        for (auto num : nums) {
            // basically shift dpPre with num distance
            for (auto i = 0; i <= sum; i++) {
                auto newReachable = num + i;
                if (!dpPre[i] || newReachable > sum)
                    continue;
                dp[newReachable]++;
            }
            std::copy (dp.begin(), dp.end(), dpPre.begin());
        }
        return dp[sum];
    }
    
    bool canPartitionBit(vector<int>& nums) {
        bitset<5001> bits(1);
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum & 1) return false;
        for (auto n : nums)
            bits |= bits << n;
        return bits[sum >> 1];
    }
};

static void Test()
{
    vector<int> nums = { 2,2,3,1 };
    Solution solution;
    std::cout << solution.canPartitionBit(nums) << std::endl;
}
}
