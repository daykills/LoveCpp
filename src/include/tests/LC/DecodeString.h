/*
 394. Decode String

 Given an encoded string, return its decoded string.
 
 The encoding rule is: k[encoded_string], where the encoded_string inside the square brackets is being repeated exactly k times. Note that k is guaranteed to be a positive integer.
 
 You may assume that the input string is always valid; No extra white spaces, square brackets are well-formed, etc.
 
 Furthermore, you may assume that the original data does not contain any digits and that digits are only for those repeat numbers, k. For example, there won't be input like 3a or 2[4].
 
 Examples:
 
 s = "3[a]2[bc]", return "aaabcbc".
 s = "3[a2[c]]", return "accaccacc".
 s = "2[abc]3[cd]ef", return "abcabccdcdcdef".
 */

#include <iostream>
#include <queue>
#include <algorithm>
#include <numeric>
#include "Common.h"

namespace DecodeString
{

string decodeString(string s) {
    // stack to store prefix and repeat num
        stack<pair<string, int>> hist;
        string cur;        
        for (auto i = 0; i < s.size();) {
            auto num = 0;
            while (s[i] <= '9' && s[i] >= '0') {
                num = num * 10 + s[i] - '0';
                i++;
                assert(i < s.size());
            }
            // num must be followed by '[]'
            if (num > 0) {
                assert(i < s.size());
                assert(s[i] == '[');
                hist.emplace(cur, num);
                assert(i < s.size() - 1);
                // reset prefix and num
                cur = "";
                num = 0;
                i++;
                continue;
            }
            
            if (s[i] == ']') {
                assert(!hist.empty());
                auto prefix = hist.top().first;
                auto repeat = hist.top().second;
                assert(repeat > 0);
                hist.pop();
                string repeatingStr = cur;
                for (auto k = 0; k < repeat - 1; k++) {
                    cur = cur + repeatingStr;
                }
                cur = prefix + cur;
                i++;
                continue;
            }
            
            // alphabet
            while (i < s.size() && ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'))) {
                cur.append(1, s[i]);
                i++;
            }
        }
        return cur;
}

static void Test()
{
    string s = "3[a]2[b4[F]c]";
    std::cout << decodeString(s) << std::endl;
}
}
