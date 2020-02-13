/*
505. The Maze II

There is a ball in a maze with empty spaces and walls. The ball can go through empty spaces by rolling up, down, left or right, but it won't stop rolling until hitting a wall. When the ball stops, it could choose the next direction.

Given the ball's start position, the destination and the maze, find the shortest distance for the ball to stop at the destination. The distance is defined by the number of empty spaces traveled by the ball from the start position (excluded) to the destination (included). If the ball cannot stop at the destination, return -1.

The maze is represented by a binary 2D array. 1 means the wall and 0 means the empty space. You may assume that the borders of the maze are all walls. The start and destination coordinates are represented by row and column indexes.

Example 1:

Input 1: a maze represented by a 2D array

0 0 1 0 0
0 0 0 0 0
0 0 0 1 0
1 1 0 1 1
0 0 0 0 0

Input 2: start coordinate (rowStart, colStart) = (0, 4)
Input 3: destination coordinate (rowDest, colDest) = (4, 4)

Output: 12

Explanation: One shortest way is : left -> down -> left -> down -> right -> down -> right.
             The total distance is 1 + 1 + 3 + 1 + 2 + 2 + 2 = 12.
 
 Example 2:

 Input 1: a maze represented by a 2D array

 0 0 1 0 0
 0 0 0 0 0
 0 0 0 1 0
 1 1 0 1 1
 0 0 0 0 0

 Input 2: start coordinate (rowStart, colStart) = (0, 4)
 Input 3: destination coordinate (rowDest, colDest) = (3, 2)

 Output: -1

 Explanation: There is no way for the ball to stop at the destination.

 Note:

 There is only one ball and one destination in the maze.
 Both the ball and the destination exist on an empty space, and they will not be at the same position initially.
 The given maze does not contain border (like the red rectangle in the example pictures), but you could assume the border of the maze are all walls.
 The maze contains at least 2 empty spaces, and both the width and height of the maze won't exceed 100.
*/

#include <iostream>
#include <queue>
#include <algorithm>
#include <numeric>
#include "Common.h"

namespace Maze2
{

struct Ball {
    int row;
    int col;
    int dir;
};

int shortestDistance(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
    auto m = maze.size();
    auto n = maze[0].size();
    vector<vector<int>> dirs = { { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 } };
    queue<Ball> q;
    set<pair<int, int>> visited;
    for (auto i = 0; i < dirs.size(); i++)
        q.push({ start[0], start[1], i });
    int step = 0;
    while (!q.empty()) {
        auto cnt = q.size();
        for (auto i = 0; i < cnt; i++) {
            auto ball = q.front();
            q.pop();
            // ball is always at valid position
            auto nextRow = ball.row + dirs[ball.dir][0];
            auto nextCol = ball.col + dirs[ball.dir][1];
            // no obstacle, then continue rolling
            if (nextRow >= 0 && nextRow < m && nextCol >= 0 && nextCol < n
                && maze[nextRow][nextCol] == 0) {
                q.push({ nextRow, nextCol, ball.dir });
                continue;
            }
            // if the stop spot is visited, skip it
            if (visited.count(pair(ball.row, ball.col)))
                continue;
            visited.emplace(ball.row, ball.col);
            // check it here to make sure the ball is stopped
            if (ball.row == destination[0] && ball.col == destination[1])
                return step;
            // no go. Check other directions
            for (auto j = 0; j < dirs.size(); j++) {
                auto& dir = dirs[j];
                // skip same dir and reverse
                if (j == ball.dir || (dir[0] == -dirs[ball.dir][0] && dir[1] == -dirs[ball.dir][1]))
                    continue;
                nextRow = ball.row + dir[0];
                nextCol = ball.col + dir[1];
                // no obstacle, then continue rolling
                if (nextRow >= 0 && nextRow < m && nextCol >= 0 && nextCol < n
                    && maze[nextRow][nextCol] == 0) {
                    q.push({ nextRow, nextCol, j });
                }
            }
        }
        step++;
    }
    return -1;
}

static void Test()
{
    vector<vector<int>> maze = {
        /*
        { 0, 0, 1, 0, 0 },
        { 0, 0, 0, 0, 0 },
        { 0, 0, 0, 1, 0 },
        { 1, 1, 0, 1, 1 },
        { 0, 0, 0, 0, 0 },
         */
        { 0, 0, 1, 0, 0 },
        { 0, 0, 0, 0, 0 },
        { 0, 0, 0, 1, 0 },
        { 1, 1, 0, 1, 1 },
        { 0, 0, 0, 0, 0 },
    };
    vector<int> start = { 0, 4 };
    vector<int> dest = { 3, 2 };
    std::cout << shortestDistance(maze, start, dest) << std::endl;
}
}
