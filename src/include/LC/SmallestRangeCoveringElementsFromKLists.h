/*
 632. Smallest Range Covering Elements from K Lists

 You have k lists of sorted integers in ascending order. Find the smallest range that includes at least one number from each of the k lists.
 
 We define the range [a,b] is smaller than range [c,d] if b-a < d-c or a < c if b-a == d-c.
 
 
 
 Example 1:
 
 Input: [[4,10,15,24,26], [0,9,12,20], [5,18,22,30]]
 Output: [20,24]
 Explanation:
 List 1: [4, 10, 15, 24,26], 24 is in range [20,24].
 List 2: [0, 9, 12, 20], 20 is in range [20,24].
 List 3: [5, 18, 22, 30], 22 is in range [20,24].
 
 
 Note:
 
 The given list may contain duplicates, so ascending order means >= here.
 1 <= k <= 3500
 -105 <= value of elements <= 105.
 */

#include <iostream>
#include <list>
#include "Common.h"

namespace SmallestRangeCoveringElementsFromKLists
{
class Solution {
public:
    vector<int> smallestRange(vector<vector<int>>& nums) {
        using index_type = pair<int, int>;
        auto lessor = [&nums](const index_type& lhs, const index_type& rhs) {
            assert(lhs.first < nums.size());
            assert(rhs.first < nums.size());
            assert(lhs.second < nums[lhs.first].size());
            assert(rhs.second < nums[rhs.first].size());
            return nums[lhs.first][lhs.second] < nums[rhs.first][rhs.second];
        };
        int minVal = INT_MAX;
        int maxVal = INT_MIN;
        int minRange = INT_MAX;
        multiset<index_type, decltype(lessor)> orderedNums(lessor);
        
        for (auto i = 0; i < nums.size(); i++)
            orderedNums.emplace(i, 0);
        
        while (true) {
            auto small = *orderedNums.begin();
            auto iNums = small.first;
            auto i = small.second;
            auto big = *prev(orderedNums.end());
            auto iNumsBig = big.first;
            auto& iBig = big.second;
            int range = nums[iNumsBig][iBig] - nums[iNums][i];
            if (range < minRange) {
                minRange = range;
                minVal = nums[iNums][i];
                maxVal = nums[iNumsBig][iBig];
            }
            // if smallest is already reaching end
            if (minRange == 0 || i == nums[iNums].size() - 1)
                break;
            orderedNums.erase(orderedNums.begin());
            small.second++;
            orderedNums.emplace(small);
            assert(orderedNums.size() == nums.size());
        }
        return {minVal, maxVal};
    }
};

static void Test()
{
    Solution solution;
    vector<vector<int>> nums {
        {-89,1,69,89,90,98},
        {-43,-36,-24,-14,49,61,66,69},
        {73,94,94,96},
        {11,13,76,79,90},
        {-40,-20,1,9,12,12,14},
        {-91,-31,0,21,25,26,28,29,29,30},
        {23,88,89},
        {31,42,42,57},
        {-2,6,11,12,12,13,15},
        {-3,25,34,36,39},
        {-7,3,29,29,31,32,33},
        {4,11,14,15,15,18,19},
        {-34,9,12,19,19,19,19,20},
        {-26,4,47,53,64,64,64,64,64,65},
        {-51,-25,36,38,50,54},
        {17,25,38,38,38,38,40},
        {-30,12,15,19,19,20,22},
        {-14,-13,-10,68,69,69,72,74,75},
        {-39,42,70,70,70,71,72,72,73},
        {-67,-34,6,26,28,28,28,28,29,30,31}
        /*
        {4,10,15,24,26},
        {0,9,12,20},
        {5,18,22,30}
         */
    };
    
    auto result = solution.smallestRange(nums);
    for (auto& val : result) {
        std::cout << val << ", ";
    }
    std::cout << std::endl;
}
}
