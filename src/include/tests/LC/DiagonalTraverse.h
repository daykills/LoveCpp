/*
 Given a sorted integer array where the range of elements are [0, 99] inclusive, return its missing ranges.
 For example, given [0, 1, 3, 50, 75], return [“2”, “4->49”, “51->74”, “76->99”]
 */

#include "Common.h"

namespace DiagonalTraverse
{
class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& matrix) {
        // delta row and col, and steps alone the direction
        vector<vector<int>> dirs = { { -1, 1 }, { 1, - 1 } };
        auto m = matrix.size();
        if (m == 0)
            return {};
        auto n = matrix[0].size();
        if (n == 0)
            return {};
        vector<int>  ans;
        ans.reserve(m * n);
        int row = 0;
        int col = 0;
        int iDir = 0;
        ans.push_back(matrix[row][col]);
        while (ans.size() < m * n) {
            int nextRow = row + dirs[iDir][0];
            int nextCol = col + dirs[iDir][1];
            
            if (nextRow >= 0 && nextRow < m && nextCol >= 0 && nextCol < n) {
                row = nextRow;
                col = nextCol;
            } else {
                // there are six possible cases that it may go out of scope
                // start with "nextRow >= m" and "nextCol >= n" because each of them covers two cases
                if (nextRow == m) {
                    row = m - 1;
                    // left-bottom coner: col = 1
                    // bottom side: col = col + 1
                    col = col + 1;
                } else if (nextCol == n) {
                    // right-top corner: row = 1
                    // right side: row = row + 1
                    col = n - 1;
                    row = row + 1;
                } else if (nextRow < 0) {
                    // top side
                    row = 0;
                    col = col + 1;
                } else {
                    assert(nextCol < 0);
                    // left side
                    col = 0;
                    row = row + 1;
                }
                iDir = (iDir + 1) % 2;
            }
            assert(row < m && row >= 0 && col < n && col >= 0);
            ans.push_back(matrix[row][col]);
        }
        return ans;
    }
};


static void Test()
{
    Solution solution;
    vector<vector<int>> matrix = {
        { 0, 1, 2, 3 },
        { 4, 5, 6, 7 },
        { 8, 9, 10, 11 }
    };
    auto res = solution.findDiagonalOrder(matrix);
    for (auto range: res)
        std::cout << range << std::endl;
}
}
