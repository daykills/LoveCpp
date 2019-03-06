/*
 5. Longest Palindromic Substring
 
 Given a string s, find the longest palindromic substring in s. You may assume that the maximum length of s is 1000.
 
 Example 1:
 
 Input: "babad"
 Output: "bab"
 Note: "aba" is also a valid answer.
 Example 2:
 
 Input: "cbbd"
 Output: "bb"
 
 */
#include <string>
#include <iostream>
#include <algorithm>
#include "Common.h"

namespace LongestPalindromicSubstring
{
    string longestPalindrome(string s) {
        auto n = s.length();
        if (n < 2) return s;
        
        // dp[i][j] means whether the substring of i to j is alindromic
        // i <= j
        const int MAX_LEN = 1000;
        bool dp[MAX_LEN][MAX_LEN] = { false };
        
        // initialize diagnose
        for (auto i = 0; i < n; i++) {
            dp[i][i] = true;
        }
        // when chars of ends are the same and dp[i + 1][j - 1] is true
        // all dp[x][j - 1] are already calculated in previous loop
        // in case i = j - 1, we only need to compare two ends.
        for (auto j = 1; j < n; j++) {
            for (auto i = 0; i < j; i++) {
                if (s[i] != s[j])
                    continue;
                dp[i][j] = (i == j - 1) || dp[i + 1][j - 1];
            }
        }
        // find the longest substring
        auto start = 0;
        auto maxLength = 1;
        for (auto j = 1; j < n; j++) {
            for (auto i = 0; i < j; i++) {
                if (dp[i][j] && (j - i + 1 > maxLength)) {
                    start = i;
                    maxLength = j - i + 1;
                }
            }
        }
        return s.substr(start, maxLength);
    }
    
    // ordinary method: loop each element, start searching for both sides of that element
    string longestPalindromeOrdinary(const string& s) {
        int len = s.length();
        int maxLen = 0;
        int leftOfMaxSubstring = 0;
        for (int i = 0; i < len; i++)
        {
            // find left and right, skip the same chars between
            char centerChar = s[i];
            int left = i;
            //// better skip this step as it's not necessary
            // while (left - 1 >= 0 && s[left - 1] == centerChar)
            // left--;
            
            int right = i;
            while (right + 1 < len && s[right + 1] == centerChar) right++;
            
            int lenTemp = right - left + 1;
            int step = 1;
            while (left - step >= 0 && right + step < len && s[left - step] == s[right + step])
            {
                step++;
            }
            
            lenTemp += 2 * (step - 1);
            
            if (lenTemp > maxLen)
            {
                maxLen = lenTemp;
                leftOfMaxSubstring = left - step + 1;
            }
        }
        return s.substr(leftOfMaxSubstring, maxLen);
    }
    
    static int Test()
    {
        string str("abbaccacccb");
        auto result = longestPalindrome(str);
        cout << str << ": " << result << endl;
        return 0;
    }
}

