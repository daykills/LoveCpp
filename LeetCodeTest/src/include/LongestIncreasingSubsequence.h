/*
https://leetcode.com/problems/longest-increasing-subsequence/

300. Longest Increasing Subsequence

Given an unsorted array of integers, find the length of longest increasing subsequence.

For example,
Given [10, 9, 2, 5, 3, 7, 101, 18],
The longest increasing subsequence is [2, 3, 7, 101], therefore the length is 4. Note that there may be more than one LIS combination, it is only necessary for you to return the length.

Your algorithm should run in O(n2) complexity.

Follow up: Could you improve it to O(n log n) time complexity?

*/

#include <string>
#include <iostream>
#include "Common.h"

namespace LongestIncreasingSubsequence
{
  static int Test(const vector<int>& data)
  {
    using namespace std;
    
    int sizeOfSeq = data.size();
    int longestLength = 0;
    vector<int> lis(sizeOfSeq);
    for (int i = 0; i < sizeOfSeq; i++)
    {      
      lis[i] = 1;
      // Assume the second last element is at j
      for (int j = 0; j <= i - 1; j++)
      {
        // If data[i] is bigger, the new length is lis[j] + 1
        if (data[i] > data[j] && lis[i] < lis[j] + 1)
        {
          lis[i] = lis[j] + 1;
        }
      }
      if (lis[i] > longestLength)
      {
        longestLength = lis[i];
      }
    }

    return longestLength;
  }
}