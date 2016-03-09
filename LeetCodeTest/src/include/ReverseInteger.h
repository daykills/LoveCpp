/*
7. Reverse Integer My Submissions Question
Total Accepted: 121837 Total Submissions: 517403 Difficulty: Easy
Reverse digits of an integer.

Example1: x = 123, return 321
Example2: x = -123, return -321

Have you thought about this?
Here are some good questions to ask before coding. Bonus points for you if you have already thought through this!

If the integer's last digit is 0, what should the output be? ie, cases such as 10, 100.

Did you notice that the reversed integer might overflow? Assume the input is a 32-bit integer, then the reverse of 1000000003 overflows. How should you handle such cases?

For the purpose of this problem, assume that your function returns 0 when the reversed integer overflows.

Update (2014-11-10):
Test cases had been added to test the overflow behavior.
*/
#include <iostream>
#include <queue>
#include <algorithm>
#include "Common.h"

namespace ReverseInteger
{
  int reverse(int x)
  {
    const int base = 10;
    int reverse = 0;
    while (x)
    {
      if (reverse > INT_MAX / base || reverse < INT_MIN / base)
        return 0;
      reverse = reverse * base + x % base;
      x = x / base;      
    }
    return reverse;
  }
  static int Test()
  {
    return reverse(1534236469);
  }
}