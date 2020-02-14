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

int largestRectangleArea(vector<int>& height) {
    int res = 0;
    for (int i = 0; i < height.size(); ++i) {
        // no need to check the up-ward slops
        if (i + 1 < height.size() && height[i] <= height[i + 1]) {
            continue;
        }
        int minH = height[i];
        for (int j = i; j >= 0; --j) {
            minH = min(minH, height[j]);
            int area = minH * (i - j + 1);
            res = max(res, area);
        }
    }
    return res;
}

static void Test()
{
    vector<int> heights = { 2,1,5,6,5,3 };
    std::cout << largestRectangleArea(heights) << std::endl;
}
}
