#include <iostream>
#include <csetjmp>
using namespace std;
jmp_buf env_main,env_fib;
constexpr int FIB_N = 40;
#define USING_ENV_MAIN

int fib_iteration(int n)
{
#if 0    
    int64_t t1 = 0, t2 = 1, nextTerm = 0;
    if(n == 0) 
    {
                //cout << t1 << ", ";
                //continue;
                return t1;
    }
    if(n == 1) 
    {
                //cout << t2 << ", ";
                //continue;
                return t2;
    }

     for (int i = 2; i <= n; ++i) {
           nextTerm = t1 + t2;
           t1 = t2;
           t2 = nextTerm;           
           //cout << nextTerm << ", ";
       }
     return nextTerm;
#else
    static int t1 = 0;
    static int t2 = 1;
    int ret;
    if(n==0)
        return t1;
    if(n==1)
        return t2;
    ret = t1 + t2;
    t1 = t2;
    t2 = ret;
    return ret;
#endif
}

int64_t fib_recursion(int n)
{
    if (n <= 1)
        return n;
    return fib_recursion(n - 1) + fib_recursion(n - 2);
}

void fib_coroutine()
{
     static int t1 = 0;
     static int t2 = 1;
     {
        int ret = t1 + t2;
        t1 = t2;
        t2 = ret;
        longjmp(env_main,ret);
     }
}

void fib_coroutine2()
{
        static int t1 = 0;
        static int t2 = 1;
        int ret;
        setjmp(env_fib);
        ret = t1 + t2;
        t1 = t2;
        t2 = ret;
        longjmp(env_main,ret);
}

void main_iter()
{
    for (int i = 0; i <= FIB_N; ++i) {
         // Prints the first two terms.
         cout << fib_iteration(i) << ", ";
     }
     cout << endl;

}
void main_recursion()
{
    for (int i = 0; i <= FIB_N; ++i) {
            // Prints the first two terms.
            cout << fib_recursion(i) << ", ";
        }
        cout << endl;
}

void main_coroutine()
{
    int count=0;
    if(!count)
        cout << count++ << ", ";
    if(count==1)
        cout << count++ << ", ";

    int val = setjmp(env_main);
    if(val)//skip 1st return val of setjmp
        cout << val << ", ";

    if(count++ > FIB_N)
    {
        cout << endl;
        return;
    }
#ifdef USING_ENV_MAIN    
    fib_coroutine();
#else
    if(!val)
        fib_coroutine2();
    else
        longjmp(env_fib,1);
#endif
}

int main() {

    main_iter();
    //main_recursion();
    //main_coroutine();
    return 0;
}
