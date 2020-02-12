/*
22. Generate Parentheses My Submissions Question
Total Accepted: 80511 Total Submissions: 223059 Difficulty: Medium
Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.

For example, given n = 3, a solution set is:

"((()))", "(()())", "(())()", "()(())", "()()()"
*/

#include <iostream>
#include <queue>
#include <algorithm>
#include "Common.h"

namespace GenerateParentheses
{
// nLeft is how many left parentheses to be added, and nRight for right;
// every layer, we add one left or right parenthese to str
// base condition: when both are zero, we add str to the result
void dfs(vector<string>& res, vector<char>& str, int nLeft, int nRight) {
    if (nLeft == 0 && nRight == 0) {
        res.emplace_back(str.data(), str.size());
        return;
    }
    // as long as leftNum is >0, we can always add '('
    if (nLeft > 0) {
        str.push_back('(');
        dfs(res, str, nLeft - 1, nRight);
        str.pop_back();
    }
    // only when nRight is bigger than nRight, we can add ')'
    if (nRight > nLeft) {
        str.push_back(')');
        dfs(res, str, nLeft, nRight - 1);
        str.pop_back();
    }
}

vector<string> generateParenthesis(int n) {
    vector<string> res;
    vector<char> str;
    str.reserve(n * 2);
    dfs(res, str, n, n);
    return res;
}

static void Test()
{
    auto result = generateParenthesis(4);
    for (auto str : result)
        cout << " " << str;
    cout << endl;
}
}
