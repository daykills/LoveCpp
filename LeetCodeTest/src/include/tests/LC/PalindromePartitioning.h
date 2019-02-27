/*
131. Palindrome Partitioning My Submissions Question
Total Accepted: 60786 Total Submissions: 220603 Difficulty: Medium
Given a string s, partition s such that every substring of the partition is a palindrome.

Return all possible palindrome partitioning of s.

For example, given s = "aab",
Return

[
["aa","b"],
["a","a","b"]
]

*/

#include <iostream>
#include <queue>
#include <memory>
#include <cassert>
#include <algorithm>
#include <vector>
#include "Common.h"

namespace PalindromePartitioning
{
  bool isPalindrome(const string& str)
  {
    int n = str.length();
    if (n == 0) return true;
    int lo = 0, hi = n - 1;
    while (lo < hi)
    {
      if (str[lo] != str[hi]) return false;
      lo++, hi--;
    }
    return true;
  }

  void dfsSearch(const string& s, int start, vector<string>& path, vector<vector<string>>& partition)
  {
    int n = s.length();
    // reached end of the string, return.
    if (start == n)
    {
      partition.emplace_back(path);
      return;
    }

    // take substring from start to start+step
    for (auto step = 1; step <= n - start; step++)
    {
      auto substring = s.substr(start, step);
      // if substring is a palindrome, we add it into path
      if (!isPalindrome(substring)) continue;
      path.emplace_back(move(substring));
      // try to find good combination
      dfsSearch(s, start + step, path, partition);
      path.pop_back();
    }
  }

  vector<vector<string>> partition(string s)
  {
    vector<string> path;
    vector<vector<string>> result;
    // DFS search for different combinations
    dfsSearch(s, 0, path, result);
    return result;
  }

  void Test()
  {
    string input("aabbaba");    
    cout << "input: " << input << endl;
    auto result = partition(input);
    for (auto& combination : result)
    {
      for (auto& palindrome : combination)
        cout << palindrome << " ";
      cout << endl;
    }
  }
}