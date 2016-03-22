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
//	list<int> a;
//	a.push_back(1);
//	list<int>::iterator it = a.begin();
//	cout << (tinyAr::getPreIterator(it) == a.end()) << endl;
	cout << "asd" << endl;
	int w[3] = {1, 2, 3};
	cout << *(tinyAr::getPreIterator(w + 1)) << endl;
	return 0;
}
