/*
137. Single Number II
Total Accepted: 74827 Total Submissions: 203388 Difficulty: Medium
Given an array of integers, every element appears three times except for one. Find that single one.

Note:
Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory?
*/

#include <algorithm>
#include <unordered_set>
#include "Common.h"

namespace SingleNumber2
{
  static int Test(vector<int>& nums)
  {
    const int bitSize = sizeof(int) * 8;
    int bitCount[bitSize] = { 0 };

    // every bit show up three times
    for (auto num : nums)
    {
      for (auto i = 0; i < bitSize && num != 0; i++)
      {
        bitCount[i] += num & 0x1;
        num = num >> 1;
      }
    }
    int result = 0;
    for (auto i = bitSize - 1; i >= 0; i--)
    {
      result = result << 1;
      if (bitCount[i] % 3 != 0)
        result = result | 0x1;
    }
    return result;
  }
}