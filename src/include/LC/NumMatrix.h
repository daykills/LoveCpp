/*
304. Range Sum Query 2D - Immutable

Given a 2D matrix matrix, find the sum of the elements inside the rectangle defined by its upper left corner (row1, col1) and lower right corner (row2, col2).

Range Sum Query 2D
The above rectangle (with the red border) is defined by (row1, col1) = (2, 1) and (row2, col2) = (4, 3), which contains sum = 8.

Example:

Given matrix = [
  [3, 0, 1, 4, 2],
  [5, 6, 3, 2, 1],
  [1, 2, 0, 1, 5],
  [4, 1, 0, 1, 7],
  [1, 0, 3, 0, 5]
]

sumRegion(2, 1, 4, 3) -> 8
sumRegion(1, 1, 2, 2) -> 11
sumRegion(1, 2, 2, 4) -> 12
Note:

You may assume that the matrix does not change.
There are many calls to sumRegion function.
You may assume that row1 ≤ row2 and col1 ≤ col2.
 */

#include <iostream>
#include <list>
#include "Common.h"

namespace NumMatrix
{

static vector<vector<int>> s_dummy;

class NumMatrix {
public:
    NumMatrix(vector<vector<int>>& matrix) : m_matrix(matrix.empty() ? s_dummy : matrix) {
        preprocess();
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        auto m = m_matrix.size();
        if (m == 0)
            return 0;
        auto n = m_matrix[0].size();
        if (n == 0)
            return 0;
        assert(row1 <= row2 && col1 <= col2);
        auto sum = m_matrix[row2][col2];
        if (row1 == 0 && col1 == 0)
            return sum;
        if (row1 > 0 && col1 > 0)
            sum += m_matrix[row1 - 1][col1 - 1] - m_matrix[row2][col1 - 1] - m_matrix[row1 - 1][col2];
        else if (row1 == 0)
            sum -= m_matrix[row2][col1 - 1];
        else // col1 == 0
            sum -= m_matrix[row1 - 1][col2];
        return sum;
    }
private:
    void preprocess() {
        auto m = m_matrix.size();
        if (m == 0)
            return;
        auto n = m_matrix[0].size();
        if (n == 0)
            return;
        for (auto i = 0; i < m; i++) {
            auto sumInRow = 0;
            for (auto j = 0; j < n; j++) {
                sumInRow += m_matrix[i][j];
                m_matrix[i][j] = sumInRow;
                if (i > 0) m_matrix[i][j] += m_matrix[i - 1][j];
            }
        }
    }
    vector<vector<int>>& m_matrix;
};

static void Test()
{
    vector<vector<int>> matrix = {
        {3,0,1,4,2},
        {5,6,3,2,1},
        {1,2,0,1,5},
        {4,1,0,1,7},
        {1,0,3,0,5}};
    NumMatrix* obj = new NumMatrix(matrix);
    std::cout << obj->sumRegion(2,1,4,3) << std::endl;
    std::cout << obj->sumRegion(1,1,2,2) << std::endl;
    std::cout << obj->sumRegion(1,2,2,4) << std::endl;
}
}
