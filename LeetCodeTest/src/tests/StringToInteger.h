/*
8. String to Integer (atoi) My Submissions Question
Total Accepted: 87045 Total Submissions: 655112 Difficulty: Easy
Implement atoi to convert a string to an integer.

Hint: Carefully consider all possible input cases. If you want a challenge, please do not see below and ask yourself what are the possible input cases.

Notes: It is intended for this problem to be specified vaguely (ie, no given input specs). You are responsible to gather all the input requirements up front.

Update (2015-02-10):
The signature of the C++ function had been updated. If you still see your function signature accepts a const char * argument, please click the reload button  to reset your code definition.

spoilers alert...

Requirements for atoi:
The function first discards as many whitespace characters as necessary until the first non-whitespace character is found. Then, starting from this character, takes an optional initial plus or minus sign followed by as many numerical digits as possible, and interprets them as a numerical value.

The string can contain additional characters after those that form the integral number, which are ignored and have no effect on the behavior of this function.

If the first sequence of non-whitespace characters in str is not a valid integral number, or if no such sequence exists because either str is empty or it contains only whitespace characters, no conversion is performed.

If no valid conversion could be performed, a zero value is returned. If the correct value is out of the range of representable values, INT_MAX (2147483647) or INT_MIN (-2147483648) is returned.
*/

#include <iostream>
#include <queue>
#include <algorithm>
#include "Common.h"

namespace StringToInteger
{
  int myAtoi(string str)
  {
    long long result = 0;
    int sign = 1;
    bool signFound = false;
    for (auto ch : str)
    {
      if (ch == ' ')
      {
        if (signFound) return (int)result;
        else continue;
      }

      // to detect the sign
      if (ch == '-' || ch == '+')
      {
        // duplicate sign detected
        if (signFound) return 0;
        sign = (ch == '+') ? 1 : -1;
        signFound = true;
        continue;
      }
      // check whether it's a number, or number started with 0
      int num = (int)(ch - '0');
      if (num < 0 || num > 9)
      {
        return (int)result;
      }

      // set signFound whenever a number is detected
      signFound = true;

      // calculate result
      result = result * 10 + num * sign;
      // check overflow
      if (sign == 1 && result > INT_MAX)
      {
        return INT_MAX;
      }
      else if (sign == -1 && result < INT_MIN)
      {
        return INT_MIN;
      }
    }
    return (int)result;
  }


  
  static void Test()
  {
    cout << "result is " << myAtoi("   +0 123") << endl;
  }
}