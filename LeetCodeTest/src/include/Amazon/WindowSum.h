/*
Input: A long array A[], and a window width k
Output: An array B[], B[i] is the sum from A[i] to A[i+w-1]
Requirement: Find a good optimal way to get B[i]
*/

#include <iostream>
#include <algorithm>
#include "Common.h"

namespace WindowSum
{
  vector<int> getSum(vector<int> input, int k)
  {
    int n = input.size();
    // handle empty input
    if (n == 0) return vector<int>();
    int lenSum = n - k + 1;
    if (lenSum <= 0) return vector<int>();
    vector<int> sum(lenSum, 0);
    // calculate the first sum. O(k)
    for (int i = 0; i < k; i++)
    {
      sum[0] += input[i];
    }
    // use a sliding window to add the head and remove the tail. O(lenSum) ~ O(n - k)
    for (int i = 1; i < lenSum; i++)
    {
      sum[i] = sum[i - 1] + input[i + k - 1] - input[i - 1];
    }    
    return sum;
  }

  int Test()
  {
    vector<int> nums{ 1, 4, 5, 11, -2, 3 };

    for (auto i : nums)
      cout << " " << i;
    cout << endl;

    auto result = getSum(nums, 3);
    for (auto i : result)
      cout << " " << i;
    cout << endl;

    return 0;
  }
}
