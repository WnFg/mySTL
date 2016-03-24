#include "stack.h"
#include <iostream>

int main()
{
	stack<int> q;
	q.push(1);
	std::cout << q.back() << std::endl;
	q.pop();
	std::cout << q.size() << std::endl;
	return 0;
}
