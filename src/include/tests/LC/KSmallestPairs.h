/*
 373. Find K Pairs with Smallest Sums

 You are given two integer arrays nums1 and nums2 sorted in ascending order and an integer k.
 
 Define a pair (u,v) which consists of one element from the first array and one element from the second array.
 
 Find the k pairs (u1,v1),(u2,v2) ...(uk,vk) with the smallest sums.
 
 Example 1:
 
 Input: nums1 = [1,7,11], nums2 = [2,4,6], k = 3
 Output: [[1,2],[1,4],[1,6]]
 Explanation: The first 3 pairs are returned from the sequence:
 [1,2],[1,4],[1,6],[7,2],[7,4],[11,2],[7,6],[11,4],[11,6]
 Example 2:
 
 Input: nums1 = [1,1,2], nums2 = [1,2,3], k = 2
 Output: [1,1],[1,1]
 Explanation: The first 2 pairs are returned from the sequence:
 [1,1],[1,1],[1,2],[2,1],[1,2],[2,2],[1,3],[1,3],[2,3]
 Example 3:
 
 Input: nums1 = [1,2], nums2 = [3], k = 3
 Output: [1,3],[2,3]
 Explanation: All possible pairs are returned from the sequence: [1,3],[2,3]
*/

#include <algorithm>
#include <unordered_set>
#include "Common.h"

namespace KSmallestPairs
{

vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
    auto lessor = [&nums1, &nums2](const std::pair<int, int>& lhs, const std::pair<int, int>& rhs) {
        return nums1[lhs.first] + nums2[lhs.second] > nums1[rhs.first] + nums2[rhs.second];
    };
    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(lessor)> q(lessor);
    vector<vector<int>> ans;
    if (nums1.empty() || nums2.empty()) return ans;
    // start with [0,0].
    q.emplace(0, 0);
    while (ans.size() < k && !q.empty()) {
        auto top = q.top();
        q.pop();
        auto i1 = top.first;
        auto i2 = top.second;
        ans.emplace_back();
        ans.back().push_back(nums1[i1]);
        ans.back().push_back(nums2[i2]);
        // the next biggest is either (i1+1, i2) or (i1, i2+1)
        if (i1 + 1 < nums1.size())
            q.emplace(i1 + 1, i2);
        // you might add the same idex twice
        // (i1, i2+1) can be reached from both (i1, i2) and (i1-1, i2+1)
        // So, we skip adding it here, except when i1==0
        if (i1 == 0 && i2 + 1 < nums2.size())
            q.emplace(i1, i2 + 1);
    }
    return ans;
}

void Test() {
    vector<int> nums1 = { 1, 7, 11 };
    vector<int> nums2 = { 2, 4, 6 };
    auto rst = kSmallestPairs(nums1, nums2, 3);
    std::cout << "Result: ";
    for (auto& pair : rst) {
        std::cout << "[" << pair[0] << "," << pair[1] << "], ";
    }
    std::cout << std::endl;
}
}
