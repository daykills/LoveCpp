/*
97. Interleaving String

Given s1, s2, s3, find whether s3 is formed by the interleaving of s1 and s2.

For example,
Given:
s1 = "aabcc",
s2 = "dbbca",

When s3 = "aadbbcbcac", return true.
When s3 = "aadbbbaccc", return false.
*/
#include <string>
#include <iostream>
#include <vector>
#include "Common.h"

namespace InterleavingString
{
  bool Test(const string& s1, const string& s2, const string& s3)
  {
    int len1 = s1.length();
    int len2 = s2.length();
    int len3 = s3.length();

    // lengths should match
    if (len1 + len2 != len3) return false;

    // result[i][k] is the result with the first i chars of s1, and first k chars of s3 (implicitly, the first (k - i) chars of s2)
    vector<vector<bool>> result(len1 + 1, vector<bool>(len3 + 1, false));
    // empty strings always true
    result[0][0] = true;
    // for cases when i = 0, k = 1:len2
    for (int k = 1; k <= len2; k++)
    {
      result[0][k] = result[0][k - 1] && (s3[k - 1] == s2[k - 1]);
    }
    
    for (int i = 1; i <= len1; i++)
    {
      // k has to be not smaller than s1
      for (int k = i; k <= len3; k++)
      {
        // check the case that excludes last char of s1 and s3
        result[i][k] = result[i - 1][k - 1] && s1[i - 1] == s3[k - 1];
        // if k == i; then no point to check s2 and s3 - result must be false
        if (false == result[i][k] && k > i)
        {
          // check the case that excluds last char of s2 and s3
          result[i][k] = result[i][k - 1] && s2[k - i - 1] == s3[k - 1];
        }
      }
    }

    return result[len1][len3];
  }
}
