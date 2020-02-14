/*
 84. Largest Rectangle in Histogram
 Given n non-negative integers representing the histogram's bar height where the width of each bar is 1, find the area of largest rectangle in the histogram.
 
 Above is a histogram where width of each bar is 1, given height = [2,1,5,6,2,3].
 
 The largest rectangle is shown in the shaded area, which has area = 10 unit.
 
 Example:
 
 Input: [2,1,5,6,2,3]
 Output: 10
*/

#include <iostream>
#include <queue>
#include <algorithm>
#include <numeric>
#include "Common.h"

namespace LargestRectangleInHistogram
{

int largestRectangleAreaOld(vector<int>& heights) {
    auto n = heights.size();
    if (n == 0) return 0;
    int ans = 0;
    for (auto i = 0; i < n; i++) {
        if (i < n - 1 && heights[i + 1] >= heights[i])
            continue;
        auto minHeight = heights[i];
        auto maxHist = minHeight;
        for (int j = i - 1; j >= 0 && minHeight > 0; j--) {
            minHeight = min(minHeight, heights[j]);
            maxHist = max(maxHist, (i - j + 1) * minHeight);
        }
        ans = max(ans, maxHist);
    }
    return ans;
}

int largestRectangleArea(vector<int>& height) {
    int res = 0;
    stack<int> st;
    height.push_back(0);
    for (int i = 0; i < height.size(); ++i) {
        if (st.empty() || height[st.top()] <= height[i]) {
            st.push(i);
        } else {
            int cur = st.top();
            st.pop();
            // cur
            auto span = st.empty() ? i : i - st.top() - 1;
            res = max(res, height[cur] * span);
            --i;
        }
    }
    return res;
}

static void Test()
{
    vector<int> heights = { 1,2,3,1,2,3,1,2,3 };
    std::cout << largestRectangleArea(heights) << std::endl;
}
}
