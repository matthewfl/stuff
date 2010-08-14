
#include <iostream>
using namespace std;
/*#include "breakin.hpp"

class something {
public:
  int hello;
public:
  something (): hello (123) {}
};


class toit {
public:
  template<typename T> void operator() (T * d) {
    //cout<<d->hello<<endl;
  }
};


class some {
public:
  struct so {
    int i;
  };
  typedef so* it;
};
*/

template <typename T> T * noConst (const T * o) {
  T * p = (T*)o;
  return p;
}


int main(int argc, char *argv[]) {
  const int a = 10;
  int * o = noConst(&a);
  *o = 15;
  cout<<*o<<endl<<a<<endl<<*(&a)<<&a<<endl<<o<<endl;

  return 0;
}
