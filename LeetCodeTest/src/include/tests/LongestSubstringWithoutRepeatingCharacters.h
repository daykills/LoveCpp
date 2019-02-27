/*
3. Longest Substring Without Repeating Characters My Submissions Question
Total Accepted: 126029 Total Submissions: 587741 Difficulty: Medium
Given a string, find the length of the longest substring without repeating characters.
For example, the longest substring without repeating letters for "abcabcbb" is "abc", which the length is 3.
For "bbbbb" the longest substring is "b", with the length of 1.
*/

#include <iostream>
#include <algorithm>
#include <unordered_map>
#include "Common.h"

namespace LongestSubstringWithoutRepeatingCharacters
{
  int lengthOfLongestSubstring(string s)
  {
    int n = s.length();
    if (n <= 1) return n;

    // map for a letter's last appearance, key is the letter, value is the last seen position
    unordered_map<char, int> lastSeen;
    // max length
    int maxLen = 0;
    // record the start of the sub string
    int startSubStr = 0;
    for (int i = 0; i < n; i++)
    {
      // check whether the current char is seen
      auto got = lastSeen.find(s[i]);
      if (got == lastSeen.end())
      {
        // current char is new, add to the map
        lastSeen.emplace(s[i], i);
        continue;
      }

      // if the repeated char is after the start of sub string
      if (got->second >= startSubStr)
      {
        maxLen = max(maxLen, i - startSubStr);
        // move the start index to the next of the repeated letter
        startSubStr = got->second + 1;
      }
      // update the last seen position
      got->second = i;
    }
    // check the last sub string
    maxLen = max(maxLen, n - startSubStr);
    return maxLen;
  }

  void Test()
  {
    string s("abba");
    cout << s << ": " << lengthOfLongestSubstring(s) << endl;
  }
}