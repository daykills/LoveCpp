/*
70. Climbing Stairs
You are climbing a stair case. It takes n steps to reach to the top.
Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?
*/

#include <string>
#include <iostream>
#include "Common.h"

namespace ClimbingStairs
{
  static int Test(int n)
  {
    if (n == 0) return 0;
    else if (n == 1) return 1;
    else if (n == 2) return 2;
    
    // ways_i is how many ways when we have i steps in total
    // start with i = 3
    int waysIMinus1 = 2;  
    int waysIMinus2 = 1;
    int totalWays = 3;
    for (int i = 3; i <= n; i++)
    {
      totalWays = waysIMinus1 + waysIMinus2;
      waysIMinus2 = waysIMinus1;
      waysIMinus1 = totalWays;
    }
    return totalWays;
  }
}