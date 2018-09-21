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
		vector<string> result;
		int n = words.size();
		if (n == 0) return result;

		// start index of words for current line, and total length for current line
		int start = 0, totalLen = 0;
		for (auto end = 0; end < n; end++)
		{
			auto wordLen = words[end].length();
			// add extra one for space
			int newTotalLen = (totalLen == 0) ? wordLen : totalLen + wordLen + 1;
			if (newTotalLen <= maxWidth)
			{
				totalLen = newTotalLen;
				continue;
			}
			else
			{
				string line;
				int extraSpaces = maxWidth - totalLen;
				// add current line to result
				int nWords = end - start;
				if (nWords == 1)
				{
					line.append(words[start]);
					line.append(extraSpaces, ' ');
				}
				else
				{
					int extraSpacesPerWord = extraSpaces / (nWords - 1) + 1;
					int extraSpacesResidule = extraSpaces % (nWords - 1);
					for (auto i = start; i < end - 1; i++)
					{
						line.append(words[i]);
						// words on the left get one more extra space
						auto nExtraSpace = (i < start + extraSpacesResidule) ? extraSpacesPerWord + 1 : extraSpacesPerWord;
						line.append(nExtraSpace, ' ');
					}
					line.append(words[end - 1]);
				}
				result.emplace_back(move(line));
				// reset status
				totalLen = wordLen;
				start = end;
			}
		}
		// handle last line
		string line;
		for (auto i = start; i < n; i++)
		{
			line.append(words[i]);
			if (i != n - 1)
				line.append(1, ' ');
			else
				line.append(maxWidth - totalLen, ' ');
		}
		result.emplace_back(move(line));
		return result;
	}
	int Test()
	{
		//vector<string> words{ "This", "is", "an", "example", "of", "text", "justification." }; // 16
		//vector<string> words{ "What", "must", "be", "shall", "be." };
		vector<string> words{ "" }; // 0
		
		int maxWidth = 0;

		for (const auto& word : words)
		{
			cout << word << endl;
		}
		auto result = fullJustify(words, maxWidth);

		cout << "With maxWidth: " << maxWidth << endl;
		for (const auto& word : result)
		{
			cout << word << endl;
		}
		return 0;
	}
}
