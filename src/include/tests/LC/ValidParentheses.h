/*
20. Valid Parentheses My Submissions Question
Total Accepted: 92601 Total Submissions: 324797 Difficulty: Easy
Given a string containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.

The brackets must close in the correct order, "()" and "()[]{}" are all valid but "(]" and "([)]" are not.
*/

#include <iostream>
#include <stack>
#include <algorithm>
#include "Common.h"

namespace ValidParentheses
{
    bool isValid(string s) {
        static const std::unordered_map<char, char> endToStartMap = { { '}', '{' }, { ']', '[' }, { ')', '(' } };
        std::stack<char> hist;
        for (auto ch : s) {
            auto it = endToStartMap.find(ch);
            if (it == endToStartMap.end()) {
                // new start
                hist.push(ch);
            } else {
                // ending, match with top of hist
                if (hist.empty() || hist.top() != it->second)
                    return false;
                hist.pop();
            }
        }
        return hist.empty();
    }
    
    int Test()
    {
        string str("()[{}()]{}ab");
        
        cout << str << ": " << isValid(str) << endl;
        return 0;
    }
}
