/*
322. Coin Change My Submissions QuestionEditorial Solution
Total Accepted: 18230 Total Submissions: 73652 Difficulty: Medium
You are given coins of different denominations and a total amount of money amount. Write a function to compute the fewest number of coins that you need to make up that amount. If that amount of money cannot be made up by any combination of the coins, return -1.

Example 1:
coins = [1, 2, 5], amount = 11
return 3 (11 = 5 + 5 + 1)

Example 2:
coins = [2], amount = 3
return -1.

Note:
You may assume that you have an infinite number of each kind of coin.
*/

#include <string>
#include <iostream>
#include "Common.h"

namespace CoinChange
{
	int coinChangeBfs(vector<int>& coins, int amount)
	{
		if (amount == 0) return 0;
		//sort(coins.begin(), coins.end(), std::greater<int>());
		// hist to store the queue of all paths - value for the current amount;
		queue<int> q;
		int count = 0;
		q.push(0);
		while (!q.empty())
		{
			count++;
			// get number of nodes on this layer
			int num = q.size();
			// add all nodes of next layer to queue
			for (auto i = 0; i < num; i++)
			{
				auto curAmount = q.front();
				q.pop();
				for (auto coin : coins)
				{
					auto newAmount = coin + curAmount;
					if (newAmount == amount) return count;
					else if (newAmount > amount) continue;
					q.push(newAmount);
				}
			}
		}
		return -1;
	}

	int coinChange(vector<int>& coins, int amount)
	{
		// dp[i] stands for how many coins needed to reach i
		vector<int> dp(amount + 1, INT_MAX);
		dp[0] = 0;
		for (auto i = 1; i <= amount; i++)
		{
			// assume last coin, go find how many coins needed for (i - coin)
			for (auto coin : coins)
			{
				auto lastAmount = i - coin;
				if (lastAmount < 0 || dp[lastAmount] == INT_MAX) continue;
				dp[i] = min(dp[i], dp[lastAmount] + 1);
			}
		}
		if (dp.back() == INT_MAX) return -1;
		return dp.back();
	}

	static void Test()
	{
		vector<int> coins{ 1, 2, 5 };
		cout << coinChange(coins, 20) << endl;
	}
}