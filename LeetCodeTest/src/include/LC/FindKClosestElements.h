/*
Find k closest elements to a given value
Given a sorted array arr[] and a value X, find the k closest elements to X in arr[].
Examples:

Input: K = 4, X = 35
arr[] = {12, 16, 22, 30, 35, 39, 42, 45, 48, 50, 53, 55, 56}
Output: 30 39 42 45

Note that if the element is present in array, then it should not be in output, only the other closest elements are required.
*/

#include <iostream>
#include <queue>
#include <set>
#include <algorithm>
#include "Common.h"

namespace FindKClosestElements
{
  ////////////////////////////////////////////////////////////////////////////////
  // use heap, then we don't require the array to be sorted
  // define a distance and its comparator
  struct Distance
  {
    Distance(int _distance, int _index) : distance(_distance), index(_index) {}
    int distance;
    int index;    
  };
  //Overload the < operator.
  bool operator < (const Distance& d1, const Distance &d2)
  {
    return d1.distance < d2.distance;
  }

  vector<int> findKClosestElements(vector<int> arr, int x, int k)
  {
    if (k == 0) return vector<int>();
    int n = arr.size();
    if (n == 0 || k >= n) return move(arr);

    //priority_queue<Distance, vector<Distance>, less<vector<Distance>::value_type> > closest;
    priority_queue<Distance> closest;

    for (int i = 0; i < n; i++)
    {
      auto distance = abs(arr[i] - x);
      // if the heap is not full
      if ((int)closest.size() < k)
      {
        closest.push(Distance(distance, i));
        continue;
      }
      // if distance is smaller than the max of closest, pop out the top
      if (distance < closest.top().distance)
      {
        closest.pop();
        closest.push(Distance(distance, i));
      }
    }

    vector<int> result;
    while(!closest.empty())
    {
      result.emplace_back(arr[closest.top().index]);
      closest.pop();
    }
    return result;
  }

  ////////////////////////////////////////////////////////////////////////////////
  // since it's already sorted, we can find the first number that's not less than x, and search on both sides
  vector<int> findKClosestElements2(vector<int> arr, int x, int k)
  {
    if (k == 0) return vector<int>();
    int n = arr.size();
    if (n == 0 || k >= n) return move(arr);

    // binary search to find the first number that's not less than x
    int lo = 0, hi = n - 1;
    while (lo < hi)
    {
      int mid = (lo + hi) >> 1;
      if (arr[mid] < x)
      {
        lo = mid + 1;
      }
      else
      {
        hi = mid;
      }
    }
    // finding the number cost O(log n), cost of the rest: O(k)
    if (arr[lo] < x) // all numbers are smaller than x, return highest k numbers
      return vector<int>(arr.begin() + n - k, arr.end());

    // if all numbers are bigger than x
    if (lo == 0)
      return vector<int>(arr.begin(), arr.begin() + k);
    
    vector<int> result(k);
    int count = 0;
    // lo is the first not-less-than-x position. start search from this point.
    int start = lo;
    hi = start;
    lo = hi - 1;    
    while (count < k)
    {
      // if one side has been reached boundary
      if (lo < 0)
      {
        result[count] = arr[hi];
        count++;
        hi++;
        continue;
      }
      if (hi >= n)
      {
        result[count] = arr[lo];
        count++;
        lo--;
        continue;
      }
      // compare distance, and add numbers to result
      if (arr[hi] - x < x - arr[lo])
      {
        result[count] = arr[hi];
        hi++;
      }
      else
      {
        result[count] = arr[lo];
        lo--;
      }
      count++;
    }
    return result;
  }

  static void Test()
  {
    vector<int> arr{ 12, 16, 22, 30, 35, 39, 42, 45, 48, 50, 53, 55, 56 };
    //vector<int> arr{ 12, 16, 22, 30, 35, 39, 42, 45, 48, 50, 53, 55, 56 };

    for (auto i : arr)
      cout << " " << i;
    cout << endl;

    auto result = findKClosestElements(arr, 35, 4);
    
    for (auto i : result)
      cout << " " << i;
    cout << endl;
  }
}