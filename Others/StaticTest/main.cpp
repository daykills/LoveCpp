// StaticTest.cpp : Defines the entry point for the console application.
//
#include <iostream>

#include "A.h"
#include "B.h"
#include "C.h"

using namespace std;
int main(int argc, char* argv[])
{
  cout << Test::s_num << endl;
  
  SetNum(33); 

  B b;

  cout << A::s_num << endl;
  
  C c;

  cout << A::s_num << endl;

  cout << const_num << endl;

	return 0;
}

