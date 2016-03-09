/*
115. Distinct Subsequences

Given a string S and a string T, count the number of distinct subsequences of T in S.

A subsequence of a string is a new string which is formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (ie, "ACE" is a subsequence of "ABCDE" while "AEC" is not).

Here is an example:
S = "rabbbit", T = "rabbit"

Return 3.
*/
#include <string>
#include <iostream>
#include "Common.h"

namespace DistinctSubsequences
{
  int Test(string s, string t) {
    int lenS = s.length();
    int lenT = t.length();

    // if T is not shorter
    if (lenT >= lenS) return s == t ? 1 : 0;

    // numSubseqs[i][j] means number of subsequences with the first (i + 1) of S and (j + 1) of T
    vector<vector<int>> numSubseqs(lenS, vector<int>(lenT, 0));

    for (int j = 0; j < lenT; j++)
    {
      for (int i = 0; i < lenS; i++)
      {
        // start with numSubseqs[i - 1][j]
        if (i > 0)
          numSubseqs[i][j] = numSubseqs[i - 1][j];
        else
          numSubseqs[i][j] = 0;
        
        if (s[i] == t[j])
        {
          // we can add cases that excluding the last char from both strings
          if (j > 0 && i > 0)
            numSubseqs[i][j] += numSubseqs[i - 1][j - 1];
          else
          {
            if (j == 0)
              numSubseqs[i][j] += 1;
          }
        }
      }
    }

    return numSubseqs[lenS - 1][lenT - 1];
  }
}