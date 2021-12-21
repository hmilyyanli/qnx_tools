#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
int main()
{
	int count = 0;
	while(1)
	{
		usleep(10000);//10ms
		count++;
		if(!(count%100))
		{
			printf("Hello world %d\n",time(NULL));
			fflush(stdout);
		}
	}
}
