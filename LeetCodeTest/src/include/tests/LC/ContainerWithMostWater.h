/*
11. Container With Most Water
Total Accepted: 70828 Total Submissions: 207743 Difficulty: Medium
Given n non-negative integers a1, a2, ..., an, where each represents a point at coordinate (i, ai). n vertical lines are drawn such that the two endpoints of line i is at (i, ai) and (i, 0). Find two lines, which together with x-axis forms a container, such that the container contains the most water.

Note: You may not slant the container.
*/

#include <iostream>
#include <queue>
#include <algorithm>
#include "Common.h"

namespace ContainerWithMostWater
{
  int maxArea(vector<int>& height)
  {
    int len = height.size(), low = 0, high = len - 1;
    int maxArea = 0;
    while (low < high)
    {
      maxArea = max(maxArea, (high - low) * min(height[low], height[high]));
      if (height[low] < height[high]) {
        low++;
      }
      else {
        high--;
      }
    }
    return maxArea;
  }

  static int Test()
  {
    vector<int> nums{ 8, 2, 5, 6, 3, 10000, 9999 };
    for (auto i : nums)
      cout << i << " ";
    cout << endl;
    cout << maxArea(nums) << endl;
    return 0;
  }
}