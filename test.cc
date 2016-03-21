#include <iostream>
using namespace std;
#include "algorithm.h"
#include "list.h"
#include "fe.cc"

/*template <class T>
void f(const T&) {
	cout << "1" << endl;
}*/

template <class T>
void f(T&) {
	cout << 2 << endl;
}

class A
{
public:
	A() : a(123) {}
	int a;	
};
int main()
{
	int er = 1;
	tinyMemo::destroy(&er);
	typedef int T;
	const int w = 1;
	const B<int>::pointer ww = &w;
	return 0;
}
