/*
 640. Solve the Equation

 Solve a given equation and return the value of x in the form of string "x=#value". The equation contains only '+', '-' operation, the variable x and its coefficient.
 
 If there is no solution for the equation, return "No solution".
 
 If there are infinite solutions for the equation, return "Infinite solutions".
 
 If there is exactly one solution for the equation, we ensure that the value of x is an integer.
 
 Example 1:
 
 Input: "x+5-3+x=6+x-2"
 Output: "x=2"
 Example 2:
 
 Input: "x=x"
 Output: "Infinite solutions"
 Example 3:
 
 Input: "2x=x"
 Output: "x=0"
 Example 4:
 
 Input: "2x+3x-6x=x+2"
 Output: "x=-1"
 Example 5:
 
 Input: "x=x+2"
 Output: "No solution"
*/

#include <iostream>
#include <stack>
#include <algorithm>
#include "Common.h"

namespace SolveEquation
{
void parse(string expr, int& coef, int& val) {
    assert(!expr.empty());
    // add "+" to make expression formalized
    if (expr[0] != '-') expr = "+" + expr;
    
    val = 0;
    coef = 0;
    int sign = 1;
    int curNum = 0;
    for (auto i = 0; i < expr.size(); i++) {
        if (expr[i] == '-' || expr[i] == '+') {
            // commit previous segment without x
            if (i > 0) {
                if (expr[i - 1] != 'x') {
                    val += curNum * sign;
                }
                curNum = 0;
            }
            sign = expr[i] == '-' ? -1 : 1;
        } else if (expr[i] == 'x') {
            assert(i > 0);
            if (expr[i - 1] <= '9' && expr[i - 1] >= '0') {
                coef += curNum * sign;
            } else {
                coef += sign;
            }
            curNum = 0;
        } else {
            assert(expr[i] <= '9' && expr[i] >= '0');
            curNum = curNum * 10 + expr[i] - '0';
        }
    }
    val += curNum * sign;
}

string solveEquation(string equation) {
    auto pos = equation.find('=');
    assert(pos != equation.npos);
    auto left = equation.substr(0, pos);
    auto right = equation.substr(pos + 1);
    int lCoef, lVal;
    parse(left, lCoef, lVal);
    int rCoef, rVal;
    parse(right, rCoef, rVal);
    int coef = lCoef - rCoef;
    int val = rVal - lVal;
    if (coef == 0 && val == 0)
        return "Infinite solutions";
    if (coef == 0)
        return "No solution";
    if (val == 0)
        return "x=0";
    return "x=" + to_string(val / coef);
}

void Test()
{
    cout << solveEquation("x+5-3+x=6+x-2") << endl;
}
}
