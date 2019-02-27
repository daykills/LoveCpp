/*
41. First Missing Positive
Total Accepted: 57850 Total Submissions: 246565 Difficulty: Hard
Given an unsorted integer array, find the first missing positive integer.

For example,
Given [1,2,0] return 3,
and [3,4,-1,1] return 2.

Your algorithm should run in O(n) time and uses constant space.
*/
#include <algorithm>
#include "Common.h"

namespace FirstMissingPositive
{
  int firstMissingPositive(vector<int>& nums)
  {
    const int n = nums.size();
    for (auto i = 0; i < n; i++)
    {
      // if already at right place
      if (nums[i] == i + 1)
        continue;

      int curNum = nums[i];
      nums[i] = 0;

      // keep placing the number to the right place      
      while (curNum <= n && curNum >= 1)
      {
        int nextI = curNum - 1; // must be within range
        int temp = nums[nextI];
        
        // the spot is already taken by right number
        if (temp == curNum) break;

        nums[nextI] = curNum;
        curNum = temp;
      }
    }
    for (auto i = 0; i < n; i++)
    {
      if (nums[i] != i + 1) return i + 1;
    }
    return n + 1;
  }
  static int Test(vector<int>& nums)
  {
    for (auto num : nums)
    {
      cout << num << " ";
    }
    cout << endl;

    return firstMissingPositive(nums);
  }
}