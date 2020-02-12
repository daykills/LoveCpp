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
    bool dfs(vector<vector<char>>& board, const string& word, int matchedLen, int i, int j) {
        if (i < 0 || i >= board.size() || j < 0 || j >= board[0].size())
            return false;
        
        auto curChar = board[i][j];
        if (word[matchedLen] != curChar)
            return false;
        matchedLen++;
        if (matchedLen == word.size())
            return true;
        
        board[i][j] = 0;
        // try next step on four directions
        bool result = false;
        result = result || dfs(board, word, matchedLen, i + 1, j);
        result = result || dfs(board, word, matchedLen, i, j + 1);
        result = result || dfs(board, word, matchedLen, i, j - 1);
        result = result || dfs(board, word, matchedLen, i - 1, j);
        board[i][j] = curChar;
        return result;
    }
    
    bool exist(vector<vector<char>>& board, string word) {
        int h = board.size();
        if (h == 0)
            return false;
        int w = board[0].size();
        if (w == 0)
            return false;
        for (auto i = 0; i < h; i++) {
            for (auto j = 0; j < w; j++) {
                if (dfs(board, word, 0, i, j))
                    return true;
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
