/*
67. Add Binary
Total Accepted: 73155 Total Submissions: 276410 Difficulty: Easy
Given two binary strings, return their sum (also a binary string).

For example,
a = "11"
b = "1"
Return "100".
*/
#include <iostream>
#include <queue>
#include <algorithm>
#include "Common.h"

namespace AddBinary
{
	string addBinary(string a, string b)
	{
		string& longStr = a.length() > b.length() ? a : b;
		string& shortStr = a.length() <= b.length() ? a : b;
		int lenLong = longStr.length();
		int lenShort = shortStr.length();
		int carry = 0;
		for (auto i = 0; i < lenLong; i++)
		{
			int sum = longStr[lenLong - i - 1] - '0' + carry;
			if (i < lenShort) sum += shortStr[lenShort - i - 1] - '0';

			longStr[lenLong - i - 1] = sum % 2 + '0';
			carry = sum / 2;
		}
		if (carry == 1)
			return "1" + longStr;
		return longStr;
	}
}