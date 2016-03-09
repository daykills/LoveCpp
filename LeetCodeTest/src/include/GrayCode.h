/*
89. Gray Code
Total Accepted: 53566 Total Submissions: 151726 Difficulty: Medium
The gray code is a binary numeral system where two successive values differ in only one bit.

Given a non-negative integer n representing the total number of bits in the code, print the sequence of gray code. A gray code sequence must begin with 0.

For example, given n = 2, return [0,1,3,2]. Its gray code sequence is:

00 - 0
01 - 1
11 - 3
10 - 2
Note:
For a given n, a gray code sequence is not uniquely defined.

For example, [0,2,3,1] is also a valid gray code sequence according to the above definition.

For now, the judge is able to judge based on one instance of gray code sequence. Sorry about that.
*/

#include <iostream>
#include <queue>
#include <algorithm>
#include "Common.h"

namespace GrayCode
{
  static vector<int> grayCode(int n)
  {
    vector<int> result;
    for (int i = 0; i < 1 << n; i++)
      result.emplace_back(i ^ (i >> 1));
    return result;
  }

  ///////////////////////////////////////////////////////////////////////
  /* 注意观察，n每增加1，即是在n-1的结果之上，最高位加1，并按照n-1的逆序。
  n = 1
  0
  1
  n=2
  0 0
  0 1
  ---
  1 1
  1 0
  n=3
  0 0 0
  0 0 1
  0 1 1
  0 1 0
  ------
  1 1 0
  1 1 1
  1 0 1
  1 0 0
  */
  static vector<int> grayCode1(int n)
  {
    if (n == 0) return vector<int>(1, 0);
    vector<int> result(1 << n);
    // initialize for n = 1
    result[0] = 0;
    result[1] = 1;
    int len = 2;
    for (int i = 1; i < n; i++)
    {
      int iStart = len;
      len = len << 1;
      // numbers before iStart are already good
      int addition = 1 << i;
      // now copy first half in reverse order, and set the highest bit as 1
      for (int j = iStart; j < len; j++)
      {
        result[j] = result[len - j - 1] | addition;
      }
    }
    return result;
  }
  static int Test()
  {
    auto result = grayCode(2);
    for (auto num : result)
    {
      cout << num << " ";
    }
    cout << endl;
    return 0;
  }
}