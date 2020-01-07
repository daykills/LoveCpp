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
    int calculate(string s) {
        stringstream ss("+" + s);
        char op;
        int num = 0;
        // preOprand: previous number used.
        // For example, 2-3*4+5, when pos is at 4, ans so far is -1, preOperand is -3
        // With * as the next operator, ans becomes "-1-(-3)+3*4=14", preOperand is 3*4=12
        int preOperand = 0;
        int ans = 0;
        // expected format: (last op num)
        while (ss >> op >> num) {
            if (op == '+' || op == '-') {
                preOperand = op == '+' ? num : -num;
                ans += preOperand;
            } else {
                auto newOperand = op == '*' ? preOperand * num : preOperand / num;
                ans = ans - preOperand + newOperand;
                preOperand = newOperand;
            }
        }
        return ans;
    }
};

static void Test()
{
    Solution solution;
    std::cout << solution.calculate("2-3*4*5") << std::endl;
}
}
