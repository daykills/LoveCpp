/*
What does Monoqueue do here:

It has three basic options:

push: push an element into the queue; O (1) (amortized)

pop: pop an element out of the queue; O(1) (pop = remove, it can't report this element)

max: report the max element in queue;O(1)

It takes only O(n) time to process a N-size sliding window minimum/maximum problem.

Note: different from a priority queue (which takes O(nlogk) to solve this problem), it doesn't pop the max element: It pops the first element (in original order) in queue.

*/

#include <algorithm>
#include <cassert>
#include <queue>
#include "Common.h"

namespace MonotonicQueue
{
  class Monoqueue
  {
    //pair.first: the actual value, 
    //pair.second: how many elements were deleted between it and the one before it.
    deque<pair<int, int>> m_deque;
    
  public:
    void push(int val)
    {
      int count = 0;
      while (!m_deque.empty() && m_deque.back().first < val)
      {
        count += m_deque.back().second + 1;
        m_deque.pop_back();
      }
      m_deque.emplace_back(val, count);
    };
    int max()
    {
      return m_deque.front().first;
    }
    void pop()
    {
      if (m_deque.front().second > 0)
      {
        m_deque.front().second--;
        return;
      }
      m_deque.pop_front();
    }
  };

  /*
  239. Sliding Window Maximum
  */
  vector<int> maxSlidingWindow(vector<int>& nums, int k)
  {
    vector<int> results;
    Monoqueue mq;
    k = min(k, (int)nums.size());
    int i = 0;
    for (; i < k - 1; ++i) //push first k - 1 numbers;
    {
      mq.push(nums[i]);
    }
    for (; i < (int)nums.size(); ++i)
    {
      mq.push(nums[i]);            // push a new element to queue;
      results.push_back(mq.max()); // report the current max in queue;
      mq.pop();                    // pop first element in queue;
    }
    return results;
  }

  static bool Test()
  {
    vector<int> nums{ 1, 3, -1, -3, 5, 3, 6, 7 };
    for (auto i : nums)
      cout << " " << i;
    cout << endl;

    auto result = maxSlidingWindow(nums, 3);
    for (auto i : result)
      cout << " " << i;
    cout << endl;

    return false;
  }
}