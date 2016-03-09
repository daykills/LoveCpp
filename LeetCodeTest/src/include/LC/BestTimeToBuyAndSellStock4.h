/*
188. Best Time to Buy and Sell Stock IV My Submissions Question
Total Accepted: 22424 Total Submissions: 104344 Difficulty: Hard
Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete at most k transactions.

Note:
You may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).
*/

#include <iostream>
#include <queue>
#include <stack>
#include "Common.h"

namespace BestTimeToBuyAndSellStock4
{
  int maxProfitInf(vector<int> &prices) {
    int buyin = INT_MAX, profit = 0;
    for (auto & price : prices) {
      if (price > buyin) profit += price - buyin;
      buyin = price;
    }
    return profit;
  }

  int maxProfit(int k, vector<int> &prices) {
    if (k == 0 || prices.empty()) return 0;
    // Max profit by k transaction from 0 to i
    const int n = prices.size();
    if (k >= n / 2) return maxProfitInf(prices);

    // balance - the balance with at most j transactions with item 0 to i
    // assume the last transaction has only buy.
    // so the initial all started at -prices[0], while i=0.
    vector<int> balance(k + 1, -prices[0]);
    // profit - the profit with at most j transactions with item 0 to i
    // balance + one optimized sell = profit
    vector<int> profit(k + 1, 0);

    for (int i = 0; i < n; ++i)
    {
      // when we have only 0 to i prices
      for (int j = 1; j <= k; ++j) {
        // whether to buy at prices[i], or remain last buy between 0 ~ i-1
        balance[j] = max(profit[j - 1] - prices[i], balance[j]);
        // whether to sell at prices[i]
        profit[j] = max(balance[j] + prices[i], profit[j]);
      }
    }

    return profit[k];
  }

  static bool Test()
  {
    vector<int> nums{ 3, 2, 6, 5, 3, 1, 2, 4 };
    for (auto i : nums)
      cout << " " << i;
    cout << endl;

    cout << "Best profit: " << maxProfit(3, nums) << endl;

    return false;
  }
}