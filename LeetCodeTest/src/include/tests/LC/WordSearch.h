/*
79. Word Search My Submissions Question
Total Accepted: 69358 Total Submissions: 307520 Difficulty: Medium
Given a 2D board and a word, find if the word exists in the grid.

The word can be constructed from letters of sequentially adjacent cell, where "adjacent" cells are those horizontally or vertically neighboring. The same letter cell may not be used more than once.

For example,
Given board =

[
['A','B','C','E'],
['S','F','C','S'],
['A','D','E','E']
]
word = "ABCCED", -> returns true,
word = "SEE", -> returns true,
word = "ABCB", -> returns false.
*/

#include <iostream>
#include <queue>
#include <memory>
#include <cassert>
#include <algorithm>
#include <vector>
#include "Common.h"

namespace WordSearch
{
	// row/col is assured to be valid, pos is valid as well
	bool dfs(vector<vector<char>>& board, const string& word, int pos, int row, int col)
	{
		// if ch at pos doesn't match
		if (board[row][col] != word[pos] || board[row][col] == 0) return false;

		// base condition: when the whole word is found
		auto newPos = pos + 1;
		if (newPos == (int)word.length()) return true;

		// all four moves
		static const vector<pair<int, int>> moves{ { 1, 0 },{ 0, 1 },{ -1, 0 },{ 0, -1 } };

		// mark this char is used
		board[row][col] = 0;

		auto found = false;
		for (const auto& move : moves)
		{
			auto newRow = move.first + row, newCol = move.second + col;
			// if row/col is out of bound
			if (newRow < 0 || newRow >= (int)board.size() || newCol < 0 || newCol >= (int)board[0].size()) continue;

			// search for next steps
			found = dfs(board, word, newPos, newRow, newCol);
			if (found) break;
		}
		// set the char back
		board[row][col] = word[pos];
		return found;
	}

	bool exist(vector<vector<char>>& board, string word)
	{
		int n = word.length();
		if (n == 0) return true;
		if (board.size() == 0) return false;
		for (auto row = 0; row < (int)board.size(); row++)
		{
			for (auto col = 0; col < (int)board[0].size(); col++)
			{
				// start dfs search from each point
				if (dfs(board, word, 0, row, col)) return true;
			}
		}
		return false;
	}

	void Test()
	{
		vector<vector<char>> board
		{
		  { 'A' }
		};

		string word("A");
		cout << "Matrix: " << endl;
		for (auto& line : board)
		{
			for (auto ch : line)
			{
				cout << ch << " ";
			}
			cout << endl;
		}
		cout << "Has word " << word << ": " << exist(board, word) << endl;
	}
}