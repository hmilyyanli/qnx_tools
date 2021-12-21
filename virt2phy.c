#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/mman.h>

 #include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>

#define PAGE_SHIFT 12
#define PAGEMAP_LENGTH 8
#define GET_BIT(X,Y) ( (X & (((unsigned long)1)<<Y)) >> Y)
#define GET_PFN(X) (X & 0x7FFFFFFFFFFFFF)

const int __endian_bit = 1;
#define is_bigendian() ( (*(char*)&__endian_bit) == 0 )


// must run with :sudo setcap cap_sys_admin+ep a.out
int main(int argc, char **argv)
{
	unsigned long vaddr, pid, paddr = 0, offset;
	char *endptr;
	FILE *pagemap;
	char filename[1024] = {0};
	int ret = -1;
	int page_size, page_shift = -1;
#if 0
	/* Allocate 1024 bytes in heap */
	char *ptr = NULL;
	ptr = malloc(MEM_LENGTH);
	if (!ptr) {
		perror("malloc fails. ");
		return -1;
	}

	/* obtain physical memory */
	memset(ptr, 1, MEM_LENGTH);

	/* lock the allocated memory in RAM */
	mlock(ptr, MEM_LENGTH);

	/* print the pid and vaddr. Thus we can work on him */
	printf("my pid: %d\n\n", getpid());
	printf("virtual address to work: 0x%lx\n", (unsigned long)ptr);
#endif

	page_size = getpagesize();
	pid = strtol(argv[1], &endptr, 10);
	vaddr = strtol(argv[2], &endptr, 16);
	printf("page size 0x%x, getting page number of virtual address %lu of process %ld\n",page_size,vaddr, pid);

	sprintf(filename, "/proc/%ld/pagemap",pid);

	printf("opening pagemap %s\n", filename);
	pagemap = fopen(filename, "rb");
	if (!pagemap) {
		perror("can't open file. ");
		goto err;
	}

	offset = (vaddr / page_size) * PAGEMAP_LENGTH;
	printf("moving to %ld\n", offset);
	if (fseek(pagemap, (unsigned long)offset, SEEK_SET) != 0) {
		perror("fseek failed. ");
		goto err;
	}
#if 0
	if (fread(&paddr, 1, (PAGEMAP_LENGTH), pagemap) < (PAGEMAP_LENGTH-1)) {
		perror("fread fails. ");
		goto err;
	}
#else
	unsigned char c_buf[PAGEMAP_LENGTH];
	int i,c;
   	for(i=0; i < PAGEMAP_LENGTH; i++){
      		c = getc(pagemap);
      		if(c==EOF){
         		printf("\nReached end of the file\n");
         		return 0;
      		}
      		if(is_bigendian())
           		c_buf[i] = c;
      		else
           		c_buf[PAGEMAP_LENGTH - i - 1] = c;
      		printf("[%d]0x%x ", i, c);
   	}
	for(i=0; i < PAGEMAP_LENGTH; i++){
      		//printf("%d ",c_buf[i]);
      		paddr = (paddr << 8) + c_buf[i];
   	}
	if(!GET_BIT(paddr, 63))
	{
		printf("page not present!\n");
		return 0;
	}
	if(GET_BIT(paddr, 62))
	{
		 printf("page swapped!\n");
                return 0;

	}
#endif	
	paddr = paddr & 0x7fffffffffffff;
	printf("physical frame address is 0x%lx\n", paddr);

	offset = vaddr % page_size;

	/* PAGE_SIZE = 1U << PAGE_SHIFT */
	while (!((1UL << ++page_shift) & page_size));
	printf("page shift:%d,offset %x\n", page_shift,offset);

	paddr = (unsigned long)((unsigned long)paddr << page_shift) + offset;
	printf("physical address is 0x%lx\n", paddr);

	int pid_mem = open("/dev/mem",O_RDWR|O_NDELAY);
	if(pid_mem < 0)
	{
		 perror("can't open file. ");
                goto err;
	}

        void* map_base = mmap(NULL,page_size,PROT_READ|PROT_WRITE,MAP_SHARED,pid_mem,paddr & ~(page_size-1));
	printf("map with base 0x%x\n",map_base);
	if(map_base == MAP_FAILED)
	{
		perror("map");
                goto err;
	}
	char* pbuf=(char*)map_base+offset;
	printf("pbuf %x\n",pbuf);
	//char buf[16];
	//memcpy(buf,map_base+offset,8);
	//for(i=0;i<8;i++)
	//	printf("buf is %x\n",pbuf[i]);
	strcpy(pbuf,"Hello\n");
	ret = 0;
err:
	fclose(pagemap);
	return ret;
}
