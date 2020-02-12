/*
 248. Strobogrammatic Number III

 A strobogrammatic number is a number that looks the same when rotated 180 degrees (looked at upside down).
 
 Write a function to count the total strobogrammatic numbers that exist in the range of low <= num <= high.
 
 Example:
 
 Input: low = "50", high = "100"
 Output: 3
 Explanation: 69, 88, and 96 are three strobogrammatic numbers.
 Note:
 Because the range might be a large number, the low and high numbers are represented as string.
 */

#include <iostream>
#include <list>
#include "Common.h"

namespace strobogrammaticInRange
{
class Solution {
public:
    bool stringNotGreater(const string& str1, const string& str2) {
        if (str1.size() != str2.size())
            return str1.size() < str2.size();
        for (auto i = 0; i < str1.size(); i++) {
            if (str1[i] != str2[i])
                return str1[i] < str2[i];
        }
        return true;
    }
    // returns all strobogrammatic numbers at len, and eligibleCount
    void dfs(const string& low, const string& high, const vector<pair<char, char>>& nums, const string& mid, int& eligibleCount) {
        // base condition
        if (mid.size() > high.size())
            return;
        if (stringNotGreater(mid, high) && stringNotGreater(low, mid)) {
            if (mid == "0" || (!mid.empty() && mid[0] != '0')) {
                eligibleCount++;
                std::cout << mid << std::endl;
            }
        }
        for (auto& num : nums) {
            dfs(low, high, nums, string(1, num.first) + mid + string(1, num.second), eligibleCount);
        }
    }
    int strobogrammaticInRange(string low, string high) {
        vector<pair<char, char>> nums = { { '6', '9' }, { '9', '6' }, { '8', '8' }, { '1', '1' }, { '0', '0' } };
        int eligibleCount = 0;
        vector<string> mids = { "", "0", "8", "1" };
        for (auto& mid : mids)
            dfs(low, high, nums, mid, eligibleCount);
        return eligibleCount;
    }
};

static void Test()
{
    string low = "34675";
    string high = "378254";
    Solution solution;
    std::cout << solution.strobogrammaticInRange(low, high) << std::endl;
}
}
