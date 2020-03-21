#pragma once

/*
68. Text Justification   My Submissions QuestionEditorial Solution
Total Accepted: 32173 Total Submissions: 199925 Difficulty: Hard
Given an array of words and a length L, format the text such that each line has exactly L characters and is fully (left and right) justified.

You should pack your words in a greedy approach; that is, pack as many words as you can in each line. Pad extra spaces ' ' when necessary so that each line has exactly L characters.

Extra spaces between words should be distributed as evenly as possible. If the number of spaces on a line do not divide evenly between words, the empty slots on the left will be assigned more spaces than the slots on the right.

For the last line of text, it should be left justified and no extra space is inserted between words.

For example,
words: ["This", "is", "an", "example", "of", "text", "justification."]
L: 16.

Return the formatted lines as:
[
"This    is    an",
"example  of text",
"justification.  "
]
Note: Each word is guaranteed not to exceed L in length.

click to show corner cases.

Corner Cases:
A line other than the last line might contain only one word. What should you do in this case?
In this case, that line should be left-justified.
*/

#include <iostream>
#include <stack>
#include <algorithm>
#include "Common.h"

namespace TextJustification
{
vector<string> fullJustify(vector<string>& words, int maxWidth)
{
    int n = words.size();
    if (n == 0) return {};
    
    vector<string> justified;
    auto iStart = 0;
    int lineLen = 0;
    for (auto i = 0; i < words.size(); i++) {
        auto& w = words[i];
        // new line length, with space
        auto newLineLen = lineLen + w.size() + (lineLen == 0 ? 0 : 1);
        if (newLineLen <= maxWidth) {
            lineLen = newLineLen;
            continue;
        }
        auto nSpaces = maxWidth - lineLen;
        // process current line as it's full
        auto nWords = i - iStart;
        // long single word process
        if (nWords == 1) {
            justified.emplace_back(words[iStart] + string(nSpaces, ' '));
            iStart = i;
            lineLen = w.size();
            continue;
        }
        // add spaces between words
        auto nSpacesForEach = 1 + nSpaces / (nWords - 1);
        auto extraSpace = nSpaces % (nWords - 1);
        string line;
        for (auto j = iStart; j < i; j++) {
            line += words[j];
            if (j != i - 1) {
                auto nSpacesToAdd = nSpacesForEach;
                if (j - iStart < extraSpace) nSpacesToAdd++;
                line += string(nSpacesToAdd, ' ');
            }
        }
        justified.emplace_back(move(line));
        iStart = i;
        lineLen = w.size();
    }
    // last line
    string line;
    for (auto i = iStart; i < n; i++) {
        line += words[i] + (i == n - 1 ? "" : " ");
    }
    line += string(maxWidth - line.size(), ' ');
    justified.emplace_back(move(line));
    return justified;
}

int Test()
{
    vector<string> words{ "This", "is", "an", "example", "of", "text", "justification." }; // 16
    //vector<string> words{ "What", "must", "be", "shall", "be." };
    //vector<string> words{ "" }; // 0
    
    int maxWidth = 16;

    for (const auto& word : words)
    {
        cout << word << endl;
    }
    auto result = fullJustify(words, maxWidth);

    cout << "With maxWidth: " << maxWidth << endl;
    for (const auto& word : result)
    {
        cout << "[" << word << "]" << endl;
    }
    return 0;
}
}
