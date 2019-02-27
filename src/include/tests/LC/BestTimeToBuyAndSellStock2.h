/*
122. Best Time to Buy and Sell Stock II My Submissions Question
Total Accepted: 78389 Total Submissions: 189031 Difficulty: Medium
Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit.
You may complete as many transactions as you like (ie, buy one and sell one share of the stock multiple times).
However, you may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).
*/

#include <iostream>
#include "Common.h"

namespace BestTimeToBuyAndSellStock2
{
  int maxProfit(vector<int>& prices)
  {
    int n = prices.size();
    if (n <= 1) return 0;

    // max profit within the first i days
    int p = 0;
    // Greedy method is applicable.
    // For example, prices are 1 2 3, then we can buy 1 sell 2 and buy 2 sell 3 (sell 2 and buy 2 is equivalent to do nothing).
    for (auto i = 1; i < n; i++)
    {
      auto delta = prices[i] - prices[i - 1];
      if (delta > 0)
      {
        p += delta;
      }
    }
    return p;
  }

  static bool Test()
  {
    vector<int> nums{ 11, 14, 15, 11, 12, 16, 10, 12, 8, 12, 10 };
    for (auto i : nums)
      cout << " " << i;
    cout << endl;
    cout << "Best profit: " << maxProfit(nums) << endl;

    return false;
  }
}