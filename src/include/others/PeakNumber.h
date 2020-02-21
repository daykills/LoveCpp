/*
 https://www.geeksforgeeks.org/print-all-the-peaks-and-troughs-in-an-array-of-integers/
 在一个array 中找peak element
 array > array, array > array
 假设array[-1] < array[0], array[array.length - 1] > array[array.length]
 第一个简单例子 数字都不同
 input： [1, 2, 3, 6, 4, 3, 7, 6]
 return: [6, 7]

 第二个假设数字是可以相等的
 input: [0, 1, 2, 2, 3, 4]
 return:4

 第三个是这个数列很长，我们分成几个交给不同机器处理
 怎么处理边界上false postive 的peak element。
 */

#include <iostream>
#include <queue>
#include <algorithm>
#include "Common.h"

namespace PeakNumber
{
vector<int> getPeaks(const vector<int>& nums) {
    auto n = nums.size();
    if (n == 0) return {};
    auto val = [&nums](int i) {
        if (i < 0 || i >= nums.size()) return INT_MIN;
        return nums[i];
    };
    bool rising = val(0) > val(-1);
    vector<int> peaks;
    // look for the turning point
    for (auto i = 1; i <= n; i++) {
        if (val(i) > val(i - 1))
            rising = true;
        else {
            if (rising) {
                peaks.push_back(val(i - 1));
            }
            rising = false;
        }
    }
    return peaks;
}

////////////////////////////////////////////////////////////////////////////////////
void Test()
{
    vector<int> nums = { 10, 10, 10, 5, 7, 4, };
    auto peaks = getPeaks(nums);
    for (auto peak : peaks)
        cout << peak << endl;
}
}
