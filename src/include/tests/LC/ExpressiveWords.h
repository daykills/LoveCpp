/*
 809. Expressive Words

 Sometimes people repeat letters to represent extra feeling, such as "hello" -> "heeellooo", "hi" -> "hiiii".  In these strings like "heeellooo", we have groups of adjacent letters that are all the same:  "h", "eee", "ll", "ooo".
 
 For some given string S, a query word is stretchy if it can be made to be equal to S by any number of applications of the following extension operation: choose a group consisting of characters c, and add some number of characters c to the group so that the size of the group is 3 or more.
 
 For example, starting with "hello", we could do an extension on the group "o" to get "hellooo", but we cannot get "helloo" since the group "oo" has size less than 3.  Also, we could do another extension like "ll" -> "lllll" to get "helllllooo".  If S = "helllllooo", then the query word "hello" would be stretchy because of these two extension operations: query = "hello" -> "hellooo" -> "helllllooo" = S.
 
 Given a list of query words, return the number of words that are stretchy.
 
 
 
 Example:
 Input:
 S = "heeellooo"
 words = ["hello", "hi", "helo"]
 Output: 1
 Explanation:
 We can extend "e" and "o" in the word "hello" to get "heeellooo".
 We can't extend "helo" to get "heeellooo" because the group "ll" is not size 3 or more.
 
 
 Notes:
 
 0 <= len(S) <= 100.
 0 <= len(words) <= 100.
 0 <= len(words[i]) <= 100.
 S and all words in words consist only of lowercase letters
*/

#include <algorithm>
#include <unordered_set>
#include "Common.h"

namespace ExpressiveWords
{

vector<int> encode(const string& str) {
    if (str.empty()) return {};
    vector<int> code;
    for (auto i = 0; i < str.size();) {
        code.push_back(str[i]);
        auto j = i + 1;
        while (j < str.size() && str[j] == str[i]) j++;
        code.push_back(j - i);
        i = j;
    }
    return code;
}

int expressiveWords(string S, vector<string>& words) {
    auto codeS = encode(S);
    int ans = 0;
    for (auto& word : words) {
        auto codeWord = encode(word);
        if (codeWord.size() != codeS.size()) continue;
        bool stretchy = true;
        for (auto i = 0; i < codeS.size(); i = i + 2) {
            if (codeWord[i] != codeS[i]) {
                stretchy = false;
                break;
            }
            if (codeWord[i + 1] == codeS[i + 1]) continue;
            if (codeS[i + 1] < 3 || codeWord[i + 1] > codeS[i + 1]) {
                stretchy = false;
                break;
            }
        }
        if (stretchy)
            ans++;
    }
    return ans;
}

void Test() {
    string S = "heeellooo";
    vector<string> words = {"hello", "hi", "helo"};
    cout << expressiveWords(S, words) << endl;
}
}
