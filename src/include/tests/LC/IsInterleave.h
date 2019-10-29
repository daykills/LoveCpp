/*
 97. Interleaving String

 Given s1, s2, s3, find whether s3 is formed by the interleaving of s1 and s2.

 Example 1:

 Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbcbcac"
 Output: true
 Example 2:

 Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbbaccc"
 Output: false
*/

#include <algorithm>
#include <unordered_set>
#include "Common.h"

namespace IsInterleave
{
bool dfs(const string& s1, const string& s2, const string& s3, int len1, int len2, unordered_map<int, unordered_map<int, bool>>& visited) {
    auto len3 = len1 + len2;
    if (len3 == s3.size()) return true;
    
    if (visited.count(len1) && visited[len1].count(len2))
        return false;

    //std::cout << s1.substr(len1) << ", " << s2.substr(len2) << ", " << s3.substr(len3) << endl;
    
    visited[len1][len2] = true;
    if (len1 == s1.size())
        return s3.compare(len3, s3.size() - len3,
                          s2.data() + len2, s2.size() - len2) == 0;
    
    if (len2 == s2.size())
        return s3.compare(len3, s3.size() - len3,
                          s1.data() + len1, s1.size() - len1) == 0;
    
    // take one char from s1
    if (s1[len1] == s3[len3]) {
        if (dfs(s1, s2, s3, len1 + 1, len2, visited))
            return true;
    }
    if (s2[len2] == s3[len3]) {
        if (dfs(s1, s2, s3, len1, len2 + 1, visited))
            return true;
    }
    return false;
}
    
bool isInterleaveDFS(string s1, string s2, string s3) {
    if (s3.size() != s1.size() + s2.size()) return false;
    unordered_map<int, unordered_map<int, bool>> visited;
    return dfs(s1, s2, s3, 0, 0, visited);
}

void Test() {
    //cout << isInterleave("aabcc", "dbbca", "aadbbcbcac") << endl;
    cout << isInterleaveDFS(
                         "bbbbbabbbbabaababaaaabbababbaaabbabbaaabaaaaababbbababbbbbabbbbababbabaabababbbaabababababbbaaababaa",
                         "babaaaabbababbbabbbbaabaabbaabbbbaabaaabaababaaaabaaabbaaabaaaabaabaabbbbbbbbbbbabaaabbababbabbabaab",
                         "babbbabbbaaabbababbbbababaabbabaabaaabbbbabbbaaabbbaaaaabbbbaabbaaabababbaaaaaabababbababaababbababbbababbbbaaaabaabbabbaaaaabbabbaaaabbbaabaaabaababaababbaaabbbbbabbbbaabbabaabbbbabaaabbababbabbabbab"
                         ) << endl;
    
    
}
}
