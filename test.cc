#include <iostream>
using namespace std;
#include "list.h"

int main()
{
	list<int> a;
	//cout << a.size() << endl;
	//a.push_back(1);
	//a.push_back(2);
	//cout << a.size() << endl;
	//a.pop_back();
	//cout << a.size() << endl;
	a.push_back(3);
	a.push_back(2);
	a.push_back(1);
	for(list<int>::iterator it = a.begin(); it != a.end(); ++it) {
		cout << it->data << endl;
	}
	a.sort();
	cout << endl;
	for(list<int>::iterator it = a.begin(); it != a.end(); ++it) {
		cout << it->data << endl;
	}
	cout << a.size() << endl;
	return 0;
}
