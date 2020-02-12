/*
78. Subsets My Submissions Question
Total Accepted: 88548 Total Submissions: 286865 Difficulty: Medium
Given a set of distinct integers, nums, return all possible subsets.

Note:
Elements in a subset must be in non-descending order.
The solution set must not contain duplicate subsets.
For example,
If nums = [1,2,3], a solution is:

[
[3],
[1],
[2],
[1,2,3],
[1,3],
[2,3],
[1,2],
[]
]
*/

#include <iostream>
#include <queue>
#include <memory>
#include <cassert>
#include <algorithm>
#include <vector>
#include "Common.h"

namespace Subsets
{
    void dfs(const vector<int>& nums, int pos, vector<int>& subset, vector<vector<int>>& subsets)
    {
        for (auto i = pos; i < nums.size(); i++) {
            subset.emplace_back(nums[i]);
            dfs(nums, i + 1, subset, subsets);
            subset.pop_back();
        }
        subsets.emplace_back(subset);
    }
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> subsets;
        vector<int> subset;
        dfs(nums, 0, subset, subsets);
        return subsets;
    }

  void Test()
  {
    vector<int> nums{ 3, 2, 0, 1 };
    auto result = subsets(nums);

    cout << "nums: ";
    for (auto num : nums)
      cout << num << " ";

    cout << endl << "subsets: ";
    for (auto& subset : result)
    {
      for (auto num : subset)
        cout << num << " ";
      cout << endl;
    }    
  }
}
