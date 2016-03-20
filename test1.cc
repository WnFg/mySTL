#include <iostream>
using namespace std;

int b = 213;
int f();

int main()
{
	extern int a;
	cout << a << endl;
	f();
	return 0;
}
