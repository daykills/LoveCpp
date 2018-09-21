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

namespace BestTimeToBuyAndSellStockWithCooldown
{
	int maxProfit(vector<int>& prices)
	{
		int n = prices.size();
		if (n < 2) return 0;

		// minimum price till i
		vector<int> minPrices(n);
		minPrices[0] = prices[0];
		for (int i = 1; i < n; i++)
		{
			minPrices[i] = min(prices[i], minPrices[i - 1]);
		}
		// dp[i] last sell at i, the max profit
		vector<int> dp(n, 0);
		// no possible to sell at 0
		dp[0] = INT_MIN;
		dp[1] = max(0, prices[1] - prices[0]);
		// last sell at i; second last sell at j (0<j<i)
		for (auto i = 2; i < n; i++)
		{
			auto profitOneTrade = prices[i] - minPrices[i - 1];
			auto profitMultipleTrades = INT_MIN;
			// second last sell at (1:i-2)
			for (auto j = 1; j < i - 1; j++)
			{
				auto profit = dp[j];
				auto min1 = prices[j + 2];
				for (auto k = j + 2; k < i; k++)
					min1 = min(min1, prices[k]);
				profitMultipleTrades = max(profitMultipleTrades, prices[i] - min1 + profit);
			}
			dp[i] = max(profitMultipleTrades, profitOneTrade);
		}
		int maxProfit = 0;
		for (auto i = 1; i < n; i++)
		{
			maxProfit = max(maxProfit, dp[i]);
		}
		return maxProfit;
	}

	static bool Test()
	{
		//vector<int> nums{ 106,373,495,46,359,919,906,440,783,583,784,73,238,701,972,308,165,774,990,675,737,990,713,157,211,880,961,132,980,136,285,239,628,221,948,939,28,541,414,180,171,640,297,873,59,814,832,611,868,633,101,67,396,264,445,548,257,656,624,71,607,67,836,14,373,205,434,203,661,793,45,623,140,67,177,885,155,764,363,269,599,32,228,111,102,565,918,592,604,244,982,533,781,604,115,429,33,894,778,885,145,888,577,275,644,824,277,302,182,94,479,563,52,771,544,794,964,827,744,366,548,761,477,434,999,86,1000,5,99,311,346,609,778,937,372,793,754,191,592,860,748,297,610,386,146,220,7,113,657,438,482,700,158,884,877,964,777,139,809,489,383,92,581,970,899,947,864,443,490,825,674,906,402,270,416,611,949,476,775,899,837,796,227,232,226,11,266,889,215,6,182,430,5,706,994,128,359,841,439,263,491,689,638,485,763,695,135,800,763,54,569,387,112,316,193,675,546,531,954,571,208,282,557,892,469,875,765,592,374,276,892,843,625,180,249,292,477,882,837,112,46,667,187,93,418,790,903,12,978,510,647,446,597,958,678,897,420,907,256,170,669,920,711,635,995,259,994,634,583,175,380,435,942,739,921,132,455,986,567,464,301,10,579,84,745,717,588,414,375,319,770,310,510,521,88,445,59,460,120,765,480,441,169,374,180,947,179,346,490,417,149,140,577,624,427,238,341,686,623,228,672,859,372,938,567,141,133,671,255,997,272,591,115,340,692,531,235,123,677,980,31,774,135,194,956,723,779,375,546,59,695,616,416,362,38,145,782,184,418,806,444,177,360,485,941,998,85,840,740,545,49,570,17,824,845,749,177,727,238,656,787,425,473,323,683,578,442,436,444,595,367,44,467,93,507,949,598,579,471,1,347,982,232,878,217,845,777,284,527,529,100,482,456,814,457,251,494,419,922,139,706,384,954,365,680,70,810,764,820,992,622,29,697,294,553,655,63,934,827,157,680,812,729,486,403,151,988,926,460,193,294,423,774,715,906,957 };
		vector<int> nums{ 1, 3, 0, 5, 4, 2 };
		for (auto i : nums)
			cout << " " << i;
		cout << endl;

		cout << "Best profit: " << maxProfit(nums) << endl;

		return false;
	}
}