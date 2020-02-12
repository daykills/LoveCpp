/*
66. Plus One
Total Accepted: 85595 Total Submissions: 262805 Difficulty: Easy
Given a non-negative number represented as an array of digits, plus one to the number.

The digits are stored such that the most significant digit is at the head of the list.
*/
#include <iostream>
#include <queue>
#include <algorithm>
#include "Common.h"

namespace PlusOne
{
  vector<int> plusOne(vector<int>& digits)
  {
    int n = digits.size();
    int plus = 1;
    for (int i = n - 1; i >= 0 && plus; i--)
    {
      auto temp = digits[i] + plus;
      plus = temp / 10;
      digits[i] = temp % 10;
    }
    if (plus)
    {
      digits.insert(digits.begin(), 1);
    }
    return digits;
  }

  
  static string Test(vector<int>& digits)
  {
    for (auto num : digits)
    {
      cout << num << " ";
    }
    cout << endl;

    auto result = plusOne(digits);
    for (auto num : result)
    {
      cout << num << " ";
    }
    cout << endl;

    return "";
  }
}
