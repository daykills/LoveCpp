/*
 773. Sliding Puzzle
 
 On a 2x3 board, there are 5 tiles represented by the integers 1 through 5, and an empty square represented by 0.
 
 A move consists of choosing 0 and a 4-directionally adjacent number and swapping it.
 
 The state of the board is solved if and only if the board is [[1,2,3],[4,5,0]].
 
 Given a puzzle board, return the least number of moves required so that the state of the board is solved. If it is impossible for the state of the board to be solved, return -1.
 
 Examples:
 
 Input: board = [[1,2,3],[4,0,5]]
 Output: 1
 Explanation: Swap the 0 and the 5 in one move.
 Input: board = [[1,2,3],[5,4,0]]
 Output: -1
 Explanation: No number of moves will make the board solved.
 Input: board = [[4,1,2],[5,0,3]]
 Output: 5
 Explanation: 5 is the smallest number of moves that solves the board.
 An example path:
 After move 0:
 [[4,1,2]
 ,[5,0,3]]
 After move 1:
 [[4,1,2]
 ,[0,5,3]]
 After move 2:
 [[0,1,2]
 ,[4,5,3]]
 After move 3:
 [[1,0,2]
 ,[4,5,3]]
 After move 4:
 [[1,2,0]
 ,[4,5,3]]
 After move 5:
 [[1,2,3]
 ,[4,5,0]]
 Input: board = [[3,2,4],[1,5,0]]
 Output: 14
*/
#include <iostream>
#include <queue>
#include <algorithm>
#include "Common.h"

namespace SlidingPuzzle
{
int slidingPuzzle(vector<vector<int>>& board) {
    string target = "123450";
    vector<vector<int>> moves = {
        {1,3}, // 0 -> 1, 3
        {0,2,4},
        {1,5},
        {0,4},
        {1,3,5},
        {2,4}
    };
    unordered_set<string> visited;
    queue<vector<char>> q;
    vector<char> initial;
    for (auto& row : board) {
        for (auto cell : row) {
            initial.push_back(cell + '0');
        }
    }
    q.push(initial);
    int steps = 0;
    while (!q.empty()) {
        auto count = q.size();
        for (auto i = 0; i < count; i++) {
            auto vect = move(q.front());
            q.pop();
            if (string(vect.data(), vect.size()) == target)
                return steps;
            auto pos = distance(vect.begin(), find(vect.begin(), vect.end(), '0'));
            assert(pos != vect.size());
            for (auto next : moves[pos]) {
                swap(vect[pos], vect[next]);
                q.push(vect);
                swap(vect[next], vect[pos]);
            }
        }
        steps++;
    }
    return steps;
}
void Test() {
    vector<vector<int>> board = {
        {4,1,2},
        {5,0,3}
    };
    cout << slidingPuzzle(board) << endl;
}
}
