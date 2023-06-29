#include <thread> 
#include <iostream>
#include <memory>
static volatile int x __attribute__((aligned(64)));
static volatile int y __attribute__((aligned(64)));
void thread1_func(void)
{
    for (int i=0 ; i< 1000000000; ++i)
    {
        x++;
    }
}

 void thread2_func(void)
   {
       int c;
       for (int i=0 ; i< 1000000000; ++i)
       {
           c = x;
        }
   }

int binarySearch(int* array, int number_of_elements, int key)
{
    int begin = 0;
    int end = number_of_elements - 1,mid;
    while (begin <= end)
    {
        mid = begin + (end - begin) / 2;
#ifdef DO_PREFETCH
        __builtin_prefetch(&array[(mid + 1 + end)/2], 0, 1);
        __builtin_prefetch(&array[(begin -1 + mid)/2], 0, 1);
#endif
        if (array[mid] > key)
        {
            end = mid - 1;
        }
        else if (array[mid] < key)
        {
            begin = mid + 1;
        }
        else
        {
            return mid;
        }
    }
    return -1;
}

void ipc_test(void) {
    while(1) {
         __asm__ ("nop\n\t"
                 "nop\n\t"
                 "nop");
    }
}
int main(int argc, char* argv[]) 
{
#if 1    
    int SIZE=1024*1024*512;
    int *array = (int*)malloc(sizeof(int)*SIZE);
    for(int i =0; i < SIZE; i++)
    {
        array[i] = i;
    }
    int NUM_LOOKUPS = 1024 * 1024 * 8;
    srand(time(NULL));
    int *lookups = (int*)malloc(NUM_LOOKUPS * sizeof(int));
    for(int i = 0; i < NUM_LOOKUPS; i++){
        lookups[i] = rand() % SIZE;
    }
    for(int i = 0; i < NUM_LOOKUPS; i++){
           int result = binarySearch(array,SIZE, lookups[i]);
       }
    free(array);
    free(lookups);
#endif    
#if 0
    std::thread thrd1(thread1_func);
    std::thread thrd2(thread2_func);
    thrd1.join();
    thrd2.join();
#endif   
    return 0;
}

