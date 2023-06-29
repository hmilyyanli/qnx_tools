#include <ucontext.h>
#include <stdio.h>
#include <stdlib.h>

static ucontext_t uctx_main, uctx_func1, uctx_func2;

#define handle_error(msg) do { perror(msg); exit(EXIT_FAILURE); } while (0)

static void
func1(void)
{
   printf("func1: started\n");
   printf("func1: swapcontext(&uctx_func1, &uctx_func2)\n");
   if (swapcontext(&uctx_func1, &uctx_func2) == -1) 
	   handle_error("swapcontext");
   printf("func1: returning\n");	//7
}

static void
func2(void)
{
   printf("func2: started\n");	//2
   printf("func2: swapcontext(&uctx_func2, &uctx_func1)\n");	//3
   if (swapcontext(&uctx_func2, &uctx_func1) == -1)	//切换到func1运行
	   handle_error("swapcontext");	
   printf("func2: returning\n");	//6
}

int
main(int argc, char *argv[])
{

   //注意在实际中要注意stack大小,否则可能会出现溢出.  
   char func1_stack[16384];
   char func2_stack[16384];

   //获取当前进程/线程上下文信息,存储到uctx_func1中
   if (getcontext(&uctx_func1) == -1)
	   handle_error("getcontext");
	   
   //uc_stack: 分配保存协程数据的堆栈空间
   uctx_func1.uc_stack.ss_sp = func1_stack;	//栈头指针
   uctx_func1.uc_stack.ss_size = sizeof(func1_stack);	//栈大小
   uctx_func1.uc_link = &uctx_main;	//协程兴许的context
   makecontext(&uctx_func1, func1, 0); //依改动得到一个新的centext

   if (getcontext(&uctx_func2) == -1)
	   handle_error("getcontext");
   uctx_func2.uc_stack.ss_sp = func2_stack;
   uctx_func2.uc_stack.ss_size = sizeof(func2_stack);
   /* Successor context is f1(), unless argc > 1 */
   //假设argc有传參数进来,则uc_link置为空.兴许代码将不再运行
   uctx_func2.uc_link = (argc > 1) ? NULL : &uctx_func1;
   makecontext(&uctx_func2, func2, 0);

   printf("main: swapcontext(&uctx_main, &uctx_func2)"); //1
   //swapcontext(ucontext_t *oucp, ucontext_t *ucp)
   // 进行上下文切换。将当前上下文保存到oucp中，切换到ucp
   //将当前上下文保存到uctx_main, 并切换到uctx_func2
   if (swapcontext(&uctx_main, &uctx_func2) == -1) 
	   handle_error("swapcontext");

   printf("main: exiting\n"); //8 ： 如argc不为空则这不会运行.
   exit(EXIT_SUCCESS);
}
