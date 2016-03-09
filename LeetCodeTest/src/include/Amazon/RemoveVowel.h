/*
remove all vowels in a string, for example input = "abcde asdf wer" output = "bcd sdf wr"
算法很简单，就是吧元音往后放。根据考场回忆，事后在eclipse 上调试成功后，具体代码如
下（本人考试时候偷偷使用了eclipse）：
*/

#include <iostream>
#include <queue>
#include <algorithm>
#include "Common.h"

namespace RemoveVowel
{
  string removeVowel(string str)
  {
    const string vowels("aeiouAEIOU");
    string result;
    for (auto ch : str)
    {
      if (vowels.find(ch) == string::npos)
      {
        result.insert(result.end(), ch);
      }
    }
    return result;
  }

  int Test()
  {
    string str("abcde asdf wer");

    cout << str << ": " << removeVowel(str) << endl;
    return 0;
  }
}
