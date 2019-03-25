/*
88. Merge Sorted Array
 Given two sorted integer arrays nums1 and nums2, merge nums2 into nums1 as one sorted array.
 
 Note:
 
 The number of elements initialized in nums1 and nums2 are m and n respectively.
 You may assume that nums1 has enough space (size that is greater or equal to m + n) to hold additional elements from nums2.
 Example:
 
 Input:
 nums1 = [1,2,3,0,0,0], m = 3
 nums2 = [2,5,6],       n = 3
 
 Output: [1,2,2,3,5,6]
*/

#include <algorithm>
#include "Common.h"

namespace MergeSortedArray
{
    void merge1(vector<int>& nums1, int m, vector<int>& nums2, int n)
    {
        auto i1 = m - 1;
        auto i2 = n -1;
        auto i = m + n -1;
        // if i2 < 0, then nums1 should be the result already
        while (i2 >= 0) {
            if (i1 < 0 || nums1[i1] <= nums2[i2]) {
                nums1[i] = nums2[i2];
                i2--;
            } else {
                nums1[i] = nums1[i1];
                i1--;
            }
            i--;
        }
    }
    
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        auto i1 = m - 1;
        auto i2 = n -1;
        for (auto i = n + m - 1; i >= 0; i--) {
            if (i1 < 0) {
                nums1[i] = nums2[i2];
                i2--;
                continue;
            }
            if (i2 < 0) {
                nums1[i] = nums1[i1];
                i1--;
                continue;
            }
            if (nums1[i1] < nums2[i2]) {
                nums1[i] = nums2[i2];
                i2--;
            } else {
                nums1[i] = nums1[i1];
                i1--;
            }
        }
    }
    
    static bool Test()
    {
        vector<int> nums1{ 1 };
        vector<int> nums2{ };
        
        for (auto i : nums1)
            cout << " " << i;
        cout << endl;
        
        for (auto i : nums2)
            cout << " " << i;
        cout << endl;
        
        merge(nums1, nums1.size(), nums2, nums2.size());
        for (auto i : nums1)
            cout << " " << i;
        cout << endl;
        
        return false;
    }
}
