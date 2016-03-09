/*
295. Find Median from Data Stream
Total Accepted: 10592 Total Submissions: 49793 Difficulty: Hard
Median is the middle value in an ordered integer list. If the size of the list is even, there is no middle value. So the median is the mean of the two middle value.

Examples:
[2,3,4] , the median is 3

[2,3], the median is (2 + 3) / 2 = 2.5

Design a data structure that supports the following two operations:

void addNum(int num) - Add a integer number from the data stream to the data structure.
double findMedian() - Return the median of all elements so far.
For example:

add(1)
add(2)
findMedian() -> 1.5
add(3)
findMedian() -> 2
*/

#include <iostream>
#include <queue>
#include <cassert>
#include <algorithm>
#include "Common.h"

namespace FindMedianFromDataStream
{
  class MedianFinder
  {
  public:
    // big and small heaps are each storing half of the numbers, with the middle number(s) as their top
    // inside big, the top is the negative minimum of the bigger half
    priority_queue<int> big;
    // inside small, the top is maxium of the smaller half
    priority_queue<int> small;
    // Adds a number into the data structure.
    void addNum(int num)
    {
      // 1st element goes to small; small always has not-less-than big elements
      if (small.empty() && big.empty())
      {
        small.push(num);
        return;
      }
      // small number goes to small heap
      if (num <= findMedian())
      {
        small.push(num);
      }
      else
      {
        // big keeps negative elements to keep its minimum at top
        big.push(-num);
      }
      // rebalance two heaps if needed
      if (small.size() < big.size())
      {
        auto num = -big.top();
        big.pop();
        small.push(num);
      }
      else if (small.size() >= big.size() + 2)
      {
        auto num = -small.top();
        small.pop();
        big.push(num);
      }
    }

    // Returns the median of current data stream
    double findMedian()
    {
      assert(!big.empty() || !small.empty());
      // if big is empty, and small not
      if (big.empty()) return small.top();
      // if both have values
      return (small.size() == big.size()) ? 0.5 * (small.top() - big.top()) : small.top();
    }
  };

  int Test()
  {
    MedianFinder mf;
    vector<int> nums{ 3, 1, 7, 5, 10, 12, 13, 3 };
    for (auto num : nums)
    {
      mf.addNum(num);
      cout << "add " << num << ", median = " << mf.findMedian() << endl;
    }
    return 0;
  }
}
