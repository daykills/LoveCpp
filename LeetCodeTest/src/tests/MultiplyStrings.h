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
  string multiply1(string num1, string num2)
  {
    // make sure num1 is shorter
    const int n1 = num1.length();
    const int n2 = num2.length();
    if (n1 > n2) return multiply1(num2, num1);
    int n = n1 + n2 - 1;
    if (n == 0) return "";

    if (n1 == 1 && num1[0] == '0')
      return "0";

    if (n2 == 1 && num2[0] == '0')
      return "0";

    vector<int> result(n, 0);
    for (int i = n1 - 1; i >= 0; i--)
    {
      int v1 = num1[i] - '0';
      for (int j = n2 - 1; j >= 0; j--)
      {
        int v2 = num2[j] - '0';
        result[i + j] += v1 * v2;
      }
    }
    int carry = 0;
    string resultStr(n, '0');
    for (int i = n - 1; i >= 0; i--)
    {
      resultStr[i] = '0' + (carry + result[i]) % 10;
      carry = (carry + result[i]) / 10;
    }
    if (carry)
      resultStr.insert(resultStr.begin(), carry + '0');
    return resultStr;
  }

  // add result with num * 10^offset, result is long enough
  void add(string& result, int num, int offset)
  {
	  int pos = result.length() - offset - 1;
	  int carry = num;
	  while (carry != 0)
	  {
		  auto sum = (carry + result[pos] - '0');
		  result[pos] = sum % 10 + '0';
		  carry = sum / 10;
		  pos--;
	  }
  }
  string multiply(string num1, string num2)
  {
	  int n1 = num1.length();
	  int n2 = num2.length();
	  string result(n1 + n2, '0');
	  for (int i = 0; i < n1; i++)
	  {
		  for (int j = 0; j < n2; j++)
		  {
			  int num = (num1[i] - '0') * (num2[j] - '0');
			  int offset = n1 + n2 - 2 - i - j;
			  add(result, num, offset);
		  }
	  }
	  int pos = 0;
	  while (pos < n1 + n2 - 1 && result[pos] == '0') pos++;
	  return result.substr(pos, n1 + n2 - pos);
  }

  static void Test()
  {
    cout << multiply("9", "9");
  }
}