#pragma once
/*
You're given an array of student scores.
If a student has higher score than both his left and right students, he's score +1; if his score is lower than left and right, he's score -1.
Only the first and last students don't get score adjustment.
Please find out the final score of all the students
*/

#include <iostream>
#include <climits>
#include <string>
#include <vector>
using namespace std;

namespace StudentScores
{
	vector<int> solution2(vector<int> &scores) {
		// write your code in C++11 (g++ 4.8.2)
		int n = scores.size();

		// store which students may have score revised
		unordered_set<int> updateList;
		// first time, all the students will update
		for (auto i = 1; i < n - 1; i++)
		{
			updateList.emplace(i);
		}

		auto pre = scores;
		while (updateList.size() > 0)
		{
			auto cur = pre;
			unordered_set<int> newUpdate;
			for (auto i : updateList)
			{
				if (pre[i - 1] > pre[i] && pre[i + 1] > pre[i])
				{
					cur[i]++;
				}
				else if (pre[i - 1] < pre[i] && pre[i + 1] < pre[i])
				{
					cur[i]--;					
				}
				else
				{
					continue;
				}
				newUpdate.emplace(i);
				if (i - 1 > 0) newUpdate.emplace(i - 1);
				if (i + 1 < n - 1) newUpdate.emplace(i + 1);
			}
			updateList = newUpdate;
			pre = move(cur);
		}
		return pre;
	}

	int Test() {
		vector<int> input{ 1,6,3,4,3,5 };
		solution2(input);
		return 0;
	}
}