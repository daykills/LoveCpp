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
        int climbStairs(int n) {
            if (n <= 2) return n;
            // for how many distinct ways to reach i - 1, i - 2
            // init for step 1 and 2
            auto iMinus2 = 1;
            auto iMinus1 = 2;
            for (auto i = 2; i < n; i++) {
                auto steps = iMinus2 + iMinus1;
                iMinus2 = iMinus1;
                iMinus1 = steps;
            }
            return iMinus1;
        }
    }
}
