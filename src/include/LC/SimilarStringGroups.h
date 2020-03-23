/*
839. Similar String Groups

Two strings X and Y are similar if we can swap two letters (in different positions) of X, so that it equals Y. Also two strings X and Y are similar if they are equal.

For example, "tars" and "rats" are similar (swapping at positions 0 and 2), and "rats" and "arts" are similar, but "star" is not similar to "tars", "rats", or "arts".

Together, these form two connected groups by similarity: {"tars", "rats", "arts"} and {"star"}.  Notice that "tars" and "arts" are in the same group even though they are not similar.  Formally, each group is such that a word is in the group if and only if it is similar to at least one other word in the group.

We are given a list A of strings.  Every string in A is an anagram of every other string in A.  How many groups are there?

Example 1:

Input: A = ["tars","rats","arts","star"]
Output: 2
 

Constraints:

1 <= A.length <= 2000
1 <= A[i].length <= 1000
A.length * A[i].length <= 20000
All words in A consist of lowercase letters only.
All words in A have the same length and are anagrams of each other.
The judging time limit has been increased for this question.
*/
#include <string>
#include <iostream>
#include "Common.h"

namespace SimilarStringGroups
{
class Solution {
public:
    bool areSimilar(const string& str1, const string& str2) {
        auto n = str1.size();
        if (n != str2.size()) return false;
        // different characters: 0 - from str1, 1 from str2
        vector<char> diffs;
        int cntDiff = 0;
        for (auto i = 0; i < n; i++) {
            if (str1[i] == str2[i]) continue;
            if (++cntDiff > 2) return false;
        }
        assert(cntDiff == 0 || cntDiff == 2);
        return true;
    }
    
    void dfs(vector<string>& words, unordered_set<string>& visited, const string& word) {
        if (visited.count(word)) return;
        visited.emplace(word);
        for (auto& next : words) {
            if (areSimilar(word, next)) {
                dfs(words, visited, next);
            }
        }
    }
    
    int numSimilarGroups(vector<string>& A) {
        unordered_set<string> visited;
        int nGroup = 0;
        for (auto& word : A) {
            if (visited.count(word)) continue;
            nGroup++;
            dfs(A, visited, word);
        }
        return nGroup;
    }
};

static void Test()
{
    vector<string> words { "tars","rats","arts","star" };
    Solution s;
    cout << s.numSimilarGroups(words) << endl;    // should be 8
}

}
