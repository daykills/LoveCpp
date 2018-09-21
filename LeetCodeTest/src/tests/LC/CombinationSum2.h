/*
40. Combination Sum II My Submissions Question
Total Accepted: 63102 Total Submissions: 232293 Difficulty: Medium
Given a collection of candidate numbers (C) and a target number (T), find all unique combinations in C where the candidate numbers sums to T.

Each number in C may only be used once in the combination.

Note:
All numbers (including target) will be positive integers.
Elements in a combination (a1, a2, … , ak) must be in non-descending order. (ie, a1 ≤ a2 ≤ … ≤ ak).
The solution set must not contain duplicate combinations.
For example, given candidate set 10,1,2,7,6,1,5 and target 8,
A solution set is:
[1, 7]
[1, 2, 5]
[2, 6]
[1, 1, 6]
*/
#include <iostream>
#include <queue>
#include <algorithm>
#include "Common.h"

namespace CombinationSum2
{
  void searchCombinations(vector<int>& candidates, int target, vector<int>& path, int lastCandidateIndex, vector<vector<int>>& combinations)
  {
    // base condition
    if (target == 0)
    {
      combinations.emplace_back(path);
      return;
    }
    if (target < 0) return;

    int n = candidates.size();
    for (auto i = lastCandidateIndex + 1; i < n; i++)
    {
      path.emplace_back(candidates[i]);
      searchCombinations(candidates, target - candidates[i], path, i, combinations);
      path.pop_back();
      // to avoid duplicate paths
      while (i < n - 1 && candidates[i] == candidates[i + 1]) i++;
    }
  }

  vector<vector<int>> combinationSum2(vector<int>& candidates, int target)
  {
    sort(candidates.begin(), candidates.end());
    vector<vector<int>> combinations;
    vector<int> path;
    searchCombinations(candidates, target, path, -1, combinations);
    return combinations;
  }

  void Test()
  {
    vector<int> candidates{ 10, 1, 2, 7, 6, 1, 5 };
    int target = 8;
    auto result = combinationSum2(candidates, target);
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