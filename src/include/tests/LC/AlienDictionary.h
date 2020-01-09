#pragma once
/*
269: ALIEN DICTIONARY (HARD)
 There is a new alien language which uses the latin alphabet. However, the order among letters are unknown to you. You receive a list of non-empty words from the dictionary, where words are sorted lexicographically by the rules of this new language. Derive the order of letters in this language.
 
 Example 1:
 
 Input:
 [
 "wrt",
 "wrf",
 "er",
 "ett",
 "rftt"
 ]
 Output: "wertf"
 
 Example 2:
 
 Input:
 [
 "z",
 "x"
 ]
 Output: "zx"
 
 Example 3:
 
 Input:
 [
 "z",
 "x",
 "z"
 ]
 Output: ""
 
 Explanation: The order is invalid, so return "".
 Note:
 
 You may assume all letters are in lowercase.
 You may assume that if a is a prefix of b, then a must appear before b in the given dictionary.
 If the order is invalid, return an empty string.
 There may be multiple valid order of letters, return any one of them is fine.

*/

#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include "Common.h"

namespace AlienDictionary
{
string alienOrder(vector<string>& words)
{
    using Graph = Graph::Graph;
    
    int n = words.size();
    if (n == 0) return "";
    
    Graph g;
    // add all chars into the graph
    for (auto c : words.front()) g.addVetex(c);
    
    for (auto i = 1; i < n; i++)
    {
        for (auto c : words[i]) g.addVetex(c);
        int len = min(words[i - 1].length(), words[i].length());
        for (auto j = 0; j < len; j++)
        {
            // different char implies the order
            if (words[i - 1][j] != words[i][j])
            {
                g.addEdge(words[i - 1][j], words[i][j]);
                break;
            }
        }
    }
    
    g.printGraph<char>();
    
    auto dfsItems = g.dfs();
    auto orderedItems = g.topologicalSort();
    stringstream ss;
    for (auto item : orderedItems)
        ss << (char)item;
    return ss.str();
}

////////////////////////////////////////////////////////////////////////////////////

static void Test()
{
    
    //Output: Order of characters is 'c', 'a', 'b'
    //vector<string> words { "caa", "aaa", "aab" };
    
    //Output: wertf
    //vector<string> words { "wrt", "wrf", "er", "ett", "rftt" };
    
    //Output: wertf
    vector<string> words { "z", "x", "z" };
    
    cout << "Words: ";
    for (auto& word : words)
    {
        cout << word << " ";
    }
    cout << endl;
    cout << "Order: " << alienOrder(words) << endl;
}
}
