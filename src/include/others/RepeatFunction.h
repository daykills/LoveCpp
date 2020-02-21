/*
 https://www.1point3acres.com/bbs/thread-426839-1-1.html
 第四个人coding，n： 1，2, 3 ，4 ，5， 6, 7，......
 F(n):  1,  2, 2,    3,  3,   4,  4, 4......
 规律是，n所对应的在fn中的数是几，就把n在fn后面重复几次
 输入是n，求fn。做一个table，计算填表就行了
 */

#include <iostream>
#include <queue>
#include <algorithm>
#include "Common.h"

namespace RepeatFunction
{
int f(int n) {
    vector<int> dp;
    dp.reserve(n + 1);
    dp.push_back(0);
    for (auto i = 1; i <= n; i++) {
        int repeat = i <= 2 ? i : dp[i];
        // no need to get values after dp[n]
        for (auto j = 0; dp.size() < n + 1 && j < repeat; j++) {
            dp.push_back(i);
        }
        if (dp.size() == n + 1) break;
    }
    return dp[n];
}

////////////////////////////////////////////////////////////////////////////////////
void Test()
{
    for (auto i = 100; i <= 100; i++)
        cout << i << ": " << f(i) << endl;
}
}
