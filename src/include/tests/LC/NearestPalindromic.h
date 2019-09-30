/*
 523. Continuous Subarray Sum
 
 Given a list of non-negative numbers and a target integer k, write a function to check if the array has a continuous subarray of size at least 2 that sums up to a multiple of k, that is, sums up to n*k where n is also an integer.
 
 Example 1:
 
 Input: [23, 2, 4, 6, 7],  k=6
 Output: True
 Explanation: Because [2, 4] is a continuous subarray of size 2 and sums up to 6.
 Example 2:
 
 Input: [23, 2, 6, 4, 7],  k=6
 Output: True
 Explanation: Because [23, 2, 6, 4, 7] is an continuous subarray of size 5 and sums up to 42.
 
 Note:
 
 The length of the array won't exceed 10,000.
 You may assume the sum of all the numbers is in the range of a signed 32-bit integer.
*/

#include <iostream>
#include <stack>
#include <algorithm>
#include "Common.h"

namespace NearestPalindromic
{
string nearestPalindromic(string n) {
    auto len = n.size();
    set<long> cands;
    // min and max candidates are: 9...9 and 10...01
    cands.emplace(pow(10, len - 1) - 1);
    cands.emplace(pow(10, len) + 1);
    // the rest possible candidates are made by taking first half and flipping & cacatenating.
    // with middle digit modified by at most 1
    // for example, 123 -> 121, 111, 131
    long half = stol(n.substr(0, (len + 1) / 2));
    for (long delta = -1; delta <= 1; delta++) {
        // modify last digit
        auto newHalf = to_string(half + delta);
        // flip it
        auto newNum = newHalf + string(newHalf.rbegin() + (len & 1), newHalf.rend());
        cands.emplace(stol(newNum));
    }
    // remove itself
    long num = stol(n);
    cands.erase(num);
    long minVal = *cands.begin();
    long minDiff = abs(num - minVal);
    for (long cand : cands) {
        auto diff = abs(cand - num);
        if (diff < minDiff) {
            minVal = cand;
            minDiff = diff;
        } else if (diff == minDiff) {
            minVal = min(minVal, cand);
        }
    }
    return to_string(minVal);
}

int Test()
{
    cout << nearestPalindromic("123") << endl;
return 0;
}
}
