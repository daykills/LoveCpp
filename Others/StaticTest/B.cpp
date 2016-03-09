#include <iostream>
#include "A.h"
#include "B.h"

using namespace std;

namespace Test
{
}

B::B()
{
  Test::s_num = 2;
  cout << Test::s_num << " From B" << endl;
  A::s_num = 21;
}