/*
 777. Swap Adjacent in LR String

 In a string composed of 'L', 'R', and 'X' characters, like "RXXLRXRXL", a move consists of either replacing one occurrence of "XL" with "LX", or replacing one occurrence of "RX" with "XR". Given the starting string start and the ending string end, return True if and only if there exists a sequence of moves to transform one string to the other.
 
 Example:
 
 Input: start = "RXXLRXRXL", end = "XRLXXRRLX"
 Output: True
 Explanation:
 We can transform start to end following these steps:
 RXXLRXRXL ->
 XRXLRXRXL ->
 XRLXRXRXL ->
 XRLXXRRXL ->
 XRLXXRRLX
 Note:
 
 1 <= len(start) = len(end) <= 10000.
 Both start and end will only consist of characters in {'L', 'R', 'X'}.
*/

#include <algorithm>
#include <unordered_set>
#include "Common.h"

namespace CanTransform
{

// Simple DFS doesn't work
// Negative case: XXL -> XLX -> LXX
bool dfsFailed(string& cur, const string& end, int startPos) {
    const static vector<pair<string, string>> kReplacements = { { "XL", "LX" }, { "RX", "XR" } };
    
    if (cur == end) return true;
    if (startPos >= cur.size()) return false;
    
    for (auto& replacement : kReplacements) {
        auto npos = cur.find(replacement.first, startPos);
        if (npos == cur.npos) continue;
        auto newStr = cur;
        newStr.replace(npos, replacement.first.size(), replacement.second);
        // start pos has to be npos to cover case like:
        if (dfsFailed(newStr, end, npos))
            return true;
    }
    return false;
}

bool dfs(const string& cur, const string& end, unordered_set<string>& visited) {
    const static vector<pair<string, string>> kReplacements = { { "XL", "LX" }, { "RX", "XR" } };
    
    if (cur == end) return true;
    visited.emplace(cur);
    for (auto& replacement : kReplacements) {
        auto& ori = replacement.first;
        auto& dest = replacement.second;
        for (auto i = 0; i < cur.size() - ori.size() + 1; i++) {
            if (cur.compare(i, ori.size(), ori) != 0)
                continue;
            auto newStr = cur;
            newStr.replace(i, ori.size(), dest);
            if (visited.count(newStr))
                continue;
            if (dfs(newStr, end, visited))
                return true;
        }
    }
    return false;
}

bool canTransformDFS(string start, string end) {
    assert(start.size() == end.size());
    unordered_set<string> visited;
    return dfs(start, end, visited);
}

bool canTransform(string start, string end) {
    assert(start.size() == end.size());
    
    auto n = start.size();
    
    auto i = 0;
    auto j = 0;
    
    while (true) {
        while (i < n && start[i] == 'X') i++;
        while (j < n && end[j] == 'X') j++;
        
        if (i == n || j == n) break;
        
        // L and R cannot transpose
        if (start[i] != end[j]) return false;
        if (start[i] == 'L') {
            if (i < j) return false;
        } else {
            if (i > j) return false;
        }
        i++;
        j++;
    }
    
    for (auto ind = i; ind < n; ind++)
        if (start[ind] != 'X') return false;
    for (auto ind = j; ind < n; ind++)
        if (end[ind] != 'X') return false;
    
    return true;
}

void Test() {
    string start, end;
    
    start = "XXRXXLXXXX";
    end =   "XXXXRXXLXX";
    
    start = "RXXLRXRXL";
    end =   "XRLXXRRLX";
    
    start = "RXXX";
    end =   "XXXR";
    
    start = "XXXL";
    end =   "LXXX";
    
    start = "XXRXXXXXXXRXRXXXLXXLXXLXXXXXRXXXXXXXXLXX";
    end =   "XXXRXXXXRXXXXXXRXXXLXXXXXXXLXXLXXRXXLXXX";
    
    cout << canTransform(start, end) << endl;
}
}
