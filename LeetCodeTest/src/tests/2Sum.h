/*
1. Two Sum
Total Accepted: 181184 Total Submissions: 872524 Difficulty: Medium
Given an array of integers, find two numbers such that they add up to a specific target number.

The function twoSum should return indices of the two numbers such that they add up to the target, where index1 must be less than index2. Please note that your returned answers (both index1 and index2) are not zero-based.

You may assume that each input would have exactly one solution.

Input: numbers={2, 7, 11, 15}, target=9
Output: index1=1, index2=2
*/
#include <iostream>
#include <queue>
#include <algorithm>
#include "Common.h"

namespace TwoSum
{
  struct Node
  {
    int index;
    int value;
  };

  static bool cmp(const Node& node1, const Node& node2)
  {
    return node1.value < node2.value;
  }

  vector<int> twoSum(vector<int>& nums, int target)
  {
    int n = nums.size();
    if (n == 0) return vector<int>();

    vector<Node> nodes(n);
    for (auto i = 0; i < n; i++)
    {
      nodes[i].index = i;
      nodes[i].value = nums[i];
    }

    sort(nodes.begin(), nodes.end(), cmp);

    int high = n - 1, low = 0;

    while (high > low)
    {
      auto sum = nodes[low].value + nodes[high].value;
      if (sum == target)
      {
        return vector<int> { nodes[low].index, nodes[high].index };
      }
      else if (sum > target)
      {
        high--;
      }
      else
      {
        low++;
      }
    }

    return vector<int>();
  }

  int Test(vector<int>& nums)
  {
    for (auto i : nums)
      cout << " " << i;
    cout << endl;
    auto result = twoSum(nums, 6);
    for (auto i : result)
      cout << " " << i;
    cout << endl;
    return 0;
  }
}