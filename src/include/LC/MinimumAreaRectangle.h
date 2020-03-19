/*
 939. Minimum Area Rectangle

 Given a set of points in the xy-plane, determine the minimum area of a rectangle formed from these points, with sides parallel to the x and y axes.

 If there isn't any rectangle, return 0.

 Example 1:

 Input: [[1,1},{1,3},{3,1},{3,3},{2,2]]
 Output: 4
 Example 2:

 Input: [[1,1},{1,3},{3,1},{3,3},{4,1},{4,3]]
 Output: 2
  

 Note:

 1 <= points.length <= 500
 0 <= points[i][0] <= 40000
 0 <= points[i][1] <= 40000
 All points are distinct.
*/

#include "Common.h"

namespace MinimumAreaRectangle
{
class Solution {
public:
    int minAreaRect(vector<vector<int>>& points) {
        if (points.empty()) return 0;
        map<int, set<int>> xy;
        for (auto& pt : points) {
            xy[pt[0]].emplace(pt[1]);
        }
        int minArea = INT_MAX;
        // choose one x pointed by it
        for (auto it1 = xy.begin(); it1 != xy.end(); it1++) {
            auto& ySet1 = it1->second;
            if (ySet1.size() < 2)
                continue;
            // choose another x
            for (auto it2 = next(it1); it2 != xy.end(); it2++) {
                auto& ySet2 = it2->second;
                if (ySet2.size() < 2)
                    continue;
                vector<int> ys;
                set_intersection(ySet1.begin(), ySet1.end(), ySet2.begin(), ySet2.end(), back_inserter(ys));
                if (ys.size() < 2)
                    continue;
                auto minDeltaY = ys[1] - ys[0];
                for (auto i = 1; i < ys.size() - 1; i++) {
                    minDeltaY = min(minDeltaY, ys[i + 1] - ys[i]);
                }
                minArea = min(minArea, minDeltaY * abs(it1->first - it2->first));
            }
        }
        return minArea == INT_MAX ? 0 : minArea;
    }
};

static void Test()
{
    vector<vector<int>> points = {
        //{1,1},{1,3},{3,1},{3,3},{2,2}
        {0,1},{3,2},{5,5},{4,5},{4,4},{2,0},{2,3},{2,2},{1,0},{5,1},{2,5},{5,2},{2,4},{4,0}
    };
    Solution s;
    std::cout << s.minAreaRect(points) << std::endl;
}
}
