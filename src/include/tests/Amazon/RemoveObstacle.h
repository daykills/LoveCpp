/*
https://oss.1point3acres.cn/forum/201903/04/135659q2ydaakokak2yd2z.png
Problem Description:

You are in charge of preparing a recently purchased lot for one of a new building. The lot is covered with trenches and has a single obstacle that needs to be taken down before the foundation can be prepared for the building. The demolition robot must remove the obstacle before progress can be made on the building. Write an algorithm to determine the minimum distance required for the demolition robot to remove the obstacle.

Assumptions:

 The lot is flat, except for trenches, and can be represented as a 2-D grid.
 The demolition robot must start from the top left corner of the lot, which is always flat and can move one block up, down, right or left at a time.
 The demolition robot cannot enter trenches and cannot leave the lot.
 The flat areas are represented as 1, areas with trenches as 0 and obstacle by 9.
 
Input:
 lot, representing the two-dimensional grid of integers
 
Output:

Return an integer representing the minimum distance traversed to remove the obstacle else return -1.
 
*/

#include <iostream>
#include <algorithm>
#include "Common.h"

namespace RemoveObstacle
{

int removeObstacle(vector<vector<int>>& lot) {
    auto m = lot.size();
    auto n = lot[0].size();
    queue<pair<int, int>> q;
    q.emplace(0, 0);
    int distance = 0;
    while (!q.empty()) {
        auto count = q.size();
        for (auto k = 0; k < count; k++) {
            auto i = q.front().first;
            auto j = q.front().second;
            q.pop();
            if (i < 0 || i >= m || j < 0 || i >= n || lot[i][j] == 0)
                continue;
            if (lot[i][j] == 9)
                return distance;
            q.emplace(i - 1, j);
            q.emplace(i + 1, j);
            q.emplace(i, j - 1);
            q.emplace(i, j + 1);
        }
        distance++;
    }
    return 0;
}

int Test()
{
    vector<vector<int>> lot = {
        { 1, 0, 0 },
        { 1, 0, 0 },
        { 1, 9, 1 },
    };
    
    cout << removeObstacle(lot) << endl;
    
    return 0;
}

}
