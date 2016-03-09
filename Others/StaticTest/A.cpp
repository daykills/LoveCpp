#include <iostream>
#include "A.h"

namespace Test
{
  
}

int A::s_num;

const int const_num = 111;

void SetNum(int num)
{
  std::cout << A::s_num << std::endl;
  A::s_num = num;
  std::cout << A::s_num << std::endl;
}