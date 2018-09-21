#pragma once
/*
130. Surrounded Regions My Submissions Question
Total Accepted: 49590 Total Submissions: 311982 Difficulty: Medium
Given a 2D board containing 'X' and 'O', capture all regions surrounded by 'X'.

A region is captured by flipping all 'O's into 'X's in that surrounded region.

For example,
X X X X
X O O X
X X O X
X O X X
After running your function, the board should be:

X X X X
X X X X
X X X X
X O X X
*/

#include "Common.h"

namespace SurroundedRegions
{
	//////////////////////////
	void bfsMarkBoundary(vector<vector<char>>& board, int i, int j)
	{
		const vector<pair<int, int>> moves{ { 1, 0 },{ 0, 1 },{ -1, 0 },{ 0, -1 } };
		int m = board.size();
		int n = board[0].size();
		queue<pair<int, int>> q;
		board[i][j] = 'B';
		q.emplace(i, j);
		while (!q.empty())
		{
			// mark the front node as 'B'
			auto cur = q.front();			
			q.pop();

			for (auto& move : moves)
			{
				auto nextI = move.first + cur.first, nextJ = move.second + cur.second;
				if (nextI < 0 || nextI >= m || nextJ < 0 || nextJ >= n) continue;
				if (board[nextI][nextJ] == 'O')
				{
					board[nextI][nextJ] = 'B';
					q.emplace(nextI, nextJ);
				}
			}
		}
	}

