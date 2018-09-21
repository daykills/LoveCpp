/*
6. ZigZag Conversion My Submissions Question
Total Accepted: 79002 Total Submissions: 336595 Difficulty: Easy
The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this: (you may want to display this pattern in a fixed font for better legibility)

P   A   H   N
A P L S I I G
Y   I   R
And then read line by line: "PAHNAPLSIIGYIR"
Write the code that will take a string and make this conversion given a number of rows:

string convert(string text, int nRows);
convert("PAYPALISHIRING", 3) should return "PAHNAPLSIIGYIR".
*/

#include <iostream>
#include <stack>
#include <algorithm>
#include "Common.h"

namespace ZigZagConversion
{
  string convert(string s, int numRows)
  {
    if (numRows == 1) return s;
    int n = s.length();

    int distRoundTrip = numRows * 2 - 2;

    vector<string> layers(numRows);

    for (int i = 0; i < n; i++)
    {
      int iRow = i % distRoundTrip;
      if (iRow >= numRows)
      {
        iRow = (distRoundTrip - iRow) % numRows;
      }
      layers[iRow].push_back(s[i]);
    }

    string& result = layers[0];
    for (int i = 1; i < numRows; i++)
    {
      result += layers[i];
    }
    return result;
  }

  int Test()
  {
    string str("1234567890");

    cout << str << ": " << convert(str, 4) << endl;
    return 0;
  }
}