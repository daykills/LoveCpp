#pragma once
/*
We have to create phone number of arbitrary length by the movement of knight and bishop on a keypad. The properties of the phone number:
The phone number cannot start on certain numbers.
The phone number should not contain special characters.
The length of the phone number is arbitrary.
The key board is arbitrary.

bishop	// piece
2		// phone number length
2 3 4	// allowed start numbers
4		// number of rows
3		// number of cols
1 2 3	// board data
4 5 6
7 8 9
+ 0 #

*/

#include <iostream>
#include <climits>
#include <string>
#include <vector>
using namespace std;

namespace PhoneNumberCombination
{
	class PhoneNumberSolver
	{
	public:
		PhoneNumberSolver(const string& filename = "") : m_filename(filename)
		{
			Init();
		}
		// read parameters from stdin or file
		void readParameters()
		{
			// no op for istream init
			struct noop
			{
				void operator()(...) const {}
			};
			// clear parameters
			Init();
			// choose input between stdin and file stream
			shared_ptr<istream> input;
			if (m_filename.empty())
				input.reset(&cin, noop());
			else
				input.reset(new ifstream(m_filename), [](std::ifstream* ptr) { ptr->close(); });

			int rowReadCount = 0;
			for (auto iLine = 0; true; iLine++)
			{
				std::string line;
				getline(*input, line);
				if (iLine == 0)	// read Piece
				{
					if (line == "knight") m_piece = Piece::knight;
					else if (line == "bishop") m_piece = Piece::bishop;
					assert(m_piece != Piece::undefined);
				}
				else if (iLine == 1) // read number length
				{
					m_numLen = stoi(line);
					assert(m_numLen != 0);
				}
				else if (iLine == 2) // read starting digits
				{
					auto chars = readCharVector(line);
					for (auto ch : chars)
					{
						// the position of the starter is unknown for now
						m_validStarters.emplace(ch, make_pair<int, int>(-1, -1));
					}
					assert(m_validStarters.size() != 0);
				}
				else if (iLine == 3) // read number of rows
				{
					m_rows = stoi(line);
					m_board.resize(m_rows);
					assert(m_rows != 0);
				}
				else if (iLine == 4) // read number of cols
				{
					m_cols = stoi(line);
					assert(m_cols != 0);
				}
				else // read board
				{
					m_board[rowReadCount] = readCharVector(line);
					int lenOfRow = m_board[rowReadCount].size();
					assert(lenOfRow == m_cols);
					// find starters and update their positions
					for (auto col = 0; col < lenOfRow; col++)
					{
						auto it = m_validStarters.find(m_board[rowReadCount][col]);
						if (it != m_validStarters.end())
						{
							it->second = make_pair(rowReadCount, col);
						}
					}
					rowReadCount++;
					if (rowReadCount == m_rows) break;
				}
			}
			m_isParamReady = true;
		}

		int countValidPhoneNumbers()
		{
			// make sure the parameters are ready
			assert(m_isParamReady);
			if (m_numLen == 0) return 0;

			auto& board = m_board;
			int count = 0;
			// start with each starters
			for (const auto& starterInfo : m_validStarters)
			{
				// check whether the stater is valid
				if (!validPosition(starterInfo.second.first, starterInfo.second.second)) continue;
				// set starter as the starting position for dfs search
				auto row = starterInfo.second.first, col = starterInfo.second.second;
				auto startingValidNumberLen = isdigit(board[row][col]) ? 1 : 0;
				dfsSearch(board, startingValidNumberLen, row, col, count);
			}
			return count;
		}

	private:
		void dfsSearch(vector<vector<char>>& board, int validNumberLen, int row, int col, int& count)
		{
			// base condition: valid number is already found, stop search
			if (validNumberLen == m_numLen)
			{
				count++;
				return;
			}
			// base condition: invalid position, stop search
			if (!validPosition(row, col)) return;
			// find all possible next positions
			auto nextPositions = (m_piece == Piece::knight) ? lShapeMoves(row, col) : diagonalMoves(row, col);
			for (const auto& pos : nextPositions)
			{
				auto newRow = pos.first, newCol = pos.second;
				// if the digit is already taken, or it's not a digit, continue
				if (board[newRow][newCol] == 0 || !isdigit(board[newRow][newCol])) continue;
				// mark the bin "used" by setting it to 0
				auto temp = board[newRow][newCol];
				board[newRow][newCol] = 0;
				dfsSearch(board, validNumberLen + 1, newRow, newCol, count);
				// set the bin back to original digit
				board[newRow][newCol] = temp;
			}
		}
		// initialize
		void Init()
		{
			m_validStarters.clear();
			m_board.clear();
			m_isParamReady = false;
			m_piece = Piece::undefined;
		}
		// get possible next position of a bishop move
		vector<pair<int, int>> diagonalMoves(int row, int col)
		{
			if (!validPosition(row, col)) return vector<pair<int, int>>();
			vector<pair<int, int>> pos;
			for (auto nextRow = 0; nextRow < m_rows; nextRow++)
			{
				if (nextRow == row) continue;
				for (auto nextCol = 0; nextCol < m_cols; nextCol++)
				{
					if (nextCol == col) continue;
					if (abs(nextRow - row) == abs(nextCol - col))
					{
						pos.emplace_back(nextRow, nextCol);
					}
				}
			}
			return pos;
		}
		// get possible next positions of a L move
		vector<pair<int, int>> lShapeMoves(int row, int col)
		{
			if (!validPosition(row, col)) return vector<pair<int, int>>();

			static vector<pair<int, int>> moves = { { 1, 2 },{ 2, 1 },{ -1, 2 },{ -2, 1 },{ 1, -2 },{ 2, -1 },{ -1, -2 },{ -2, -1 } };
			vector<pair<int, int>> pos;
			for (const auto& move : moves)
			{
				int newRow = row + move.first, newCol = col + move.second;
				if (validPosition(newRow, newCol))
					pos.emplace_back(newRow, newCol);
			}
			return pos;
		}
		// check whether a position is valid
		bool validPosition(int row, int col)
		{
			return row >= 0 && row < m_rows && col >= 0 && col < m_cols;
		}
		// read char array from a line of string with delimiter
		vector<char> readCharVector(const string& line)
		{
			vector<char> result;
			for (auto ch : line)
			{
				if (ch != ' ' && ch != 0) result.emplace_back(ch);
			}
			return result;
		}
		// Piece type def
		enum Piece { knight, bishop, undefined };		
		// fields
		bool m_isParamReady;
		string m_filename;
		Piece m_piece;
		int m_numLen;
		unordered_map<char, pair<int, int>> m_validStarters;	// keep starters and their positions
		int m_rows;
		int m_cols;
		vector<vector<char>> m_board;
	};

	int Test() {
		PhoneNumberSolver solver("data\\string_array_data.txt");
		//PhoneNumberSolver solver;
		solver.readParameters();
		cout << "count: " << solver.countValidPhoneNumbers() << endl;
		return 0;
	}
}
