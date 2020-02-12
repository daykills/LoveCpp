/*
 837. New 21 Game
 Alice plays the following game, loosely based on the card game "21".
 
 Alice starts with 0 points, and draws numbers while she has less than K points.  During each draw, she gains an integer number of points randomly from the range [1, W], where W is an integer.  Each draw is independent and the outcomes have equal probabilities.
 
 Alice stops drawing numbers when she gets K or more points.  What is the probability that she has N or less points?
 
 Example 1:
 
 Input: N = 10, K = 1, W = 10
 Output: 1.00000
 Explanation:  Alice gets a single card, then stops.
 Example 2:
 
 Input: N = 6, K = 1, W = 10
 Output: 0.60000
 Explanation:  Alice gets a single card, then stops.
 In 6 out of W = 10 possibilities, she is at or below N = 6 points.
 Example 3:
 
 Input: N = 21, K = 17, W = 10
 Output: 0.73278
 Note:
 
 0 <= K <= N <= 10000
 1 <= W <= 10000
 Answers will be accepted as correct if they are within 10^-5 of the correct answer.
 The judging time limit has been reduced for this question.
*/

#include <algorithm>
#include <unordered_set>
#include "Common.h"

namespace New21Game
{

double new21GameReadable(int N, int K, int W) {
    // dp[i]: prob of reaching i points
    vector<double> dp(N + 2, 0);
    dp[0] = 1;
    for (auto i = 1; i <= N; i++) {
        // i can be reached from (i - W), ..., (i - 1)
        auto lo = max(0, i - W);
        // if previous point is >= K, don't connect
        auto hi = min(i - 1, K - 1);
        // better to use slide window sum; or it's gonna fail for performance
        for (auto j = lo; j <= hi; j++)
            dp[i] += dp[j];
        dp[i] /= W;
    }

    double ans = 0;
    for (auto i = K; i <= N; i++)
        ans += dp[i];
    return ans;
}

double new21Game(int N, int K, int W) {
    if (K == 0 || N >= K + W) return 1.0;
    // dp[i]: prob of reaching i points
    vector<double> dp(N + 2, 0);
    dp[0] = 1;
    // sum of previous dp probs (up to W of them)
    double wSum = 1;
    for (auto i = 1; i <= N; i++) {
        // i can be reached from the window
        dp[i] = wSum / W;ExpressiveWords.h
        // update wSum
        // slide out lower end
        if (i >= W) {
            wSum -= dp[i - W];
        }
        // higher end to include dp[i] when i<K
        if (i < K) {
            wSum += dp[i];
        }
    }
    
    double ans = 0;
    for (auto i = K; i <= N; i++)
        ans += dp[i];
    return ans;
}

void Test() {
    cout << new21Game(1, 0, 1) << endl;
    //cout << new21Game(9367, 7346, 5344) << endl;
    //cout << new21Game(21, 17, 10) << endl;
}
}
