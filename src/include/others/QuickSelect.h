/*
 https://lemire.me/blog/2017/06/14/quickselect-versus-binary-heap-for-top-k-queries/
 https://www.geeksforgeeks.org/quickselect-algorithm/
 
 Quickselect Algorithm

 Quickselect is a selection algorithm to find the k-th smallest element in an unordered list. It is related to the quick sort sorting algorithm.

 Examples:

 Input: arr[] = {7, 10, 4, 3, 20, 15}
            k = 3
 Output: 7

 Input: arr[] = {7, 10, 4, 3, 20, 15}
            k = 4
 Output: 10
 The algorithm is similar to QuickSort. The difference is, instead of recurring for both sides (after finding pivot), it recurs only for the part that contains the k-th smallest element. The logic is simple, if index of partitioned element is more than k, then we recur for left part. If index is same as k, we have found the k-th smallest element and we return. If index is less than k, then we recur for right part. This reduces the expected complexity from O(n log n) to O(n), with a worst case of O(n^2).
 */

#include <iostream>
#include <queue>
#include <algorithm>
#include "Common.h"

namespace QuickSelect
{

// Standard partition process of QuickSort().
// It considers the last element as pivot
// and moves all smaller element to left of
// it and greater elements to right
int partition(vector<int>& arr, int l, int r)
{
    int x = arr[r];
    int i = l;
    for (int j = l; j <= r - 1; j++) {
        if (arr[j] <= x) {
            swap(arr[i], arr[j]);
            i++;
        }
    }
    swap(arr[i], arr[r]);
    return i;
}

// This function returns k'th smallest
// element in arr[l..r] using QuickSort
// based method.  ASSUMPTION: ALL ELEMENTS
// IN ARR[] ARE DISTINCT
void quickSelect(vector<int>& arr, int l, int r, int k)
{
    // If k is smaller than number of
    // elements in array
    if (k > 0 && k <= r - l + 1) {
  
        // Partition the array around last
        // element and get position of pivot
        // element in sorted array
        int index = partition(arr, l, r);
  
        // If position is same as k
        if (index - l == k - 1)
            return;
  
        // If position is more, recur
        // for left subarray
        if (index - l > k - 1)
            quickSelect(arr, l, index - 1, k);
        else
            quickSelect(arr, index + 1, r, k - index + l - 1);
    }
  
    // If k is more than number of elements in array
    assert(false);
    
}

////////////////////////////////////////////////////////////////////////////////////
void Test()
{
    vector<int> nums = { 1, 10, 5, 7, 4, };
    quickSelect(nums, 0, nums.size() - 1, 3);
    for (auto num : nums)
        cout << num << endl;
}
}
