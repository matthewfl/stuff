#ifndef _combine_hpp_matthewfl
#define _combine_hpp_matthewfl

namespace matthewfl {
  template <typename a,
	    typename b>
  class  combine: public a, public b {};
} // end namespace matthewfl
