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
int candy(vector<int>& ratings) {
    auto n = ratings.size();
    if (n <= 1) return n;
    // start with 1 candy each
    vector<int> candies(n ,1);
    // make sure it's good from left to right
    for (auto i = 1; i < n; i++) {
        if (ratings[i] > ratings[i -1])
            candies[i] = candies[i - 1] + 1;
    }
    // now from right to left
    for (auto i = n - 1; i >= 1; i--) {
        if (ratings[i - 1] > ratings[i])
            candies[i - 1] = max(candies[i - 1], candies[i] + 1);
    }
    return accumulate(candies.begin(), candies.end(), 0);
}

void Test()
{
    vector<int> ratings = { 1, 2, 2 };
    for (auto i : ratings)
        cout << " " << i;
    cout << endl;
    cout << "result: " << candy(ratings) << endl;
}
}
