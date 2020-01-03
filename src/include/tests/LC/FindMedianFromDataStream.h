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
class MedianFinder {
public:
    /** initialize your data structure here. */
    MedianFinder() {
        
    }
    
    void addNum(int num) {
        // when both are empty
        if (m_smallQ.empty() && m_bigQ.empty()) {
            m_smallQ.push(num);
            return;
        }
        auto median = findMedian();
        if (num <= median)
            m_smallQ.push(num);
        else
            m_bigQ.push(num);
        
        // rebalance two queues
        if (m_smallQ.size() < m_bigQ.size()) {
            m_smallQ.push(m_bigQ.top());
            m_bigQ.pop();
        } else if (m_smallQ.size() == m_bigQ.size() + 2) {
            m_bigQ.push(m_smallQ.top());
            m_smallQ.pop();
        }
    }
    
    double findMedian() {
        assert(!m_smallQ.empty());
        assert(m_smallQ.size() >= m_bigQ.size());
        if (m_bigQ.size() < m_smallQ.size()) {
            return m_smallQ.top();
        } else {
            return (m_smallQ.top() + m_bigQ.top()) * 0.5;
        }
    }
private:
    // small queue size >= big queue size
    priority_queue<int> m_smallQ;
    // big queue is a min heap
    priority_queue<int, vector<int>, greater<int>> m_bigQ;
    
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
