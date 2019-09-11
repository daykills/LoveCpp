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
        int last = 0;
        int ans = 0;
        // (last op num)
        while (ss >> op >> num) {
            if (op == '+' || op == '-') {
                num = op == '-' ? -num : num;
                ans += last;
            } else {
                num = op == '*' ? last * num : last / num;
            }
            last = num;
        }
        return ans + last;
    }
};

static void Test()
{
    Solution solution;
    std::cout << solution.calculate("3+2*2") << std::endl;
}
}
