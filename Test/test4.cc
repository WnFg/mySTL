#include "../algorithm.h"
#include <iostream>
#include <time.h> 
#include <stdio.h> 
#include<sys/time.h>
#include "../vector.h"
using namespace std;
vector<int> vec;
int main(void)
{
	struct timeval startTime,endTime;
	float Timeuse;
	int i,j;
	
	gettimeofday(&startTime,NULL);
	for(i =0;i <10;i++)
	{
		printf("Nice to see you\n");
		for(j = 0;j <100; j++);
	}
	for(int i = 0; i < 10000000; i++)
		vec.push_back(i);
	gettimeofday(&endTime,NULL);
	
	Timeuse = 1000000*(endTime.tv_sec - startTime.tv_sec) + (endTime.tv_usec - startTime.tv_usec);
	
	Timeuse /= 1000000;
	
	printf("Timeuse = %f\n",Timeuse);
	
return 0;
}
