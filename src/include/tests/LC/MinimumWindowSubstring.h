/*
76. Minimum Window Substring My Submissions Question
Total Accepted: 55923 Total Submissions: 267490 Difficulty: Hard
Given a string S and a string T, find the minimum window in S which will contain all the characters in T in complexity O(n).

For example,
S = "ADOBECODEBANC"
T = "ABC"
Minimum window is "BANC".

Note:
If there is no such window in S that covers all characters in T, return the empty string "".

If there are multiple such windows, you are guaranteed that there will always be only one unique minimum window in S.
*/
#include <string>
#include <iostream>
#include "Common.h"

namespace MinimumWindowSubstring
{
	string minWindow(string s, string t)
	{
		int m = s.length();
		int n = s.length();
		if (m == 0 || n == 0) return "";

		// to hold all chars used in window
		unordered_set<char> inUse;
		// notUsed to hold all not used chars
		multiset<char> notUsed(t.begin(), t.end());
		deque<char> window;
		string result;
		int minLenWindow = INT_MAX;
		bool previousWindowQualified = false;
		for (auto ch : s)
		{
			// always add ch to the back of window
			window.push_back(ch);

			if (previousWindowQualified)
			{
				// if ch == window.front, then current window minus front is also qualified
				if (ch == window.front())
				{
					window.pop_front();
					//remove front from the window as long as the front is not needed, keep front always needed
					while (!window.empty())
					{

						auto front = window.front();
						// update inUse and notUsed
						auto itInUse = inUse.find(front);
						// remove it only when it's not needed at all
						if (itInUse == inUse.end())
						{
							window.pop_front();
							inUse.erase(itInUse); // must use it here to avoid remove multiple ones
							notUsed.emplace(front);
						}
						else
						{
							// stop at useful char
							break;
						}
					}
				}
			}

			// update inUse and notUsed
			auto it = notUsed.find(ch);
			if (it != notUsed.end())
			{
				notUsed.erase(it);
				inUse.emplace(ch);
			}

			// if we have the qualified substring
			if (notUsed.empty())
			{
				int lenWindow = window.size();
				if (lenWindow < minLenWindow)
				{
					// update
					minLenWindow = lenWindow;
					result = string(window.begin(), window.end());
				}
			}

			//remove front from the window as long as the front is not needed, keep front always needed
			while (!window.empty())
			{

				auto front = window.front();
				// update inUse and notUsed
				auto itInUse = inUse.find(front);
				// remove it only when it's not needed at all
				if (itInUse == inUse.end())
				{
					window.pop_front();
					inUse.erase(itInUse); // must use it here to avoid remove multiple ones
					notUsed.emplace(front);
				}
				else
				{
					// stop at useful char
					break;
				}
			}
		}
		return result;
	}

	static void Test()
	{
		string s("aadacadc");
		string t("adc");
		cout << minWindow(s, t) << endl;	// should be 8
	}
}