/*
 https://www.1point3acres.com/bbs/thread-592519-1-1.html
 Roblox
 5. 十进制数转2进制数. follow up: given a base10 number and an array. 这个array告诉你下一位是应该是几进制的。输出这个杂七杂八的数字。
 例子：
 如果这个array是【 2，2，3】
 输入的base10数字     输出
 1                              1
 2                              2
 3                              10
 4                              11
 5                              12
 6                             100
 7                             101
 8                              102
 9                              110
 10                            111
 大概这么个样子 不需要把这个数组用完，并且这个数组应该从最后一个数字开始用。例如6的话，为什么输出是100。因为最先开始的是base 3， 所以6%3=0。然后6/=3得到2。下面是base2 的情况了，2%2=0, 2/=2得到1， 所以最后是100。
 
 */

#include <iostream>
#include <queue>
#include <algorithm>
#include "Common.h"

namespace NumberConverter
{
class Solution {
public:
    int convert(const vector<int>& bases, int num) {
        int ans = 0;
        int tenBase = 1;
        for (int i = bases.size() - 1; i >= 0; i--) {
            if (!num) break;
            if (num >= bases[i])
                ans += num % bases[i] * tenBase;
            else
                ans += num * tenBase;
            num = num / bases[i];
            tenBase *= 10;
        }
        return ans;
    }
};

////////////////////////////////////////////////////////////////////////////////////
void Test()
{
    Solution s;
    vector<int> bases = { 2,2,3 };
    for (auto i = 1; i <= 10; i++) {
        cout << i << ": " << s.convert(bases, i) << endl;
    }
    
}
}
