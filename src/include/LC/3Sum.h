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
    void search(const vector<int>& sorted, int start, int target, vector<vector<int>>& result)
    {
        int n = sorted.size();
        int lo = start, hi = n - 1;
        while(lo < hi)
        {
            auto sum = sorted[lo] + sorted[hi] + target;
            if(sum == 0)
            {
                result.emplace_back(vector<int>{ target, sorted[lo] , sorted[hi]});
                while(lo < hi && sorted[lo + 1] == sorted[lo]) lo++;
                while(lo < hi && sorted[hi - 1] == sorted[hi]) hi--;
                lo++, hi--;
            }
            else if(sum < 0)
            {
                lo++;
            }
            else
            {
                hi--;
            }
        }
    }

    vector<vector<int>> threeSum(vector<int>& nums)
    {
        vector<vector<int>> result;
        int n = nums.size();
        if(n == 0) return result;
        // sort nums
        sort(nums.begin(), nums.end());
        
        for(auto i = 0; i < n - 2; i++)
        {
            // for each i, find the other two numbers
            search(nums, i + 1, nums[i], result);
            // move to next different number
            while(i < n - 2 && nums[i + 1] == nums[i]) i++;
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
