#pragma once
/*
 311. Sparse Matrix Multiplication

 Given two sparse matrices A and B, return the result of AB.
 
 You may assume that A's column number is equal to B's row number.
 
 Example:
 
 Input:
 
 A = [
 [ 1, 0, 0],
 [-1, 0, 3]
 ]
 
 B = [
 [ 7, 0, 0 ],
 [ 0, 0, 0 ],
 [ 0, 0, 1 ]
 ]
 
 Output:
 
 |  1 0 0 |   | 7 0 0 |   |  7 0 0 |
 AB = | -1 0 3 | x | 0 0 0 | = | -7 0 3 |
 | 0 0 1 |
*/

#include "Common.h"

namespace SparseMatrixMultiplication
{

class Solution {
public:
    // only store non-zero values
    // [i][j] -> val
    map<int, map<int, int>> getSparseMatrix(vector<vector<int>>& matrix, bool byRow) {
        auto m = matrix.size();
        assert(m);
        auto n = matrix[0].size();
        assert(n);
        map<int, map<int, int>> sparse;
        if (byRow) {
            for (auto i = 0; i < m; i++) {
                for (auto j = 0; j < n; j++) {
                    if (matrix[i][j] == 0) continue;
                    if (sparse.empty() || sparse.count(i) == 0) {
                        sparse.emplace(i, map<int, int>());
                    }
                    auto& curVec = sparse[i];
                    curVec[j] = matrix[i][j];
                }
            }
        } else {
            // column
            for (auto j = 0; j < n; j++) {
                for (auto i = 0; i < m; i++) {
                    if (matrix[i][j] == 0) continue;
                    if (sparse.empty() || sparse.count(j) == 0) {
                        sparse.emplace(j, map<int, int>());
                    }
                    auto& curVec = sparse[j];
                    curVec[i] = matrix[i][j];
                }
            }
        }
        return sparse;
    };
    
    int multplyVec(map<int, int>& vec1, map<int, int>& vec2) {
        auto it1 = vec1.begin();
        auto it2 = vec2.begin();
        int result = 0;
        while (it1 != vec1.end() && it2 != vec2.end()) {
            if (it1->first == it2->first) {
                result += it1->second * it2->second;
                it1++;
                it2++;
            }
            else if (it1->first < it2->first)
                it1++;
            else
                it2++;
        }
        return result;
    }
    
    vector<vector<int>> multiply(vector<vector<int>>& A, vector<vector<int>>& B) {
        auto m = A.size();
        assert(m);
        auto n = A[0].size();
        assert(n);
        assert(n == B.size());
        auto l = B[0].size();
        assert(l);
        
        auto sparseA = getSparseMatrix(A, true);
        auto sparseB = getSparseMatrix(B, false);
        vector<vector<int>> result(m, vector<int>(l, 0));
        
        auto itA = sparseA.begin();
        for (auto i = 0; i < m && itA != sparseA.end(); i++) {
            if (i != itA->first) continue;
            auto itB = sparseB.begin();
            for (auto j = 0; j < l && itB != sparseB.end(); j++) {
                if (j != itB->first) continue;
                result[i][j] = multplyVec(itA->second, itB->second);
                itB++;
            }
            itA++;
        }
        return result;;
    }
};

void Test()
{
    vector<vector<int>> matrixA {
        {1, 1},
        {1, 0}
    };
    vector<vector<int>> matrixB {
        { 1, 0 },
        { 1, 0 },
    };
    Solution s;
    auto result = s.multiply(matrixA, matrixB);
    for (auto& row : result) {
        for (auto v : row) {
            cout << v << ", ";
        }
        cout << endl;
    }
}
}
