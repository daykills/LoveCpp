/*
38. Count and Say My Submissions Question
Total Accepted: 74286 Total Submissions: 262354 Difficulty: Easy
The count-and-say sequence is the sequence of integers beginning as follows:
1, 11, 21, 1211, 111221, ...

1 is read off as "one 1" or 11.
11 is read off as "two 1s" or 21.
21 is read off as "one 2, then one 1" or 1211.
Given an integer n, generate the nth sequence.
*/

#include <iostream>
#include <stack>
#include <algorithm>
#include "Common.h"

namespace CountAndSay
{
  string countAndSay(int n)
  {
    if (n < 1) return "";
    if (n == 1) return "1";
    string pre = countAndSay(n - 1);
    int len = pre.length();
    string result;
    for (auto i = 0; i < len; i++)
    {
      char cur = pre[i];
      int end = i;
      while (end < len - 1 && pre[end] == pre[end + 1]) end++;
      result.append(to_string(end - i + 1) + cur);
      i = end;
    }
    return result;
  }

  void Test()
  {
    for(int n = 1; n <= 6; n++)
      cout << n << ": " << countAndSay(n) << endl;
  }
}
