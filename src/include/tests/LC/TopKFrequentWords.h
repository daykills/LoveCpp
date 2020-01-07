/*
 692. Top K Frequent Words
 
 Given a non-empty list of words, return the k most frequent elements.
 
 Your answer should be sorted by frequency from highest to lowest. If two words have the same frequency, then the word with the lower alphabetical order comes first.
 
 Example 1:
 
 Input: ["i", "love", "leetcode", "i", "love", "coding"], k = 2
 Output: ["i", "love"]
 Explanation: "i" and "love" are the two most frequent words.
 Note that "i" comes before "love" due to a lower alphabetical order.
 Example 2:
 
 Input: ["the", "day", "is", "sunny", "the", "the", "the", "sunny", "is", "is"], k = 4
 Output: ["the", "is", "sunny", "day"]
 Explanation: "the", "is", "sunny" and "day" are the four most frequent words,
 with the number of occurrence being 4, 3, 2 and 1 respectively.
 Note:
 
 You may assume k is always valid, 1 ≤ k ≤ number of unique elements.
 Input words contain only lowercase letters.
 Follow up:
 
 Try to solve it in O(n log k) time and O(n) extra space.
 */

#include <iostream>
#include <list>
#include "Common.h"

namespace TopKFrequentWords
{
vector<string> topKFrequent(vector<string>& words, int k) {
    unordered_map<string, int> wordCount;
    for (auto& word : words) {
        wordCount[word]++;
    }
    
    auto lessor = [&wordCount](const string& str1, const string& str2) {
        if (wordCount[str1] == wordCount[str2])
            return str1 < str2;
        return wordCount[str1] > wordCount[str2];
    };
    priority_queue<string, vector<string>, decltype(lessor)> minHeap(lessor);
    for (auto& wordAndCount : wordCount) {
        if (minHeap.size() < k) {
            minHeap.emplace(wordAndCount.first);
            continue;
        }
        if (lessor(minHeap.top(), wordAndCount.first))
            continue;
        minHeap.pop();
        minHeap.emplace(wordAndCount.first);
    }
    vector<string> ans;
    ans.reserve(k);
    while (!minHeap.empty()) {
        ans.push_back(minHeap.top());
        minHeap.pop();
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

static void Test()
{
    vector<string> words = {"i", "love", "leetcode", "i", "love", "coding"};
    auto ans = topKFrequent(words, 2);
    for (auto& word : ans)
        std::cout << word << std::endl;
}
}
