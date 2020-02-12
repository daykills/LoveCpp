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
void dfs(string& digits, vector<char>& letters, vector<string>& ans) {
    static auto getLetterRange = [](char digitChar) {
        int digit = digitChar - '0';
        char lo = (digit - 2) * 3 + 'a';
        char hi = lo + 2;
        if (digit == 7) {
            hi++;
        } else if (digit == 8) {
            lo++;
            hi++;
        } else if (digit == 9) {
            lo++;
            hi += 2;
        }
        return make_pair(lo, hi);
    };
    auto curInd = letters.size();
    if (curInd == digits.size()) {
        if (!letters.empty())
            ans.emplace_back(letters.data(), letters.size());
        return;
    }
    auto range = getLetterRange(digits[curInd]);
    for (char ch = range.first; ch <= range.second; ch++) {
        letters.push_back(ch);
        dfs(digits, letters, ans);
        letters.pop_back();
    }
}
vector<string> letterCombinations(string digits) {
    vector<char> letters;
    vector<string> ans;
    dfs(digits, letters, ans);
    return ans;
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
