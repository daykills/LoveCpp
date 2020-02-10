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
    // INT_MIN / -1 will be overflow
    if (dividend == INT_MIN && divisor == -1) return INT_MAX;
    // find the sign
    bool negSign = (dividend > 0) ^ (divisor > 0);
    // convert both numbers to long long to avoid overflow (e.g. INT_MIN -> INT_MAX)
    long long lDividend = llabs(dividend);
    long long lDivisor = llabs(divisor);

    long long result = 0;
    long long remainder = lDividend;
    while (true)
    {
      // addtion is 2^N. multiDivisor = addtion * lDivisor.
      long long addtion = 1;
      long long multiDivisor = lDivisor;
      while (multiDivisor < remainder)
      {
        multiDivisor = multiDivisor << 1;
        addtion = addtion << 1;
      }

      // lDivisor * addtion == remainder, result is found
      if (multiDivisor == remainder)
      {
        result += addtion;
        break;
      }
      // multiDivisor is too much, then roll back one to make multiDivisor smaller than remainder
      addtion = addtion >> 1;
      multiDivisor = multiDivisor >> 1;
      // in case no addtion is needed, then result is already reached
      if (addtion == 0) break;
      // update remainder and result
      remainder -= multiDivisor;
      result += addtion;
    }
    result = negSign ? -result : result;
    return (int)result;
  }

  int Test()
  {
    int num1 = 11;
    int num2 = 3;
    cout << num1 << " / " << num2 << endl;
    return divide(num1, num2);
  }
}
