/*
43. Multiply Strings My Submissions Question
Total Accepted: 53518 Total Submissions: 236227 Difficulty: Medium
Given two numbers represented as strings, return multiplication of the numbers as a string.

Note: The numbers can be arbitrarily large and are non-negative.
*/
#include <iostream>
#include <queue>
#include <algorithm>
#include "Common.h"

namespace MultiplyStrings
{
string multiply(string num1, string num2) {
    if (num1 == "0" || num2 == "0")
        return "0";
    auto n1 = num1.size();
    auto n2 = num2.size();
    
    // reverse product stored in vector
    std::vector<int> result(n1 + n2, 0);
    for (auto i1 = 0; i1 < n1; i1++) {
        int digit1 = num1[n1 - i1 - 1] - '0';
        for (auto i2 = 0; i2 < n2; i2++) {
            int digit2 = num2[n2 - i2 - 1] - '0';
            auto offset = i1 + i2;
            auto product = digit2 * digit1;
            // apply product to result
            auto carry = 0;
            while (product || carry) {
                auto sum = result[offset] + product % 10 + carry;
                result[offset] = sum % 10;
                carry = sum / 10;
                product = product / 10;
                offset++;
            }
        }
    }
    
    auto n = result.size();
    vector<char> resultCharVec;
    resultCharVec.reserve(n);
    bool nonZero = false;
    for (auto i = 0; i < n; i++) {
        auto num = result[n - i - 1];
        if (num == 0 && nonZero == false)
            continue;
        nonZero = true;
        resultCharVec.push_back(num + '0');
    }
    return string(resultCharVec.data(), resultCharVec.size());
}

static void Test()
{
    cout << multiply("123", "456") << endl;
}

}
