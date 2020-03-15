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
int jump(vector<int>& nums) {
    int n = nums.size();
    if (n < 2)
        return 0;
    // farthest that last jump can reach
    int lastJump = -1;
    // maxReach keeps the maxium reach so far
    int maxReach = 0;
    int step = 0;
    for (auto i = 0; i < n; i++) {
        auto next = i + nums[i];
        maxReach = max(maxReach, next);
        if (maxReach >= n - 1) {
            assert(lastJump < n - 1);
            return ++step;
        }
        // out of last jump range
        if (i >= lastJump) {
            step++;
            lastJump = maxReach;
        }
    }
    return step;
}

static void Test()
{
    vector<int> jumps{ 1, 1, 1, 1 };
    for (auto i : jumps)
        cout << i << " ";
    cout << endl;
    cout << "result greedy: " << jump(jumps) << endl;
}
}
