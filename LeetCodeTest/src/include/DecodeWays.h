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
  static int Test(const string& s)
  {
    if (s.empty()) return 0;

    int n = s.length();
    
    if (s[0] == '0') return 0;

    // ways[i] means with the first i numbers, how many ways of decoding
    // i started with 2
    int ways = 1;
    int waysIMinus2 = 1;    // i - 2
    int waysIMinus1 = 1; // i - 1
    for (int i = 2; i <= n; i++)
    {
      const auto& lastNumber = s[i - 2];
      const auto& curNumber = s[i - 1];

      if (lastNumber == '1')
      {
        if (curNumber == '0')
        {
          ways = waysIMinus2;
        }
        else
        {
          ways = waysIMinus1 + waysIMinus2;
        }
      }
      else if (lastNumber == '2')
      {
        if (curNumber == '0')
        {
          ways = waysIMinus2;
        }
        else if (curNumber <= '6')
        {
          ways = waysIMinus1 + waysIMinus2;
        }
      }
      else
      {
        // invalid cases like 100, 30
        if (curNumber == '0')
          return 0;
        ways = waysIMinus1;
      }
      waysIMinus2 = waysIMinus1;
      waysIMinus1 = ways;      
    }
    return ways;
  }
}