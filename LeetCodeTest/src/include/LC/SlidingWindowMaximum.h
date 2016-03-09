/*
239. Sliding Window Maximum My Submissions Question
Total Accepted: 20718 Total Submissions: 79634 Difficulty: Hard
Given an array nums, there is a sliding window of size k which is moving from the very left of the array to the very right.
You can only see the k numbers in the window. Each time the sliding window moves right by one position.

For example,
Given nums = [1,3,-1,-3,5,3,6,7], and k = 3.

Window position                Max
---------------               -----
[1  3  -1] -3 5  3  6  7       3
1 [3  -1  -3] 5  3  6  7       3
1  3 [-1  -3  5] 3  6  7       5
1  3  -1 [-3  5  3] 6  7       5
1  3  -1  -3 [5  3  6] 7       6
1  3  -1  -3  5 [3  6  7]      7
Therefore, return the max sliding window as [3,3,5,5,6,7].

Note:
You may assume k is always valid, ie: 1 ≤ k ≤ input array's size for non-empty array.

Follow up:
Could you solve it in linear time?

Hint:

How about using a data structure such as deque (double-ended queue)?
The queue size need not be the same as the window's size.
Remove redundant elements and the queue should store only elements that need to be considered.
*/

#include <iostream>
#include <queue>
#include <algorithm>
#include "Common.h"

namespace SlidingWindowMaximum
{
  //////////////////////////////////////////////////////////
  // maintain two heaps of size K for both max and min in the window
  // priority_queue is the c++ adapter for heap

  //////////////////////////////////////////////////////////
  // use dequeue to make sure the front is always the biggest number,
  // and small numbers in the back get removed when new element comes in
  // numbers in deque is always in decending order.
  vector<int> slidingWindowMaximum(vector<int> nums, int k)
  {
    int n = nums.size();
    // dq saves all the potential max numbers
    vector<int> result;
    deque<int> dq;
    for (int i = 0; i < n; i++)
    {
      // de-queue nums[i - k] (if it's the biggest) as it's out of window
      if (!dq.empty() && dq.front() == i - k) dq.pop_front();
      // clean queue - make sure new number becomes the smallest, at the back
      while (!dq.empty() && nums[dq.back()] <= nums[i])
        dq.pop_back();
      // add i to dq
      dq.emplace_back(i);
      if (i - k + 1 >= 0)
      {
        result.push_back(nums[dq.front()]);
      }
    }
    return result;    
  }

  int Test()
  {
    //vector<int> nums{ 1, -1 };
    vector<int> nums{ 5, 4, 3, 2, 1, -2, 3 };

    for (auto i : nums)
      cout << " " << i;
    cout << endl;

    auto result = slidingWindowMaximum(nums, 4);
    for (auto i : result)
      cout << " " << i;
    cout << endl;

    return 0;
  }
}
