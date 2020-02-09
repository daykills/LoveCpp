/*
 212. Word Search II

 Given a 2D board and a list of words from the dictionary, find all words in the board.
 
 Each word must be constructed from letters of sequentially adjacent cell, where "adjacent" cells are those horizontally or vertically neighboring. The same letter cell may not be used more than once in a word.
 
 Example:
 
 Input:
 board = [
 {'o','a','a','n'},
 {'e','t','a','e'},
 {'i','h','k','r'},
 {'i','f','l','v']
 ]
 words = ["oath","pea","eat","rain"]
 
 Output: ["eat","oath"]
 
 
 Note:
 
 All inputs are consist of lowercase letters a-z.
 The values of words are distinct.
*/

#include <iostream>
#include <stack>
#include <algorithm>
#include "Common.h"

namespace WordSearch2
{

class Solution {
private:
    class TrieNode {
    public:
        TrieNode() : m_isWord(false) {}
        bool isWord() const {
            return m_isWord;
        }
        TrieNode* getNode(char c) {
            if (m_children.count(c))
                return m_children[c];
            return nullptr;
        }
        void insert(const string& word) {
            if (word.empty()) {
                m_isWord = true;
                return;
            }
            auto c = word.front();
            if (!m_children.count(c))
                m_children[c] = new TrieNode();
            m_children[c]->insert(word.substr(1));
        }
    private:
        bool m_isWord;
        unordered_map<char, TrieNode*> m_children;
    };
    
    class Trie {
    public:
        /** Initialize your data structure here. */
        Trie() {}
        
        /** Inserts a word into the trie. */
        void insert(string word) {
            if (word.empty()) return;
            m_root.insert(word);
        }
        
        TrieNode* root() { return &m_root; }
        
    private:
        TrieNode m_root;
    };
    
    void dfs(vector<vector<char>>& board, int row, int col, TrieNode* node, vector<char>& str, unordered_set<string>& ans) {
        auto m = board.size();
        auto n = board[0].size();
        if (row < 0 || row >= m || col < 0 || col >= n)
            return;
        auto curChar = board[row][col];
        // check if curChar is a valid move
        auto nextNode = node->getNode(curChar);
        if (!nextNode) return;
        
        str.push_back(curChar);
        if (nextNode->isWord()) {
            ans.emplace(str.data(), str.size());
        }
        // look for next character
        board[row][col] = 0;
        
        dfs(board, row - 1, col, nextNode, str, ans);
        dfs(board, row + 1, col, nextNode, str, ans);
        dfs(board, row, col - 1, nextNode, str, ans);
        dfs(board, row, col + 1, nextNode, str, ans);
        
        board[row][col] = curChar;
        str.pop_back();
    }
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        Trie trie;
        for (auto word : words) {
            trie.insert(word);
        }
        auto m = board.size();
        auto n = board[0].size();
        unordered_set<string> ans;
        vector<char> str;
        for (auto row = 0; row < m; row++) {
            for (auto col = 0; col < n; col++) {
                dfs(board, row, col, trie.root(), str, ans);
            }
        }
        vector<string> ansVec;
        for (auto& word : ans)
            ansVec.push_back(word);
        return ansVec;
    }
};

void Test()
{
    vector<string> words = {"oath","pea","eat","rain"};
    vector<vector<char>> board = {
        {'o','a','a','n'},
        {'e','t','a','e'},
        {'i','h','k','r'},
        {'i','f','l','v'}
    };
    Solution s;
    auto ans = s.findWords(board, words);
    for (auto word : ans) {
        cout << word << endl;
    }
}
}
