/*
49. Group Anagrams My Submissions Question
Total Accepted: 68651 Total Submissions: 255445 Difficulty: Medium
Given an array of strings, group anagrams together.

For example, given: ["eat", "tea", "tan", "ate", "nat", "bat"],
Return:

[
["ate", "eat","tea"],
["nat","tan"],
["bat"]
]
Note:
For the return value, each inner list's elements must follow the lexicographic order.
All inputs will be in lower-case.
*/

#include <iostream>
#include <stack>
#include <algorithm>
#include "Common.h"

namespace GroupAnagrams
{
  vector<vector<string>> groupAnagrams(vector<string>& strs)
  {
    // a hashtable for the result. key is the sorted string, value is the anagrams in order
    unordered_map<string, vector<string>> mapping;
    // group them with the key being the sorted string
    for (const auto& str : strs)
    {
      string sortedStr = str;
      sort(sortedStr.begin(), sortedStr.end());
      mapping[sortedStr].emplace_back(str);
    }
    vector<vector<string>> result;
    // sort strings, and add them to result
    for (auto& pair : mapping)
    {
      vector<string> anagram = pair.second;
      sort(anagram.begin(), anagram.end());
      result.emplace_back(std::move(anagram));
    }
    return std::move(result);
  }

  int Test()
  {
    vector<string> strs{ "aacdf", "aacd", "aac", "aacdfg" };
    for (auto& str : strs)
    {
      cout << str << " ";
    }

    cout << endl;

    auto result = groupAnagrams(strs);
    for (auto& group : result)
    {
      for (auto& str : group)
        cout << str << " ";
      cout << endl;
    }
    return 0;
  }
}
