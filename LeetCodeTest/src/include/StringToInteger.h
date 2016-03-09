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
    vector<int> nums;
    bool signDetected = false;
    int sign = 1;
    for (auto ch : str)
    {
      if (ch == ' ')
      {
        if (nums.empty())
          continue;
        else
          break;
      }

      // check for sign
      if (!signDetected && (ch == '-' || ch == '+'))
      {
        sign = (ch == '-') ? - 1 : 1;
        signDetected = true;
        continue;
      }
      
      int val = ch - '0';
      if ((val < 0 || val > 9))
        break;
      
      // stop detecting signs after first valid number
      signDetected = true;
      nums.emplace_back(val);
    }

    // start from high digits
    int n = nums.size();
    if (n == 0) return 0;
    int result = 0;
    for (int i = 0; i < n; i++)
    {
      // check whether it overflows. must check negative first
      if (sign == - 1 && (INT_MIN + nums[i]) / -10 <= result)
        return INT_MIN;
      else if ((INT_MAX - nums[i]) / 10 <= result)
        return INT_MAX * sign;
      else 
      result = result * 10 + nums[i];
    }
    return result * sign;
  }
  
  static int Test()
  {
    return myAtoi("-2147483647");
    //return myAtoi("2147395599");
    //return myAtoi("010");
  }
}