/*
39. Combination Sum My Submissions Question
Total Accepted: 83534 Total Submissions: 275056 Difficulty: Medium
Given a set of candidate numbers (C) and a target number (T), find all unique combinations in C where the candidate numbers sums to T.

The same repeated number may be chosen from C unlimited number of times.

Note:
All numbers (including target) will be positive integers.
Elements in a combination (a1, a2, … , ak) must be in non-descending order. (ie, a1 ≤ a2 ≤ … ≤ ak).
The solution set must not contain duplicate combinations.
For example, given candidate set 2,3,6,7 and target 7,
A solution set is:
[7]
[2, 2, 3]
*/
#include <iostream>
#include <queue>
#include <algorithm>
#include "Common.h"

namespace CombinationSum
{
  void findOneCombination(const vector<int>& candidates, int target, vector<int>& path, int lastCandidateIndex, vector<vector<int>>& combinations)
  {
    // base condition
    // path didn't work out
    if (target < 0) return;
    // path hit the target
    if (target == 0)
    {
      combinations.emplace_back(path);
      return;
    }
    int n = candidates.size();
    for (int i = lastCandidateIndex; i < n; i++)
    {
      // make sure path is non-descending
      if (!path.empty() && candidates[i] < path.back()) continue;
      path.emplace_back(candidates[i]);
      findOneCombination(candidates, target - candidates[i], path, i, combinations);
      path.pop_back();
      while (i < n - 1 && candidates[i] == candidates[i + 1]) i++;
    }
  }

  vector<vector<int>> combinationSum(vector<int>& candidates, int target)
  {
    // sort it
    sort(candidates.begin(), candidates.end());
    vector<vector<int>> combinations;
    // dfs traverse all possibilities
    vector<int> path;
    findOneCombination(candidates, target, path, 0, combinations);
    return combinations;
  }

  void Test()
  {
    vector<int> candidates{ 3, 2, 7, 6, 5 };
    int target = 8;
    auto result = combinationSum(candidates, target);
    cout << "target: " << target << endl;
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