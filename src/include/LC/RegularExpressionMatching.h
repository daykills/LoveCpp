/*
 10. Regular Expression Matching

 Given an input string (s) and a pattern (p), implement regular expression matching with support for '.' and '*'.
 
 '.' Matches any single character.
 '*' Matches zero or more of the preceding element.
 The matching should cover the entire input string (not partial).
 
 Note:
 
 s could be empty and contains only lowercase letters a-z.
 p could be empty and contains only lowercase letters a-z, and characters like . or *.
 Example 1:
 
 Input:
 s = "aa"
 p = "a"
 Output: false
 Explanation: "a" does not match the entire string "aa".
 Example 2:
 
 Input:
 s = "aa"
 p = "a*"
 Output: true
 Explanation: '*' means zero or more of the preceding element, 'a'. Therefore, by repeating 'a' once, it becomes "aa".
 Example 3:
 
 Input:
 s = "ab"
 p = ".*"
 Output: true
 Explanation: ".*" means "zero or more (*) of any character (.)".
 Example 4:
 
 Input:
 s = "aab"
 p = "c*a*b"
 Output: true
 Explanation: c can be repeated 0 times, a can be repeated 1 time. Therefore, it matches "aab".
 Example 5:
 
 Input:
 s = "mississippi"
 p = "mis*is*p*."
 Output: false
 
 */

#include "Common.h"

namespace RegularExpressionMatching
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
