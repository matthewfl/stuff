#ifndef _ilang_any
#define _ilang_any

/* based off the boost::any class
 * created to give greater control over the generic types
 * added features:
 *  able to delete generic types that are pointers without know what they are
 *  
 */

#include <typeinfo>
#include <assert.h>

namespace ilang {
  class any {
  public:
    any () :
      content(0) {}

    template <typename ValueType>
    any (const ValueType &value) :
      content(new holder<ValueType>(value)) {}

    any(const any &other) :
      content(other.content ? other.content->clone() : 0) {}

    ~any () {
      delete content;
    }

    any & swap (any & rhs) 
    {
      placeHolder *tmp = content;
      content = rhs.content;
      rhs.content = tmp;
      return *this;
    }
    
    any & operator=(any rhs) {
      rhs.swap(*this);
      return *this;
    }

    template<typename ValueType>
    any &operator=(const ValueType &rhs) {
      any(rhs).swap(*this);
      return *this;
    }

    bool empty() const {
      return !content;
    }

    const std::type_info & type () const {
      return content ? content->type() : typeid(void);
    }

    const bool isPointer () const {
      return content->isPointer();
    }

    template <typename T>
    const bool canCast () const {
      //return content ? content->canCast<T>() : false;
      if(content->type() == typeid(T)) return true;
      if(isPointer()) {
	//return dynamic_cast<T>(static_cast<holder<void*>* >(content)->held);
      
	return false;
      }else{
	return dynamic_cast<holder<T>* >(content);
      }
    }

    
    template <typename T>
    T Cast () {
      
    }

  private:
    class placeHolder {
    public:
      virtual ~placeHolder() {};
      virtual const std::type_info & type() const = 0;
      virtual placeHolder * clone () const = 0;
      virtual const bool isPointer () const = 0;
      virtual void destroy () = 0;
      //template <typename T> virtual const bool canCast const () = 0; // doesn't work
    };

    template <class ValueType>
    class holder : public placeHolder {
    public:
      // these are the same for both
      holder (const ValueType &value) :
	held(value) {}
      
      virtual const std::type_info &type() const {
	return typeid(ValueType);
      }
      virtual placeHolder *clone() const {
	return new holder(held);
      }

      // these are different
      virtual const bool isPointer() const { return false; }
      virtual ~holder () {
	
      }
      virtual void destroy () {
	// not a pointer so not a problem
      }

      // the Variable
      ValueType held;
    };

    
    template <typename ValueType>
    class holder<ValueType*> : public placeHolder {
    public:
      typedef ValueType* ValueType_ptr;
      // these are the same for both
      holder(const ValueType_ptr &value) :
	held(value) {}
      virtual const std::type_info &type() const {
	return typeid(ValueType_ptr);
      }
      virtual placeHolder *clone() const {
	return new holder(held);
      }
      
      // these are different
      virtual const bool isPointer () const { return true; }
      virtual ~holder () {

      }
      virtual void destroy () {
	delete held;
      }
      // the Variable
      ValueType_ptr held;
    };

    // the Variable
    placeHolder *content;
  };
};

#endif // _ilang_any
