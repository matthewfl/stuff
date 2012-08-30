#include "any.hpp"

#include <iostream>
using namespace std;
using namespace ilang;

class A {
public:
  virtual void Print () {
    cout << "from class A\n";
  }
};

class B : public A {
  virtual void Print () {
    cout << "from class B\n";
  }
};

int main () {
  any a(new B);
  cout << a.type().name() << endl 
       << a.isPointer() <<  endl
       << a.canCast<B*>() << endl;
}
// g++ -std=c++11 -Wall -w any_test.cc -o any_test

