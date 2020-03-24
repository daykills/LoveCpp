/*
https://www.1point3acres.com/bbs/thread-570261-1-1.html
 模拟小球从board中滑落，假设board由n*m个cell组成，每个cell有对角线或者反对角线的墙壁，设计class模拟这个过程，class需要提供flip(row, col)方法翻转墙壁，dropBall(col)方法得出小球从顶端放入时从低端掉出的坐标(或者掉不出)。follow up 如果现场景dropBall()有million次的调用但是flip()调用很少该怎么优化
 第二题：dropBall(0) = 2; dropBall(1)会卡住
      0 1 2
 0 |\|\|/|
 1 |/|\|\|

*/

#include "Common.h"

namespace FlipBoard
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
