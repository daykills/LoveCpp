#include <iostream>
#include <string>
#include <vector>
#include "Common.h"



/*
Problem Statement for ZigZag

Problem Statement

A sequence of numbers is called a zig-zag sequence if the differences between successive numbers strictly alternate between positive and negative. The first difference (if one exists) may be either positive or negative. A sequence with fewer than two elements is trivially a zig-zag sequence.

For example, 1,7,4,9,2,5 is a zig-zag sequence because the differences (6,-3,5,-7,3) are alternately positive and negative. In contrast, 1,4,7,2,5 and 1,7,4,5,5 are not zig-zag sequences, the first because its first two differences are positive and the second because its last difference is zero.

Given a sequence of integers, sequence, return the length of the longest subsequence of sequence that is a zig-zag sequence. A subsequence is obtained by deleting some number of elements (possibly zero) from the original sequence, leaving the remaining elements in their original order.

Definition

Class:	ZigZag
Method:	longestZigZag
Parameters:	int[]
Returns:	int
Method signature:	int longestZigZag(int[] sequence)
(be sure your method is public)

Constraints
-	sequence contains between 1 and 50 elements, inclusive.
-	Each element of sequence is between 1 and 1000, inclusive.

Examples
0)
{ 1, 7, 4, 9, 2, 5 }
Returns: 6
The entire sequence is a zig-zag sequence.

1)
{ 1, 17, 5, 10, 13, 15, 10, 5, 16, 8 }
Returns: 7
There are several subsequences that achieve this length. One is 1,17,10,13,10,16,8.

2)
{ 44 }
Returns: 1

3)
{ 1, 2, 3, 4, 5, 6, 7, 8, 9 }
Returns: 2

4)
{ 70, 55, 13, 2, 99, 2, 80, 80, 80, 80, 100, 19, 7, 5, 5, 5, 1000, 32, 32 }
Returns: 8

5)
{ 374, 40, 854, 203, 203, 156, 362, 279, 812, 955,
600, 947, 978, 46, 100, 953, 670, 862, 568, 188,
67, 669, 810, 704, 52, 861, 49, 640, 370, 908,
477, 245, 413, 109, 659, 401, 483, 308, 609, 120,
249, 22, 176, 279, 23, 22, 617, 462, 459, 244 }
Returns: 36
*/

// to find the longest zig-zag sub-array
int TestLongestZigZag()
{
  using namespace std;

  vector<int> inputs = CommonUtils::getIntVector();

  /////////////////////////////////////////
  int sizeOfArray = inputs.size();

  // max sequence that ends at i, with last difference being positive
  vector<int> seqPos(sizeOfArray, 1);
  // max sequence that ends at i, with last difference being negative
  vector<int> seqNeg(sizeOfArray, 1);
  // Both start with 1 at i=0 

  for (auto i = 1; i < sizeOfArray; i++)
  {
    // calculate seqPos[i] and seqNeg[i]
    // assume the second last number is at j (0 ~ i-1)
    for (auto j = 0; j <= i - 1; j++)
    {
      auto diff = inputs[i] - inputs[j];
      // no difference, then no change
      auto seqPosAtI = 1;
      auto seqNegAtI = 1;
      if (0 == diff)
      {
        seqPosAtI = seqPos[j];
        seqNegAtI = seqNeg[j];
      }
      else if (0 < diff) // difference between i-1 and i is positive
      {
        seqPosAtI = seqNeg[j] + 1;
        seqNegAtI = 1;
      }
      else
      {
        seqNegAtI = seqPos[j] + 1;
        seqPosAtI = 1;
      }
      // if the temp length is bigger, update it.
      if (seqPosAtI > seqPos[i]) seqPos[i] = seqPosAtI;
      if (seqNegAtI > seqNeg[i]) seqNeg[i] = seqNegAtI;
    }
  }

  int maxLen = 0;
  int endingAt = -1;

  for (auto i = 0; i < sizeOfArray; i++)
  {
    if (seqPos[i] > maxLen)
    {
      maxLen = seqPos[i];
      endingAt = i;
    }
    if (seqNeg[i] > maxLen)
    {
      maxLen = seqNeg[i];
      endingAt = i;
    }
  }

  cout << "Max len: " << maxLen << " EndingAt: " << endingAt + 1 << endl;

  return maxLen;
}
