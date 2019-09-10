/*
 399. Evaluate Division
 
 Equations are given in the format A / B = k, where A and B are variables represented as strings, and k is a real number (floating point number). Given some queries, return the answers. If the answer does not exist, return -1.0.
 
 Example:
 Given a / b = 2.0, b / c = 3.0.
 queries are: a / c = ?, b / a = ?, a / e = ?, a / a = ?, x / x = ? .
 return [6.0, 0.5, -1.0, 1.0, -1.0 ].
 
 The input is: vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> queries , where equations.size() == values.size(), and the values are positive. This represents the equations. Return vector<double>.
 
 According to the example above:
 
 equations = [ ["a", "b"], ["b", "c"] ],
 values = [2.0, 3.0],
 queries = [ ["a", "c"], ["b", "a"], ["a", "e"], ["a", "a"], ["x", "x"] ].
 
 The input is always valid. You may assume that evaluating the queries will result in no division by zero and there is no contradiction.
 */

#include <iostream>
#include <list>
#include "Common.h"

namespace EvaluateDivision
{
class Solution {
public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        vector<double> res;
        for (int i = 0; i < equations.size(); ++i) {
            m[equations[i][0]][equations[i][1]] = values[i];
            m[equations[i][1]][equations[i][0]] = 1.0 / values[i];
        }
        for (auto query : queries) {
            unordered_set<string> visited;
            bool found = false;
            double val = -1;
            dfs(query[0], query[1], visited, found, val);
            res.push_back(found ? val : -1);
        }
        return res;
    }
    void dfs(const string& num, const string& den, unordered_set<string>& visited, bool& found, double& v) {
        if ((m.count(num) == 0)) return;
        if (m[num].count(den)) {
            v = m[num][den];
            found = true;
            return;
        }
        for (auto& nextNumAndVal : m[num]) {
            auto& nextNum = nextNumAndVal.first;
            if (visited.count(nextNum))
                continue;
            visited.emplace(nextNum);
            bool nextFound = false;
            double nextVal = -1;
            dfs(nextNum, den, visited, nextFound, nextVal);
            if (nextFound) {
                found = true;
                v = nextNumAndVal.second * nextVal;
                return;
            }
        }
    }
    
private:
    unordered_map<string, unordered_map<string, double>> m;
};

static void Test()
{
    Solution solution;
    vector<vector<string>> equations = { {"a","e"},{"b","f"} };
    vector<double> values = { 4.0,3.0 };
    vector<vector<string>> queries = { { "a","b"}, {"e", "e"} };
    auto res = solution.calcEquation(equations, values, queries);
    for (auto& v : res) {
        std::cout << v << std::endl;
    }
}
}
