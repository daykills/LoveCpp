/*
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
        auto start = 0;
        auto maxLen = 1;
        // store the last seen position
        std::unordered_map<char, int> lastPosMap { { s[0], 0 } };
        for (auto end = start + 1; end < len; end++) {
            auto it = lastPosMap.find(s[end]);
            if (it == lastPosMap.end()) {
                lastPosMap[s[end]] = end;
                continue;
            }
            // if a char is seen before, update maxLen
            auto lastPos = it->second;
            // only consider if lastPos is within the substr
            if (lastPos >= start) {
                maxLen = max(maxLen, end - start);
                start = lastPos + 1;
            }
            lastPosMap[s[end]] = end;
        }
        maxLen = max(maxLen, (int)len - start);
        return maxLen;
    }
    
    void Test()
    {
        string s("abcbca");
        cout << s << ": " << lengthOfLongestSubstring(s) << endl;
    }
}

