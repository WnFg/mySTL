#include <iostream>
using namespace std;
#include "list.h"

int main()
{
	list<int> a;
	cout << a.size() << endl;
	a.push_back(1);
	a.push_back(2);
	cout << a.size() << endl;
	a.pop_back();
	cout << a.size() << endl;
	return 0;
}
