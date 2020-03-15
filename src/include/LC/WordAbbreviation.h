/*
 527. Word Abbreviation

 Given an array of n distinct non-empty strings, you need to generate minimal possible abbreviations for every word following rules below.
 
 Begin with the first character and then the number of characters abbreviated, which followed by the last character.
 If there are any conflict, that is more than one words share the same abbreviation, a longer prefix is used instead of only the first character until making the map from word to abbreviation become unique. In other words, a final abbreviation cannot map to more than one original words.
 If the abbreviation doesn't make the word shorter, then keep it as original.
 Example:
 Input: ["like", "god", "internal", "me", "internet", "interval", "intension", "face", "intrusion"]
 Output: ["l2e","god","internal","me","i6t","interval","inte4n","f2e","intr4n"]
 Note:
 Both n and the length of each word will not exceed 400.
 The length of each word is greater than 1.
 The words consist of lowercase English letters only.
 The return answers should be in the same order as the original array.
 */

#include <iostream>
#include <list>
#include "Common.h"

namespace WordAbbreviation
{
class Solution {
public:
    vector<string> wordsAbbreviation(vector<string>& dict) {
        auto encoder = [](const string& str, int prefixLen) {
            // 1 for suffix, 2 for middle characters to be compressed
            if (str.size() < prefixLen + 3)
                return str;
            ostringstream os;
            os << str.substr(0, prefixLen) << str.size() - prefixLen - 1 << str.back();
            return os.str();
        };
        // code -> (len, indice of compressed words)
        unordered_map<string, pair<int, vector<int>>> grouped;
        for (auto i = 0; i < dict.size(); i++) {
            auto& str = dict[i];
            auto code = encoder(str, 1);
            grouped[code].first = 1;
            grouped[code].second.push_back(i);
        }
        
        vector<string> compressed(dict.size());
        // move words from grouped to compressed
        while (!grouped.empty()) {
            unordered_map<string, pair<int, vector<int>>> newGrouped;
            for (auto& group : grouped) {
                auto prefixLen = group.second.first;
                auto& wordIds = group.second.second;
                auto& compressedWord = group.first;
                if (wordIds.size() == 1)
                    compressed[wordIds.front()] = compressedWord;
                else {
                    for (auto& wordInd : wordIds) {
                        auto code = encoder(dict[wordInd], prefixLen + 1);
                        newGrouped[code].first = prefixLen + 1;
                        newGrouped[code].second.push_back(wordInd);
                    }
                }
            }
            grouped = move(newGrouped);
        }
        
        return compressed;
    }
};

static void Test()
{
    Solution solution;
    vector<string> dict {
        "like","god","internal","me","internet","interval","intension","face","intrusion"
    };
    auto result = solution.wordsAbbreviation(dict);
    for (auto& word : result) {
        std::cout << word << ", ";
    }
    std::cout << std::endl;
}
}
