/*
20. Valid Parentheses My Submissions Question
Total Accepted: 92601 Total Submissions: 324797 Difficulty: Easy
Given a string containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.

The brackets must close in the correct order, "()" and "()[]{}" are all valid but "(]" and "([)]" are not.
*/

#include <iostream>
#include <stack>
#include <algorithm>
#include "Common.h"

namespace ValidParentheses
{
  bool isValid(string& s)
  {
    unordered_map<char, char> mapping
    {
      { '(', ')' },
      { '[', ']' },
      { '{', '}' }
    };
    std::stack<char> history;
    for (auto ch : s)
    {
      auto it = mapping.find(ch);
      // if ch is a key
      if (it != mapping.end())
      {
        history.push(ch);
        continue;
      }
      // ch must match with stack top
      if (history.empty() || mapping[history.top()] != ch) return false;
      history.pop();
    }
    return history.empty();
  }

  int Test()
  {
    string str("()[{}()]{}ab");

    cout << str << ": " << isValid(str) << endl;
    return 0;
  }
}
