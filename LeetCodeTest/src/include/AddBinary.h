/*
67. Add Binary
Total Accepted: 73155 Total Submissions: 276410 Difficulty: Easy
Given two binary strings, return their sum (also a binary string).

For example,
a = "11"
b = "1"
Return "100".
*/
#include <iostream>
#include <queue>
#include <algorithm>
#include "Common.h"

namespace AddBinary
{
  string addBinary(string a, string b)
  {
    auto& longNum = a.size() > b.size() ? a : b;
    auto& shortNum = a.size() > b.size() ? b : a;
    int m = longNum.size();
    int n = shortNum.size();

    int plus = 0;
    for (int i = m - 1; i >= 0; i--)
    {
      auto result = plus;
      if (longNum[i] == '1') result++;
      auto iShort = i + n - m;
      if (iShort >= 0 && shortNum[iShort] == '1') result++;
      longNum[i] = (result % 2) ? '1' : '0';
      plus = result / 2;
    }
    if (plus)
      longNum.insert(longNum.begin(), '1');

    return longNum;
  }

  string intToBin(unsigned int num)
  {
    string bin;
    while (num)
    {
      bin = ((num & 0x1) ? "1" : "0") + bin;
      num = num >> 1;
    }
    return bin;
  }

  unsigned int stringToInt(string& str)
  {
    unsigned int num = 0;
    for (auto ch : str)
    {
      num = num << 1;
      if (ch == '1')
        num = num | 0x1;
    }
    return num;
  }

  // failed to handle big numbers
  string addBinary1(string a, string b)
  {
    return intToBin(stringToInt(a) + stringToInt(b));
  }
  static string Test()
  {
    string num1 = "11";
    string num2 = "1";
    cout << num1 << " + " << num2 << endl;
    return addBinary(num1, num2);
  }
}