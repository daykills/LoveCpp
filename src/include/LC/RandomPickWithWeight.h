/*
 528. Random Pick with Weight

 Given an array w of positive integers, where w[i] describes the weight of index i, write a function pickIndex which randomly picks an index in proportion to its weight.
 
 Note:
 
 1 <= w.length <= 10000
 1 <= w[i] <= 10^5
 pickIndex will be called at most 10000 times.
 Example 1:
 
 Input:
 ["Solution","pickIndex"]
 [[[1]],[]]
 Output: [null,0]
 Example 2:
 
 Input:
 ["Solution","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex"]
 [[[1,3]],[],[],[],[],[]]
 Output: [null,0,1,1,1,0]
 Explanation of Input Syntax:
 
 The input is two lists: the subroutines called and their arguments. Solution's constructor has one argument, the array w. pickIndex has no arguments. Arguments are always wrapped with a list, even if there aren't any.
*/

#include <iostream>
#include "Common.h"

namespace RandomPickWithWeight
{
class Solution {
public:
    Solution(vector<int>& w) {
        m_ranges.reserve(w.size());
        for (auto weight : w)
            m_ranges.push_back(m_ranges.empty() ? weight : weight + m_ranges.back());
    }
    
    int pickIndex() {
        auto rangeMax = m_ranges.back();
        auto r = random() % rangeMax;
        auto upper = upper_bound(m_ranges.begin(), m_ranges.end(), r);
        return upper - m_ranges.begin();
    }
    // m_ranges[i] represents the upper range of hits for value i.
    vector<int> m_ranges;
};

void Test()
{
    vector<int> weight = { 1, 3, 6 };
    Solution s(weight);
    for (auto i  = 0; i < 10; i++)
        cout << s.pickIndex() << ", ";
    cout << endl;
    
}
}
