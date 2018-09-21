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

namespace ValidPalindrome
{
  bool isPalindrome(string s)
  {
    int lo = 0, hi = s.length() - 1;

    while (lo < hi)
    {
      while (lo < hi && !isalnum(s[lo])) lo++;
      while (lo < hi && !isalnum(s[hi])) hi--;
      // no alphanumeric found
      if (lo == hi) break;
      if (toupper(s[lo]) == toupper(s[hi]))
      {
        lo++, hi--;
      }
      else
      {
        return false;
      }
    }
    return true;
  }

  int Test()
  {
    string str("a ba");

    cout << str << ": " << isPalindrome(str) << endl;
    return 0;
  }
}
