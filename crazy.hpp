#ifndef _CRAZY_HPP
#define _CRAZY_HPP

template <typename T> class Crazy {
private:
  T o;
public:
  T & operator * () { return &o; }
  T
};

#endif // _CRAZY_HPP
