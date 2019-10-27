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
int singleNumberOld(vector<int>& nums) {
    unordered_set<int> single;
    unordered_set<int> dups;
    for (auto num : nums) {
        if (single.count(num)) {
            dups.emplace(num);
            single.erase(num);
        } else if (dups.count(num) == 0) {
            single.emplace(num);
        }
    }
    assert(single.size() == 1);
    return *single.begin();
}

int singleNumber(vector<int>& nums) {
    // store counts of each bits.
    // remove those dups with %3.
    const int kIntBits = sizeof(int) * 8;
    // bits[0] is the low bit
    vector<int> bits(kIntBits, 0);
    for (auto num : nums) {
        for (auto bit = 0; bit < kIntBits; bit++) {
            bits[bit] += num & 1;
            num = num >> 1;
        }
    }
    int ans = 0;
    for (auto bit = 0; bit < kIntBits; bit++) {
        auto deduped = bits[bit] % 3;
        if (deduped)
            ans += 1 << bit;
    }
    return ans;
}

int singleNumberOldOld(vector<int>& nums)
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

void Test() {
    vector<int> nums = { 2,2,3,2 };
    cout << singleNumber(nums) << endl;
}
}
