/*
 767. Reorganize String

 Given a string S, check if the letters can be rearranged so that two characters that are adjacent to each other are not the same.
 
 If possible, output any possible result.  If not possible, return the empty string.
 
 Example 1:
 
 Input: S = "aab"
 Output: "aba"
 Example 2:
 
 Input: S = "aaab"
 Output: ""
 Note:
 
 S will consist of lowercase letters and have length in range [1, 500].
 */

#include "Common.h"

namespace ReorganizeString
{
class Solution {
public:
    string reorganizeString(string S) {
        unordered_map<char,int> m;
        for (const auto& c: S) ++m[c];
        priority_queue<pair<char,int>,vector<pair<char,int>>,Comp> q(m.begin(), m.end());
        ostringstream os;
        while(q.size() > 1){
            auto a=q.top(); q.pop();
            auto b=q.top(); q.pop();
            os << a.first << b.first;
            if (--a.second) q.push(a);
            if (--b.second) q.push(b);
        }
        if (q.size()==1 && q.top().second==1){
            os << q.top().first;
            q.pop();
        }
        return q.empty() ? os.str() : "";
    }
private:
    class Comp {
    public:
        bool operator()(const pair<char,int>& lhs, const pair<char,int>& rhs) const {
            return lhs.second < rhs.second;
        }
    };
};

static void Test()
{
    Solution solution;
    std::cout << solution.reorganizeString("aaaaaccc") << std::endl;
}
}
