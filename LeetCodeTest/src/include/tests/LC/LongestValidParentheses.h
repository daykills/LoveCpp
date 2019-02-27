/*
32. Longest Valid Parentheses My Submissions Question
Total Accepted: 58250 Total Submissions: 262195 Difficulty: Hard
Given a string containing just the characters '(' and ')', find the length of the longest valid (well-formed) parentheses substring.

For "(()", the longest valid parentheses substring is "()", which has length = 2.

Another example is ")()())", where the longest valid parentheses substring is "()()", which has length = 4.
*/

#include <iostream>
#include <stack>
#include <algorithm>
#include "Common.h"

namespace LongestValidParentheses
{
  int longestValidParentheses(string s)
  {
    int n = s.length();

    int maxLen = 0;
    // store length of valid parentheses stopping at i, l[i] = 0 if s[i] == '('
    vector<int> l(n, 0);
    // build array l
    for (auto i = 0; i < n; i++)
    {
      // can't end with '('
      if (s[i] == '(')
      {
        l[i] = 0;
        continue;
      }

      // record whether s[i] finally founds a matching '('
      bool foundMatch = false;
      // search back for the value of l[i] 
      auto j = i - 1;
      while (j >= 0)
      {
        // if there is a valid substring ending at j, skip it
        if (l[j] > 0)
        {
          j -= l[j];
          continue;
        }
        // s[j] and s[i] make a new pair
        if (!foundMatch && s[j] == '(')
        {
          foundMatch = true;
          j--;
          continue;
        }
        // found a un-usable ')' at s[j], no valid substring can be found.
        break;
      }
      // j is the first un-usable parenthes
      if (foundMatch)
      {
        l[i] = i - j;
        maxLen = max(l[i], maxLen);
      }
    }
    return maxLen;
  }

  int Test()
  {
    string str(")()(()())");

    cout << str << ": " << longestValidParentheses(str) << endl;
    return 0;
  }
}
