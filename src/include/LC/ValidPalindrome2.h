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

namespace ValidPalindrome2
{
  bool isPalindrome(string s)
  {
      int lo = 0;
      int hi = s.size() - 1;
      while (lo < hi) {
          cout << s[lo] << ", " << s[hi] << std::endl;
          if (s[lo] == s[hi]) {
              lo++;
              hi--;
              continue;
          }
          
          if (s[lo + 1] == s[hi]) {
              auto loTemp = lo + 2;
              auto hiTemp = hi - 1;
              while (loTemp < hiTemp) { if (s[loTemp++] != s[hiTemp--]) break; }
              if (loTemp >= hiTemp) return true;
          }
          if (s[lo] == s[hi - 1]) {
              auto loTemp = lo + 1;
              auto hiTemp = hi - 2;
              while (loTemp < hiTemp) { if (s[loTemp++] != s[hiTemp--]) break; }
              if (loTemp >= hiTemp) return true;
          }
          return false;
      }
      return true;
  }

  int Test()
  {
    string str("aguokepatgbnvfqmgmlcupuufxoohdfpgjdmysgvhmvffcnqxjjxqncffvmhvgsymdjgpfdhooxfuupuculmgmqfvnbgtapekouga");
    cout << str << std::endl << isPalindrome(str) << endl;
    return 0;
  }
}
