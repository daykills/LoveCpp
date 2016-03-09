// CPPTest.cpp : Defines the entry point for the console application.
//

#include <iostream>

class BaseT
{
public:
  BaseT() {
    std::cout << "Base: " << this << std::endl;
  }
  int x;
  int y;
  int z;
};

class Derived : public BaseT
{
public:
  Derived() {
    std::cout << "Derived: " << this << std::endl;
  }

  int h;

  void fun(){}
};

int main() {
  //Derived d;

  Derived* pD = new Derived();
  BaseT* pB = pD;
  std::cout << "Base: " << pB << std::endl;
  std::cout << "Derived: " << pD << std::endl;
  return 0;
}