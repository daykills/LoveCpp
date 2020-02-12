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
    auto n = nums.size();
    vector<int> result;
    result.reserve(n - k + 1);
    // dq: nums in order that from max to low, from early to late
    // If later num is bigger than its precedents, erase all the precedents
    deque<int> dq;
    for (auto i = 0; i < n; i++) {
        if (!dq.empty() && dq.front() <= i - k)
            dq.pop_front();
        // remove precedents to keep dq in order
        while (!dq.empty() && nums[i] >= nums[dq.back()])
            dq.pop_back();
        dq.push_back(i);
        if (i >= k - 1)
            result.push_back(nums[dq.front()]);
    }
    return result;
}
//////////////////
vector<int> maxSlidingWindowPQ(vector<int>& nums, int k) {
    // keep the val and its index
    priority_queue<pair<int, int>> valAndIndice;
    vector<int> res;
    for (int i = 0; i < nums.size(); i++) {
        // if the max vals are out of window, pop them
        while (!valAndIndice.empty() && valAndIndice.top().second <= i - k)
            valAndIndice.pop();
        valAndIndice.emplace(nums[i], i);
        if (i >= k - 1) res.push_back(valAndIndice.top().first);
    }
    return res;
}

//////////////////
vector<int> maxSlidingWindowSet(vector<int>& nums, int k) {
    vector<int> res;
    multiset<int, greater<int>> numSet;
    for (int i = 0; i < nums.size(); i++) {
        // must find the iterator; or all vals are removed
        if (i >= k)
            numSet.erase(numSet.find(nums[i - k]));
        numSet.emplace(nums[i]);
        if (i >= k - 1) res.push_back(*numSet.begin());
    }
    return res;
}

int Test()
{
    //vector<int> nums{ 1, -1 };
    vector<int> nums{1,3,-1,-3,5,3,6,7};
    
    for (auto i : nums)
        cout << " " << i;
    cout << endl;
    
    auto result = slidingWindowMaximum(nums, 3);
    for (auto i : result)
        cout << " " << i;
    cout << endl;
    
    return 0;
}
}
