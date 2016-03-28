#include "map.h"
#include <iostream>
#include "set.h"
#include "queue.h"
#include "__rb_tree.h"
//map<int, int> mp;
queue<int> q;
set<int> st;
rb_tree<int> rb;
class A
{
public:
	int a, b;	
	void operator= (int x) {
		a = x;
	}
};

map<int, int> mp;
int main()
{
	mp.insert(1, 2);
	mp.insert(2, 3);
	std::cout << mp[2] << std::endl;
	mp[2] = 4;
	A a;
	a.a = 1, a.b = 2;
	A b;
	b = 5;
	b = a;
	std::cout << b.a << " " << b.b << std::endl;
	return 0;
}
