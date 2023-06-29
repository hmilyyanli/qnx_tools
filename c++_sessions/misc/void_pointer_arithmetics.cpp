#include <iostream>
//#include <unistd.h>
//#include <sys/time.h>
//#include <stdlib.h>
//#include <sys/wait.h>
template <int SIZE>
class Test
{
    //const int SIZE = 5;
public:
    Test():b(SIZE){}
    int b;
};

struct s
{
int16_t m1 [ 32 ];
};
struct t
{
int32_t m2;
struct s m3;
};
void fn ( )
{
union // Breaks Rule 9–5–1
{
struct s u1;
struct t u2;
} a;
a.u2.m3 = a.u1; // Non-compliant
}
//const int SIZE = 5;
int main(int argc, char* argv[])
{
	//printf("size of is %ld\n", sizeof(struct Test));
	std::cout << "hello" << std::endl;
	//const int size = atoi(argv[1]);
	//std::cout << "size is " << size << std::endl;
	//int arr[SIZE];
	//Test<size> m_t;
	//fn();
	int a[5];
	void* pa=(void*)a;
	std::cout << "addr: "<< pa << std::endl;
	pa +=1;
	std::cout << "addr again: "<< pa << std::endl;
#if 0
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
	int* p = (int*)malloc(1024);
	if(!p)
	{
		printf("malloc failed\n");
	}
	 pid_t pids;
	 if ((pids = fork()) < 0) {
            perror("fork");
            abort();
        } else if (pids == 0) {
		*p = 0x1234;
	}
	 else
	 {
		 int status;
        pid_t pid = wait(&status);
		printf("val:%x\n",*p);
	 }
#endif
}
