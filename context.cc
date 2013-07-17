#include <ucontext.h>

#include <iostream>
using namespace std;


int main_not (int argc, char **argv) {
	ucontext_t context;
	int count = 1;
	getcontext(&context);
	cout << "hello world " << count++ << endl;
	setcontext(&context);
	return 0;
}



       #include <ucontext.h>
       #include <stdio.h>
       #include <stdlib.h>

       static ucontext_t uctx_main, uctx_func1, uctx_func2;

       #define handle_error(msg) \
           do { perror(msg); exit(EXIT_FAILURE); } while (0)

       static void
       func1(void)
       {
           printf("func1: started\n");
           printf("func1: swapcontext(&uctx_func1, &uctx_func2)\n");
           if (swapcontext(&uctx_func1, &uctx_func2) == -1)
               handle_error("swapcontext");
           printf("func1: returning\n");
       }

       static void
       func2(void)
       {
           printf("func2: started\n");
           printf("func2: swapcontext(&uctx_func2, &uctx_func1)\n");
           if (swapcontext(&uctx_func2, &uctx_func1) == -1)
               handle_error("swapcontext");
           printf("func2: returning\n");
       }

       int
       main_context_test(int argc, char *argv[])
       {
           char func1_stack[16384];
           char func2_stack[16384];

           if (getcontext(&uctx_func1) == -1)
               handle_error("getcontext");
           uctx_func1.uc_stack.ss_sp = func1_stack;
           uctx_func1.uc_stack.ss_size = sizeof(func1_stack);
           uctx_func1.uc_link = &uctx_main;
           makecontext(&uctx_func1, func1, 0);

           if (getcontext(&uctx_func2) == -1)
               handle_error("getcontext");
           uctx_func2.uc_stack.ss_sp = func2_stack;
           uctx_func2.uc_stack.ss_size = sizeof(func2_stack);
           /* Successor context is f1(), unless argc > 1 */
           uctx_func2.uc_link = NULL;//(argc > 1) ? NULL : &uctx_func1;
           makecontext(&uctx_func2, func2, 0);

           printf("main: swapcontext(&uctx_main, &uctx_func2)\n");
           if (swapcontext(&uctx_main, &uctx_func2) == -1)
               handle_error("swapcontext");

           printf("main: exiting\n");
           exit(EXIT_SUCCESS);
       }


//#include <thread>
#include <boost/thread.hpp>
#include <assert.h>

boost::thread_specific_ptr<int> thread_count;

static void switch_to(void) {
	cout << "switched value " << thread_count.get() << "\t" << *(thread_count.get()) << endl;
}

static void thread_start() {
	cout << "thread has started\n";
	thread_count.reset(new int);
	while(*thread_count.get() < 10) {
		(*thread_count.get())++;
		cout << *thread_count.get() << endl;
	}

	char stack[2000];
	ucontext_t context_to;
	ucontext_t context_self;
	assert(getcontext(&context_to) != -1);
	context_to.uc_stack.ss_sp = stack;
	context_to.uc_stack.ss_size = 2000;
	context_to.uc_link = &context_self;
	makecontext(&context_to, switch_to, 0);
	
	cout << "before swap\n";
	assert(swapcontext(&context_self, &context_to) != -1);
	cout << "after swap\n";
	
	//boost::this_thread::sleep(100);
}

int main(int argc, char **argv) {
	boost::thread thr(thread_start);
	boost::thread thr2(thread_start);
	thr.join();
	thr2.join();
	cout << "done\n" << flush;
}
