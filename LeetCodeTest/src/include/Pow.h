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
  double myPow(double x, int n)
  {
    if (x == 0) return 0;
    if (n == 0 || x == 1.0) return 1;
    if (x == -1.0) return (n & 0x1) ? -1 : 1;
    if (n < 0) return 1 / myPow(x, -n);    
    
    double half = myPow(x, n >> 1);
    if (n & 0x1)
    {
      return half * half * x;
    }
    else
    {
      return half * half;
    }
  }
  static double Test()
  {
    return myPow(-1, 2222);
  }
}