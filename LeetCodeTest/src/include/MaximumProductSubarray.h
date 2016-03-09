/*
Maximum Product Subarray
Find the contiguous subarray within an array (containing at least one number) which has the largest product.
For example, given the array [2,3,-2,4],
the contiguous subarray [2,3] has the largest product = 6.
*/

#include <string>
#include <iostream>
#include <algorithm>
#include "Common.h"

namespace MaximumProductSubarray
{
  static int Test(const vector<int>& nums)
  {
    int n = nums.size();

    vector<int> dpMin(n, 0);
    vector<int> dpMax(n, 0);
    int maxProduct = dpMax[0] = dpMin[0] = nums[0];

    for (int i = 1; i < n; i++)
    {
      dpMax[i] = max(max(dpMax[i - 1] * nums[i], dpMin[i - 1] * nums[i]), nums[i]);
      maxProduct = max(maxProduct, dpMax[i]);
      dpMin[i] = min(min(dpMax[i - 1] * nums[i], dpMin[i - 1] * nums[i]), nums[i]);
    }
    return maxProduct;
  }
  // too slow
  static int Test1(const vector<int>& nums)
  {
    int n = nums.size();
    
    // product of num[i] to num[j]
    int p;
    int maxProduct = INT_MIN;
    for (int i = 0; i < n; i++)
    {
      bool isDataAtIZero = (nums[i] == 0);

      // start with diagonal
      p = nums[i];
      if (p > maxProduct)
        maxProduct = p;
      
      for (int j = i + 1; j < n; j++)
      {
        // if i or j is zero
        if (isDataAtIZero || nums[j] == 0)
        {
          p = 0;
          if (0 > maxProduct)
            maxProduct = 0;
          continue;
        }
        
        p = p * nums[j];
        if (p > maxProduct)
          maxProduct = p;
      }
    }
    return maxProduct;
  }
}