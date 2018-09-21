/*
14. Longest Common Prefix My Submissions Question
Total Accepted: 90166 Total Submissions: 326384 Difficulty: Easy
Write a function to find the longest common prefix string amongst an array of strings.
*/

#include <iostream>
#include <stack>
#include <algorithm>
#include "Common.h"

namespace LongestCommonPrefix
{
  string longestCommonPrefix(vector<string>& strs)
  {
    int n = strs.size();
    if (n == 0) return "";

    auto& firstStr = strs[0];
    int endOfPrefix = firstStr.length() - 1;
    for (auto i = 1; i < n; i++)
    {
      const auto& curStr = strs[i];
      // if curStr is shorter, update endOfPrefix
      endOfPrefix = min((int)curStr.length() - 1, endOfPrefix);
      // compare curStr with first endOfPrefix letters of firstStr, and update endOfPrefix
      for (auto index = endOfPrefix; index >= 0; index--)
      {
        // if index is not common, endOfPrefix move to index - 1
        if (curStr[index] != firstStr[index])
        {
          endOfPrefix = index - 1;
        }
      }
      // no common prefix
      if (endOfPrefix == -1) return "";
    }
    return firstStr.substr(0, endOfPrefix + 1);
  }

  int Test()
  {
    vector<string> strs{ "aacdf", "aacd", "aac", "aacdfg" };
    for (auto& str : strs)
    {
      cout << str << " ";
    }
    
    cout << endl << "result: " << longestCommonPrefix(strs) << endl;
    return 0;
  }
}
