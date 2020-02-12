#pragma once
/*
[LintCode] 613 High Five
 
There are two properties in the node student id and scores, to ensure that each student will have at least 5 points, find the average of 5 highest scores for each person.
Example
    Example 1:
    Input:
    [[1,91},{1,92},{2,93},{2,99},{2,98},{2,97},{1,60},{1,58},{2,100},{1,61]]
    Output:
    1: 72.40
    2: 97.40

Example 2:
    Input:
    [[1,90},{1,90},{1,90},{1,90},{1,90},{1,90]]
    Output:
    1: 90.00
*/

#include <iostream>
#include <queue>
#include <memory>
#include <cassert>
#include <algorithm>
#include <vector>
#include "Common.h"

namespace HighFive
{
map<int, double> highFive(vector<vector<int>>& scores) {
    // min heap to keep the top 5 scores
    unordered_map<int, priority_queue<int, vector<int>, greater<int>>> allHighScores;
    for (auto& idAndScore : scores) {
        auto studentId = idAndScore[0];
        auto score = idAndScore[1];
        auto& highScores = allHighScores[studentId];
        if (highScores.size() < 5 || highScores.top() < score) {
            highScores.push(score);
            if (highScores.size() > 5)
                highScores.pop();
        }
    }
    map<int, double> ans;
    for (auto& idAndScores : allHighScores) {
        auto studentId = idAndScores.first;
        auto& scores = idAndScores.second;
        double sum = 0;
        int count = scores.size();
        while (!scores.empty()) {
            sum += scores.top();
            scores.pop();
        }
        ans.emplace(studentId, sum / count);
    }
    return ans;
}
void Test()
{
    vector<vector<int>> scores = {
        {1,91},{1,92},{2,93},{2,99},{2,98},{2,97},{1,60},{1,58},{2,100},{1,61}
    };
    auto ans = highFive(scores);
    for (auto& idAndScore : ans) {
        cout << idAndScore.first << ", " << idAndScore.second << endl;
    }
}

}
