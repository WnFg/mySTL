#include <iostream>
using namespace std;
#include "algorithm.h"
#include "list.h"

/*template <class T>
void f(const T&) {
	cout << "1" << endl;
}*/

template <class T>
void f(T&) {
	cout << 2 << endl;
}

int main()
{
	const int aaaa = 1;
	f(aaaa);
	list<int> a;
	a.push_back(3);
	a.push_back(2);
	a.push_back(1);
	for(list<int>::iterator it = a.begin(); it != a.end(); ++it) {
		cout << it->data << endl;
	}
	a.sort(tinyAr::less<int>());
	cout << endl;
	for(list<int>::iterator it = a.begin(); it != a.end(); ++it) {
		cout << it->data << endl;
	}
	cout << a.size() << endl;
	return 0;
}
