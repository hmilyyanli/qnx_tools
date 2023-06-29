#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <malloc.h>
int main(int argc, char *argv[])
{
	unsigned char *buffer1,*buffer2;
	int i;

	if (!mlockall(MCL_CURRENT | MCL_FUTURE))
		mallopt(M_TRIM_THRESHOLD, -1UL);//forbit memory trim
	//mallopt(M_MMAP_MAX, 0);//forbit mmap system call,os will call brk instead

	buffer1 = malloc(256*1024);
	if (!buffer1)
		exit(-1);

	/* 
	 * Touch each page in this piece of memory to get it
	 * mapped into RAM
	 */
	for (i = 0; i < 256*1024; i += 4 * 1024)
		buffer1[i] = 0;
	//free(buffer);
	/* <do your RT-thing> */

	//while(1);
    buffer2 = malloc(512*1024);
    if (!buffer2)
         exit(-1);
    //memset(buffer2,0,1024);
    //strcpy(buffer2, "Hello\n");
    //printf("%s",buffer2);
    for (i = 0; i < 512*1024; i += 4 * 1024)
         buffer2[i] = 1;
    free(buffer1);
    free(buffer2);
	return 0;
}
