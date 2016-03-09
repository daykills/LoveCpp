/*
123. Best Time to Buy and Sell Stock III
https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/

Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete at most two transactions.

Note:
You may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).
*/

#include <iostream>
#include "Common.h"

namespace BestTimeToBuyAndSellStock3
{
  int maxProfit(vector<int>& prices)
  {
    int n = prices.size();
    if (n <= 1) return 0;

    // if only allow one transaction, we can calculate the maximum profit of (0 ~ i) and (i+1 ~ n-1). Find the maximum sum.

    // maximum profit and minimum price within the first i days
    vector<int> p(n, 0);
    int min = prices[0];
    for (int i = 1; i < n; i++)
    {
      // update minimum price
      min = std::min(min, prices[i]);
      p[i] = std::max(prices[i] - min, p[i - 1]);
    }

    // reverse order, find the max p (from last day to i day).
    vector<int> p_reverse(n, 0);
    // need to keep track of max now
    int max = prices[n - 1];
    for (int i = n - 2; i >= 0; i--)
    {
      // update minimum price
      max = std::max(max, prices[i]);
      p_reverse[i] = std::max(max - prices[i], p_reverse[i + 1]);
    }

    // find the max sum
    int maxP = p[n - 1];  // skip reverse trade
    for (int i = 0; i < n - 1; i++)
    {
      maxP = std::max(p[i] + p_reverse[i + 1], maxP);
    }
    return maxP;
  }

  static bool Test()
  {
    vector<int> nums{ 3, 2, 6, 5, 0, 3 };
    for (auto i : nums)
      cout << " " << i;
    cout << endl;

    cout << "Best profit: " << maxProfit(nums) << endl;

    return false;
  }
}