/*
 279. Perfect Squares
 Medium
 
 1805
 
 154
 
 Favorite
 
 Share
 Given a positive integer n, find the least number of perfect square numbers (for example, 1, 4, 9, 16, ...) which sum to n.
 
 Example 1:
 
 Input: n = 12
 Output: 3
 Explanation: 12 = 4 + 4 + 4.
 Example 2:
 
 Input: n = 13
 Output: 2
 Explanation: 13 = 4 + 9.
*/

#include <algorithm>
#include <unordered_set>
#include "Common.h"

namespace NumSquares
{
int numSquaresBFS(int n) {
    auto maxCand = (int)sqrt(n);
    // q to store remainder
    queue<int> q;
    q.push(n);
    int step = 0;
    while (!q.empty()) {
        auto cnt = q.size();
        for (auto i = 0; i < cnt; i++) {
            auto remainder = q.front(); q.pop();
            for (auto num = maxCand; num >= 1; num--) {
                auto square = num * num;
                if (square > remainder)
                    continue;
                if (square == remainder)
                    return step + 1;
                q.push(remainder - square);
            }
        }
        step++;
    }
    return INT_MAX;
}

int numSquares(int n) {
    if (n < 2) return n;
    // dp[i] is the min squares to reach i
    vector<int> dp(n + 1, INT_MAX);
    dp[0] = 0;
    for (auto i = 1; i <= n; i++) {
        for (int j = 1; j < sqrt(i) + 1; j++) {
            auto square = j * j;
            if (square > i)
                continue;
            dp[i] = min(dp[i], dp[i - square] + 1);
        }
    }
    return dp.back();
}

void Test() {
    cout << numSquares(8935) << endl;
}
}
