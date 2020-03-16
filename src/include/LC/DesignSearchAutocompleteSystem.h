/*
 642. Design Search Autocomplete System

 Design a search autocomplete system for a search engine. Users may input a sentence (at least one word and end with a special character '#'). For each character they type except '#', you need to return the top 3 historical hot sentences that have prefix the same as the part of sentence already typed. Here are the specific rules:

 The hot degree for a sentence is defined as the number of times a user typed the exactly same sentence before.
 The returned top 3 hot sentences should be sorted by hot degree (The first is the hottest one). If several sentences have the same degree of hot, you need to use ASCII-code order (smaller one appears first).
 If less than 3 hot sentences exist, then just return as many as you can.
 When the input is a special character, it means the sentence ends, and in this case, you need to return an empty list.
 Your job is to implement the following functions:

 The constructor function:

 AutocompleteSystem(String[] sentences, int[] times): This is the constructor. The input is historical data. Sentences is a string array consists of previously typed sentences. Times is the corresponding times a sentence has been typed. Your system should record these historical data.

 Now, the user wants to input a new sentence. The following function will provide the next character the user types:

 List<String> input(char c): The input c is the next character typed by the user. The character will only be lower-case letters ('a' to 'z'), blank space (' ') or a special character ('#'). Also, the previously typed sentence should be recorded in your system. The output will be the top 3 historical hot sentences that have prefix the same as the part of sentence already typed.

  
 Example:
 Operation: AutocompleteSystem(["i love you", "island","ironman", "i love leetcode"], [5,3,2,2])
 The system have already tracked down the following sentences and their corresponding times:
 "i love you" : 5 times
 "island" : 3 times
 "ironman" : 2 times
 "i love leetcode" : 2 times
 Now, the user begins another search:

 Operation: input('i')
 Output: ["i love you", "island","i love leetcode"]
 Explanation:
 There are four sentences that have prefix "i". Among them, "ironman" and "i love leetcode" have same hot degree. Since ' ' has ASCII code 32 and 'r' has ASCII code 114, "i love leetcode" should be in front of "ironman". Also we only need to output top 3 hot sentences, so "ironman" will be ignored.

 Operation: input(' ')
 Output: ["i love you","i love leetcode"]
 Explanation:
 There are only two sentences that have prefix "i ".

 Operation: input('a')
 Output: []
 Explanation:
 There are no sentences that have prefix "i a".

 Operation: input('#')
 Output: []
 Explanation:
 The user finished the input, the sentence "i a" should be saved as a historical sentence in system. And the following input will be counted as a new search.

  
 Note:

 The input sentence will always start with a letter and end with '#', and only one blank space will exist between two words.
 The number of complete sentences that to be searched won't exceed 100. The length of each sentence including those in the historical data won't exceed 100.
 Please use double-quote instead of single-quote when you write test cases even for a character input.
 Please remember to RESET your class variables declared in class AutocompleteSystem, as static/class variables are persisted across multiple test cases. Please see here for more details.
 
 */

#include "Common.h"

namespace DesignSearchAutocompleteSystem
{
class AutocompleteSystem {
public:
    AutocompleteSystem(vector<string>& sentences, vector<int>& times) {
        assert(sentences.size() == times.size());
        for (auto i = 0; i < sentences.size(); i++) {
            m_freq[sentences[i]] += times[i];
        }
    }
    
    vector<string> input(char c) {
        using tuple_type = pair<string, int>;
        if (c == '#') {
            if (!m_data.empty())
                m_freq[m_data]++;
            m_data = "";
            return {};
        }
        m_data.push_back(c);
        // lessor for min heap
        auto lessor = [](const tuple_type& lhs, const tuple_type& rhs) {
            return lhs.second > rhs.second || (lhs.second == rhs.second && lhs.first <  rhs.first);
        };
        priority_queue<tuple_type, vector<tuple_type>, decltype(lessor)> minHeap(lessor);
        for (auto& wordAndFreq : m_freq) {
            bool matched = true;
            for (auto i = 0; i < m_data.size(); i++) {
                if (i >= wordAndFreq.first.size() || m_data[i] != wordAndFreq.first[i]) {
                    matched = false;
                    break;
                }
            }
            if (matched) {
                minHeap.push(wordAndFreq);
                if (minHeap.size() > 3) minHeap.pop();
            }
        }
        vector<string> ans(minHeap.size());
        for (int i = ans.size() - 1; i >= 0; i--) {
            ans[i] = minHeap.top().first;
            minHeap.pop();
        }
        return ans;
    }
private:
    unordered_map<string, int> m_freq;
    string m_data;
};

/**
* Your AutocompleteSystem object will be instantiated and called as such:
* AutocompleteSystem* obj = new AutocompleteSystem(sentences, times);
* vector<string> param_1 = obj->input(c);
*/

static void Test()
{
    vector<string> sentences {
        "i love you","island","iroman","i love leetcode"
    };
    vector<int> times {
        5,3,2,2
    };
    
    string inputs = "i a#";
    
    AutocompleteSystem s(sentences, times);
    
    for (auto ch : inputs) {
        auto completions = s.input(ch);
        cout << ch << ": ";
        for (auto& str : completions)
            cout << "[" << str << "], ";
        cout << endl;
    }
}
}
