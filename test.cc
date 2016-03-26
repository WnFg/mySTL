#include <iostream>
#include "queue.h"

int a[] = {3, 2, 3, 1, 2};

priority_queue<int> q, w(a, a + 5);
queue<int> qq;

int main()
{
	for(int i = 10; i > 0; i--) {
		q.push(i);
	}
	qq.push(1);
	std::cout << *qq.begin() << std::endl;
	std::cout << w.top() << std::endl;
	while(!q.empty()) {
		std::cout << q.top() << std::endl;
		q.pop();
	}
	return 0;
}
