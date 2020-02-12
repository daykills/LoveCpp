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
    // create a connection map
    std::vector<std::vector<int>> createConnectionMap(vector<string>& wordList) {
        std::vector<std::vector<int>> connection(wordList.size());
        for (auto i = 0; i < wordList.size(); i++) {
            auto& map = connection[i];
            auto& str1 = wordList[i];
            for (auto j = i + 1; j < wordList.size(); j++) {
                auto& str2 = wordList[j];
                auto diff = 0;
                for (auto len = 0; len < str1.size(); len++) {
                    if (str1[len] != str2[len])
                        diff++;
                    if (diff > 1)
                        break;
                }
                if (diff == 1) {
                    // add two-way connection
                    map.emplace_back(j);
                    connection[j].emplace_back(i);
                }
            }
        }
        return connection;
    }
    
    // build a graph before bfs
    int ladderLengthGraph(string beginWord, string endWord, vector<string>& wordList) {
        auto itForEnd = std::find(wordList.begin(), wordList.end(), endWord);
        auto iEnd = static_cast<int>(std::distance(wordList.begin(), itForEnd));
        if (iEnd >= wordList.size())
            return 0;
        wordList.emplace_back(beginWord);
        auto connectionMap = createConnectionMap(wordList);
        auto iBegin = wordList.size() - 1;
        // add the begin word into visited
        std::unordered_set<int> visited;
        // queue to store the words to be visited, and its depth
        std::queue<std::pair<int, int>> q;
        q.emplace(iBegin, 0);
        while (!q.empty()) {
            // visit top
            auto iTop = q.front().first;
            visited.emplace(iTop);
            auto depth = q.front().second;
            if (iTop == iEnd)
                return depth;
            q.pop();
            // add unvisited children to queue
            for (auto child : connectionMap[iTop]) {
                if (visited.find(child) == visited.end()) {
                    q.emplace(child, depth + 1);
                }
            }
        }
        return 0;
    }
    
    /////////////////////////////////////////
    // create a bi-directional graph and the bfs
    // but actually, we will never use one node twice (never repeat the same node in your path)
    // so we don't have to create a graph. we can get the neighbors on the fly
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        if (std::find(wordList.begin(), wordList.end(), endWord) == wordList.end())
            return 0;
        // no need to check visited as we can remove the node from all after enqueue
        std::unordered_set<std::string> all(wordList.begin(), wordList.end());
        // queue to store the words to be visited, and its depth
        std::queue<std::pair<std::string, int>> q;
        q.emplace(beginWord, 1);
        while (!q.empty()) {
            // visit cur
            auto cur = q.front().first;
            auto depth = q.front().second;
            if (cur == endWord)
                return depth;
            q.pop();
            for (auto len = 0; len < cur.size(); len++) {
                auto tmp = cur[len];
                for (auto c = 'a'; c <= 'z'; c++) {
                    if (c == tmp)
                        continue;
                    cur[len] = c;
                    if (all.find(cur) != all.end()) {
                        q.emplace(cur, depth + 1);
                        all.erase(cur);
                    }
                }
                cur[len] = tmp;
            }
        }
        return 0;
    }
    void Test()
    {
        string beginWord("hit"), endWord("cog");
        vector<string> wordList
        {
            "hot", "dot", "dog", "lot", "log", "cog"
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

