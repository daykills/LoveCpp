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
        int n, last, ans = 0;
        while (ss >> op >> n) {
            if (op == '+' || op == '-') {
                n = op == '+' ? n : -n;
                ans += n;
            } else {
                n = op == '*' ? last * n : last / n;
                ans = ans - last + n; // simulate a stack by recovering last values
            }
            last = n;
        }
        return ans;
    }
};

static void Test()
{
    Solution solution;
    std::cout << solution.calculate("3+2*2") << std::endl;
}
}
