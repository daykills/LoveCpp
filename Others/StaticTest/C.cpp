#include <iostream>
#include "A.h"
#include "C.h"
using namespace std;
namespace Test
{
}

C::C()
{
  Test::s_num = 3;
  cout << Test::s_num << " From C" << endl;
  A::s_num = 31;
}