/*
 909. Snakes and Ladders

 On an N x N board, the numbers from 1 to N*N are written boustrophedonically starting from the bottom left of the board, and alternating direction each row.  For example, for a 6 x 6 board, the numbers are written as follows:


 You start on square 1 of the board (which is always in the last row and first column).  Each move, starting from square x, consists of the following:

 You choose a destination square S with number x+1, x+2, x+3, x+4, x+5, or x+6, provided this number is <= N*N.
 (This choice simulates the result of a standard 6-sided die roll: ie., there are always at most 6 destinations, regardless of the size of the board.)
 If S has a snake or ladder, you move to the destination of that snake or ladder.  Otherwise, you move to S.
 A board square on row r and column c has a "snake or ladder" if board[r][c] != -1.  The destination of that snake or ladder is board[r][c].

 Note that you only take a snake or ladder at most once per move: if the destination to a snake or ladder is the start of another snake or ladder, you do not continue moving.  (For example, if the board is `[[4,-1},{-1,3]]`, and on the first move your destination square is `2`, then you finish your first move at `3`, because you do not continue moving to `4`.)

 Return the least number of moves required to reach square N*N.  If it is not possible, return -1.

 Example 1:

 Input: [
 {-1,-1,-1,-1,-1,-1},
 {-1,-1,-1,-1,-1,-1},
 {-1,-1,-1,-1,-1,-1},
 {-1,35,-1,-1,13,-1},
 {-1,-1,-1,-1,-1,-1},
 {-1,15,-1,-1,-1,-1}]
 Output: 4
 Explanation:
 At the beginning, you start at square 1 [at row 5, column 0].
 You decide to move to square 2, and must take the ladder to square 15.
 You then decide to move to square 17 (row 3, column 5), and must take the snake to square 13.
 You then decide to move to square 14, and must take the ladder to square 35.
 You then decide to move to square 36, ending the game.
 It can be shown that you need at least 4 moves to reach the N*N-th square, so the answer is 4.
 Note:

 2 <= board.length = board[0].length <= 20
 board[i][j] is between 1 and N*N or is equal to -1.
 The board square with number 1 has no snake or ladder.
 The board square with number N*N has no snake or ladder.
 */


#include "Common.h"

namespace SnakesAndLadders
{

void numToPosition(int num, int n, int& row, int& col) {
    assert(num <= n * n && num >= 1);
    auto inverseRow = (num - 1) / n;
    col = (num - 1) % n;
    if (inverseRow % 2 == 1)
        col = n - 1 - col;
    row = n - 1 - inverseRow;
}

int snakesAndLadders(vector<vector<int>>& board) {
    auto n = board.size();
    assert(n > 0);
    assert(n == board[0].size());
    queue<int> q;
    q.emplace(1);
    int step = 0;
    int nTotal = n * n;
    vector<int> visited(nTotal + 1, 0);
    while (!q.empty()) {
        auto cnt = q.size();
        for (auto i = 0; i < cnt; i++) {
            auto num = q.front(); q.pop();
            if (num == n * n)
                return step;
            visited[num] = 1;
            for (auto nextNum = num + 1; nextNum <= min(nTotal, num + 6); nextNum++) {
                int nextRow, nextCol;
                numToPosition(nextNum, n, nextRow, nextCol);
                
                auto jump = board[nextRow][nextCol];
                auto trueNextNum = jump != -1 ? jump : nextNum;
                if (visited[trueNextNum])
                    continue;
                q.emplace(trueNextNum);
            }
        }
        step++;
    }
    return -1;
}

static void Test()
{
    /*
    vector<vector<int>> board {
        {-1,-1,-1,-1,-1,-1},
        {-1,-1,-1,-1,-1,-1},
        {-1,-1,-1,-1,-1,-1},
        {-1,35,-1,-1,13,-1},
        {-1,-1,-1,-1,-1,-1},
        {-1,15,-1,-1,-1,-1},
    };
     */
    /*
    vector<vector<int>> board {
        {-1,-1,-1},
        {-1,9,8},
        {-1,8,9},
    };
     */
    /*
    vector<vector<int>> board {
        {1,1,-1},
        {1,1,1},
        {-1,1,1},
    };
    */
    vector<vector<int>> board {
        {-1,-1,19,10,-1},
        {2,-1,-1,6,-1},
        {-1,17,-1,19,-1},
        {25,-1,20,-1,-1},
        {-1,-1,-1,-1,15},
    };
    
    cout << snakesAndLadders(board) << endl;
}
}
