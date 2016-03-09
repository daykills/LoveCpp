/*
Given two lists of integers, write a function that returns a list that contains only the intersection
(elements that occur in both lists) of the two lists. The returned list should only contain unique integers, no duplicates.
For example, [4, 2, 73, 11, -5] and [-5, 73, -1, 9, 9, 4, 7] would return the list [-5, 4, 73] in no particular order.
*/

#include <iostream>
#include <queue>
#include <unordered_set>
#include <algorithm>
#include "Common.h"

namespace ArrayIntersections
{
  // find all unique triplets in the nums with index >= start_index
  vector<int> findIntersections(vector<int>& nums1, vector<int>& nums2)
  {
    unordered_set<int> map;
    for (auto num : nums1)
    {
      if (map.find(num) == map.end())
      {
        map.emplace(num);
      }
    }
    vector<int> result;
    for (auto num : nums2)
    {
      if (map.find(num) != map.end())
      {
        result.emplace_back(num);
      }
    }
    return result;
  }

  void Test()
  {
    vector<int> nums1{ 2, 7, 5, 4, 1, 1 };
    vector<int> nums2{ 0, 2, 3, 4, 1 };

    for (auto i : nums1)
      cout << " " << i;
    cout << endl;

    for (auto i : nums2)
      cout << " " << i;
    cout << endl;

    auto result = findIntersections(nums1, nums2);
    for (auto i : result)
      cout << " " << i;
    cout << endl;
  }
}