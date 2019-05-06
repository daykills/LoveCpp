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
    void dfs(vector<vector<int>>& combinations, vector<int>& combination, int n, int k) {
        // base condition
        auto curLen = combination.size();
        if (curLen == k) {
            combinations.emplace_back(combination);
            return;
        }
        auto lastNum = curLen == 0 ? 0 : combination.back();
        // not enough remaining numbers to get k numbers
        if (k - curLen + lastNum > n)
            return;
        for (auto nextNum = lastNum + 1; nextNum <= n; nextNum++) {
            combination.emplace_back(nextNum);
            dfs(combinations, combination, n, k);
            combination.pop_back();
        }
    }
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> combinations;
        if (k > n)
            return combinations;
        vector<int> combination;
        dfs(combinations, combination, n, k);
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
