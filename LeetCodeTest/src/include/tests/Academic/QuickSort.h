/*
Merge sort
*/

#include <algorithm>
#include "Common.h"

namespace QuickSort
{
  void swap(std::vector<int>& data, int i, int j)
  {
    int v = data[i];
    data[i] = data[j];
    data[j] = v;
  }

  void Partition(std::vector<int>& data, int left, int right)
  {
    if (left < right)
    {
      int i = left;
      int j = right;
      int mid = (left + right) / 2;
      int med = data[mid];

      while (i < j)
      {
        while (data[i] < med) i++;
        while (data[j] > med) j--;
        if (i <= j)
        {
          swap(data, i, j);
          i++;
          j--;
        }
      }
      Partition(data, left, j);
      Partition(data, i, right);
    }
  }

  void QuickSort(std::vector<int>& data)
  {
    int len = data.size();
    Partition(data, 0, len - 1);
  }

  static bool Test()
  {
    vector<int> nums{ 1, 4, 5, 11, 12, 13, -1, -1, -1, -1, -1 };
    for (auto i : nums)
      cout << " " << i;
    cout << endl;

    QuickSort(nums);

    for (auto i : nums)
      cout << " " << i;
    cout << endl;

    return false;
  }
}