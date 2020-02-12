/*
 658. Find K Closest Elements

 Given a sorted array, two integers k and x, find the k closest elements to x in the array. The result should also be sorted in ascending order. If there is a tie, the smaller elements are always preferred.
 
 Example 1:
 
 Input: [1,2,3,4,5], k=4, x=3
 Output: [1,2,3,4]
 Example 2:
 
 Input: [1,2,3,4,5], k=4, x=-1
 Output: [1,2,3,4]
 Note:
 
 The value k is positive and will always be smaller than the length of the sorted array.
 Length of the given array is positive and will not exceed 104
 Absolute value of elements in the array and x will not exceed 104
 
 UPDATE (2017/9/19):
 The arr parameter had been changed to an array of integers (instead of a list of integers). Please reload the code definition to get the latest changes.
*/

#include <iostream>
#include <stack>
#include <algorithm>
#include <cstdint>
#include "Common.h"

namespace FindClosestElements
{

vector<int> findClosestElements(vector<int>& arr, int k, int x) {
    assert(k <= arr.size());
    int lowBoundIndex = std::lower_bound(arr.begin(), arr.end(), x) - arr.begin();
    // if x is bigger than all of them
    if (lowBoundIndex == arr.size())
        return vector<int>(arr.end() - k, arr.end());
    else if (lowBoundIndex == 0)
        return vector<int>(arr.begin(), arr.begin() + k);

    // if within bound, arr[hi] must >= x; arr[lo] must < x
    int hi = lowBoundIndex;
    int lo = hi - 1;
    // hi and lo are only for consideration, not accepted yet
    int count = 0;
    while (count++ < k) {
        if (lo < 0) {
            assert(hi < arr.size());
            hi++;
        } else if (hi >= arr.size()) {
            assert(lo >= 0);
            lo--;
        } else {
            if (x - arr[lo] <= arr[hi] - x) lo--;
            else hi++;
        }
    }
    // lo and hi should not be included in the final results
    return vector<int>(arr.begin() + lo + 1, arr.begin() + hi);
}

void Test()
{
    vector<int> arr = { 0,1,2,2,2,3,6,8,8,9 };
    
    for (auto i : arr)
        cout << " " << i;
    cout << endl;
    
    auto result = findClosestElements(arr, 5, 9);
    
    for (auto i : result)
        cout << " " << i;
    cout << endl;
}
}
