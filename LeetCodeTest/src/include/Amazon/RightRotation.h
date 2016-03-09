/*
1.8 Assume you have a method isSubstring which checks if one word is a substring of another.
Given two strings, s1 and s2, write code to check if s2 is a rotation of s1 using only one call to isSubstring
(e.g., "waterbottle" is a rotation of "erbottlewat").
[cpp] view plain copy
*/

#include <iostream>
#include <queue>
#include <algorithm>
#include "Common.h"

namespace RightRotation
{
  static bool isSubstring(string sub, string str)
  {
    return str.find(sub) != string::npos;
  }
  static bool rightRotation(string str1, string str2)
  {
    if (str1.length() != str2.length()) return false;
    string str1Dup = str1 + str1;
    return isSubstring(str2, str1Dup);
  }

  int Test()
  {
    string str1("waterbottle");
    string str2("erbottlewat");

    cout << str1 << " " << str2 << ": " << rightRotation(str1, str2) << endl;
    return 0;
  }
}
