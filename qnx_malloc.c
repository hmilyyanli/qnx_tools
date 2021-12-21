#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <limits.h>
#include <sys/wait.h>
#include <spawn.h>
#include <sys/mman.h>
#include <pthread.h>

#ifdef __QNX__
#include <forksafe_mutex.h>
#define CMD_PATH "/proc/boot/ls"
#else
#define CMD_PATH "/bin/ls"
#endif
/*
 * this CNT magic number based on /proc/$pid/pmap provided informatio
 * CNT = heap start - share memory end
 */
int main()
{
    	char* p;
	printf("please check the memory usage before malloc\n");
	getchar();
	p = malloc(10*1024*1024);
	if(!p)
	{
		printf("alloc failed\n");	
	}
	else{

	printf("please check the memory usage after malloc\n");
	getchar();
	}
		
}

#if 0
        //printf("press anykey continue...\n");
        //getchar();
        char* const c_argv[] = {"ls", NULL};

        posix_spawn(&pid,CMD_PATH,NULL,NULL,c_argv,NULL);
#endif

