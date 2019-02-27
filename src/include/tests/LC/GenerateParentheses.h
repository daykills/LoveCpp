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
  // leftNum is how many left parentheses left, and rightNum for right;
  // every layer, we add one left or right parenthese to combination
  // base condition is when both are zero, we add combination to the result and return
  void generate(int leftNum, int rightNum, string combination, vector<string>& result)
  {
    // base condition
    if (leftNum == 0 && rightNum == 0)
    {
      result.emplace_back(combination);
      return;
    }
    // as long as leftNum is >0, we can always add a left parenthese
    if (leftNum > 0)
    {
      generate(leftNum - 1, rightNum, combination + "(", result);
    }
    // only when leftNum is smaller than rightNum, we can add ")"
    if (leftNum < rightNum)
    {
      generate(leftNum, rightNum - 1, combination + ")", result);
    }
  }

  vector<string> generateParenthesis(int n)
  {
    vector<string> result;
    generate(n, n, "", result);
    return result;
  }

  static void Test()
  {
    auto result = generateParenthesis(4);
    for (auto str : result)
      cout << " " << str;
    cout << endl;
  }
}