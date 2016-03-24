#include "queue.h"
#include <iostream>

int main()
{
	queue<int> q;
	q.push(1);
	std::cout << q.front() << std::endl;
	q.pop();
	std::cout << q.empty() << std::endl;
	return 0;
}
