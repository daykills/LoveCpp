/*
46. Permutations My Submissions Question
Total Accepted: 91404 Total Submissions: 260919 Difficulty: Medium
Given a collection of distinct numbers, return all possible permutations.

For example,
[1,2,3] have the following permutations:
[1,2,3], [1,3,2], [2,1,3], [2,3,1], [3,1,2], and [3,2,1].
*/
#include <iostream>
#include <queue>
#include <algorithm>
#include "Common.h"

namespace Permutations
{
    void dfs(vector<int>& nums, vector<int>& cur, unordered_set<int>& curSet, vector<vector<int>>& result) {
        if (cur.size() == nums.size()) {
            result.emplace_back(cur);
            return;
        }
        for (auto i = 0; i < nums.size(); i++) {
            // don't re-add number to cur
            auto it = curSet.find(i);
            if (it != curSet.end())
                continue;
            curSet.emplace(i);
            cur.emplace_back(nums[i]);
            dfs(nums, cur, curSet, result);
            cur.pop_back();
            curSet.erase(i);
        }
    }
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> result;
        unordered_set<int> curSet;
        vector<int> cur;
        dfs(nums, cur, curSet, result);
        return result;
    }

  void Test()
  {
    vector<int> candidates{ 3, 7, 6, 5 };
    auto result = permute(candidates);
    cout << "candidates: ";
    for (auto candidate : candidates)
    {
      cout << candidate << " ";
    }
    cout << endl << "Result: " << endl;
    for (auto& combination : result)
    {
      for (auto& num : combination)
      {
        cout << num << " ";
      }
      cout << endl;
    }
  }
}
