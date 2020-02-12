/*
 282. Expression Add Operators

 Given a string that contains only digits 0-9 and a target value, return all possibilities to add binary operators (not unary) +, -, or * between the digits so they evaluate to the target value.
 
 Example 1:
 
 Input: num = "123", target = 6
 Output: ["1+2+3", "1*2*3"]
 Example 2:
 
 Input: num = "232", target = 8
 Output: ["2*3+2", "2+3*2"]
 Example 3:
 
 Input: num = "105", target = 5
 Output: ["1*0+5","10-5"]
 Example 4:
 
 Input: num = "00", target = 0
 Output: ["0+0", "0-0", "0*0"]
 Example 5:
 
 Input: num = "3456237490", target = 9191
 Output: []
 */

#include <iostream>
#include <list>
#include "Common.h"

namespace ExpressionAddOperators
{
// cumulative: calculated result based on curStr
// preOprand: previous number used.
// For example, 2-3*4+5, when pos is at 4, curStr is "2-3", cumulative is -1, preOperand is -3
// With * as the next operator, cumulative is "-1-(-3)+3*4=14", preOperand is 3*4=12
void dfs(const string& num, int target, vector<string>& res, int pos, const string& curStr, long cumulative, long preOprand) {
    if (pos == num.size() && cumulative == target) {
        res.push_back(curStr);
        return;
    }
    for (auto end = pos; end < num.size(); end++) {
        auto subNum = num.substr(pos, end - pos + 1);
        long v = stol(subNum);
        if (pos == 0) {
            dfs(num, target, res, end + 1, subNum, v, v);
        } else {
            dfs(num, target, res, end + 1, curStr + "+" + subNum, cumulative + v, v);
            dfs(num, target, res, end + 1, curStr + "-" + subNum, cumulative - v, -v);
            dfs(num, target, res, end + 1, curStr + "*" + subNum, cumulative - preOprand + preOprand * v, preOprand * v);
        }
        
        if (num[pos] == '0')
            break;
    }
}

vector<string> addOperators(string num, int target) {
    vector<string> res;
    if (num.empty())
        return res;
    dfs(num, target, res, 0, "", 0, 0);
    return res;
}

static void Test()
{
    string num = "232";
    int target  = 5;
    auto ans = addOperators(num, target);
    for (auto& exp : ans)
        std::cout << exp << std::endl;
}
}
