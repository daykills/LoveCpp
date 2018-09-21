/*
70. Climbing Stairs
You are climbing a stair case. It takes n steps to reach to the top.
Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?
*/

#include <string>
#include <iostream>
#include "Common.h"

namespace DecodeWays
{
  int numDecodings(string s)
  {
    int n = s.length();
    if (n == 0) return n;
    // if first letter is 0, return 0 as not valid for decoding
    if (s[0] == '0') return 0;

    // 1 way to decode when there are first 0 letters
    int prePre = 1;
    // for first one letter, 1 way to decode
    int pre = 1;
    // dynamic programming, use previous two results
    // ways[i] = ways[i - 1] + ways[i - 2] if last two letters are smaller than 26
    int result = pre;
    for (auto i = 2; i <= n; i++)
    {
      // now handle ith number. i = 2 ~ n.

      // check whether last two letters are smaller than 26
      int preNum = s[i - 2] - '0';
      int curNum = s[i - 1] - '0';
      int number = preNum * 10 + curNum;

      // if it's '00', cannot decode
      if (number == 0) return 0;

      // ways[i] is at least ways[i - 1] if curNum is not 0
      result = (curNum == 0) ? 0 : pre;

      // ways[i] = ways[i - 1] + ways[i - 2] if number is valid (10 ~ 26)
      if (number <= 26 && number >= 10) result += prePre;

      prePre = pre;
      pre = result;
    }
    return result;
  }

  static void Test()
  {
    string input("12034");
    cout << input << " can have: " << numDecodings(input) << endl;
  }
}
