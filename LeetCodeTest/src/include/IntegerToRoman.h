/*
12. Integer to Roman My Submissions Question
Total Accepted: 55367 Total Submissions: 148452 Difficulty: Medium
Given an integer, convert it to a roman numeral.

Input is guaranteed to be within the range from 1 to 3999.
*/
#include <iostream>
#include <queue>
#include <algorithm>
#include "Common.h"

namespace IntegerToRoman
{
  static string intToRoman(int num)
  {
    string vs[] = { "I", "IV", "V", "IX", "X", "XL", "L", "XC", "C", "CD", "D", "CM", "M" };
    int ks[] = { 1, 4, 5, 9, 10, 40, 50, 90, 100, 400, 500, 900, 1000 };
    int len = sizeof(ks) / sizeof(int);

    int index = len - 1;
    int value = num;
    string result = "";
    while (index >= 0 && value != 0)
    {
      if (value >= ks[index])
        result += vs[index], value -= ks[index];
      else
        index--;
    }
    return result;
  }

  static string Test()
  {
    int num = 35;
    cout << num << endl;

    return intToRoman(num);
  }
}