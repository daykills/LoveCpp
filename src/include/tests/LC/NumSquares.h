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
int numSquares(int n) {
    if (n <= 0) return 0;
    // cntPerfectSquares[i] = the least number of perfect square numbers
    // which sum to i. Note that cntPerfectSquares[0] is 0.
    vector<int> cntPerfectSquares(n + 1, INT_MAX);
    cntPerfectSquares[0] = 0;
    for (int i = 1; i <= n; i++)
    {
        // For each i, it must be the sum of some number (i - j*j) and
        // a perfect square number (j*j).
        for (int j = 1; j * j <= i; j++)
        {
            cntPerfectSquares[i] =
            min(cntPerfectSquares[i], cntPerfectSquares[i - j*j] + 1);
        }
    }
    
    return cntPerfectSquares.back();
}

int numSquaresBFS(int n) {
    int maxNum = (int)sqrt(n);
    // q of sum & perfect squres
    queue<pair<int, vector<int>>> q;
    // start with nothing
    q.emplace(0, vector<int>());
    while (true) {
        auto sum = q.front().first;
        auto hist = std::move(q.front().second);
        q.pop();
        for (auto num = maxNum; num >= 1; num--) {
            auto sqr = num * num;
            auto newSum = sum + sqr;
            hist.push_back(sqr);
            if (newSum == n)
                return hist.size();
            q.emplace(newSum, hist);
            hist.pop_back();
        }
    }
    return 0;
}

void Test() {
    cout << numSquares(8935) << endl;
}
}
