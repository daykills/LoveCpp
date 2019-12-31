/*
 3. Longest Substring Without Repeating Characters

 Given a string, find the length of the longest substring without repeating characters.
 
 Example 1:
 
 Input: "abcabcbb"
 Output: 3
 Explanation: The answer is "abc", with the length of 3.
 Example 2:
 
 Input: "bbbbb"
 Output: 1
 Explanation: The answer is "b", with the length of 1.
 Example 3:
 
 Input: "pwwkew"
 Output: 3
 Explanation: The answer is "wke", with the length of 3.
 Note that the answer must be a substring, "pwke" is a subsequence and not a substring.
 */

#include <iostream>
#include <algorithm>
#include <unordered_map>
#include "Common.h"

namespace LongestSubstringWithoutRepeatingCharacters
{
int lengthOfLongestSubstring(string s) {
    auto len = s.size();
    if (len < 2)
        return len;
    auto lo = 0;
    auto maxLen = 1;
    // store the last seen position
    std::unordered_map<char, int> charPos { { s[0], 0 } };
    for (auto i = lo + 1; i < len; i++) {
        // never seen or last seen before lo, update maxLen
        if (charPos.count(s[i]) == 0 || charPos[s[i]] < lo) {
            charPos[s[i]] = i;
            maxLen = max(maxLen, i - lo + 1);
            continue;
        }
        lo = charPos[s[i]] + 1;
        charPos[s[i]] = i;
    }
    return maxLen;
}

void Test()
{
    string s("abcabcbb");
    cout << s << ": " << lengthOfLongestSubstring(s) << endl;
}
}

