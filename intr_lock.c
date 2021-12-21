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
#include <sys/neutrino.h>

#ifdef __QNX__
#define CMD_PATH "/proc/boot/ls"
#else
#define CMD_PATH "/bin/ls"
#endif
//char *data;
static int cur;
static intrspin_t lock;
pthread_mutex_t plock = PTHREAD_MUTEX_INITIALIZER;

void* sub_thread(void* args)
{
	ThreadCtl( _NTO_TCTL_IO, 0 );
	while(1){
#if 0		
	InterruptLock(&lock);
	cur++;
	//printf("sub cur:%d\n",cur);
	sleep(1);
	InterruptUnlock(&lock);
#endif
		pthread_mutex_lock(&plock);
		cur++;
		printf("sub cur:%d\n",cur);
		sleep(1);
		 pthread_mutex_unlock(&plock);	
		//InterruptUnlock(&lock);
	}
	pthread_exit(0);
}
int main()
{
	pid_t pid;
	pthread_t ptid;
	int status;
	ThreadCtl( _NTO_TCTL_IO, 0 );
	pthread_create(&ptid,NULL,sub_thread,NULL);
	while(1){
		//InterruptLock(&lock);
		pthread_mutex_lock(&plock);
		//cur--;
		printf("main cur:%d\n",cur);
		//sleep(1);
		pthread_mutex_unlock(&plock);
		//InterruptUnlock(&lock);
	}	
	
	
#if 0	
	pid_t pid;
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
	printf("mmap: %p %lx     cnt:%d\n",data,base,cnt);
	//printf("please check pages_wired value from /proc/vm/stats\n");
	//printf("press any key to do fork...\n");
	getchar();

	if( (pid=fork()) < 0 )
	{
		perror("fork failed\n");
		exit(1);
	}else if(pid ==0)
	{
		printf("start child\n");
		getchar();
		if(execl(CMD_PATH,"ls",NULL,NULL) < 0)
			printf("echo failed");
	}
	else {
		printf("this is father\n");
	}

	for(i=0; i< CNT; i += ps*ps/8)
	{
		*(char*)st1 = 0x12;
		st1 += ps*ps/16;
	}
	sleep(10);
	wait(NULL);
#endif
		
}

#if 0
        //printf("press anykey continue...\n");
        //getchar();
        char* const c_argv[] = {"ls", NULL};

        posix_spawn(&pid,CMD_PATH,NULL,NULL,c_argv,NULL);
#endif

