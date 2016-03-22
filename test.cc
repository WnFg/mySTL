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

/*class 
{
public:
	A() : a(123) {}
	int a;	
};*/
int main()
{
	cout << "asd" << endl;
	int w[3] = {1, 2, 3};
	cout << *(tinyAr::getPreIterator(w + 1)) << endl;
	list<int> lt;
	for(int i = 0; i < 10; i++) {
		lt.push_back(i);
	}

	lt.sort(tinyAr::greater<int>());
	for(list<int>::iterator it = lt.begin(); it != lt.end(); ++it) {
		cout << it->data << endl;
	}

	cout << lt.front() << endl;
	return 0;
}
