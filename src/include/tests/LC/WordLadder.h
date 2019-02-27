/*
127. Word Ladder My Submissions Question
Total Accepted: 69547 Total Submissions: 355132 Difficulty: Medium
Given two words (beginWord and endWord), and a dictionary's word list, find the length of shortest transformation sequence from beginWord to endWord, such that:

Only one letter can be changed at a time
Each intermediate word must exist in the word list
For example,

Given:
beginWord = "hit"
endWord = "cog"
wordList = ["hot","dot","dog","lot","log"]
As one shortest transformation is "hit" -> "hot" -> "dot" -> "dog" -> "cog",
return its length 5.

Note:
Return 0 if there is no such transformation sequence.
All words have the same length.
All words contain only lowercase alphabetic characters.
*/

#include <iostream>
#include <queue>
#include <memory>
#include <cassert>
#include <algorithm>
#include <vector>
#include "Common.h"

namespace WordLadder
{
  void updateToVisit(string& word, int newDepth, unordered_set<string>& wordList, queue<pair<string, int>>& toVisit)
  {
    // change character one by one to see whether there is a match in wordList
    int wordLen = word.length();
    for (auto i = 0; i < wordLen; i++)
    {
      const auto curChar = word[i];
      for (auto j = 0; j < 26; j++)
      {
        word[i] = j + 'a';
        if (wordList.find(word) != wordList.end())
        {
          toVisit.emplace(word, newDepth);
          // if others can reach word X earlier, we don't need to reach X again as the other path is shorter.
          wordList.erase(word);
        }
      }
      // set the word back to original
      word[i] = curChar;
    }
  }

  int ladderLength2(string beginWord, string endWord, unordered_set<string>& wordList)
  {
    // add endWord, remove beginWord from wordList
    wordList.erase(beginWord);
    wordList.emplace(endWord);

    // bfs search for shortest path
    // queue to keep the word to be visited and its depth
    queue<pair<string, int>> toVisit;
    toVisit.emplace(beginWord, 1);
    while (!toVisit.empty())
    {
      auto curWord = toVisit.front().first;
      auto depth = toVisit.front().second;
      if (curWord == endWord) return depth;
      toVisit.pop();
      updateToVisit(curWord, depth + 1, wordList, toVisit);
    }
    // failed to find a path
    return 0;
  }

  /////////////////////////////////////////
  void addNextWords(string word, unordered_set<string>& wordDict, queue<string>& toVisit)
  {
	  // remove word since if we have reached word here, at the shortest distance, no point to revisit word any more
	  wordDict.erase(word);
	  for (int p = 0; p < (int)word.length(); p++) {
		  char letter = word[p];
		  for (int k = 0; k < 26; k++) {
			  word[p] = 'a' + k;
			  if (wordDict.find(word) != wordDict.end()) {
				  toVisit.push(word);
				  wordDict.erase(word);
			  }
		  }
		  word[p] = letter;
	  }
  }

  int ladderLength(string beginWord, string endWord, unordered_set<string>& wordDict) {
	  wordDict.insert(endWord);
	  queue<string> toVisit;
	  addNextWords(beginWord, wordDict, toVisit);
	  int dist = 2;
	  while (!toVisit.empty()) {
		  int num = toVisit.size();
		  for (int i = 0; i < num; i++) {
			  string word = toVisit.front();
			  toVisit.pop();
			  if (word == endWord) return dist;
			  addNextWords(word, wordDict, toVisit);
		  }
		  dist++;
	  }
	  return 0;
  }
  /////////////////////////////////////////

  void Test()
  {
    string beginWord("hit"), endWord("cog");
    unordered_set<string> wordList
    {
      "hot", "dot", "dog", "lot", "log"
    };

    cout << "begin: " << beginWord << " end: " << endWord << endl;
    cout << "words: ";
    for (auto& word : wordList)
    {
      cout << word << " ";
    }
    cout << endl << "result: " << ladderLength(beginWord, endWord, wordList) << endl;
  }
}