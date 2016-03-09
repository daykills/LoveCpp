/*
128. Longest Consecutive Sequence
Total Accepted: 58283 Total Submissions: 186411 Difficulty: Hard
Given an unsorted array of integers, find the length of the longest consecutive elements sequence.

For example,
Given [100, 4, 200, 1, 3, 2],
The longest consecutive elements sequence is [1, 2, 3, 4]. Return its length: 4.

Your algorithm should run in O(n) complexity.
*/
#include <iostream>
#include <unordered_set>
#include "Common.h"

namespace LongestConsecutiveSequence
{
  //////////////////////////////////////////////////////////////////
  //-9 ---> index is 0 //9 --->index is 18
  int getBucket(int n, int base)
  {
    return n / base % 10 + 9;
  }

  //按照个位(base=1)、十位(base=10)排序
  void countSort(vector<int> &num, int base)
  {
    using namespace std;
    vector<int> numback(num);
    vector<int> counts(19, 0);
    for (int i = 0; i < (int)numback.size(); i++)
    {
      int bucket = getBucket(numback[i], base);
      ++counts[bucket];
    }
    for (int j = 1; j < (int)counts.size(); j++)
      counts[j] += counts[j - 1];
    for (int j = (int)numback.size() - 1; j >= 0; j--)
    {
      int index = getBucket(numback[j], base);
      num[counts[index] - 1] = numback[j];
      counts[index]--;
    }
  }
  //O(N) sort, then scan to get the result
  void radixSort(vector<int> &num)
  {
    int max = INT_MIN;
    for (int i = 0; i < (int)num.size(); i++)
      max = std::max(max, abs(num[i])); //!! abs
    int base = 1;
    while (max / base)
    {
      countSort(num, base);
      base *= 10;
    }
  }
  //ref https://oj.leetcode.com/discuss/2731/this-problem-has-a-o-n-solution?show=4368#a4368
  int Test(vector<int> &num)
  {
    if (num.size() <= 1) return num.size();
    radixSort(num);
    int max = 1;
    int len = 1;
    for (int i = 1; i < (int)num.size(); i++)
    {
      if (num[i] == num[i - 1])//!!
        continue;
      if (num[i] == num[i - 1] + 1)
        len++;
      else
      {
        max = std::max(max, len);
        len = 1;
      }
    }
    return std::max(max, len);
  }
  //////////////////////////////////////////////////////////////////
  int TestOwn2(vector<int>& nums)
  {
    int result = 0;
    unordered_set<int> map(nums.begin(), nums.end());
    while (!map.empty())
    {
      // every number that's inspected is no longer needed
      int num = *map.begin();
      map.erase(map.begin());
      int len = 1;
      // find the down-side length
      int nextNum = num;
      while (true)
      {
        auto iter = map.find(--nextNum);
        if (iter == map.end()) break;
        map.erase(iter);
        len++;
      }
      // find the up-side length
      nextNum = num;
      while (true)
      {
        auto iter = map.find(++nextNum);
        if (iter == map.end()) break;
        map.erase(iter);
        len++;
      }
      result = max(result, len);
    }
    return result;
  }

  int TestMyOwnMethod(vector<int>& nums)
  {
    if (0 == nums.size()) return 0;
    // longest length starts with 1
    int longestLen = 1;
    // key is the number, value is the length of consecutive up to this number
    unordered_map<int, int> map;
    for (auto num : nums)
    {
      map.emplace(num, 1);
    }
    for (auto num : nums)
    {
      // there is number prior to his
      if (map.find(num - 1) != map.end())
      {
        map[num] = map[num - 1] + 1;
        if (map[num] > longestLen) longestLen = map[num];
      }
      else
      {
        // update counts of numbers after num
        int numNext = num;
        while (map.end() != map.find(numNext + 1))
        {
          numNext++;
          map[numNext] = map[numNext - 1] + 1;
        }        
        if (numNext != num && map[numNext] > longestLen) longestLen = map[numNext];
      }
    }
    return longestLen;
  }
}