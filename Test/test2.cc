#include <iostream>
using namespace std;
int a = 123;
extern int b;

int f()
{
	cout << b << endl;
	return 0;
}
