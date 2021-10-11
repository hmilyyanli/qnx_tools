#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/mman.h>

void show_usage()
{
	fprintf(stderr,"devmem ADDRESS [WIDTH [VALUE]]\n");
	return;
}

void* func1(void)
{
	//char *ptr1 = malloc(10);
	/* do some work */
	return malloc(20);
}

void func2(void)
{
	char *ptr2 = malloc(10);
	int i;
	/* do some work */
	if (ptr2) {
		for(i=0; i< 1; i++){
		printf("ptr2[1] != 0\n");
		}
	}
	free(ptr2);
	/* do some more work */
	return;
}

void func3(void *ptr3)
{
	/* do some work */
	//free(ptr3);
	/* do some more work */
	free(ptr3);
	return;
}
int main (int argc, char *argv[])
{
#if 0	
	int opt = 0, verbose = 0, pin = -1, direction = -1, gpio_module = -1;
	int cmd = -1;
	extern char *optarg;

	// Handle commandline arguments
	// -m gpio_module  The GPIO module. Can be a value from 1 to 6
	// -p pin          The GPIO pin you want to set
	// -d direction    The direction of the GPIO pin. Can be: 0 (=write)|1(=read)
	// -c command      Action to perform. Can be: set|reset|read
	while ((opt = getopt(argc, argv, "m:p:d:c:v")) != -1) {
		switch (opt) {
		case 'm':
			gpio_module = strtol(optarg, NULL, 10);
			if (errno != 0) gpio_module = -1;
			break;
		case 'p':
			pin = strtol(optarg, NULL, 10);
			if (errno != 0) pin = -1;
			break;
		case 'd':
			direction = strtol(optarg, NULL, 10);
			if (errno != 0 || direction > 1) direction = -1;

			if      (strcmp(optarg, "write") == 0) direction = 0;
			else if (strcmp(optarg, "read")  == 0) direction = 1;
			else direction = -1;
		case 'c':
			if      (strcmp(optarg, "set")   == 0) cmd = 0;
			else if (strcmp(optarg, "reset") == 0) cmd = 1;
			else if (strcmp(optarg, "read")  == 0) cmd = 2;
			else cmd = -1;
			break;
		case 'v':
			verbose++;
			break;
		default:
			break;
		}
	}
#endif
#if 1
	off_t target;
	unsigned page_size,mapped_size, offset_in_page;
	void *map_base, *virt_addr;
	uint32_t writeval;
	if (!argv[1])
	{
		show_usage();
		return 0;	
	}
	target = strtoull(argv[1], NULL, 0); /* allows hex, oct etc */
	page_size = mapped_size = 0x1000; //map 4K
	offset_in_page = (unsigned)target & (page_size - 1);
	map_base = (uint32_t*)mmap_device_memory(NULL, mapped_size, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, target & ~(off_t)(page_size - 1));
	if ( map_base == MAP_FAILED) {
		printf("map failed\n");
        	return -1;
	}
	virt_addr = (char*)map_base + offset_in_page;
	if (!argv[2])
	{
		//read	
		printf("0x%x=0x%x",target,*(volatile uint32_t*)virt_addr);
	}
	else
	{
		writeval = strtoull(argv[2], NULL, 0);
		*(volatile uint32_t*)virt_addr = writeval;
		 printf("Read back: 0x%x=0x%x",target,*(volatile uint32_t*)virt_addr);
	}
	munmap_device_memory(map_base,mapped_size);
#endif
	return 0;
}	
