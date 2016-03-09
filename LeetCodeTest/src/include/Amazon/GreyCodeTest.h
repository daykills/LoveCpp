/*
������byte���ж������Ƿ�Ϊgrey code����ʵ��Ŀ���Ѿ���ʾ��XOR�ͱ������� leetcode
��Ҫ���Ǽ� byte
*/
#include <iostream>
#include <queue>
#include <algorithm>
#include "Common.h"

namespace GreyCodeTest
{
  // find all unique triplets in the nums with index >= start_index
  bool greyCode(int a, int b)
  {
    unsigned int x = (a ^ b);
    int count = 0;
    while (x != 0)
    {
      x = x & (x - 1);
      count++;
    }
    return (count == 1);
  }

  int Test()
  {
    int a = 5;
    int b = 5;

    cout << a << " " << b << ": " << greyCode(a, b) << endl;
    return 0;
  }
}
