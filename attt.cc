#include <atomic>
#include <iostream>

using namespace std;

int main () {
	atomic<int> ii;
	cout << "test" << endl;
	cout << ii.is_lock_free() << endl;
}
