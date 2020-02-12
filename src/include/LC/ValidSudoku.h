/*
36. Valid Sudoku My Submissions Question
Total Accepted: 67075 Total Submissions: 223815 Difficulty: Easy
Determine if a Sudoku is valid, according to: Sudoku Puzzles - The Rules.

The Sudoku board could be partially filled, where empty cells are filled with the character '.'.


A partially filled sudoku which is valid.

Note:
A valid Sudoku board (partially filled) is not necessarily solvable. Only the filled cells need to be validated.
*/

#include <iostream>
#include <queue>
#include <memory>
#include <cassert>
#include <algorithm>
#include "Common.h"

namespace ValidSudoku
{
bool isValidSudoku(vector<vector<char>>& board)
{
    static constexpr int n = 9;
    static constexpr int nMinor = 3;
    assert(board.size() == n);
    assert(board[0].size() == n);
    std::bitset<n> hist;
    // scan each row
    for (auto row = 0; row < n; row++) {
        hist.reset();
        for (auto col = 0; col < n; col++) {
            if (board[row][col] != '.') {
                int num = board[row][col] - '0';
                if (hist[num])
                    return false;
                hist[num] = 1;
            }
        }
    }
    // scan each col
    for (auto col = 0; col < n; col++) {
        hist.reset();
        for (auto row = 0; row < n; row++) {
            if (board[row][col] != '.') {
                int num = board[row][col] - '0';
                if (hist[num])
                    return false;
                hist[num] = 1;
            }
        }
    }
    // scan each row
    for (auto row = 0; row < n; row += nMinor) {
        for (auto col = 0; col < n; col += nMinor) {
            hist.reset();
            for (auto i = 0; i < n; i++) {
                auto rowMinor = i / nMinor;
                auto colMinor = i % nMinor;
                if (board[row + rowMinor][col + colMinor] != '.') {
                    int num = board[row + rowMinor][col + colMinor] - '0';
                    if (hist[num])
                        return false;
                    hist[num] = 1;
                }
            }
        }
    }
    return true;
}

void Test()
{
    vector<string> input{
        ".87654321",
        "2........",
        "3........",
        "4........",
        "5........",
        "6........",
        "7........",
        "8........",
        "9........"
    };
    
    for (auto& line : input)
    {
        cout << line << " " << endl;
    }
    
    vector<vector<char>> matrix;
    for (auto& line : input)
    {
        matrix.emplace_back(vector<char>(line.begin(), line.end()));
    }
    
    cout << "result: " << isValidSudoku(matrix) << endl;
}
}
