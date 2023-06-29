#include<sys/wait.h>/*引入wait函数的头文件*/
#include<sys/reg.h>/* 对寄存器的常量值进行定义，如Eax，EBX....... */
#include<sys/user.h>/*gdb调试专用文件，里面有定义好的各种数据类型*/
#include<sys/ptrace.h>/*引入prtace头文件*/
#include<unistd.h>/*引入fork函数的头文件*/
#include<sys/syscall.h> /* SYS_write */
#include<stdio.h>
int main() {
    pid_t child;/*定义子进程变量*/
    long orig_rax;//定义rax寄存器的值的变量
    int status;/*定义进程状态变量*/
    int iscalling = 0;/*判断是否正在被调用*/
    struct user_regs_struct regs;/*定义寄存器结构体数据类型*/
    child = fork();/*利用fork函数创建子进程*/
    if(child == 0) 
    {
        ptrace(PTRACE_TRACEME, 0, 0);//发送信号给父进程表示已做好准备被跟踪（调试）
        execl("/bin/ls", "ls", "-l", "-h", NULL);/*执行命令ls -l -h,注意，这里函数参数必须要要以NULL结尾来终止参数列表*/
    }
    else
    {
        while(1)
        {
            wait(&status);//等待子进程发来信号或者子进程退出
            if(WIFEXITED(status))//WIFEXITED函数(宏)用来检查子进程是被ptrace暂停的还是准备退出
            {
                break;
            }
            orig_rax = ptrace(PTRACE_PEEKUSER, child, 8 * ORIG_RAX, 0);//获取rax值从而判断将要执行的系统调用号
            if(orig_rax == SYS_write)//如果系统调用是write
            {    
                ptrace(PTRACE_GETREGS, child, 0, &regs);
                if(!iscalling)
                {
                    iscalling = 1;
                    printf("SYS_write call with %lld, %lld, %lld\n",regs.rdi, regs.rsi, regs.rdx);//打印出系统调用write的各个参数内容
                }
                else
                {
                    printf("SYS_write call return %lld\n", regs.rax);//打印出系统调用write函数结果的返回值
                    iscalling = 0;
                }
            }

            ptrace(PTRACE_SYSCALL, child, 0, 0);//PTRACE_SYSCALL,其作用是使内核在子进程进入和退出系统调用时都将其暂停
            //得到处于本次调用之后下次调用之前的状态
        }
    }
    return 0;
}
/* https://www.anquanke.com/post/id/231078 */
