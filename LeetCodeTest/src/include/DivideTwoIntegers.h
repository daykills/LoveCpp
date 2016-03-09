/*
29. Divide Two Integers
Total Accepted: 59251 Total Submissions: 384361 Difficulty: Medium
Divide two integers without using multiplication, division and mod operator.

If it is overflow, return MAX_INT.
*/
#include <iostream>
#include <queue>
#include <algorithm>
#include "Common.h"

namespace DivideTwoIntegers
{
  int divide(int dividend, int divisor)
  {
    if (divisor == 0) return INT_MAX;
    if (dividend == 0) return 0;
    int sign = (dividend > 0) ^ (divisor > 0) ? 1 : -1;
    auto residual = llabs(dividend);
    auto dvs = llabs(divisor);
    int result = 0;
    // residul = old residul - dvs multiplied by 2's power
    while (residual >= dvs)
    {
      long long tempDvs = dvs;
      int multiple = 1;
      // as long as we can do another multiplication
      while (residual >= (tempDvs << 1))
      {
        tempDvs <<= 1;
        multiple <<= 1;
      }
      residual -= tempDvs;
      result += multiple;
    }
    return sign ? result : -result;
  }
  int Test()
  {
    int num1 = 2147483647;
    int num2 = 3;
    cout << num1 << " / " << num2 << endl;
    return divide(num1, num2);
  }
}
