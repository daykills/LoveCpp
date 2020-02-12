/*
71. Simplify Path My Submissions Question
Total Accepted: 48640 Total Submissions: 224436 Difficulty: Medium
Given an absolute path for a file (Unix-style), simplify it.

For example,
path = "/home/", => "/home"
path = "/a/./b/../../c/", => "/c"
click to show corner cases.

Corner Cases:
Did you consider the case where path = "/../"?
In this case, you should return "/".
Another corner case is the path might contain multiple slashes '/' together, such as "/home//foo/".
In this case, you should ignore redundant slashes and return "/home/foo".
*/

#include <iostream>
#include <stack>
#include <algorithm>
#include "Common.h"

namespace SimplifyPath
{
	string simplifyPath(string path)
	{
		int lastSlash = 0;
		vector<string> paths;
		int n = path.length();
		for (int i = 0; i <= n; i++)
		{
			// if meet a slash or end of string, check whether we have a new substring
			if (i == n || path[i] == '/')
			{
				// if the substring is not empty
				if (i >= lastSlash + 2)
				{
					auto substr = path.substr(lastSlash + 1, i - lastSlash - 1);
					// pop the last folder if it's ".."
					if (substr == "..")
					{
						if (!paths.empty()) paths.pop_back();
					}
					else if (!substr.empty() && substr != ".")
					{
						paths.emplace_back(move(substr));
					}
				}
				lastSlash = i;
			}
		}
		string result;
		for (auto& foldername : paths)
		{
			result.append("/" + move(foldername));
		}
		if (result.empty()) return "/";
		return result;
	}

	int Test()
	{
		string str("/.");

		cout << str << ": " << simplifyPath(str) << endl;
		return 0;
	}
}
