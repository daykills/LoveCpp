/*
76. Minimum Window Substring My Submissions Question
Total Accepted: 55923 Total Submissions: 267490 Difficulty: Hard
Given a string S and a string T, find the minimum window in S which will contain all the characters in T in complexity O(n).

For example,
S = "ADOBECODEBANC"
T = "ABC"
Minimum window is "BANC".

Note:
If there is no such window in S that covers all characters in T, return the empty string "".

If there are multiple such windows, you are guaranteed that there will always be only one unique minimum window in S.
*/
#include <string>
#include <iostream>
#include "Common.h"

namespace MinimumWindowSubstring
{
class Solution {
public:
    string minWindow(string s, string t) {
        // required chars start with positive
        // non-required chars start with 0
        vector<int> charCount(128, 0);
        for (auto c : t)
            charCount[c]++;
        
        auto nRequiredChar = 0;
        auto minLen = INT_MAX;
        string substr;
        auto lo = 0;
        for (auto i = 0; i < s.size(); i++) {
            charCount[s[i]]--;
            if (charCount[s[i]] >= 0) nRequiredChar++;
            // we got all required characters, so we can move lo to right
            while (nRequiredChar == t.size()) {
                // when moving a required char out
                if (charCount[s[lo]]++ == 0) {
                    // substr from lo to i
                    auto len = i - lo + 1;
                    if (len < minLen) {
                        substr = s.substr(lo, len);
                        minLen = len;
                    }
                    nRequiredChar--;
                }
                lo++;
            }
        }
        return substr;
    }
};

static void Test()
{
    string s("ADOBECODEBANC");
    string t("COO");
    Solution solu;
    cout << solu.minWindow(s, t) << endl;    // should be 8
}

}
