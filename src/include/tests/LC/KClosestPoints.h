/*
 973. K Closest Points to Origin
 We have a list of points on the plane.  Find the K closest points to the origin (0, 0).
 
 (Here, the distance between two points on a plane is the Euclidean distance.)
 
 You may return the answer in any order.  The answer is guaranteed to be unique (except for the order that it is in.)
*/

#include <iostream>
#include <queue>
#include <algorithm>
#include "Common.h"

namespace KClosestPoints
{
vector<vector<int>> kClosest(vector<vector<int>>& points, int K) {
    auto lessor = [&points](int i, int j) {
        return (points[i][0] * points[i][0] + points[i][1] * points[i][1]) <
        (points[j][0] * points[j][0] + points[j][1] * points[j][1]);
    };
    priority_queue<int, vector<int>, decltype(lessor)> maxHeap(lessor);
    for (auto i = 0; i < points.size(); i++) {
        if (maxHeap.size() < K) {
            maxHeap.push(i);
            continue;
        }
        // closer point found
        if (lessor(i, maxHeap.top())) {
            maxHeap.pop();
            maxHeap.push(i);
        }
    }
    vector<vector<int>> ans;
    ans.reserve(K);
    while (!maxHeap.empty()) {
        auto top = maxHeap.top();
        maxHeap.pop();
        ans.push_back(points[top]);
    }
    return ans;
}

void Test()
{
    vector<vector<int>> points = {
        { 1,3 }, { -2, 2 }, { 2, 4 }, { -1, 2 }, { 4, 1 }, { 3, 4 }
    };
    
    for (auto& pt : points)
    {
        cout << "x = " << pt[0] << " y = " << pt[1] << endl;
    }
    cout << "==============" << endl;
    auto result = kClosest(points, 3);
    for (auto& pt : result)
    {
        cout << "x = " << pt[0] << " y = " << pt[1] << endl;
    }
}
}
