/*
 647. Palindromic Substrings
 Medium
 
 1733
 
 87
 
 Favorite
 
 Share
 Given a string, your task is to count how many palindromic substrings in this string.
 
 The substrings with different start indexes or end indexes are counted as different substrings even they consist of same characters.
 
 Example 1:
 
 Input: "abc"
 Output: 3
 Explanation: Three palindromic strings: "a", "b", "c".
 
 
 Example 2:
 
 Input: "aaa"
 Output: 6
 Explanation: Six palindromic strings: "a", "a", "a", "aa", "aa", "aaa".
 
 
 Note:
 
 The input string length won't exceed 1000.
*/

#include <algorithm>
#include <unordered_set>
#include "Common.h"

namespace CountSubstrings
{

void findPalindrom(const string& s, int left, int right, int& count) {
    while (left >= 0 && right < s.size() && s[left] == s[right]) {
        left--;
        right++;
        count++;
    }
}

int countSubstrings(string s) {
    auto n = s.size();
    if (n == 0) return 0;
    int ans = 0;
    for (auto i = 0; i < n; i++) {
        findPalindrom(s, i, i, ans);
        findPalindrom(s, i, i + 1, ans);
    }
    return ans;
}

void Test() {
    cout << countSubstrings("aaa") << endl;
}
}
