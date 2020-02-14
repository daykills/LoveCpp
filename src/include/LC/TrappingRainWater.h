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

namespace TrappingRainWater
{
int trap(vector<int>& height) {
    if (height.size() < 3) return 0;
    auto itMax = std::max_element(height.begin(), height.end());
    auto iMax = distance(height.begin(), itMax);
    auto water = 0;
    auto lastHeight = height[0];
    // for lower part
    for (auto i = 1; i < iMax; i++) {
        if (height[i] >= lastHeight) {
            lastHeight = height[i];
        } else {
            water += lastHeight - height[i];
        }
    }
    // for higher part
    lastHeight = height.back();
    for (auto i = height.size() - 2; i > iMax; i--) {
        if (height[i] >= lastHeight) {
            lastHeight = height[i];
        } else {
            water += lastHeight - height[i];
        }
    }
    return water;
}

int trapStack(vector<int>& height) {
    auto n = height.size();
    stack<int> s;
    int water = 0;
    for (auto i = 0; i < n; i++) {
        // down-ward slop, push to stack
        if (s.empty() || height[s.top()] >= height[i]) {
            s.push(i);
            continue;
        }
        // ditch found
        while (!s.empty() && height[s.top()] <= height[i]) {
            auto t = s.top();
            s.pop();
            // false ditch
            if (s.empty())
                break;
            auto waterLevel = min(height[i], height[s.top()]);
            auto bottom = height[t];
            water += (waterLevel - bottom) * (i - s.top() - 1);
        }
    }
    return water;
}

int trapStack_old(vector<int>& height) {
    stack<int> st;
    int i = 0, res = 0, n = height.size();
    while (i < n) {
        if (st.empty() || height[i] <= height[st.top()]) {
            st.push(i++);
        } else {
            int t = st.top(); st.pop();
            if (st.empty()) continue;
            int waterLevel = min(height[i], height[st.top()]);
            int bottomLevel = height[t];
            res += (waterLevel - bottomLevel) * (i - st.top() - 1);
        }
    }
    return res;
}

static void Test()
{
    vector<int> heights { 0,1,0,2,1,0,1,3,2,1,2,1 };
    for (auto i : heights)
        cout << " " << i;
    cout << endl;
    cout << "result: " << trapStack(heights) << endl;
}
}
