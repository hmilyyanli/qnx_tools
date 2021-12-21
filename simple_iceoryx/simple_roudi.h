#include <stdio.h>
#include <stddef.h>
typedef struct
{
    int m_offset;//must atomic when used in multi-process.	
}Relocatable;

typedef struct 
{
	void* startptr;
	void* endptr;
}SegInfoS;

typedef struct
{
    unsigned int id;  
    int m_offset;  
}RelativePointer;
