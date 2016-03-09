#pragma once
namespace Test
{
  static int s_num = 1; // static has to be initialized
}

class A
{
public:
  static int s_num;
};

extern const int const_num;

extern void SetNum(int num);