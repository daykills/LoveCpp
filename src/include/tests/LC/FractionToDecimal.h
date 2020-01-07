/*
 166. Fraction to Recurring Decimal

 Given two integers representing the numerator and denominator of a fraction, return the fraction in string format.
 
 If the fractional part is repeating, enclose the repeating part in parentheses.
 
 Example 1:
 
 Input: numerator = 1, denominator = 2
 Output: "0.5"
 Example 2:
 
 Input: numerator = 2, denominator = 1
 Output: "2"
 Example 3:
 
 Input: numerator = 2, denominator = 3
 Output: "0.(6)"
 */

#include <iostream>
#include <list>
#include "Common.h"

namespace FractionToDecimal
{
class Solution {
public:
    string fractionToDecimal(int numerator, int denominator) {
        assert(denominator != 0);
        int signNum = numerator >= 0 ? 1 : -1;
        int signDen = denominator >= 0 ? 1 : -1;
        long absNum = abs((long)numerator);
        long absDen = abs((long)denominator);
        string signStr = (numerator == 0 || signNum == signDen) ? "" : "-";
        string integerStr = signStr + to_string(absNum / absDen);
        long rem = absNum % absDen;
        if (rem == 0)
            return integerStr;
        integerStr = integerStr + ".";
        // if same rem value appears, we know it's repeating
        unordered_map<long, int> remPos;
        string decimal;
        auto pos = 0;
        while (rem) {
            if (remPos.count(rem)) {
                return integerStr + decimal.substr(0, remPos[rem])
                    + "(" + decimal.substr(remPos[rem]) + ")";
            }
            remPos.emplace(rem, pos++);
            // calculate next digit
            rem *= 10;
            auto digit = rem / absDen;
            decimal.append(1, digit + '0');
            rem = rem % denominator;
        }
        return integerStr + decimal;
    }
};

static void Test()
{
    Solution solution;
    std::cout << solution.fractionToDecimal(86, 7) << std::endl;
    std::cout << solution.fractionToDecimal(7, -12) << std::endl;
    std::cout << solution.fractionToDecimal(3, 7) << std::endl;
    std::cout << solution.fractionToDecimal(66, 100) << std::endl;
    std::cout << solution.fractionToDecimal(3, 4) << std::endl;
    std::cout << solution.fractionToDecimal(2, 3) << std::endl;
}
}
