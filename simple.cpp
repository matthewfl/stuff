#! /usr/local/bin/cxx

#include <iostream>

#include <assert.h>

#ifndef NDEBUG
#ifndef debug
#define debug(OUT) \
    std::cout<<__FILE__ <<":"<<__LINE__<<" "<< #OUT <<std::endl;
#endif // debug
#endif // NDEBUG

    /*
template <short Size = sizeof(void*)> 
			      short PointerCompair (void*, void*);

short PointerCompair <8> (void * a, void * b) {
  long _a = reinterpret_cast<long>(a);
  long _b = reinterpret_cast<long>(b);
  return _a == _b ? 0 : _a > _b ? 1 : -1;
}
    */
    /*
template <short Size = sizeof(void*)> class PointerCompair {

};
class PointerCompair <8> {
public:
  static short Compair (void * a, void * b) {
    long _a = reinterpret_cast<long>(a);
    long _b = reinterpret_cast<long>(b);
    return _a == _b ? 0 : _a > _b ? 1 : -1;
  }
};
class PointerCompair <4> {
public:
  static short Compair (void * a, void * b) {
    int _a = reinterpret_cast<int>(a);
    int _b = reinterpret_cast<int>(b);
    return _a == _b ? 0 : _a > _b ? 1 : -1;
  }
};
    */

int Compair (void * a, void * b) {
    long _a = reinterpret_cast<long>(a);
    long _b = reinterpret_cast<long>(b);
    std::cout<<_a<<" "<<_b<<"\n";
    return _b - _a;// ? 0 : _a > _b ? 1 : -1;
  }
/*
#include <stdlib.h>
void * operator new (size_t size) {
  std::cout<<size<<std::endl;
  return malloc(size);
}

void operator delete (void * loc) {
  free(loc);
}
*/

using namespace std;

class test {
public:
  test () {
    cout<<"made\n";
  }
  ~test () {
    cout << "destroyed\n";
  }
};

int main (int argc, char *argv[]) {
  int * a = new int;
  int * b = new int[256];
  int * c = new int;
  test * t = new test;
  delete t;
  cout<<Compair(a, b)<<endl<<Compair(b,c);
  //cout<<endl<<(char*)a+4;
  char * h = (char*)a+1;
  //*h = "h";
  cout<<*h;
  /*cout << sizeof(void*);  
  cout << endl << sizeof (int) << endl
       << sizeof (long) << endl
       << sizeof (long long) << endl
       << reinterpret_cast<long>(a) << endl
       << reinterpret_cast<long>(b) << endl 
       << PointerCompair::Compair(a, b) << endl;*/
}
