/*
https://oss.1point3acres.cn/forum/201903/04/135658fpf1ci11i1svssk9.png
Problem Description:


 
*/

#include <iostream>
#include <algorithm>
#include "Common.h"

namespace ClosestXdestinations
{

vector<vector<int>> closestXdestinations(vector<vector<int>>& locations, int numDeliveries) {
    auto lessor = [&locations](int i, int j) {
        auto& p1 = locations[i];
        auto dist1 = p1[0] * p1[0] + p1[1] * p1[1];
        auto& p2 = locations[j];
        auto dist2 = p2[0] * p2[0] + p2[1] * p2[1];
        return dist1 < dist2;
    };
    set<int, decltype(lessor)> sorted(lessor);
    for (int i = 0; i < locations.size(); i++)
        sorted.emplace(i);
    vector<vector<int>> deliveries;
    for (auto i : sorted) {
        if (deliveries.size() == numDeliveries)
            break;
        deliveries.push_back(locations[i]);
    }
    return deliveries;
}

void Test()
{
    vector<vector<int>> locations = {
        { 1, 2 },
        { 3, 4 },
        { 1, -1 },
    };
    
    auto deliveries = closestXdestinations(locations, 2);
    for (auto& delivery : deliveries)
        cout << delivery[0] << ", " << delivery[1] << endl;
}

}
