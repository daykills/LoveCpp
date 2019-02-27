/*
77. Combinations My Submissions Question
Total Accepted: 69891 Total Submissions: 207367 Difficulty: Medium
Given two integers n and k, return all possible combinations of k numbers out of 1 ... n.

For example,
If n = 4 and k = 2, a solution is:

[
[2,4],
[3,4],
[2,3],
[1,2],
[1,3],
[1,4],
]
*/

#include <iostream>
#include <queue>
#include <algorithm>
#include "Common.h"

namespace CombinationSum
{
  // combination is the result containing first i picks; all numbers in combination are accending; combination stores all results
  void dfsSearch(int n, int k, vector<int>& combination, vector<vector<int>>& combinations)
  {
    int alreadyPicked = combination.size();
    int lastPicked = (alreadyPicked == 0) ? 0 : combination.back();
    // base condition: not enough numbers left to fill k slots
    if (k - alreadyPicked > n - lastPicked) return;
    // base condition: combination complete, return
    if (alreadyPicked == k)
    {
      combinations.emplace_back(combination);
      return;
    }
    // try numbers bigger than the last picked number
    for (auto i = lastPicked + 1; i <= n; i++)
    {
      combination.push_back(i);
      dfsSearch(n, k, combination, combinations);
      combination.pop_back();
    }
  }
  vector<vector<int>> combine(int n, int k)
  {
    vector<vector<int>> combinations;
    vector<int> combination;
    dfsSearch(n, k, combination, combinations);
    return combinations;
  }

  void Test()
  {
    int n = 6, k = 3;
    auto result = combine(n, k);
    cout << "n: " << n << " k: " << k << endl;
    cout << "Combinations: " << endl;
    for (auto& combination : result)
    {
      for (auto num : combination)
        cout << num << " ";
      cout << endl;
    }
  }
}