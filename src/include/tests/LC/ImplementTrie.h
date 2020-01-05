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
/*
class TrieNode {
private:
    // map is in order
    unordered_map<char, TrieNode*> m_children;
    //
    bool isEndOfAWord;
public:
    char value;
    // Initialize your data structure here.
    TrieNode(char ch = 0) : value(ch), isEndOfAWord(false)
    {
    }
    void insert(const string& str)
    {
        if (str.empty())
        {
            return;
        }
        
        auto ch = str.front();
        
        if (m_children.find(ch) == m_children.end())
        {
            m_children.emplace(ch, new TrieNode(ch));
        }
        // last letter, mark next child isEndOfAWord
        if (str.length() == 1)
        {
            m_children[ch]->isEndOfAWord = true;
            return;
        }
        // recursively insert the rest of remaining string
        m_children[ch]->insert(str.substr(1, str.length() - 1));
    }
    bool search(const string& str)
    {
        // if str is empty, and there is an ending character, then we find the word
        if (str.empty()) return isEndOfAWord;
        auto ch = str.front();
        if (m_children.find(ch) == m_children.end()) return false;
        return m_children[ch]->search(str.substr(1, str.length() - 1));
    }
    bool startsWith(const string& str)
    {
        if (str.empty()) return true;
        auto ch = str.front();
        if (m_children.find(ch) == m_children.end()) return false;
        return m_children[ch]->startsWith(str.substr(1, str.length() - 1));
    }
};

class Trie {
public:
    Trie() {
        root = new TrieNode();
    }
    
    // Inserts a word into the trie.
    void insert(string word)
    {
        root->insert(word);
    }
    
    // Returns if the word is in the trie.
    bool search(string word)
    {
        return root->search(word);
    }
    
    // Returns if there is any word in the trie
    // that starts with the given prefix.
    bool startsWith(string prefix)
    {
        return root->startsWith(prefix);
    }
    
private:
    TrieNode* root;
};
*/

class Trie {
public:
    /** Initialize your data structure here. */
    Trie() {
    }
    /** Inserts a word into the trie. */
    void insert(string word) {
        if (word.empty()) {
            m_children.emplace(kEndOfWord, new Trie());
            return;
        }
        if (!m_children.count(word[0]))
            m_children.emplace(word[0], new Trie());
        auto child = m_children[word[0]];
        child->insert(word.substr(1));
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        if (word.empty())
            return m_children.count(kEndOfWord);
        if (!m_children.count(word[0]))
            return false;
        return m_children[word[0]]->search(word.substr(1));
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        if (prefix.empty())
            return true;
        if (!m_children.count(prefix[0]))
            return false;
        return m_children[prefix[0]]->startsWith(prefix.substr(1));
    }
private:
    static constexpr char kEndOfWord = 0;
    unordered_map<char, Trie*> m_children;
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
