#include "algorithm.h"
#include "deque.h"

#include <iostream>
#include <algorithm>
/*int b = 1;

int f(int x, const int& w = b) {
	return x + w;
}*/

/*class A{
public:
	int a;
	int f(int x, const int& w = this->a) {
		return x + a;
	}
};
*/
/*template <class T>
void f(T a) {
	a = 2;
}

template <class T>
void f(const T& a) {
	std::cout << "asd" << std::endl;
}

template <class T>
void f(const T a) {
		
}*/

void f(const int a) {}
void f(const int& a) {}
int main()
{
//	int b;
//	const int& a = b;
//	std::cout << f(a) << std::endl;
	int b = 1;
	f(b);
	deque<int> q;
	
	for(int i = 0; i < 5; i++) {
		q.push_back(5 - i);
	}
	
	q.push_front(2);
	q.pop_back();
	q.pop_back();
	for(int i = 0; i < q.size(); i++) {
		std::cout << q[i] << std::endl;
	}
	return 0;
}
