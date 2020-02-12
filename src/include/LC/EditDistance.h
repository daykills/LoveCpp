/*
72. Edit Distance

Given two words word1 and word2, find the minimum number of steps required to convert word1 to word2. (each operation is counted as 1 step.)

You have the following 3 operations permitted on a word:

a) Insert a character
b) Delete a character
c) Replace a character
*/

#include <string>
#include <iostream>
#include <algorithm>
#include "Common.h"

namespace EditDistance
{
  int Test(const string& word1, const string& word2) {
    
    int len1 = word1.length();
    int len2 = word2.length();

    if (len1 == 0) return len2;
    else if (len2 == 0) return len1;

    // steps[i][j] means minimum steps required to convert word1[0:i] to word2[0:j]
    vector<vector<int>> steps(len1 + 1, vector<int>(len2 + 1, 0));

    // initialize for cases j = 0
    for (int i = 0; i <= len1; i++)
    {
      // i deletions
      steps[i][0] = i;
    }

    // initialize for cases i = 0
    for (int j = 0; j <= len2; j++)
    {
      // j insertions
      steps[0][j] = j;
    }

    for (int i = 1; i <= len1; i++)
    {
      for (int j = 1; j <= len2; j++)
      {
        // the current words are at (i - 1) and (j - 1)
        if (word1[i - 1] == word2[j - 1])
        {
          // no additional convertion is needed
          steps[i][j] = steps[i - 1][j - 1];
        }
        else
        {
          // word1[i] -> word2[j] can have three options
          // 1. word1[i - 1] -> word2[j], plus a deletion
          // 2. word1[i] -> word2[j - 1], plus an insertion
          // 3. word1[i - 1] -> word2[j - 1], plus a replacement
          steps[i][j] = min(min(steps[i - 1][j], steps[i][j - 1]), steps[i - 1][j - 1]) + 1;
        }
      }
    }

    return steps[len1][len2];
  }
}
