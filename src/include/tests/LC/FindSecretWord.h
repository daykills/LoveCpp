/*
 843. Guess the Word

 This problem is an interactive problem new to the LeetCode platform.
 
 We are given a word list of unique words, each word is 6 letters long, and one word in this list is chosen as secret.
 
 You may call master.guess(word) to guess a word.  The guessed word should have type string and must be from the original list with 6 lowercase letters.
 
 This function returns an integer type, representing the number of exact matches (value and position) of your guess to the secret word.  Also, if your guess is not in the given wordlist, it will return -1 instead.
 
 For each test case, you have 10 guesses to guess the word. At the end of any number of calls, if you have made 10 or less calls to master.guess and at least one of these guesses was the secret, you pass the testcase.
 
 Besides the example test case below, there will be 5 additional test cases, each with 100 words in the word list.  The letters of each word in those testcases were chosen independently at random from 'a' to 'z', such that every word in the given word lists is unique.
 
 Example 1:
 Input: secret = "acckzz", wordlist = ["acckzz","ccbazz","eiowzz","abcczz"]
 
 Explanation:
 
 master.guess("aaaaaa") returns -1, because "aaaaaa" is not in wordlist.
 master.guess("acckzz") returns 6, because "acckzz" is secret and has all 6 matches.
 master.guess("ccbazz") returns 3, because "ccbazz" has 3 matches.
 master.guess("eiowzz") returns 2, because "eiowzz" has 2 matches.
 master.guess("abcczz") returns 4, because "abcczz" has 4 matches.
 
 We made 5 calls to master.guess and one of them was the secret, so we pass the test case.
 Note:  Any solutions that attempt to circumvent the judge will result in disqualification.
 */

#include <iostream>
#include <list>
#include "Common.h"

namespace FindSecretWord
{
class Master {
public:
    Master(const string& secret, vector<string>& wordlist) : m_secret(secret), m_wordset(wordlist.begin(), wordlist.end()) {}
    int guess(const string& word) const {
        if (m_wordset.count(word) == 0)
            return -1;
        assert(m_secret.size() == word.size());
        int cnt = 0;
        for (auto i = 0; i < word.size(); i++) {
            if (m_secret[i] == word[i])
                cnt++;
        }
        return cnt;
    }
private:
    unordered_set<string> m_wordset;
    string m_secret;
};

int commonCharCount(const string& base, const string& str) {
    assert(base.size() == str.size());
    int cnt = 0;
    for (auto i = 0; i < base.size(); i++) {
        if (base[i] == str[i])
            cnt++;
    }
    return cnt;
}

void findSecretWord(vector<string>& wordlist, Master& master) {
    unordered_set<string> dropSet;
    while (true) {
        string word = wordlist[rand() % (wordlist.size())];
        if (dropSet.count(word))
            continue;
        dropSet.emplace(word);
        auto match = master.guess(word);
        if (match == 0) {
            // remove all words with at least one hit
            for (auto& str : wordlist) {
                if (str == word || dropSet.count(str))
                    continue;
                if (commonCharCount(word, str) > 0)
                    dropSet.emplace(str);
            }
            continue;
        }

        assert(match != -1);
        if (match == word.size())
            return;
        for (auto& str : wordlist) {
            if (str == word || dropSet.count(str))
                continue;
            if (commonCharCount(word, str) != match)
                dropSet.emplace(str);
        }
    }
}

static void Test()
{
    string secret = "ccoyyo";
    vector<string> wordlist = {"wichbx","oahwep","tpulot","eqznzs","vvmplb","eywinm","dqefpt","kmjmxr","ihkovg","trbzyb","xqulhc","bcsbfw","rwzslk","abpjhw","mpubps","viyzbc","kodlta","ckfzjh","phuepp","rokoro","nxcwmo","awvqlr","uooeon","hhfuzz","sajxgr","oxgaix","fnugyu","lkxwru","mhtrvb","xxonmg","tqxlbr","euxtzg","tjwvad","uslult","rtjosi","hsygda","vyuica","mbnagm","uinqur","pikenp","szgupv","qpxmsw","vunxdn","jahhfn","kmbeok","biywow","yvgwho","hwzodo","loffxk","xavzqd","vwzpfe","uairjw","itufkt","kaklud","jjinfa","kqbttl","zocgux","ucwjig","meesxb","uysfyc","kdfvtw","vizxrv","rpbdjh","wynohw","lhqxvx","kaadty","dxxwut","vjtskm","yrdswc","byzjxm","jeomdc","saevda","himevi","ydltnu","wrrpoc","khuopg","ooxarg","vcvfry","thaawc","bssybb","ccoyyo","ajcwbj","arwfnl","nafmtm","xoaumd","vbejda","kaefne","swcrkh","reeyhj","vmcwaf","chxitv","qkwjna","vklpkp","xfnayl","ktgmfn","xrmzzm","fgtuki","zcffuv","srxuus","pydgmq"};
    Master master(secret, wordlist);
    findSecretWord(wordlist, master);
}
}
