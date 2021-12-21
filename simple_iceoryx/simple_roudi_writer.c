#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "simple_roudi.h"

#define ROUDI_RELOCATED_POINTER

#define ROUDI_MGMT "/ROUDI_MGMT"
#define MGMT_SIZE 4096

#ifdef ROUDI_RELATIVE_POINTER
#define MAX_SEG_NUM	10
#define ROUDI_DATA "/ROUDI_DATA"
#define DATA_SIZE 4096
static SegInfoS gSegInfo[10];
#define SEG_ID	5
#endif

#ifdef ROUDI_RELOCATED_POINTER
void relocatable_init(Relocatable** ppReloc,void* addr)
{
	*ppReloc = (Relocatable*)addr;
}
void relocatable_load(Relocatable* pReloc, void* val)
{
	pReloc->m_offset = val - (void*)&pReloc->m_offset;
}
#endif

#ifdef ROUDI_RELATIVE_POINTER
void relative_init(RelativePointer** ppRela, void* addr)
{
	*ppRela = (RelativePointer*)addr;
}

int seg_register(RelativePointer* pRela, void* seg_addr, unsigned int size)
{
	pRela->id = SEG_ID;
	gSegInfo[pRela->id].startptr = seg_addr;
	gSegInfo[pRela->id].endptr = seg_addr + size -1;
	return SEG_ID;
}
void relative_load(RelativePointer* pRela, void* val)
{
        pRela->m_offset = val - (void*)gSegInfo[pRela->id].startptr;	
}
void seg_unregister(RelativePointer* pRela, unsigned int id)
{
	 gSegInfo[pRela->id].startptr = gSegInfo[pRela->id].endptr = NULL;
}
#endif
int main(int argc, char *argv[])
{
	int res;
	int fd;
#ifdef ROUDI_RELATIVE_POINTER
	int fd_data;
	void *pdata;
#endif
	pid_t pid;
	void *addr;
	int *pint;
	/* fixed struct for all participates */
#ifdef ROUDI_RELOCATED_POINTER	
        Relocatable *m_reloc;
#endif
#ifdef ROUDI_RELATIVE_POINTER
	RelativePointer *m_rela;
	int seg_id;
#endif
	pid = getpid();

	// get shared memory file descriptor (NOT a file)
	fd = shm_open(ROUDI_MGMT, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
	if (fd == -1)
	{
		perror("open mgmt");
		return 10;
	}
	
	// extend shared memory object as by default it's initialized with size 0
	res = ftruncate(fd, MGMT_SIZE);
	if (res == -1)
	{
		perror("ftruncate");
		return 20;
	}
	// map shared memory to process address space
	addr = mmap(NULL, MGMT_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	if (addr == MAP_FAILED)
	{
		perror("mmap");
		return 30;
	}
#ifdef ROUDI_RELOCATED_POINTER	
	pint = addr+128;
        *pint = 0x12345678;
	relocatable_init(&m_reloc, addr);
        relocatable_load(m_reloc,pint);
#endif

#ifdef ROUDI_RELATIVE_POINTER
	fd_data = shm_open(ROUDI_DATA, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
        if (fd == -1)
        {
                perror("open data");
                return 10;
        }
	res = ftruncate(fd_data, DATA_SIZE);
        if (res == -1)
        {
                perror("ftruncate data");
                return 20;
        }
	pdata = mmap(NULL, DATA_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd_data, 0);
        if (addr == MAP_FAILED)
        {
                perror("mmap data");
                return 30;
        }
	pint = pdata + 128;
	*pint = 0x78563412;
	relative_init(&m_rela,addr);
	seg_id = seg_register(m_rela,pdata,DATA_SIZE);
	relative_load(m_rela,pint);
	//do more operation here.
	seg_unregister(m_rela,seg_id);
#endif	
	printf("PID %d: Write to shared memory: 0x%x,press any key after reader started\n", pid, *pint);
	getchar();

#ifdef ROUDI_RELATIVE_POINTER
	res = munmap(pdata, DATA_SIZE);
        if (res == -1)
        {
                perror("munmap");
                return 40;
        }
	fd_data = shm_unlink(ROUDI_DATA);
        if (fd_data == -1)
        {
                perror("unlink");
                return 100;
        }

#endif	
	res = munmap(addr, MGMT_SIZE);
	if (res == -1)
	{
		perror("munmap");
		return 40;
	}

	fd = shm_unlink(ROUDI_MGMT);
	if (fd == -1)
	{
		perror("unlink");
		return 100;
	}
	return 0;
}	
