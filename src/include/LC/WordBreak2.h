#pragma once
/*
140. Word Break II My Submissions Question
Total Accepted: 53041 Total Submissions: 272210 Difficulty: Hard
Given a string s and a dictionary of words dict, add spaces in s to construct a sentence where each word is a valid dictionary word.

Return all such possible sentences.

For example, given
s = "catsanddog",
dict = ["cat", "cats", "and", "sand", "dog"].

A solution is ["cats and dog", "cat sand dog"].
*/

#include <iostream>
#include <queue>
#include <memory>
#include <cassert>
#include <algorithm>
#include <vector>
#include "Common.h"

namespace WordBreak2
{
vector<string> wordBreakDP(string s, vector<string>& wordDict) {
    auto n = s.length();
    if (n == 0)
        return {};
    
    unordered_set<string> wordSet(wordDict.begin(), wordDict.end());
    // dp[i]: all phrases formed by first i chars
    vector<vector<string>> dp(n + 1);
    dp[0].emplace_back("");
    for (auto i = 1; i <= n; i++) {
        auto& phrases = dp[i];
        int hi = i - 1;
        for (int lo = hi; lo >= 0; lo--) {
            auto subStr = s.substr(lo, hi - lo + 1);
            if (!wordSet.count(subStr))
                continue;
            auto& prePhrases = dp[lo];
            for (auto& phrase : prePhrases)
                phrases.emplace_back(phrase + (phrase.empty() ? "" : " ") + subStr);
        }
    }
    return dp.back();
}

unordered_map<string, vector<string>> m_cachedResult;

vector<string> wordBreak(string s, vector<string>& wordDict) {
    auto n = s.length();
    if (n == 0)
        return { "" };
    if (m_cachedResult.count(s))
        return m_cachedResult[s];
    vector<string> phrases;
    for (auto& word : wordDict) {
        if (word != s.substr(0, word.size()))
            continue;
        auto remainingPhrases = wordBreak(s.substr(word.size()), wordDict);
        for (auto& phrase : remainingPhrases)
            phrases.emplace_back(word + (phrase.empty() ? "" : " ") + phrase);
    }
    m_cachedResult[s] = phrases;
    return phrases;
}

void Test()
{
    
    //string s("hipangpang");
    string s("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
    
    vector<string> wordDict{
        //"hi", "pang", "hip", "ang"
        
        "a","aa","aaa","aaaa","aaaaa","aaaaaa","aaaaaaa","aaaaaaaa","aaaaaaaaa","aaaaaaaaaa"
    };
    cout << "input: " << s << endl;
    cout << "result: " << endl;
    auto result = wordBreak(s, wordDict);
    for(auto& sentence : result)
        cout << sentence << endl;
}
}
