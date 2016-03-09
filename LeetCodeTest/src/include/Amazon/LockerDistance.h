#pragma once
/*
A city is represented as a 2D grid. Amazon could put lockers on cross points of the grid.

You're given the city scale: int cityLength, int cityWidth, both range [1 ~ 9];
Also given vector<int> lockerXCoordinates, vector<int> lockerYCoordinates to represent the locker locations (coordinate). Coordinates are 1 based, not 0.

For each cross point, find the distance to the nearest locker.

For example, if it's a city of 3 * 5; and locker location is [1, 1], you should have the return as below:

0 1 2
1 2 3
2 3 4
3 4 5
4 5 6

*/

#include <iostream>
#include <string>
#include <memory>
#include <fstream>
#include <queue>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <cassert>
#include <Common.h>

using namespace std;

namespace LockerDistance
{
  // as given, the maximum possible length/width are blow
  static const int MAX_I_SIZE = 10;
  static const int MAX_J_SIZE = 10;
  static const int DISTANCE_UNDEFINED = -1;
  static const int NUM_MOVES = 4;

  // direction 0 - i++; 1 - j++; 2 - i--; 3 - j--; others error
  void move(int& i, int& j, int direction)
  {
    if (direction == 0) i++;
    else if (direction == 1) j++;
    else if (direction == 2) i--;
    else if (direction == 3) j--;
    else assert(false);
  }  

  // should have used depth first method to find the distance for grid[i][j]
  // but I just forgot how to do it in graph
  void updateDistance(vector<vector<int>>& grid, int blockI, int blockJ)
  {
    const int maxI = grid.size();
    const int maxJ = grid[0].size();

    assert(blockI < maxI);
    assert(blockJ < maxJ);

    // for breadth first search, save whether a block is visited
    int visited[MAX_I_SIZE][MAX_J_SIZE] = { 0 };

    queue<pair<int, int>> blockQueue;

    blockQueue.emplace(blockI, blockJ);
    visited[blockI][blockJ] = 1;

    // BFS to find the minimum distance
    while (!blockQueue.empty())
    {
      auto curI = blockQueue.front().first;
      auto curJ = blockQueue.front().second;
      blockQueue.pop();
      // found a locker. since it's BFS search, this locker is the nearest.
      if (grid[curI][curJ] == 0)
      {
        grid[blockI][blockJ] = abs(curI - blockI) + abs(curJ - blockJ);
        return;
      }
      // add four neighbour points into queue if they're not visited yet
      for (int i = 0; i < NUM_MOVES; i++)
      {
        int nextI = curI, nextJ = curJ;
        move(nextI, nextJ, i);
        // check boundary
        if (nextI < 0 || nextI >= MAX_I_SIZE || nextJ < 0 || nextJ >= MAX_J_SIZE
          || nextI >= maxI || nextJ >= maxJ)
          continue;
        if (visited[nextI][nextJ] == 0)
        {
          visited[nextI][nextJ] = 1;
          blockQueue.emplace(nextI, nextJ);
        }
      }      
    }

    // no locker found
    assert(false);
  }

  vector<vector<int>> getLockerDistanceGrid(int cityLength, int cityWidth, vector<int> lockerXCoordinates, vector<int> lockerYCoordinates)
  {
    // length along x, width along y direction.
    // the initial value -1 means the distance is not identified; 0 means a locker is right there.
    vector<vector<int>> grid(cityLength, vector<int>(cityWidth, DISTANCE_UNDEFINED));
    // xy coord should match
    assert(lockerXCoordinates.size() == lockerYCoordinates.size());
    // set locker location, index starting at 0. if lock is located at i,j, then grid[i][j] = 0
    for (int iLocker = 0; iLocker < (int)lockerXCoordinates.size(); iLocker++)
    {
      int i = lockerXCoordinates[iLocker] - 1;
      int j = lockerYCoordinates[iLocker] - 1;
      grid[i][j] = 0;
    }
    for (int i = 0; i < cityLength; i++)
    {
      for (int j = 0; j < cityWidth; j++)
      {
        if (grid[i][j] == 0) continue;
        updateDistance(grid, i, j);
      }
    }
    return grid;
  }

  void Test()
  {
    /*
    3 5 1 1
    */
    int len = 9;
    int wid = 9;
    auto lockerX = vector<int> { 2, 3, 6, 3, 7, 3 };
    auto lockerY = vector<int> { 1, 4, 4, 7, 4, 8 };
    auto result = getLockerDistanceGrid(len, wid, lockerX, lockerY);

    for (auto j = 0; j < wid; j++)
    {
      for (auto i = 0; i < len; i++)
        cout << result[i][j] << " ";
      cout << endl;
    }
  }
}