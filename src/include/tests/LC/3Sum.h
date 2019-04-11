/*
 15. 3Sum
 Total Accepted: 97791 Total Submissions: 541755 Difficulty: Medium
 Given an array S of n integers, are there elements a, b, c in S such that a + b + c = 0? Find all unique triplets in the array which gives the sum of zero.
 
 Note:
 Elements in a triplet (a,b,c) must be in non-descending order. (ie, a ¡Ü b ¡Ü c)
 The solution set must not contain duplicate triplets.
 For example, given array S = {-1 0 1 2 -1 -4},
 
 A solution set is:
 (-1, 0, 1)
 (-1, -1, 2)
 */
#include <iostream>
#include <queue>
#include <algorithm>
#include "Common.h"

namespace ThreeSum
{
    // from start to end of sorted nums, find two sum for target.
    void search(const vector<int>& sortedNums, int start, int target, vector<vector<int>>& result)
    {
        int n = static_cast<int>(sortedNums.size());
        int lo = start, hi = n - 1;
        while (lo < hi)
        {
            auto sum = sortedNums[lo] + sortedNums[hi] + target;
            if (sum == 0)
            {
                result.emplace_back(vector<int>{ target, sortedNums[lo], sortedNums[hi]});
                while (lo < hi && sortedNums[lo + 1] == sortedNums[lo]) lo++;
                while (lo < hi && sortedNums[hi - 1] == sortedNums[hi]) hi--;
                lo++;
                hi--;
            }
            else if (sum < 0)
            {
                while (lo < hi && sortedNums[lo + 1] == sortedNums[lo]) lo++;
                lo++;
            }
            else
            {
                while (lo < hi && sortedNums[hi - 1] == sortedNums[hi]) hi--;
                hi--;
            }
        }
    }
    
    vector<vector<int>> threeSumOld(vector<int>& nums)
    {
        vector<vector<int>> result;
        int n = static_cast<int>(nums.size());
        if (n == 0) return result;
        // sort nums
        sort(nums.begin(), nums.end());
        
        for (auto i = 0; i < n - 2; i++)
        {
            // for each i, find the other two numbers
            search(nums, i + 1, nums[i], result);
            // move to next different number
            while (i < n - 2 && nums[i + 1] == nums[i]) i++;
        }
        return result;
    }
    
    vector<vector<int>> threeSum(vector<int>& nums)
    {
        if (nums.size() < 3)
            return vector<vector<int>>();
        // make sure nums is sorted
        std::sort(nums.begin(), nums.end());
        vector<vector<int>> result;
        auto lo = nums.begin();
        auto hi = nums.end();
        auto count = 0;
        // search for (hi, mid, lo) that qualifies
        while (std::distance(lo, hi) >= 3) {
            auto expected = -(*lo + *(hi - 1));
            auto it = std::lower_bound(lo + 1, hi - 1, expected);
            if (it != hi - 1) {
                result.emplace_back(vector<int> {
                    static_cast<int>(std::distance(nums.begin(), lo)),
                    static_cast<int>(std::distance(nums.begin(), it)),
                    static_cast<int>(std::distance(nums.begin(), hi - 1))
                });
            }
            if (count++ % 2) {
                lo++;
            } else {
                hi--;
            }
        }
        return result;
    }
    
    int Test()
    {
        vector<int> nums = { -1, 0, 1, 2, -1, -1, -4 };
        for (auto i : nums)
            cout << " " << i;
        cout << endl;
        auto results = threeSum(nums);
        for (auto result : results)
        {
            for (auto i : result)
                cout << " " << i;
            cout << endl;
        }
        return 0;
    }
}
