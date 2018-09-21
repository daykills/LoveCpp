/*
Write a function to test if a string matches a pattern (string).

string:     input string to test
pattern:   match mask that may contain wildcards like ? and *
A ? matches any single character
A * matches zero or more characters

Examples:
String: abcdd            abcdd                     abcdd                 abcde                 abcde
Pattern: abcdd           afcdde                    ab?d                   a*c*                    *fe
Result: match           NOT match                 NOT match              match               NOT match

*/

#include <iostream>
#include <queue>
#include <memory>
#include <cassert>
#include <algorithm>
#include <vector>
#include "Common.h"

namespace WildcardMatching
{
	// dfs is not gonna be fast enough
	void dfs(const string& pattern, int pos_pattern, const string& str, int pos_str, bool& result)
	{
		// base condition: if pattern == path, return true;
		if (pattern.length() == pos_pattern)
		{
			// if the pattern ends with * or str just happens to end, the result is true
			result = (pattern.back() == '*' || str.length() == pos_str);
			return;
		}

		// if str already reaches end, but pattern still not finish, it fails
		if (str.length() == pos_str) return;

		// current char of pattern to match
		char ch = pattern[pos_pattern];
		if (ch == '?')
		{
			dfs(pattern, pos_pattern + 1, str, pos_str + 1, result);
		}
		else if (ch == '*')
		{
			for (auto pos = pos_str; pos < (int)str.length(); pos++)
			{
				// find next non-star character. **** can be treated as single *
				auto nextNonStar = pos_pattern + 1;
				while (nextNonStar < (int)pattern.length() && pattern[nextNonStar] == '*') nextNonStar++;

				dfs(pattern, nextNonStar, str, pos, result);
				if (result) return;
			}
		}
		else
		{
			if (ch == str[pos_str])
			{
				dfs(pattern, pos_pattern + 1, str, pos_str + 1, result);
			}
			else
			{
				return;
			}
		}
	}

	bool isMatchDfs(const string& str, const string& pattern)
	{
		bool result = false;
		dfs(pattern, 0, str, 0, result);
		return result;
	}

	void Test()
	{
		/*
		Examples:
		String: abcdd            abcdd                     abcdd                 abcde                 abcde		aaabbbaabaaaaababaabaaabbabbbbbbbbaabababbabbbaaaaba
		Pattern: abcdd           afcdde                    ab?d                   a*c*                    *fe		a*******b
		Result: match           NOT match                 NOT match              match               NOT match
		*/
		string str = "aaabbbaabaaaaababaabaaabbabbbbbbbbaabababbabbbaaaaba";
		string pattern = "a*******b";

		cout << "string: " << str << " pattern: " << pattern << " match: " << isMatchDfs(str, pattern) << endl;
	}
}