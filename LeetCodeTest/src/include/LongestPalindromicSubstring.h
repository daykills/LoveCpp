/*
5. Longest Palindromic Substring

Given a string S, find the longest palindromic substring in S.

You may assume that the maximum length of S is 1000, and there exists one unique longest palindromic substring.

*/
#include <string>
#include <iostream>
#include <algorithm>
#include "Common.h"

namespace LongestPalindromicSubstring
{
  string Test(const string& s) {
    int len = s.length();    
    if (len == 0) return s;

    // d[i][j] represents whether s[j : i] is palindromic
    //vector<vector<bool>> d(len, vector<bool>(len, false));
    bool d[1000][1000] = { false };
    // diagonal line is always true (single char)
    for (int i = 0; i < len; i++)
      d[i][i] = true;
    
    // set d[0][0] as initial
    int maxLen = 1;
    int leftOfMaxSubstring = 0;

    for (int i = 1; i < len; i++)
    {
      for (int j = 0; j < i; j++)
      {
        // when j == i - 1, we only need i and j equal.
        if (s[i] == s[j] && (j == i - 1 || d[i - 1][j + 1]))
        {
          d[i][j] = true;
          int lenTemp = i - j + 1;
          if (lenTemp > maxLen)
          {
            leftOfMaxSubstring = j;
            maxLen = lenTemp;
          }
        }
      }
    }
    return s.substr(leftOfMaxSubstring, maxLen);
  }

  // ordinary method: loop each element, start searching for both sides of that element
  string Test1(const string& s) {
    int len = s.length();
    int maxLen = 0;
    int leftOfMaxSubstring = 0;
    for (int i = 0; i < len; i++)
    {
      // find left and right, skip the same chars between
      char centerChar = s[i];
      int left = i;
      //// better skip this step as it's not necessary
      // while (left - 1 >= 0 && s[left - 1] == centerChar)
      // left--;

      int right = i;
      while (right + 1 < len && s[right + 1] == centerChar) right++;

      int lenTemp = right - left + 1;
      int step = 1;
      while (left - step >= 0 && right + step < len && s[left - step] == s[right + step])
      {
        step++;        
      }

      lenTemp += 2 * (step - 1);

      if (lenTemp > maxLen)
      {
        maxLen = lenTemp;
        leftOfMaxSubstring = left - step + 1;
      }
    }
    return s.substr(leftOfMaxSubstring, maxLen);
  }

  static int Test()
  {
    string str("abbaccacccb");
    auto result = Test(str);
    cout << str << ": " << result << endl;
    return 0;
  }
}