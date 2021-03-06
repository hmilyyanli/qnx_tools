#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <limits.h>
#include <sys/wait.h>
#include <spawn.h>
#include <sys/mman.h>
#include <pthread.h>
#include <forksafe_mutex.h>

#ifdef __QNX__
#define CMD_PATH "/proc/boot/ls"
#else
#define CMD_PATH "/bin/ls"
#endif
char *data;
/*
 * this CNT magic number based on /proc/$pid/pmap provided informatio
 * CNT = heap start - share memory end
 */
#define CNT 56129810432
int cnt = 0;

int main()
{
	pid_t pid;
#if 0	
	long i,j=0;
	long ps = sysconf(_SC_PAGESIZE);
	unsigned long st1, base = 0x4d20e6c000;//base is share memory region end
	base = ((unsigned long)base & 0xfffffffffffff000);//page aligned
	st1 = base;
	for(i=0; i< CNT; i += ps*ps/8)
	{
		data = mmap((void*)base, ps-1, PROT_READ|PROT_WRITE, MAP_ANON|MAP_PRIVATE|MAP_FIXED, -1, 0);
		mlock(data, ps-1);
		base += ps*ps/16;
		cnt ++;
	}
#endif
	if( (pid=fork()) < 0 )
	{
		perror("fork failed\n");
		exit(1);
	}else if(pid ==0)
	{
		printf("start child with pid %d\n",getpid());
		if(execl(CMD_PATH,"ls",NULL,NULL) < 0)
			printf("echo failed");
	}
	else {
		printf("this is father\n");
	}
	wait(NULL);
		
}

#if 0
        //printf("press anykey continue...\n");
        //getchar();
        char* const c_argv[] = {"ls", NULL};

        posix_spawn(&pid,CMD_PATH,NULL,NULL,c_argv,NULL);
#endif

