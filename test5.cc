#include "algorithm.h"
#include "deque.h"
#include <iostream>

int main()
{
	deque<int> q;
	
	for(int i = 0; i < 5; i++) {
		q.push_back(i);
	}
	
	for(int i = 0; i < q.size(); i++) {
		std::cout << q[i] << std::endl;
	}
	return 0;
}
