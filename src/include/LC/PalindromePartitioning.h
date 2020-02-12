/*
131. Palindrome Partitioning My Submissions Question
Total Accepted: 60786 Total Submissions: 220603 Difficulty: Medium
Given a string s, partition s such that every substring of the partition is a palindrome.

Return all possible palindrome partitioning of s.

For example, given s = "aab",
Return

[
["aa","b"],
["a","a","b"]
]

*/

#include <iostream>
#include <queue>
#include <memory>
#include <cassert>
#include <algorithm>
#include <vector>
#include "Common.h"

namespace PalindromePartitioning
{
    std::vector<std::vector<bool>> getPalindromeMat(const std::string& s)
    {
        std::vector<std::vector<bool>> mat(s.size(), std::vector<bool>(s.size(), false));
        // starting with each single char or duplex, and expand
        for (auto i = 0; i < s.size(); i++) {
            // coreLen is 1 or 2 as the starting point of search
            for (auto coreLen = 1; coreLen <= 2; coreLen++) {
                // start expanding palindrome search from lo/hi to both directions
                auto lo = i - 1;
                auto hi = i + coreLen;
                if (coreLen == 1) {
                    mat[i][i] = true;
                } else {
                    if (i == s.size() - 1)
                        continue;
                    if (s[i] != s[i + 1])
                        continue;
                    mat[i][i + 1] = mat[i + 1][i] = true;
                }
                while (lo >= 0 && hi < s.size() && s[lo] == s[hi]) {
                    mat[lo][hi] = mat[hi][lo] = true;
                    lo--;
                    hi++;
                }
            }
            
        }
        return mat;
    }
    
    void dfs(vector<vector<string>>& result, const string& s, const std::vector<std::vector<bool>>& palindromeMat, int pos, vector<string>& palindromes)
    {
        // base condition when reaching end of string
        if (pos == s.size()) {
            result.emplace_back(palindromes);
            return;
        }
        // look for possible palindromes between pos and end
        for (auto end = pos; end < s.size(); end++) {
            if (palindromeMat[pos][end]) {
                palindromes.emplace_back(s.substr(pos, end - pos + 1));
                dfs(result, s, palindromeMat, end + 1, palindromes);
                palindromes.pop_back();
            }
        }
    }
    
    vector<vector<string>> partitionDP(string s) {
        auto mat = getPalindromeMat(s);
        vector<vector<string>> ret;
        vector<string> palindromes;
        dfs(ret, s, mat, 0, palindromes);
        return ret;
    }
    
    bool isPalindrome(const string& str, int lo, int hi)
    {
        if (hi >= str.size() || lo < 0 || lo > hi)
            return false;
        
        while(lo < hi)
        {
            if(str[lo] != str[hi]) return false;
            lo++, hi--;
        }
        return true;
    }
    
    void dfs(vector<vector<string>>& result, const string& s, int pos, vector<string>& palindromes)
    {
        // base condition when reaching end of string
        if (pos == s.size()) {
            result.emplace_back(palindromes);
            return;
        }
        // look for possible palindromes between pos and end
        for (auto end = pos; end < s.size(); end++) {
            if (isPalindrome(s, pos, end)) {
                palindromes.emplace_back(s.substr(pos, end - pos + 1));
                dfs(result, s, end + 1, palindromes);
                palindromes.pop_back();
            }
        }
    }
    
    vector<vector<string>> partition(string s) {
        vector<vector<string>> ret;
        vector<string> palindromes;
        dfs(ret, s, 0, palindromes);
        return ret;
    }

  void Test()
  {
    string input("aabbaba");    
    cout << "input: " << input << endl;
    auto result = partitionDP(input);
    for (auto& combination : result)
    {
      for (auto& palindrome : combination)
        cout << palindrome << " ";
      cout << endl;
    }
  }
}
