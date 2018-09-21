#pragma once
/*
135. Candy My Submissions Question
Total Accepted: 47846 Total Submissions: 218577 Difficulty: Hard
There are N children standing in a line. Each child is assigned a rating value.

You are giving candies to these children subjected to the following requirements:

Each child must have at least one candy.
Children with a higher rating get more candies than their neighbors.
What is the minimum candies you must give?
*/

#include <iostream>
#include <queue>
#include <algorithm>
#include "Common.h"

namespace JumpGame2
{
	int jumpBfs(vector<int>& nums)
	{
		int n = nums.size();
		if (n < 2) return 0;
		// queue to store the location and step
		queue<pair<int, int>> q;

		// enqueue for the first move
		for (auto i = 1; i <= nums[0]; i++)
			q.emplace(0, i);

		unordered_set<int> visited;

		int step = 1;
		while (!q.empty())
		{
			int nMoves = q.size();
			for (auto i = 0; i < nMoves; i++)
			{
				auto move = q.front();
				q.pop();

				auto pos = move.first + move.second;
				// we can reach the end from move. return
				if (pos >= n - 1) return step;
				// if already visited, skip
				if (visited.find(pos) != visited.end()) continue;
				// mark pos visited
				visited.emplace(pos);
				// enqueue all moves
				for (auto nextStep = nums[pos]; nextStep >= 1; nextStep--)
				{
					q.emplace(pos, nextStep);
				}
			}
			step++;
		}
		return step;
	}

	int jump(vector<int>& nums)
	{
		int n = nums.size();
		if (n < 2) return 0;

		int step = 0;
		int lastJump = -1;
		// maxJump keeps the maxium reach so far
		int maxJump = 0;
		for (auto i = 0; i < n; i++)
		{
			int maxNext = i + nums[i];
			if (maxNext >= n - 1) return ++step;
			maxJump = max(maxJump, maxNext);

			// getting out of the range of last jump
			if (i >= lastJump)
			{
				lastJump = maxJump;
				step++;
			}
		}
		return step;
	}

	static void Test()
	{
		vector<int> jumps{ 1, 5, 0, 11, 8, 2, 1, 4, 1, 0, 3, 5, 1, 0, 0, 3 };
		for (auto i : jumps)
			cout << i << " ";
		cout << endl;
		cout << "result greedy: " << jump(jumps) << endl;
		cout << "result bfs: " << jumpBfs(jumps) << endl;
	}
}