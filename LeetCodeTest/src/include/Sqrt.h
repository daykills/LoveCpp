/*
69. Sqrt(x) My Submissions Question
Total Accepted: 83360 Total Submissions: 337418 Difficulty: Medium
Implement int sqrt(int x).

Compute and return the square root of x.
*/
#include <iostream>
#include <queue>
#include <algorithm>
#include "Common.h"

namespace Sqrt
{
  int mySqrt(int x)
  {
    if (x <= 1) return x;
    
    int lo = 0;
    int hi = x / 2;
    while (lo < hi)
    {
      int mid = (lo + hi) / 2;
      long long sq = (long long)mid * (long long)mid;
      if (sq == x) return mid;
      else if (sq < x)
      {
        if (((long long)mid + 1)*((long long)mid + 1) > x) //(mid+1)*(mid+1) may over int
          return mid;
        lo = mid + 1;
      }
      else
      {
        hi = mid;        
      }
    }
    return (lo * lo == x) ? lo : -1;
  }
  static int Test()
  {
    return mySqrt(2147395599);
  }
}