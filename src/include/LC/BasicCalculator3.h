/*
 772. Basic Calculator III

 Implement a basic calculator to evaluate a simple expression string.
 
 The expression string may contain open ( and closing parentheses ), the plus + or minus sign -, non-negative integers and empty spaces .
 
 The expression string contains only non-negative integers, +, -, *, / operators , open ( and closing parentheses ) and empty spaces . The integer division should truncate toward zero.
 
 You may assume that the given expression is always valid. All intermediate results will be in the range of [-2147483648, 2147483647].
 
 Some examples:
 
 "1 + 1" = 2
 " 6-4 / 2 " = 4
 "2*(5+5*2)/3+(6/2+8)" = 21
 "(2+6* 3+5- (3*14/7+2)*5)+3"=-12
 
 
 Note: Do not use the eval built-in library function.
 */

#include <iostream>
#include <list>
#include "Common.h"

namespace BasicCalculator3
{
class Solution {
public:
    int calculate(string s) {
        int n = s.size();
        int sum = 0;
        int curSum = 0;
        int num = 0;
        char op = '+';
        for (auto i = 0; i < n; i++) {
            auto c = s[i];
            // process number and parenthese
            if (c >= '0' && c <= '9') {
                num = num * 10 + c - '0';
            } else if (c == '(') {
                // find the range of complete parenthese expression
                auto start = i;
                auto cnt = 0;
                for (; i < n; i++) {
                    if (s[i] == '(') cnt++;
                    else if (s[i] == ')') cnt--;
                    if (cnt == 0)
                        break;
                }
                auto sub = s.substr(start + 1, i - start - 1);
                num = calculate(sub);
            }
            // process operators
            bool isPlusOrMinus = c == '+' || c == '-';
            bool isMultDivid = c == '*' || c == '/';
            bool isLast = i == n - 1;
            // op + num + c
            if (isPlusOrMinus || isMultDivid || isLast) {
                switch (op) {
                    case '+': curSum += num; break;
                    case '-': curSum -= num; break;
                    case '*': curSum *= num; break;
                    case '/': curSum /= num; break;
                }
                if (isPlusOrMinus || isLast) {
                    sum += curSum;
                    curSum = 0;
                }
                op = c;
                num = 0;
            }
        }
        return sum;
    }
};

static void Test()
{
    Solution solution;
    std::cout << solution.calculate(" 6-4 / 2 ") << std::endl;
}
}
