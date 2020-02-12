/*
 32. Longest Valid Parentheses
 
 Given a string containing just the characters '(' and ')', find the length of the longest valid (well-formed) parentheses substring.
 
 Example 1:
 
 Input: "(()"
 Output: 2
 Explanation: The longest valid parentheses substring is "()"
 Example 2:
 
 Input: ")()())"
 Output: 4
 Explanation: The longest valid parentheses substring is "()()"
 */

#include "Common.h"

namespace LongestValidParentheses
{
int longestValidParentheses(string s) {
    auto n = s.size();
    if (n < 2) return 0;
    // dp[i]: max len of valid parentheses ending at i
    // if s[i] == '(', dp[i] is always odd
    vector<int> dp(n, 0);
    dp[0] = s[0] == '(' ? 1 : 0;
    int maxLen = 0;
    for (auto i = 1; i < n; i++) {
        auto preLen = dp[i - 1];
        // dp[i] ending at '(' is odd number only
        if (s[i] == '(') {
            dp[i] = 1;
            if (preLen % 2 == 0) {
                assert(s[i - 1] == ')');
                dp[i] += preLen;
            }
            continue;
        }
        assert(s[i] == ')');
        if (preLen % 2) {
            // s[i - 1] == '('
            dp[i] = preLen + 1;
            
        } else {
            // s[i - 1] == ')', look for an open parenthese
            int iOpenParenthese = i - 1 - preLen;
            if (iOpenParenthese < 0 || s[iOpenParenthese] == ')')
                continue;
            dp[i] = preLen + 1 + dp[iOpenParenthese];
        }
        maxLen = max(maxLen, dp[i]);
    }
    return maxLen;
}

static void Test()
{
    string s = ")()())";
    cout << longestValidParentheses(s) << endl;
}
}
