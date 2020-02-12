/*
149. Max Points on a Line My Submissions Question
Total Accepted: 52751 Total Submissions: 377870 Difficulty: Hard
Given n points on a 2D plane, find the maximum number of points that lie on the same straight line.
*/

#include <iostream>
#include <queue>
#include <algorithm>
#include <numeric>
#include "Common.h"

namespace MaxPointsOnALine
{

int maxPoints(vector<vector<int>>& points)
{
    int maxCount = 0;
    auto n = points.size();
    if (n < 3)
        return n;
    for (auto i = 0; i < n; i++) {
        auto& base = points[i];
        unordered_map<string, int> counts;
        int dup = 1;
        for (auto j = i + 1; j < n; j++) {
            int dx = points[j][0] - base[0];
            int dy = points[j][1] - base[1];
            if (dx == 0 && dy == 0) {
                dup++;
                continue;
            }
            // normalize horizontal and vertical lines
            if (dx == 0) {
                dy = 1;
            } else if (dy == 0) {
                dx = 1;
            }
            int g = gcd(dx, dy);
            int normalizedDx = dx / g;
            int normalizedDy = dy / g;
            if (normalizedDx < 0) {
                normalizedDx = -normalizedDx;
                normalizedDy = -normalizedDy;
            }
            counts[to_string(normalizedDx) + '_' + to_string(normalizedDy)]++;
        }
        int maxCountFromBase = 0;
        for (auto& count : counts) {
            maxCountFromBase = max(maxCountFromBase, count.second);
        }
        maxCountFromBase += dup;
        maxCount = max(maxCount, maxCountFromBase);
    }
    return maxCount;
}
static void Test()
{
    vector<vector<int>> points = { {1,1},{3,2},{5,3},{4,1},{2,3},{1,4} };
    std::cout << maxPoints(points) << std::endl;
}
}
