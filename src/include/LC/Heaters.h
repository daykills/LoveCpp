/*
475. Heaters

Winter is coming! Your first job during the contest is to design a standard heater with fixed warm radius to warm all the houses.

Now, you are given positions of houses and heaters on a horizontal line, find out minimum radius of heaters so that all houses could be covered by those heaters.

So, your input will be the positions of houses and heaters seperately, and your expected output will be the minimum radius standard of heaters.

Note:

Numbers of houses and heaters you are given are non-negative and will not exceed 25000.
Positions of houses and heaters you are given are non-negative and will not exceed 10^9.
As long as a house is in the heaters' warm radius range, it can be warmed.
All the heaters follow your radius standard and the warm radius will the same.
 

Example 1:

Input: [1,2,3],[2]
Output: 1
Explanation: The only heater was placed in the position 2, and if we use the radius 1 standard, then all the houses can be warmed.
 

Example 2:

Input: [1,2,3,4],[1,4]
Output: 1
Explanation: The two heater was placed in the position 1 and 4. We need to use radius 1 standard, then all the houses can be warmed.
*/

#include <iostream>
#include <queue>
#include <algorithm>
#include <numeric>
#include "Common.h"

namespace Heaters
{

int findRadius(vector<int>& houses, vector<int>& heaters) {
    if (!is_sorted(houses.begin(), houses.end()))
        sort(houses.begin(), houses.end());
    if (!is_sorted(heaters.begin(), heaters.end()))
        sort(heaters.begin(), heaters.end());
    int minRadius = 0;
    auto it = heaters.begin();
    for (auto house : houses) {
        auto firstNoLess = lower_bound(it, heaters.end(), house);
        int minDistance = INT_MAX;
        if (firstNoLess != heaters.end()) {
            it = firstNoLess;
            minDistance = *it - house;
        }
        if (firstNoLess != heaters.begin()) {
            it = firstNoLess - 1;
            minDistance = min(minDistance, house - *it);
        }
        minRadius = max(minRadius, minDistance);
    }
    return minRadius;
}

static void Test()
{
    vector<int> houses = { 282475249,622650073,984943658,144108930,470211272,101027544,457850878,458777923 };
    vector<int> heaters = { 823564440,115438165,784484492,74243042,114807987,137522503,441282327,16531729,823378840,143542612 };
    std::cout << findRadius(houses, heaters) << std::endl;
}
}
