#ifndef _matthewfl_operator_hpp
#define _matthewfl_operator_hpp

#ifndef global_operator
namespace matthewfl {
#endif

  template <typename T> inline const bool operator > (const T a, const T b) {
    return b.operator < (a);
  }
  template <typename T> inline const bool operator <= (const T a, const T b) {
    return a.operator < (b) || a.operator == (b);
  }
  template <typename T> inline const bool operator >= (const T a, const T b) {
    return b.operator < (a) || b.operator == (a);
  }
  template <typename T> inline const bool operator != (const T a, const T b) {
    return !(a.operator == (b));
  }

#ifndef global_operator
} // namespace matthewfl
#endif

#endif // _matthewfl_operator_hpp
