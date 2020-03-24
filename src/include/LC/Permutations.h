/*
 46. Permutations My Submissions Question
 Total Accepted: 91404 Total Submissions: 260919 Difficulty: Medium
 Given a collection of distinct numbers, return all possible permutations.
 
 For example,
 [1,2,3] have the following permutations:
 [1,2,3], [1,3,2], [2,1,3], [2,3,1], [3,1,2], and [3,2,1].
 */
#include "Common.h"

namespace Permutations
{
void dfs(vector<int>& nums, vector<int>& cur, unordered_set<int>& curSet, vector<vector<int>>& result) {
    if (cur.size() == nums.size()) {
        result.emplace_back(cur);
        return;
    }
    for (auto i = 0; i < nums.size(); i++) {
        // don't re-add number to cur
        auto it = curSet.find(i);
        if (it != curSet.end())
            continue;
        curSet.emplace(i);
        cur.emplace_back(nums[i]);
        dfs(nums, cur, curSet, result);
        cur.pop_back();
        curSet.erase(i);
    }
}
vector<vector<int>> permuteDFS(vector<int>& nums) {
    vector<vector<int>> result;
    unordered_set<int> curSet;
    vector<int> cur;
    dfs(nums, cur, curSet, result);
    return result;
}

vector<vector<int>> permute(vector<int>& nums) {
    auto n = nums.size();
    if (n == 0) return {};
    // preResult with first i numbers, start with i = 1
    vector<vector<int>> preResult { { nums.front() } };
    for (auto i = 2; i <= nums.size(); i++) {
        vector<vector<int>> newResult;
        auto curNum = nums[i - 1];
        for (auto& pre : preResult) {
            pre.push_back(curNum);
            newResult.push_back(pre);
            for (auto j = 0; j < pre.size() - 1; j++) {
                swap(pre[j], pre.back());
                newResult.push_back(pre);
                swap(pre[j], pre.back());
            }
        }
        preResult = move(newResult);
    }
    return preResult;
}

void Test()
{
    vector<int> candidates{ 1, 2, 3 };
    auto result = permute(candidates);
    cout << "candidates: ";
    for (auto candidate : candidates)
    {
        cout << candidate << " ";
    }
    cout << endl << "Result: " << endl;
    for (auto& combination : result)
    {
        for (auto& num : combination)
        {
            cout << num << " ";
        }
        cout << endl;
    }
}
}
