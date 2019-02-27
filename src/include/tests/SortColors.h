/*
75. Sort Colors
Total Accepted: 86210 Total Submissions: 253422 Difficulty: Medium
Given an array with n objects colored red, white or blue, sort them so that objects of the same color are adjacent, with the colors in the order red, white and blue.

Here, we will use the integers 0, 1, and 2 to represent the color red, white, and blue respectively.

Note:
You are not suppose to use the library's sort function for this problem.
*/
#include <algorithm>
#include "Common.h"

namespace SortColors
{
  void sortColors(vector<int>& nums) {
    const int n = nums.size();
    // last index of the occurance
    int zero = 0;
    int one = 0;
    int two = 0;
    for (auto i = 0; i < n; i++)
    {
      if (nums[i] == 0)
      {
        // shift the other two index
        nums[two++] = 2; 
        nums[one++] = 1;
        nums[zero++] = 0;
      }
      else if (nums[i] == 1)
      {
        nums[two++] = 2;
        nums[one++] = 1;
      }
      else
      {
        nums[two++] = 2;
      }
    }
  }
  static int Test(vector<int>& nums)
  {
    for (auto num : nums)
    {
      cout << num << " ";
    }
    cout << endl;
    
    sortColors(nums);
    
    for (auto num : nums)
    {
      cout << num << " ";
    }
    cout << endl;
    return 0;
  }
}