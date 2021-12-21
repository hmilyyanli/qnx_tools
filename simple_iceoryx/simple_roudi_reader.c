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
#define MAX_SEG_NUM     10
#define ROUDI_DATA "/ROUDI_DATA"
#define DATA_SIZE 4096
static SegInfoS gSegInfo[10];
#define SEG_ID  5
#endif

#ifdef ROUDI_RELOCATED_POINTER
void relocatable_init(Relocatable** ppReloc,void* addr)
{
        *ppReloc = (Relocatable*)addr;
}
int relocatable_store(Relocatable* pReloc)
{
	int* ptr = (int*)(pReloc->m_offset + (void*)&pReloc->m_offset);
	return *ptr;
}
#endif

#ifdef ROUDI_RELATIVE_POINTER
void relative_init(RelativePointer** ppRela, void* addr)
{
        *ppRela = (RelativePointer*)addr;
}

void seg_register_with_id(RelativePointer* pRela, void* seg_addr, unsigned int size)
{
	gSegInfo[pRela->id].startptr = seg_addr;
        gSegInfo[pRela->id].endptr = seg_addr + size -1;
        return ;
}

int relative_restore(RelativePointer* pRela)
{
        //pRela->m_offset = val - (void*)pRela->segInfo[SEG_ID].startptr;
	int* ptr = (int*)(pRela->m_offset + (void*)gSegInfo[pRela->id].startptr);
        return *ptr;

}

void seg_unregister(RelativePointer* pRela)
{
	 int id = pRela->id;
         gSegInfo[pRela->id].startptr = gSegInfo[pRela->id].endptr = NULL;
}
#endif

int main(int argc, char *argv[])
{
	int res;
	int fd;
	pid_t pid;
	void *addr;
	int val;
#ifdef ROUDI_RELATIVE_POINTER
        int fd_data;
        void *pdata;
	RelativePointer *m_rela;
        int seg_id;
#endif
#ifdef ROUDI_RELOCATED_POINTER
	Relocatable *m_reloc;
#endif	
	
	pid = getpid();

	// get shared memory file descriptor (NOT a file)
	fd = shm_open(ROUDI_MGMT, O_RDWR, S_IRUSR | S_IWUSR);
	if (fd == -1)
	{
		perror("open");
		return 10;
	}

	// map shared memory to process address space
	addr = mmap(NULL, MGMT_SIZE, PROT_READ, MAP_SHARED, fd, 0);
	if (addr == MAP_FAILED)
	{
		perror("mmap");
		return 30;
	}
#ifdef ROUDI_RELOCATED_POINTER	
	relocatable_init(&m_reloc, addr);
	val = relocatable_store(m_reloc);
	printf("PID %d: Read from shared memory: 0x%x\n", pid, val);
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
	relative_init(&m_rela,addr);
	seg_register_with_id(m_rela, pdata, DATA_SIZE);
	val = relative_restore(m_rela);
	seg_unregister(m_rela);
	 printf("PID %d: Read from shared memory: 0x%x\n", pid, val);
#endif	
	return 0;
}	
