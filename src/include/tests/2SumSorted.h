/*
 167. Two Sum II - Input array is sorted
 Given an array of integers that is already sorted in ascending order, find two numbers such that they add up to a specific target number.
 
 The function twoSum should return indices of the two numbers such that they add up to the target, where index1 must be less than index2.
 
 Note:
 
 Your returned answers (both index1 and index2) are not zero-based.
 You may assume that each input would have exactly one solution and you may not use the same element twice.
 Example:
 
 Input: numbers = [2,7,11,15], target = 9
 Output: [1,2]
 Explanation: The sum of 2 and 7 is 9. Therefore index1 = 1, index2 = 2.
 Accepted
 212,058
 Submissions
 430,481
 */

#include "Common.h"

namespace TwoSumSorted
{
    vector<int> twoSum(vector<int>& numbers, int target) {
        auto low = 0;
        auto high = numbers.size() - 1;
        while (low < high) {
            auto sum = numbers[low] + numbers[high];
            if (sum == target) {
                return { low + 1, high + 1 };
            } else if (sum < target) {
                low++;
            } else {
                high--;
            }
        }
        return {};
    }
    
    int Test()
    {
        vector<int> nums{ 2, 7, 11, 15 };
        for (auto i : nums)
            cout << " " << i;
        cout << endl;
        auto result = twoSum(nums, 9);
        for (auto i : result)
            cout << " " << i;
        cout << endl;
        return 0;
    }
}
