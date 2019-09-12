/*
 Leetcode 353: Design Snake Game
 
 Design a Snake game that is played on a device with screen size = width x height. Play the game online if you are not familiar with the game.
 
 The snake is initially positioned at the top left corner (0,0) with length = 1 unit.
 
 You are given a list of food’s positions in row-column order. When a snake eats the food, its length and the game’s score both increase by 1.
 
 Each food appears one by one on the screen. For example, the second food will not appear until the first food was eaten by the snake.
 
 When a food does appear on the screen, it is guaranteed that it will not appear on a block occupied by the snake.
 
 Example:
 
 Given width = 3, height = 2, and food = [[1,2],[0,1]].
 
 Snake snake = new Snake(width, height, food);
 
 Initially the snake appears at position (0,0) and the food at (1,2).
 
 |S| | |
 | | |F|
 
 snake.move("R"); -> Returns 0
 
 | |S| |
 | | |F|
 
 snake.move("D"); -> Returns 0
 
 | | | |
 | |S|F|
 
 snake.move("R"); -> Returns 1 (Snake eats the first food and right after that, the second food appears at (0,1) )
 
 | |F| |
 | |S|S|
 
 snake.move("U"); -> Returns 1
 
 | |F|S|
 | | |S|
 
 snake.move("L"); -> Returns 2 (Snake eats the second food)
 
 | |S|S|
 | | |S|
 
 snake.move("U"); -> Returns -1 (Game over because snake collides with border)
 
 Credits:
 Special thanks to @elmirap for adding this problem and creating all test cases.
 */

#include <iostream>
#include <list>
#include "Common.h"

namespace SnakeGame
{
class SnakeGame {
public:
    /** Initialize your data structure here.
     @param width - screen width
     @param height - screen height
     @param food - A list of food positions
     E.g food = [[1,1], [1,0]] means the first food is positioned at [1,1], the second is at [1,0]. */
    SnakeGame(int width, int height, const vector<pair<int, int>>& food) : m_w(width), m_h(height), m_food(food)
    {
        assert(m_w > 0 && m_h > 0);
        m_snake.emplace_back(0, 0);
        m_snakeSet.emplace(toString(0, 0));
    }
    
    /** Moves the snake.
     @param direction - 'U' = Up, 'L' = Left, 'R' = Right, 'D' = Down
     @return The game's score after the move. Return -1 if game over.
     Game over when snake crosses the screen boundary or bites its body. */
    int move(const string& direction) {
        static unordered_map<string, pair<int, int>> s_moves = {
            { "U", { -1, 0 }}, { "L", { 0, -1 }}, { "R", { 0, 1 }}, { "D", { 1, 0 } }
        };
        
        auto& move = s_moves[direction];
        int newRow = m_snake.back().first + move.first;
        int newCol = m_snake.back().second + move.second;
        
        // hit border
        if (newRow >= m_h || newRow < 0 || newCol >= m_w || newCol < 0)
            return -1;
        
        auto len = m_snake.size();
        assert(len >= 1);
        
        // eat
        bool eat = false;
        if (len <= m_food.size()) {
            auto& foodPos = m_food[len - 1];
            eat = (foodPos.first == newRow && foodPos.second == newCol);
        }
        if (!eat) {
            m_snakeSet.erase(toString(m_snake.front().first, m_snake.front().second));
            m_snake.erase(m_snake.begin());
        }
        
        // eat self
        auto newPosKey = toString(newRow, newCol);
        if (m_snakeSet.count(newPosKey))
            return -1;
        m_snake.emplace_back(newRow, newCol);
        m_snakeSet.emplace(newPosKey);
        
        return m_snake.size() - 1;
    }
private:
    string toString(int row, int col) const {
        return to_string(row) + "_" + to_string(col);
    }
    const int m_w;
    const int m_h;
    const vector<pair<int, int>>& m_food;
    // back is the head, front is the tail
    list<pair<int, int>> m_snake;
    unordered_set<string> m_snakeSet;
};

static void Test()
{
    /**
     * Your SnakeGame object will be instantiated and called as such:
     * SnakeGame obj = new SnakeGame(width, height, food);
     * int param_1 = obj.move(direction);
     */
    int width = 3;
    int height = 2;
    vector<pair<int, int>> food = { { 1, 2 }, { 0, 1 } };
    SnakeGame snake(width, height, food);
    assert(snake.move("R") == 0); //-> Returns 0
    assert(snake.move("D") == 0); //-> Returns 0
    assert(snake.move("R") == 1); // -> Returns 1
    assert(snake.move("U") == 1); // -> Returns 1
    assert(snake.move("L") == 2); // -> Returns 2 (Snake eats the second food)
    assert(snake.move("U") == -1); // -> Returns -1 (Game over because snake collides with border)
}
}
