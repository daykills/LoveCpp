/*
30. Substring with Concatenation of All Words My Submissions Question
Total Accepted: 50952 Total Submissions: 247852 Difficulty: Hard
You are given a string, s, and a list of words, words, that are all of the same length. Find all starting indices of substring(s) in s that is a concatenation of each word in words exactly once and without any intervening characters.

For example, given:
s: "barfoothefoobarman"
words: ["foo", "bar"]

You should return the indices: [0,9].
(order does not matter).
*/

#include <iostream>
#include <stack>
#include <algorithm>
#include "Common.h"

namespace SubstringWithConcatenationOfAllWords
{
  vector<int> findSubstring(string s, vector<string>& words)
  {
    vector<int> result;
    int n = words.size();
    if (n == 0) return result;

    // create a hash set for words, key is the string, value is count
    unordered_map<string, int> wordSet;
    for (auto i = 0; i < n; i++)
    {
      wordSet[words[i]]++;
    }

    int length = s.length();
    int wordLen = words[0].length();
    // search first 
    for (auto i = 0; i < length - wordLen * n + 1; i++)
    {
      unordered_map<string, int> searchedWordSet;
      int validWordCount = 0;
      // search for each word
      for (auto j = 0; j < n; j++)
      {
        auto substr = s.substr(i + j * wordLen, wordLen);
        auto find = wordSet.find(substr);
        // substr is not in words
        if (find == wordSet.end()) break;
        // too many substr were found
        if (searchedWordSet[substr] >= find->second) break;
        // increase count for substr
        searchedWordSet[substr]++;
        validWordCount++;
      }
      // if all n words are found, add the result
      if (validWordCount == n) result.push_back(i);
    }
    return result;
  }

  int Test()
  {
    string s("ababcdbbcacbba");
    vector<string> words{ "a", "b", "c", "b" };
    for (auto& str : words)
    {
      cout << str << " ";
    }

    cout << endl;

    auto result = findSubstring(s, words);
    for (auto& i : result)
    {
      cout << i << " ";      
    }
    cout << endl;
    return 0;
  }
}
