/*
 480. Sliding Window Median
 Hard
 
 598
 
 62
 
 Add to List
 
 Share
 Median is the middle value in an ordered integer list. If the size of the list is even, there is no middle value. So the median is the mean of the two middle value.
 
 Examples:
 [2,3,4] , the median is 3
 
 [2,3], the median is (2 + 3) / 2 = 2.5
 
 Given an array nums, there is a sliding window of size k which is moving from the very left of the array to the very right. You can only see the k numbers in the window. Each time the sliding window moves right by one position. Your job is to output the median array for each window in the original array.
 
 For example,
 Given nums = [1,3,-1,-3,5,3,6,7], and k = 3.
 
 Window position                Median
 ---------------               -----
 [1  3  -1] -3  5  3  6  7       1
 1 [3  -1  -3] 5  3  6  7       -1
 1  3 [-1  -3  5] 3  6  7       -1
 1  3  -1 [-3  5  3] 6  7       3
 1  3  -1  -3 [5  3  6] 7       5
 1  3  -1  -3  5 [3  6  7]      6
 Therefore, return the median sliding window as [1,-1,-1,3,5,6].
 
 Note:
 You may assume k is always valid, ie: k is always smaller than input array's size for non-empty array.
 */

#include "Common.h"

namespace SlidingWindowMedian
{
void rebalance(multiset<long>& smaller, multiset<long>& bigger) {
    // rebalance smaller and bigger
    if (smaller.size() == bigger.size() + 2) {
        bigger.emplace(*smaller.rbegin());
        smaller.erase(prev(smaller.end()));
    } else if (smaller.size() < bigger.size()) {
        smaller.emplace(*bigger.begin());
        bigger.erase(bigger.begin());
    }
    assert(smaller.size() == bigger.size() || smaller.size() == bigger.size() + 1);
}

double getMedian(const multiset<long>& smaller, const multiset<long>& bigger) {
    assert(smaller.size() == bigger.size() || smaller.size() == bigger.size() + 1);
    if (smaller.size() == bigger.size()) {
        return (*smaller.rbegin() + *bigger.begin()) * 0.5;
    }
    else
        return *smaller.rbegin();
}

vector<double> medianSlidingWindowOld(vector<int>& nums, int k) {
    multiset<long> smaller;
    multiset<long> bigger;
    vector<double> res;
    for (auto hi = 0; hi < nums.size(); hi++) {
        if (smaller.empty() || bigger.empty() || nums[hi] < *bigger.begin()) {
            smaller.emplace(nums[hi]);
        } else {
            bigger.emplace(nums[hi]);
        }
        rebalance(smaller, bigger);
        
        if (hi < k - 1)
            continue;
        
        auto median = getMedian(smaller, bigger);
        res.emplace_back(median);
        
        auto lo = hi + 1 - k;
        
        if (nums[lo] > median) {
            auto it = bigger.find(nums[lo]);
            assert(it != bigger.end());
            bigger.erase(it);
        }
        else {
            auto it = smaller.find(nums[lo]);
            assert(it != smaller.end());
            smaller.erase(it);
        }
        rebalance(smaller, bigger);
    }
    return res;
}

vector<double> medianSlidingWindow(vector<int>& nums, int k) {
    multiset<int> win(nums.begin(), nums.begin() + k);
    auto mid = next(win.begin(), k / 2);
    vector<double> res;
    res.reserve(nums.size() - k + 1);
    for (auto i = k; ; i++) {
        double median = *mid;
        // k is even
        if (k % 2 == 0)
            median = (median + *prev(mid)) * 0.5;
        res.push_back(median);
        if (i == nums.size())
            return res;
        win.insert(nums[i]);
        if (nums[i])
        win.erase(win.lower_bound(nums[i - k]));
    }
    return res;
}

static void Test()
{
    // expected [1073741824.0,1.5,2.5,3.5,4.5,5.5,6.5,1073741827.0]
    //vector<int> nums = { 2147483647,1,2,3,4,5,6,7,2147483647 };
    //auto k = 2;
    
    // expected [[8,6,8,8,5]]
    //vector<int> nums = { 7,0,3,9,9,9,1,7,2,3 };
    //auto k = 6;
    
    // expected [2.5]
    vector<int> nums = { 1,4,2,3 };
    auto k = 4;
    
    auto ans = medianSlidingWindow(nums, k);
    for (auto node : ans) {
        cout << node << " ";
    }
    cout << endl;
}
}
