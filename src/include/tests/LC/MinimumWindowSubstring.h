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
	string minWindow(string s, string t)
	{
        // charCount stores counts of each character in the window
        // for required characters, count range is [expected, 0], 0 means window has enough such charaters
        // for un-required characters, count range is [-INT, 0].
        std::vector<int> charCount(128, 0);
        for (auto c : t) charCount[c]++;
        
        auto requiredCharacterCountInWindow = 0;
        auto minLen = INT_MAX;
        string ans = "";
        auto left = 0;
        for (auto i = 0; i < s.size(); i++) {
            // one more required char is included
            if (--charCount[s[i]] >= 0) requiredCharacterCountInWindow++;
            // if we have all characters in window, slide left side of the window
            while (requiredCharacterCountInWindow == t.size()) {
                // required char count is zero in window 0
                // non-required is negative
                if (charCount[s[left]]++ == 0) {
                    auto len = i - left + 1;
                    if (len < minLen) {
                        ans = s.substr(left, len);
                        minLen = len;
                    }
                    left++;
                    requiredCharacterCountInWindow--;
                    break;
                }
                left++;
            }
        }
        return ans;
	}

	static void Test()
	{
		string s("ADOBECODEBANC");
		string t("COO");
		cout << minWindow(s, t) << endl;	// should be 8
	}
}
