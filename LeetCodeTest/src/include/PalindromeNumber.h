/*
9. Palindrome Number My Submissions Question
Total Accepted: 105521 Total Submissions: 343701 Difficulty: Easy
Determine whether an integer is a palindrome. Do this without extra space.

click to show spoilers.

Some hints:
Could negative integers be palindromes? (ie, -1)

If you are thinking of converting the integer to string, note the restriction of using extra space.

You could also try reversing an integer. However, if you have solved the problem "Reverse Integer", you know that the reversed integer might overflow. How would you handle such case?

There is a more generic way of solving this problem.
*/
#include <iostream>
#include <queue>
#include <algorithm>
#include "Common.h"

namespace PalindromeNumber
{
  bool isPalindrome(int x)
  {
    // Palindrome by definition is defined as something that looks exactly identical read from either side. Negative numbers are all non-palindromes because of the negative sign.
    if (x < 0) return false;
    int copyX = x;
    int reverse = 0;
    int base = 10;
    while (x)
    {
      // rever takes the last digist
      reverse = reverse * base + x % base;
      x = x / base;
    }
    return (reverse == copyX);
  }
  static bool Test()
  {
    return isPalindrome(1321);
  }
}