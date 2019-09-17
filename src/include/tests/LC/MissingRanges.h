/*
 Given a sorted integer array where the range of elements are [0, 99] inclusive, return its missing ranges.
 For example, given [0, 1, 3, 50, 75], return [“2”, “4->49”, “51->74”, “76->99”]
 */

#include "Common.h"

namespace MissingRanges
{
class Solution {
public:
    vector<string> findMissingRanges(vector<int>& nums, int lower, int upper) {
        vector<string> res;
        auto last = lower;
        for (auto i = 0; i <= nums.size(); i++) {
            if (i < nums.size() && nums[i] < lower) {
                continue;
            }
            // beyond last element
            if (i == nums.size() || nums[i] > upper) {
                if (upper == last + 1)
                    res.emplace_back(to_string(upper));
                else if (upper > last + 1)
                    res.emplace_back(to_string(last + 1) + "->" + to_string(upper));
                break;
            }
            // skiped
            if (nums[i] == last + 2) {
                res.emplace_back(to_string(last + 1));
            } else if (nums[i] > last + 2) {
                // nums[i] > last + 2
                res.emplace_back(to_string(last + 1) + "->" + to_string(nums[i] - 1));
            }
            last = nums[i];
        }
        return res;
    }
};


static void Test()
{
    Solution solution;
    vector<int> nums = { 0, 1, 3, 50, 75 };
    auto res = solution.findMissingRanges(nums, 1, 76);
    for (auto range: res)
        std::cout << range << std::endl;
}
}
