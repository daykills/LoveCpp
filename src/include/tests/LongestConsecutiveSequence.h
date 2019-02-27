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

  // count sort
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
  int longestConsecutive(vector<int>& nums)
  {
	  unordered_set<int> table(nums.begin(), nums.end());

	  int maxLen = 0;
	  // pick one element, and count its length; remove elements by the way
	  while (!table.empty())
	  {
		  auto cur = *(table.begin());
		  table.erase(table.begin());
		  int count = 1;

		  // check the down side
		  int num = cur - 1;
		  for (auto it = table.find(num); it != table.end(); )
		  {
			  table.erase(it);
			  it = table.find(--num);
			  count++;
		  }

		  // check the upper side
		  num = cur + 1;
		  for (auto it = table.find(num); it != table.end();)
		  {
			  table.erase(it);
			  it = table.find(++num);
			  count++;
		  }
		  maxLen = max(maxLen, count);
	  }
	  return maxLen;
  }
  /////////////////////////////////////////////
  int longestConsecutive2(vector<int>& nums)
  {
	  // hash table to save number and its index in the continous sub-sequence
	  unordered_map<int, int> table;
	  for (auto num : nums)
	  {
		  // update the order of num
		  table[num]++;
		  // update order of upper nums of num
		  int upper = num + 1;
		  while (table.find(upper) != table.end())
		  {
			  table[upper++]++;
		  }
	  }
	  int maxLen = 0;
	  for (auto& pair : table)
	  {
		  maxLen = max(maxLen, pair.second);
	  }
	  return maxLen;
  }
  void Test()
  {
	  vector<int> nums{ 1,0,-1 };
	  cout << "result: " << longestConsecutive(nums) << endl;
  }
}