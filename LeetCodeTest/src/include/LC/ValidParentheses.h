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
      { '{', '}' }, { '[', ']' }, { '(', ')' }
    };

    if (s.empty()) return true;
    // must have even number of chars
    if (s.length() & 0x1) return false;
    stack<char> stack;
    for (auto ch : s)
    {
      // char is one of the keys "{(["
      if (mapping.find(ch) != mapping.end())
      {
        stack.emplace(ch);
        continue;
      }
      // ch must be one of "}])", then stack top must be key
      if (stack.empty()) return false;
      
      auto iter = mapping.find(stack.top());
      if (iter->second != ch) return false;
      stack.pop();
    }
    return stack.empty();
  }

  int Test()
  {
    string str("()[{}()]{}ab");

    cout << str << ": " << isValid(str) << endl;
    return 0;
  }
}
