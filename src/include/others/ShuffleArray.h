/*
 https://github.com/julycoding/The-Art-Of-Programming-By-July/blob/master/ebook/zh/02.09.md
 https://www.geeksforgeeks.org/shuffle-array-a1-b1-a2-b2-a3-b3-bn-without-using-extra-space/
 Given an array of 2n elements in the following format { a1, a2, a3, a4, ….., an, b1, b2, b3, b4, …., bn }. The task is shuffle the array to {a1, b1, a2, b2, a3, b3, ……, an, bn } without using extra space.
 
 Examples :
 
 Input : arr[] = { 1, 2, 9, 15 }
 Output : 1 9 2 15
 
 Input :  arr[] = { 1, 2, 3, 4, 5, 6 }
 Output : 1 4 2 5 3 6
 
 */

#include "Common.h"

namespace ShuffleArray
{
class Solution {
public:
    void dfs(vector<int>& nums, int lo, int hi) {
        auto n = hi - lo + 1;
        if (n <= 2)
            return;
        assert(n % 2 == 0);
        auto mid = (lo + hi + 1) / 2;
        auto hiInd = mid;
        auto loInd = (lo + mid + 1) / 2;
        for (; loInd < mid; loInd++, hiInd++)
            swap(nums[loInd], nums[hiInd]);
        dfs(nums, lo, mid - 1);
        dfs(nums, mid, hi);
    }
    
    void shuffle(vector<int>& nums) {
        dfs(nums, 0, nums.size() - 1);
    }
    
    void shuffleBrutal(vector<int>& nums) {
        auto n = nums.size();
        assert(n > 0 && n % 2 == 0);
        for (int leftInd = 1, rightInd = n / 2; rightInd < n; rightInd++, leftInd += 2) {
            for (auto i = rightInd; i > leftInd; i--) {
                swap(nums[i], nums[i - 1]);
            }
        }
    }
};
static void Test()
{
    Solution solution;
    vector<int> nums {
        1, 3, 5, 7, 2, 4, 6, 8
    };
    solution.shuffle(nums);
    for (auto& val : nums) {
        std::cout << val << std::endl;
    }
}
}
