/*
50. Pow(x, n) My Submissions Question
Total Accepted: 81105 Total Submissions: 290968 Difficulty: Medium
Implement pow(x, n).
*/
#include <iostream>
#include <queue>
#include <algorithm>
#include "Common.h"

namespace Pow
{
    double myPow(double x, int n) {
        if (n < 0) {
            // handle INT_MIN
            return 1 / (myPow(x, -1 * (n + 1)) * x);
        }
        if (n == 1) return x;
        if (n == 0) return 1;
        
        assert(n > 1);
        
        auto half = n / 2;
        auto res = n % 2;
        auto halfPow = myPow(x, half);
        return myPow(x, res) * halfPow * halfPow;
    }
    static double Test()
    {
        return myPow(-1, 2222);
    }
}
