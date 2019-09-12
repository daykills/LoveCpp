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
        int s1 = numerator >= 0 ? 1 : -1;
        int s2 = denominator >= 0 ? 1 : -1;
        long long num = abs( (long long)numerator );
        long long den = abs( (long long)denominator );
        long long out = num / den;
        long long rem = num % den;
        unordered_map<long long, int> m;
        string res = to_string(out);
        if (s1 * s2 == -1 && (out > 0 || rem > 0)) res = "-" + res;
        if (rem == 0) return res;
        res += ".";
        string s = "";
        int pos = 0;
        while (rem != 0) {
            if (m.find(rem) != m.end()) {
                s.insert(m[rem], "(");
                s += ")";
                return res + s;
            }
            m[rem] = pos;
            s += to_string((rem * 10) / den);
            rem = (rem * 10) % den;
            ++pos;
        }
        return res + s;
    }
};

static void Test()
{
    Solution solution;
    std::cout << solution.fractionToDecimal(3, 7) << std::endl;
    std::cout << solution.fractionToDecimal(66, 100) << std::endl;
    std::cout << solution.fractionToDecimal(3, 4) << std::endl;
    std::cout << solution.fractionToDecimal(2, 3) << std::endl;
}
}