	void myBfsSolve(vector<vector<char>>& board)
	{
		int m = board.size();
		if (m == 0) return;
		int n = board[0].size();

		for (int i = 0; i < m; i++)
		{
			if (board[i][0] == 'O')
			{
				bfsMarkBoundary(board, i, 0);
			}

			if (board[i][n - 1] == 'O')
			{
				bfsMarkBoundary(board, i, n - 1);
			}
		}
		for (int j = 0; j < n; j++)
		{
			if (board[0][j] == 'O')
			{
				bfsMarkBoundary(board, 0, j);
			}

			if (board[m - 1][j] == 'O')
			{
				bfsMarkBoundary(board, m - 1, j);
			}
		}
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (board[i][j] == 'O') board[i][j] = 'X';
				if (board[i][j] == 'B') board[i][j] = 'O';
			}
		}
	}
	//////////////////////////
	bool dfsSearchWayOut(vector<vector<char>>& board, int i, int j, const vector<pair<int, int>>& moves)
	{
		int m = board.size();
		int n = board[0].size();

		board[i][j] = 'X';

		for (auto& move : moves)
		{
			auto nextI = i + move.first, nextJ = j + move.second;
			// i,j is out of the grid, found way out!
			if (nextI >= m || nextI < 0 || nextJ >= n || nextJ < 0)
			{
				board[i][j] = 'O';
				return true;
			}

			// can only go to 'O'
			if (board[nextI][nextJ] == 'X') continue;
			// set nextIJ as 'X'
			board[nextI][nextJ] = 'X';
			// if on any direction, it finds way out, return true
			if (dfsSearchWayOut(board, nextI, nextJ, moves))
			{
				// if find way out, mark ij back to 'O', stop searching
				board[nextI][nextJ] = 'O';
				board[i][j] = 'O';
				return true;
			}
		}
		// couldn't find way out. ij is marked as X
		return false;
	}

	void solveDfs(vector<vector<char>>& board)
	{
		int m = board.size();
		if (m == 0) return;
		int n = board[0].size();
		vector<pair<int, int>> moves{ { 1, 0 },{ 0, 1 },{ -1, 0 },{ 0, -1 } };

		for (int i = 1; i < m - 1; i++)
		{
			for (int j = 1; j < n - 1; j++)
			{
				if (board[i][j] == 'O')
				{
					dfsSearchWayOut(board, i, j, moves);
				}
			}
		}
	}
	///////////////////////////
	void bfsBoundary(vector<vector<char> >& board, int w, int l)
	{
		int width = board.size();
		int length = board[0].size();
		deque<pair<int, int> > q;
		q.push_back(make_pair(w, l));
		board[w][l] = 'B';
		while (!q.empty()) {
			pair<int, int> cur = q.front();
			q.pop_front();
			pair<int, int> adjs[4] = { { cur.first - 1, cur.second },
			{ cur.first + 1, cur.second },
			{ cur.first, cur.second - 1 },
			{ cur.first, cur.second + 1 } };
			for (int i = 0; i < 4; ++i)
			{
				int adjW = adjs[i].first;
				int adjL = adjs[i].second;
				if ((adjW >= 0) && (adjW < width) && (adjL >= 0)
					&& (adjL < length)
					&& (board[adjW][adjL] == 'O')) {
					q.push_back(make_pair(adjW, adjL));
					board[adjW][adjL] = 'B';
				}
			}
		}
	}

	void solve(vector<vector<char> > &board) {
		int width = board.size();
		if (width == 0) //Add this to prevent run-time error!
			return;
		int length = board[0].size();
		if (length == 0) // Add this to prevent run-time error!
			return;

		for (int i = 0; i < length; ++i)
		{
			if (board[0][i] == 'O')
				bfsBoundary(board, 0, i);

			if (board[width - 1][i] == 'O')
				bfsBoundary(board, width - 1, i);
		}

		for (int i = 0; i < width; ++i)
		{
			if (board[i][0] == 'O')
				bfsBoundary(board, i, 0);
			if (board[i][length - 1] == 'O')
				bfsBoundary(board, i, length - 1);
		}

		for (int i = 0; i < width; ++i)
		{
			for (int j = 0; j < length; ++j)
			{
				if (board[i][j] == 'O')
					board[i][j] = 'X';
				else if (board[i][j] == 'B')
					board[i][j] = 'O';
			}
		}
	}
	///////////////////////////

	void Test()
	{
		vector<string> boardStr
		{
			"XOOOOOOOOOOOOOOOOOOO","OXOOOOXOOOOOOOOOOOXX","OOOOOOOOXOOOOOOOOOOX","OOXOOOOOOOOOOOOOOOXO","OOOOOXOOOOXOOOOOXOOX","XOOOXOOOOOXOXOXOXOXO","OOOOXOOXOOOOOXOOXOOO","XOOOXXXOXOOOOXXOXOOO","OOOOOXXXXOOOOXOOXOOO","XOOOOXOOOOOOXXOOXOOX","OOOOOOOOOOXOOXOOOXOX","OOOOXOXOOXXOOOOOXOOO","XXOOOOOXOOOOOOOOOOOO","OXOXOOOXOXOOOXOXOXOO","OOXOOOOOOOXOOOOOXOXO","XXOOOOOOOOXOXXOOOXOO","OOXOOOOOOOXOOXOXOXOO","OOOXOOOOOXXXOOXOOOXO","OOOOOOOOOOOOOOOOOOOO","XOOOOXOOOXXOOXOXOXOO"
		};

		vector<vector<char>> board;
		cout << "Matrix: " << endl;
		for (auto& line : boardStr)
		{
			vector<char> lineCh;
			for (auto ch : line)
			{
				cout << ch << " ";
				lineCh.emplace_back(ch);
			}
			board.emplace_back(move(lineCh));
			cout << endl;
		}
		solve(board);
		auto dfsResult = board;
		myBfsSolve(dfsResult);

		cout << "Compare: " << endl;
		int m = board.size();
		int n = board.size();
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (board[i][j] != dfsResult[i][j])
					cout << i << " " << j << endl;
			}
		}
		
		cout << "Result: " << endl;
		for (auto& line : board)
		{
			for (auto ch : line)
			{
				cout << ch << " ";
			}
			cout << endl;
		}
	}
}