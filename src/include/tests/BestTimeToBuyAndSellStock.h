/*
121. Best Time to Buy and Sell Stock
https://leetcode.com/problems/best-time-to-buy-and-sell-stock/

Say you have an array for which the ith element is the price of a given stock on day i.

If you were only permitted to complete at most one transaction (ie, buy one and sell one share of the stock), design an algorithm to find the maximum profit.
*/

#include <iostream>
#include "Common.h"

namespace BestTimeToBuyAndSellStock
{
  int maxProfit(vector<int>& prices)
  {
    int n = prices.size();
    if (n <= 1) return 0;
    
    // maximum profit and minimum price within the first i days
    int p = 0, min = prices[0];
    // you have to buy before sell; also, need to keep track of the minimum price when scanning - though the minimum price may not be used eventually
    for (int i = 1; i < n; i++)
    {
      // update minimum price
      min = std::min(min, prices[i]);
      p = std::max(prices[i] - min, p);
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