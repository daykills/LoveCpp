/*
208. Implement Trie (Prefix Tree) My Submissions Question
Total Accepted: 32419 Total Submissions: 128258 Difficulty: Medium
Implement a trie with insert, search, and startsWith methods.

Note:
You may assume that all inputs are consist of lowercase letters a-z.
*/

#include <iostream>
#include <stack>
#include <algorithm>
#include "Common.h"

namespace ImplementTrie
{
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
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        auto node = &m_root;
        for (auto c : word) {
            node = node->getNode(c);
            if (!node) return false;
        }
        return node->isWord();
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        auto node = &m_root;
        for (auto c : prefix) {
            node = node->getNode(c);
            if (!node) return false;
        }
        return node;
    }
    
    TrieNode* root() { return &m_root; }
    
private:
    TrieNode m_root;
};

int Test()
{
    Trie trie;
    trie.insert("a");
    trie.insert("abc");
    cout << trie.search("ab") << endl;
    cout << trie.search("abc") << endl;
    cout << trie.startsWith("ab") << endl;
    return 0;
}
}
