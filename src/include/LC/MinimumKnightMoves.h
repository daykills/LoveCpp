/*
1197. Minimum Knight Moves

In an infinite chess board with coordinates from -infinity to +infinity, you have a knight at square [0, 0].

A knight has 8 possible moves it can make, as illustrated below. Each move is two squares in a cardinal direction, then one square in an orthogonal direction.
 
Return the minimum number of steps needed to move the knight to the square [x, y].  It is guaranteed the answer exists.

Example 1:

Input: x = 2, y = 1
Output: 1
Explanation: [0, 0] → [2, 1]
Example 2:

Input: x = 5, y = 5
Output: 4
Explanation: [0, 0] → [2, 1] → [4, 2] → [3, 4] → [5, 5]
 

Constraints:

|x| + |y| <= 300
*/
#include <string>
#include <iostream>
#include "Common.h"

namespace MinimumKnightMoves
{
class Solution {
public:
    int minKnightMoves(int x, int y) {
        vector<vector<int>> dirs {
            { 1, 2 }, { 2, 1 }, { 2, -1 }, { 1, -2 },
            { -1, -2 }, { -2, -1 }, { -2, 1 }, { -1, 2 },
        };
        unordered_set<string> visited;
        queue<pair<int, int>> q;
        q.emplace(0, 0);
        int step = 0;
        while (true) {
            auto n = q.size();
            for (auto i = 0; i < n; i++) {
                auto cur = q.front(); q.pop();
                if (cur.first == x && cur.second == y)
                    return step;
                auto hashCode = to_string(cur.first) + "_" + to_string(cur.second);
                if (visited.count(hashCode))
                    continue;
                visited.emplace(hashCode);
                for (auto& dir : dirs) {
                    auto nextX = dir[0] + cur.first;
                    auto nextY = dir[1] + cur.second;
                    q.emplace(nextX, nextY);
                }
            }
            step++;
        }
        assert(false);
        return -1;
    }
};

static void Test()
{
    Solution s;
    cout << s.minKnightMoves(5, 5) << endl;    // should be 8
}

}
