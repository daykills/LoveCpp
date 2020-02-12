/*
 187. Repeated DNA Sequences

 All DNA is composed of a series of nucleotides abbreviated as A, C, G, and T, for example: "ACGAATTCCG". When studying DNA, it is sometimes useful to identify repeated sequences within the DNA.
 
 Write a function to find all the 10-letter-long sequences (substrings) that occur more than once in a DNA molecule.
 
 Example:
 
 Input: s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT"
 
 Output: ["AAAAACCCCC", "CCCCCAAAAA"]
*/

#include <iostream>
#include <stack>
#include <algorithm>
#include <cstdint>
#include "Common.h"

namespace FindRepeatedDnaSequences
{
vector<string> findRepeatedDnaSequences(string s) {
    constexpr int SEQ_LEN = 10;
    uint32_t kWindow = 0;
    for (auto i = 0; i < SEQ_LEN * 2; i++)
        kWindow = (kWindow << 1) + 1;
    unordered_set<uint32_t> seqs;
    unordered_set<uint32_t> ansSet;
    uint32_t seq = 0;
    for (auto i = 0; i < s.size(); i++) {
        auto ch = s[i];
        seq = (seq << 2) & kWindow;
        if (ch == 'A') {
            seq |= 0;
        } else if (ch == 'C') {
            seq |= 1;
        } else if (ch == 'G') {
            seq |= 2;
        } else { // (ch == 'T') {
            seq |= 3;
        }
        if (i < SEQ_LEN - 1) continue;
        auto it = seqs.find(seq);
        if (it != seqs.end()) {
            ansSet.emplace(seq);
            continue;
        }
        seqs.emplace(seq);
    }
    vector<string> ans;
    for (uint32_t seq : ansSet) {
        vector<char> seqStr(SEQ_LEN, 'A');
        const uint32_t subWindow = 0b11;
        for (int i = SEQ_LEN - 1; i >= 0; i--) {
            auto code = subWindow & seq;
            if (code == 0) {
                seqStr[i] = 'A';
            } else if (code == 1) {
                seqStr[i] = 'C';
            } else if (code == 2) {
                seqStr[i] = 'G';
            } else { // code == 3) {
                seqStr[i] = 'T';
            }
            seq = seq >> 2;
        }
        ans.emplace_back(seqStr.data(), seqStr.size());
    }
    return ans;
}

void Test()
{
    bitset<1<<20> S1;
    cout << sizeof(S1) << std::endl;
    auto rst = findRepeatedDnaSequences("AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT");
    for (auto& seq : rst) {
        cout << seq << endl;
    }
}
}
