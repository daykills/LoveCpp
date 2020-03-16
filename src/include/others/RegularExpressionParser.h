/*
 
 # Implement a simple regular expression parser:
 
 # 1. Write a function that will parse a regular expression pattern and return an object that defines the operation for our regular expression pattern matching.
 
 # Pattern Syntax:
 
 # == Character matchers:
 #   .   Matches any character
 #   \s  Matches a space or tab character
 #   \   Treats the following character as a literal,
 #       eg \. matches a single period
 #   All other characters are treated as literals.
 
 # ==  Modifiers (only appear following matchers):
 #   +  Match at least one or more of the preceding matcher
 #   *  Match zero or more of the preceding matcher
 
 */

#include "Common.h"

namespace RegularExpressionParser
{
class Solution {
public:
    bool isMatch(string s, string p) {
        int m = s.size(), n = p.size();
        // dp[i][j] first i chars and first j chars matched
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        // initial
        dp[0][0] = 1;
        // dp[i][j] = dp[i - 1][j - 1] if s[i - 1] == p[j - 1] or p[j - 1] == '.'
        // if p[j - 1] == '*'
        //      a) dp[i][j] = dp[i][j - 2], for no repeat
        //      b) dp[i][j] = dp[i - 1][j], when s[i - 1] == p[i - 2] || p[i - 2] == '.'
        for (auto i = 0; i <= m; i++) {
            for (auto j = 1; j <= n; j++) {
                if (p[j - 1] == '*') {
                    // * has to follow a character
                    assert(j > 1);
                    dp[i][j] = dp[i][j - 2] // no repeat, including "" -> ".*"
                        || (i > 0 && dp[i - 1][j] && (s[i - 1] == p[j - 2] || p[j - 2] == '.')); // with repeat
                } else {
                    dp[i][j] = i > 0 && dp[i - 1][j - 1]
                    && (s[i - 1] == p[j - 1] || p[j - 1] == '.');
                }
            }
        }
        return dp[m][n];
    }
    
    bool isMatchDFS(string s, string p) {
        return helper(s, 0, p, 0);
    }
private:
    bool helper(string& s, int sMatched, string& p, int pMatched) {
        const bool strComplete = sMatched == s.size();
        const bool patternComplete = pMatched == p.size();
        const auto strLen = s.size() - sMatched;
        const auto patternLen = p.size() - pMatched;
        
        const bool firstCharMatched = !strComplete && !patternComplete
        && (s[sMatched] == p[pMatched] || p[pMatched] == '.');
        
        // base condition
        if (patternComplete)
            return strComplete;
        if (patternLen == 1) {
            return strLen == 1 && firstCharMatched;
        }
        
        assert(patternLen >= 2);
        // without * match
        if (p[pMatched + 1] != '*') {
            if (strComplete)
                return false;
            return firstCharMatched && helper(s, sMatched + 1, p, pMatched + 1);
        }
        // p has pattern of x*...
        // try to match multiple repeating characters
        for (auto i = sMatched; i < s.size(); i++) {
            if (s[i] == p[pMatched] || p[pMatched] == '.') {
                if (helper(s, i + 1, p, pMatched + 2))
                    return true;
            } else {
                break;
            }
        }
        // no match
        return helper(s, sMatched, p, pMatched + 2);
    }
};

static void Test()
{
    Solution solution;
    std::cout << solution.isMatch("aa", "a*") << std::endl;
}
}
