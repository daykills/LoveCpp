/*
Merge sort
*/

#include <algorithm>
#include "Common.h"

namespace MergeSort
{
  // merge two sorted groups (iLeft ~ iMid - 1) and (iMid ~ iRight)

  void MergeGroups(const std::vector<int>& in, std::vector<int>& out, int iLeft, int iMid, int iRight)
  {
    int i1 = iLeft;
    int i2 = iMid;
    // to output one number a time
    for (int i = iLeft; i <= iRight; i++)
    {
      if (i2 > iRight || (i1 < iMid && in[i1] <= in[i2]))
      {
        out[i] = in[i1];
        i1++;
      }
      else
      {
        out[i] = in[i2];
        i2++;
      }
    }
  }

  void MergeSort(std::vector<int>& in)
  {
    int len = in.size();
    std::vector<int> out(len);
    // group width starting from 1
    for (int width = 1; width < len; width *= 2)
    {
      // i is the starting index of group pairs
      for (int i = 0; i < len; i += width * 2)
      {
        int iMid = std::min(i + width, len - 1);
        int iRight = std::min(iMid + width - 1, len - 1);
        MergeGroups(in, out, i, iMid, iRight);
      }
      in = out;
    }
  }

  static bool Test()
  {
    vector<int> nums{ 1, 4, 5, 11, 12, 13, -1, -1, -1, -1, -1 };
    for (auto i : nums)
      cout << " " << i;
    cout << endl;

    MergeSort(nums);

    for (auto i : nums)
      cout << " " << i;
    cout << endl;

    return false;
  }
}