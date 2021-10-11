#include <stdio.h> 
#include <time.h> 
#include <stdlib.h> 
#include <string.h> 
#define LOOP 5000 
#define SIZE 500000 
int main(int argc, char* argv[]) 
{ 
	int t; 
	int i; 
	float elapse; 
	static char dummy[SIZE]; 
	t = clock(); 
	for(i=0; i<LOOP; i++ ) { 
		memset( dummy, 0, sizeof( dummy) ); 
	} 
	elapse = ( clock()-t ) / (float)CLOCKS_PER_SEC; 
	printf("Duration %f sec, %.1f MBytes/sec \n", 
		elapse, sizeof(dummy)*LOOP/elapse/1000000); 
	return 0; 
} 	
