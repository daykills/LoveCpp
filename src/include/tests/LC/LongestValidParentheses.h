/*
 32. Longest Valid Parentheses My Submissions Question
 Total Accepted: 58250 Total Submissions: 262195 Difficulty: Hard
 Given a string containing just the characters '(' and ')', find the length of the longest valid (well-formed) parentheses substring.
 
 For "(()", the longest valid parentheses substring is "()", which has length = 2.
 
 Another example is ")()())", where the longest valid parentheses substring is "()()", which has length = 4.
 */

#include <iostream>
#include <stack>
#include <algorithm>
#include "Common.h"

namespace LongestValidParentheses
    {
    int longestValidParenthesesOld(string s)
    {
        int n = s.length();
        
        int maxLen = 0;
        // store length of valid parentheses stopping at i, l[i] = 0 if s[i] == '('
        vector<int> l(n, 0);
        // build array l
        for (auto i = 0; i < n; i++)
        {
            // can't end with '('
            if (s[i] == '(')
            {
                l[i] = 0;
                continue;
            }
            
            // record whether s[i] finally founds a matching '('
            bool foundMatch = false;
            // search back for the value of l[i]
            auto j = i - 1;
            while (j >= 0)
            {
                // if there is a valid substring ending at j, skip it
                if (l[j] > 0)
                {
                    j -= l[j];
                    continue;
                }
                // s[j] and s[i] make a new pair
                if (!foundMatch && s[j] == '(')
                {
                    foundMatch = true;
                    j--;
                    continue;
                }
                // found a un-usable ')' at s[j], no valid substring can be found.
                break;
            }
            // j is the first un-usable parenthes
            if (foundMatch)
            {
                l[i] = i - j;
                maxLen = max(l[i], maxLen);
            }
        }
        return maxLen;
    }
    
    int longestValidParentheses(string s) {
        // dp[i] represents the longest length ending at i.
        // if s[i] == '(', dp[i] is the longest length
        vector<int> dp(s.size(), 0);
        auto ans = 0;
        for (auto i = 1; i < s.size(); i++) {
            if (s[i] == '(') continue;
            assert(s[i] == ')');
            if (s[i - 1] == '(') {
                dp[i] = 2 + (i >= 2 ? dp[i - 2] : 0);
            } else {
                auto preLen = dp[i - 1];
                if (preLen == 0)
                    continue;
                int preI = i - 1 - preLen;
                if (preI >= 0 && s[preI] == '(') {
                    dp[i] = preLen + 2;
                    // connect previous parentheses
                    if (preI > 0)
                        dp[i] += dp[preI - 1];
                }
            }
            ans = max(ans, dp[i]);
        }
        return ans;
    }
    
    int Test()
    {
        //string str(")()(()())");
        //string str("()(())");
        string str("))())()()())))");
        
        cout << str << ": " << longestValidParentheses(str) << endl;
        return 0;
    }
    }

