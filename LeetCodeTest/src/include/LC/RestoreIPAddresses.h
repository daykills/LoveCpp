#pragma once
/*
93. Restore IP Addresses My Submissions Question
Total Accepted: 52646 Total Submissions: 228599 Difficulty: Medium
Given a string containing only digits, restore it by returning all possible valid IP address combinations.

For example:
Given "25525511135",

return ["255.255.11.135", "255.255.111.35"]. (Order does not matter)
*/

#include <iostream>
#include <queue>
#include <memory>
#include <cassert>
#include <algorithm>
#include <vector>
#include "Common.h"

namespace RestoreIPAddresses
{
	void dfsSearch(const string& s, int start, vector<string>& ip, vector<string>& result)
	{
		// base condition: reach the end of the string
		if (start >= (int)s.length())
		{
			if (ip.size() == 4)
			{
				// if address is valid, move ip to result
				string address = ip[0];
				for (int i = 1; i < 4; i++)
				{
					address.append(".");
					address.append(ip[i]);
				}
				result.emplace_back(move(address));				
			}
			return;
		}

		if (ip.size() == 4) return;

		int nextSector = 0;
		// at most three digits
		for (int len = 1; len <= 3; len++)
		{
			if (start + len - 1 >= (int)s.length()) break;			
			nextSector = 10 * nextSector + s[start + len - 1] - '0';
			// if it's too big
			if (nextSector > 255) break;
			ip.emplace_back(s.begin() + start, s.begin() + start + len);
			dfsSearch(s, start + len, ip, result);
			ip.pop_back();
			// if it's zero, no point to search further
			if (nextSector == 0) break;
		}
	}
	vector<string> restoreIpAddresses(string s)
	{
		vector<string> ip;
		vector<string> result;
		dfsSearch(s, 0, ip, result);
		return result;
	}

	void Test()
	{
		string s("111111111111111111111111111");
		auto result = restoreIpAddresses(s);

		cout << "IPs: ";
		for (auto num : result)
			cout << num << endl;
	}
}
