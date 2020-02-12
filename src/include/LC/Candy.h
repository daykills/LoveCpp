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

namespace Candy
{
  int candy(vector<int>& ratings)
  {
    int n = ratings.size();
    if (n <= 1) return n;
    int totalCandies = 0;
    // they all start with one
    vector<int> candies(n, 1);
    // adjust from left to right
    for (int i = 0; i < n - 1; i++)
    {
      if (ratings[i] < ratings[i + 1])
        candies[i + 1] = candies[i] + 1;
    }
    // now one direction is good, start from right to left
    int total = candies[n - 1];
    for (int i = n - 1; i > 0; i--)
    {
      // if the left guy has high rating, he should have more than right
      if (ratings[i - 1] > ratings[i])
        candies[i - 1] = max(candies[i] + 1, candies[i - 1]);
      total += candies[i - 1];
    }
    return total;
  }
  static void Test()
  {
    vector<int> ratings{2, 2};
    for (auto i : ratings)
      cout << " " << i;
    cout << endl;
    cout << "result: " << candy(ratings) << endl;
  }
}