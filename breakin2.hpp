
namespace matthewfl {

  template <typename TO, typename WITH> 
  class BreakIn {
  public:
   BreakIn () {}
   ~BreakIn() {}
   
    template <typename ret = void, typename give> ret run (give data) {
      holding(inherit)
  }

  private:
    WITH holding;
    template <typename TO, typename WITH> class inherit : public,private,protected TO {
    public:
      friend class WITH;
    };
 };
  
  
} // matthewfl
