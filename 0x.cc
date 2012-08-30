#include <iostream>

using namespace std;

int main () {
	auto something = [&](int a){
		cout << "it works\n" << a;
	};
	something (5);
}
