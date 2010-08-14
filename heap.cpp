#! /usr/local/bin/cxx

    /* a test for a handle object
     */

#include <stdlib.h>

#ifndef Matthewfl_heap_PointersListSize
#define Matthewfl_heap_PointersListSize 30
#endif

#include <iostream>

#define matthewfl_debug(msg) \
    std::cout << __LINE__ << ": " << msg << std::endl;

namespace matthewfl {
  namespace heap {
    namespace PrivateHeap {
      template <typename Size> int _real_PointerCompair (void * P1, void * P2) {
	Size _p1 = reinterpret_cast<Size>(P1);
	Size _p2 = reinterpret_cast<Size>(P2);
	return _p2 - _p1;
      }
      int PointerCompair (void * P1, void * P2) {
	if(sizeof(void*) == 8) {
	  return _real_PointerCompair<unsigned long> (P1, P2);
	}
	return 0;
      }
      class Pointers {
      private:
	void * pointers[Matthewfl_heap_PointersListSize];
	unsigned char freePointers;
	void swap (Pointers &p) {
	  /*void * tempPoint[Matthewfl_heap_PointersListSize];// = p.pointers;
	  unsigned char tempFree = p.freePointers;
	  p.pointers = pointers;
	  p.freePointers = freePointers;
	  pointers = tempPoint;
	  freePointers = tempFree;*/
	  Pointers tmp = p;
	  p = *this;
	  *this = tmp;
	}
	Pointers * next;
	void destroySelf () {
	  if(next != NULL) {
	    swap(*next);
	    Pointers * temp = next;
	    next = temp->next;
	    delete temp;
	  }
	}
      public:
	Pointers (): freePointers(Matthewfl_heap_PointersListSize), next(NULL) {
	  for(unsigned char a = 0; a < Matthewfl_heap_PointersListSize; a++)
	    pointers[a] = NULL;
	}
	void ** findPointer () {
	  if(freePointers <= 0) { // no more space
	    matthewfl_debug("matthewfl::heap::private::Pointers full");
	    if (next == NULL) next = new Pointers;
	    return next->findPointer();
	  }else if(freePointers == Matthewfl_heap_PointersListSize && next != NULL) { // delete self
	    destroySelf();
	    return findPointer();
	  }
	  // give it a pointer
	  for(unsigned char a = 0; a < Matthewfl_heap_PointersListSize; a++) {
	    if(pointers[a] == NULL) {
	      freePointers--;
	      pointers[a] = (void*)1; // do not let it give it out again if not used
	      return &pointers[a];
	    }
	  }
	  
	}
	void update () { // update the amount of free space
	  freePointers = 0;
	  for(unsigned int a = 0; a < Matthewfl_heap_PointersListSize; a++) {
	    if(pointers[a] == NULL)
	      freePointers++;
	  }
	  if(Matthewfl_heap_PointersListSize == freePointers) {
	    destroySelf();
	    update();
	  }
	  if(next != NULL)
	    next->update();
	}
      };
      class Manager {
      public:
	static unsigned short counter;
	static Pointers * headPointerNode;
      public:
	static bool _initialized;
	static bool init () {
	  if(Manager::_initialized) return true;
	  matthewfl_debug("matthewfl::heap::private::Manager::init");
	  counter = 0;
	  Manager::headPointerNode = new Pointers;
	  _initialized = true;
	  return true;
	}
	static void * getPointer () {
	  counter++;
	  matthewfl_debug("matthewfl::heap::private::Manager::getPointer");
	  return headPointerNode->findPointer();
	}
      };
      bool Manager::_initialized = false;
      Pointers * Manager::headPointerNode;// = NULL;
      unsigned short Manager::counter;// = 0;
    } // namespace PrivateHeap
    template <typename Type> class Handle {
    private:
      Type ** location;
      void init () {
	PrivateHeap::Manager::init();
	location = reinterpret_cast<Type**> (PrivateHeap::Manager::getPointer());
      }
      void swap(Handle<Type> &h) {
	Type ** tmp = h.location;
	h.location = location;
	location = tmp;
      }
    public:
      Handle (Type * t) {
	init();
	(*location) = reinterpret_cast<Type*>(t);
      }
      Handle (const Handle<Type> &h) {
	location = h.location;
      }
      Handle () {}
      Type & operator * () { return **location; }
      inline Type & operator -> () { return operator*(); }
      Handle<Type> & operator = (Type * d) { 
	Handle<Type> t (d);
	swap(t);
	return *this;
      };
      void operator delete (void * _d) { 
	Handle<Type> * d = reinterpret_cast<Handle<Type> > (_d); 
        delete *(d->location);
	*(d->location) = NULL;
	d->location = NULL;
      }
      void * operator new (size_t size) {
	
      }
      Type * getLocation () { return *location; }
    };
  }// namespace heap

} // namespace matthewfl

#include <iostream>
using namespace std;

using matthewfl::heap::Handle;
int main (int argc, char * argv[]) {
  cout << "running \n";
  Handle<int> a = new int;
  *a = 123;
  cout << *a << endl;
  matthewfl_debug("back");
}
