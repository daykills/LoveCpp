/*
remove all vowels in a string, for example input = "abcde asdf wer" output = "bcd sdf wr"
�㷨�ܼ򵥣����ǰ�Ԫ������š����ݿ������䣬�º���eclipse �ϵ��Գɹ��󣬾��������
�£����˿���ʱ��͵͵ʹ����eclipse����
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
