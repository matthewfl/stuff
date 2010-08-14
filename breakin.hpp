
namespace matthewfl {
  
  template <class WITH> class BreakIn {
  public:
    BreakIn () {}
    ~BreakIn () {}
    template <typename T> void run (T * d) {
      holding((inherit<T>*)d);
    }
    template <typename T> void operator() (T * d) {
      holding((inherit<T>*)d);
    }
    WITH & get () const {
      return &holding;
    }
    template <typename TO> class inherit : protected TO {
      friend class WITH;
    };
  private:
    WITH holding;
  };

  template <typename TO,typename WITH, typename RET = void*>
  RET BreakInTo(TO * t, WITH * w) {
    return ((*w)((BreakIn<WITH>::inherit<TO>*)(t)));
  }

} // namespace matthewfl
