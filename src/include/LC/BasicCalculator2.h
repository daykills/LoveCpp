/*
 227. Basic Calculator II

 Implement a basic calculator to evaluate a simple expression string.
 
 The expression string contains only non-negative integers, +, -, *, / operators and empty spaces . The integer division should truncate toward zero.
 
 Example 1:
 
 Input: "3+2*2"
 Output: 7
 Example 2:
 
 Input: " 3/2 "
 Output: 1
 Example 3:
 
 Input: " 3+5 / 2 "
 Output: 5
 Note:
 
 You may assume that the given expression is always valid.
 Do not use the eval built-in library function.
 */

#include <iostream>
#include <list>
#include "Common.h"

namespace BasicCalculator2
{
class Solution {
public:
    // O(N) time O(1) space
    int calculate1(string s) {
        stringstream ss("+" + s);
        char op;
        int num = 0;
        // preOprand: previous number used.
        // For example, 2-3*4+5, when pos is at 4, ans so far is -1, last is -3
        // With * as the next operator, ans becomes "-1-(-3)+3*4=14", preOperand is 3*4=12
        int last = 0;
        int ans = 0;
        // expected format: (last op num)
        while (ss >> op >> num) {
            if (op == '+' || op == '-') {
                last = op == '+' ? num : -num;
                ans += last;
            } else {
                auto newNum = op == '*' ? last * num : last / num;
                ans = ans - last + newNum;
                last = newNum;
            }
        }
        return ans;
    }
    
    int calculate(string s) {
        long res = 0, curRes = 0, num = 0, n = s.size();
        char op = '+';
        for (int i = 0; i < n; ++i) {
            char c = s[i];
            if (c >= '0' && c <= '9') {
                num = num * 10 + c - '0';
            }
            if (c == '+' || c == '-' || c == '*' || c == '/' || i == n - 1) {
                switch (op) {
                    case '+': curRes += num; break;
                    case '-': curRes -= num; break;
                    case '*': curRes *= num; break;
                    case '/': curRes /= num; break;
                }
                if (c == '+' || c == '-' || i == n - 1) {
                    res += curRes;
                    curRes = 0;
                }
                op = c;
                num = 0;
            }
        }
        return res;
    }
};

static void Test()
{
    Solution solution;
    std::cout << solution.calculate("2-3*4/2") << std::endl;
}
}
