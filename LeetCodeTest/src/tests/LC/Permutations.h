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
  void traverse(const vector<int>& nums, unordered_map<int, int>& path, vector<vector<int>>& permutes)
  {
    int n = nums.size();
    int nPath = path.size();
    // base condition
    // move path to permutes
    if (nPath == n)
    {
      vector<int> permute(n);
      for (auto& pair : path)
      {
        permute[pair.second] = nums[pair.first];
      }
      permutes.emplace_back(move(permute));
      return;
    }

    for (auto i = 0; i < n; i++)
    {
      auto got = path.find(i);
      // number already used
      if (got != path.end()) continue;
      // add current number to path, its index in permute is nPath
      path.emplace(i, nPath);
      traverse(nums, path, permutes);
      path.erase(path.find(i));
    }
  }
  vector<vector<int>> permute(vector<int>& nums)
  {
    vector<vector<int>> permutes;
    // hash map to record the path (included index). key is the index in nums, value is the index in the permute.
    unordered_map<int, int> path;
    traverse(nums, path, permutes);
    return permutes;
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