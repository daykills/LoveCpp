/*
 464. Can I Win

 In the "100 game," two players take turns adding, to a running total, any integer from 1..10. The player who first causes the running total to reach or exceed 100 wins.
 
 What if we change the game so that players cannot re-use integers?
 
 For example, two players might take turns drawing from a common pool of numbers of 1..15 without replacement until they reach a total >= 100.
 
 Given an integer maxChoosableInteger and another integer desiredTotal, determine if the first player to move can force a win, assuming both players play optimally.
 
 You can always assume that maxChoosableInteger will not be larger than 20 and desiredTotal will not be larger than 300.
 
 Example
 
 Input:
 maxChoosableInteger = 10
 desiredTotal = 11
 
 Output:
 false
 
 Explanation:
 No matter which integer the first player choose, the first player will lose.
 The first player can choose an integer from 1 up to 10.
 If the first player choose 1, the second player can only choose integers from 2 up to 10.
 The second player will win by choosing 10 and get a total = 11, which is >= desiredTotal.
 Same with other integers chosen by the first player, the second player will always win.
*/

#include <iostream>
#include <stack>
#include <algorithm>
#include <cstdint>
#include "Common.h"

namespace CanIWin
{
class Solution {
public:
    bool canIWin(int maxChoosableInteger, int desiredTotal) {
        unordered_map<int, bool> memo;
        if((1 + maxChoosableInteger) * maxChoosableInteger < desiredTotal * 2)
            return false;
        return dfs(maxChoosableInteger, desiredTotal, 0, memo);
    }
    bool dfs(int maxint, int dt, int used, unordered_map<int, bool>& memo){
        if(memo.count(used))
            return memo[used];
        for(int i = maxint - 1; i >= 0; i--) {
            if(((used >> i) & 1) == 1) continue;
            if((i + 1) >= dt || !dfs(maxint, dt - (i + 1), used | (1 << i), memo))
                return memo[used] = true;
        }
        return memo[used] = false;
    }
};

void Test()
{
    Solution s;
    cout << s.canIWin(10, 11) << std::endl;
}
}
