/*
 1. Two Sum
 Given an array of integers, return indices of the two numbers such that they add up to a specific target.
 
 You may assume that each input would have exactly one solution, and you may not use the same element twice.
 
 Example:
 
 Given nums = [2, 7, 11, 15], target = 9,
 
 Because nums[0] + nums[1] = 2 + 7 = 9,
 return [0, 1].
 */

#include "Common.h"

namespace TwoSum
{
    vector<int> twoSum(vector<int>& nums, int target) {
        std::map<int, int> preNums;
        for (auto i = 0; i < nums.size(); i++) {
            auto num = nums[i];
            auto iter = preNums.find(target - num);
            if (iter != preNums.end()) {
                return { iter->second, i };
            }
            preNums[num] = i;
        }
        return {};
    }
    
    int Test()
    {
        vector<int> nums{ 2, 7, 11, 15 };
        for (auto i : nums)
            cout << " " << i;
        cout << endl;
        auto result = twoSum(nums, 9);
        for (auto i : result)
            cout << " " << i;
        cout << endl;
        return 0;
    }
}
