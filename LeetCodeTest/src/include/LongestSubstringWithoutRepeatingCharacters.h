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
    // keep the index of last char occurance
    unordered_map<char, int> charHist;
    // start is last repeated char
    int start = -1;
    int maxLen = 0;
    for (int i = 0; i < (int)s.size(); i++)
    {
      char ch = s[i];
      auto iter = charHist.find(ch);
      if (iter != charHist.end())
      {
        start = max(start, iter->second);
      }
      charHist[ch] = i;
      maxLen = max(maxLen, i - start);
    }
    return maxLen;
  }

  void Test()
  {
    string s("abba");
    cout << s << ": " << lengthOfLongestSubstring(s) << endl;
  }
}