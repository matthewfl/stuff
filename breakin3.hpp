#ifndef _BreakIn_Hpp
#define _BreakIn_Hpp


namespace matthewfl {

  namespace breakIn {
    template <typename TO, typename WITH> class BREAK: protected TO {
      friend class WITH;
    };
    template <typename TO, typename WITH> void run (TO &t, WITH &w) {
      BREAK<TO, WITH> * obj = (BREAK<TO, WITH>*)&t;
      w.BREAK(*obj);
    }
  } // namespace breakIn

} // namespace matthewfl



#endif // _BreakIn_Hpp
