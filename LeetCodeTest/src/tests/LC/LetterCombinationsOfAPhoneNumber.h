/*
17. Letter Combinations of a Phone Number My Submissions Question
Total Accepted: 72734 Total Submissions: 258753 Difficulty: Medium
Given a digit string, return all possible letter combinations that the number could represent.

A mapping of digit to letters (just like on the telephone buttons) is given below.

Input:Digit string "23"
Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].
*/
#include <iostream>
#include <queue>
#include <algorithm>
#include "Common.h"

namespace LetterCombinationsOfAPhoneNumber
{
	vector<string> dfsTraverse(string& digits, int startPos, const vector<string>& mapping)
	{
		vector<string> result;
		// base case for recursion
		if (startPos >= (int)digits.length()) return result;
		// get number as int
		int number = (int)(digits[startPos] - '0');
		assert(number >= 0 && number <= 9);
		// get mapped letters
		auto& letters = mapping[number];
		// get sub result for digits after the startPos
		auto subResult = dfsTraverse(digits, startPos + 1, mapping);
		// for 0 and 1
		if (letters.empty()) return subResult;
		// append strings of subResult
		for (auto letter : letters)
		{
			string prefix(1, letter);
			if (subResult.size() == 0)
			{
				result.emplace_back(prefix);
			}
			else
			{
				for (auto& strInSubResult : subResult)
				{
					result.emplace_back(prefix + strInSubResult);
				}
			}
		}
		return result;
	}
	vector<string> letterCombinations(string digits) {
		// number to letters mapping
		vector<string> mapping{ "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz" };
		// use dfs traverse to list all numbers
		return dfsTraverse(digits, 0, mapping);
	}

	void Test()
	{
		string input;
		cout << "Please input the number: ";
		getline(cin, input);

		auto result = letterCombinations(input);
		cout << "For number: " << input << endl;
		for (auto& str : result)
		{
			cout << str << " ";
		}
		cout << endl;
	}
}
