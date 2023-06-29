#include <stdio.h>
#include <sys/mman.h> 	/* for mlock() */
#include <stdlib.h>		/* for malloc() */
#include <string.h>		/* for memset() */

/* for getpid() */
#include <sys/types.h>
#include <unistd.h>

#define MEM_LENGTH 4096

int main()
{
	/* Allocate 1024 bytes in heap */
	char *ptr = NULL;
	ptr = malloc(MEM_LENGTH);
	if (!ptr) {
		perror("malloc fails. ");
		return -1;
	}

	/* obtain physical memory */
	memset(ptr, 0x55, MEM_LENGTH);

	/* lock the allocated memory in RAM */
	mlock(ptr, MEM_LENGTH);

	/* print the pid and vaddr. Thus we can work on him */
	printf("my pid: %d\n\n", getpid());
	printf("virtual address to work: 0x%lx\n", (unsigned long)ptr);

	/* make the program to wait for user input */
	getchar();
	printf("buf val %s\n",ptr);
	return 0;
}
