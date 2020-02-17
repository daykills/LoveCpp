/*
 85. Maximal Rectangle

 Given a 2D binary matrix filled with 0's and 1's, find the largest rectangle containing only 1's and return its area.
 
 Example:
 
 Input:
 [
 ["1","0","1","0","0"],
 ["1","0","1","1","1"],
 ["1","1","1","1","1"],
 ["1","0","0","1","0"]
 ]
 Output: 6
*/

#include <algorithm>
#include <unordered_set>
#include "Common.h"

namespace MaximalRectangle
{

int maximalRectangle(vector<vector<char>>& matrix) {
    auto m = matrix.size();
    if (m == 0) return 0;
    auto n = matrix[0].size();
    if (n == 0) return 0;
    int maxArea = 0;
    // histogram based on each row
    vector<int> hist(n + 1, 0);
    for (auto i = 0; i < m; i++) {
        // calculate max histogram area based on hist
        // refer to Largest Rectangle in Histogram
        // s to store a monotone increasing stack
        stack<int> s;
        // n + 1 as we need to clear the stack at the end
        for (auto j = 0; j < n + 1; j++) {
            hist[j] = (j == n || matrix[i][j] == '0') ? 0 : hist[j] + 1;
            // clear stack until all elements are smaller than hist[j]
            while (!s.empty() && hist[j] <= hist[s.top()]) {
                auto cur = s.top(); s.pop();
                auto span = s.empty() ? j : (j - 1 - s.top());
                maxArea = max(maxArea, span * hist[cur]);
            }
            s.push(j);
        }
    }
    return maxArea;
}

void Test() {
    vector<vector<char>> matrix = {
        {'1','0','1','0','0'},
        {'1','0','1','1','1'},
        {'1','1','1','1','1'},
        {'1','0','0','1','0'}
    };
    cout << maximalRectangle(matrix) << endl;
}
}
