/*
 224. Basic Calculator

 Implement a basic calculator to evaluate a simple expression string.
 
 The expression string may contain open ( and closing parentheses ), the plus + or minus sign -, non-negative integers and empty spaces .
 
 Example 1:
 
 Input: "1 + 1"
 Output: 2
 Example 2:
 
 Input: " 2-1 + 2 "
 Output: 3
 Example 3:
 
 Input: "(1+(4+5+2)-3)+(6+8)"
 Output: 23
 Note:
 You may assume that the given expression is always valid.
 Do not use the eval built-in library function.
 */

#include <iostream>
#include <list>
#include "Common.h"

namespace BasicCalculator
{
class Solution {
public:
    int calculate(string s) {
        int n = s.size();
        // stack to store: prev number and sign for next
        stack<pair<int, int>> st;
        int sum = 0;
        int sign = 1;
        for (auto i = 0; i < n; i++) {
            if (s[i] == ' ') continue;
            if (s[i] == '+') {
                sign = 1;
            } else if (s[i] == '-') {
                sign = -1;
            } else if (s[i] == '('){
                st.emplace(sum, sign);
                sum = 0;
                sign = 1;
            } else if (s[i] == ')'){
                assert(!st.empty());
                auto top = st.top(); st.pop();
                sum = top.first + top.second * sum;
            } else {
                // meet a number
                assert(s[i] >= '0' && s[i] <= '9');
                int num = 0;
                while (i < n && s[i] >= '0' && s[i] <= '9') {
                    num *= 10;
                    num += s[i] - '0';
                    i++;
                }
                i--;
                sum += sign * num;
            }
        }
        return sum;
    }
};

static void Test()
{
    Solution solution;
    std::cout << solution.calculate("(1 +( 4+5+2)-3)+(6+8)") << std::endl;
}
}
