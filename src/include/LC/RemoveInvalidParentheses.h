/*
 301. Remove Invalid Parentheses
 
 Remove the minimum number of invalid parentheses in order to make the input string valid. Return all possible results.
 
 Note: The input string may contain letters other than the parentheses ( and ).
 
 Example 1:
 
 Input: "()())()"
 Output: ["()()()", "(())()"]
 Example 2:
 
 Input: "(a)())()"
 Output: ["(a)()()", "(a())()"]
 Example 3:
 
 Input: ")("
 Output: [""]
 */

#include "Common.h"

namespace RemoveInvalidParentheses
{
class Solution {
public:
    /*
     BFS 来解，我把给定字符串排入队中，然后取出检测其是否合法，若合法直接返回，不合法的话，对其进行遍历，对于遇到的左右括号的字符，去掉括号字符生成一个新的字符串，如果这个字符串之前没有遇到过，将其排入队中，用 HashSet 记录一个字符串是否出现过。对队列中的每个元素都进行相同的操作，直到队列为空还没找到合法的字符串的话，那就返回空集
     */
    vector<string> removeInvalidParentheses(string s) {
        vector<string> res;
        unordered_set<string> visited{{s}};
        queue<string> q{{s}};
        bool found = false;
        while (!q.empty()) {
            string t = q.front(); q.pop();
            if (isValid(t)) {
                res.push_back(t);
                found = true;
            }
            if (found)
                continue;
            for (int i = 0; i < t.size(); ++i) {
                if (t[i] != '(' && t[i] != ')')
                    continue;
                string str = t.substr(0, i) + t.substr(i + 1);
                if (!visited.count(str)) {
                    q.push(str);
                    visited.insert(str);
                }
            }
        }
        return res;
    }
    
    bool isValid(string t) {
        int cnt = 0;
        for (int i = 0; i < t.size(); ++i) {
            if (t[i] == '(') ++cnt;
            else if (t[i] == ')' && --cnt < 0) return false;
        }
        return cnt == 0;
    }
};

int Test()
{
    string str("()())()");
    Solution s;
    auto res = s.removeInvalidParentheses(str);
    for (auto& valid : res)
        cout << valid << endl;
    return 0;
}
}
