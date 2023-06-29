#include <iostream>
#include <thread>
#include <unistd.h>
void thread1(void)
{
    while(1)
    {
    std::cout << "in thread1\n" <<  std::endl;
    sleep(1);
    
    }
}
int main()
{
    std::thread m_thread1(thread1);
    m_thread1.join();
    while(1)
    {
        std::cout << "in main\n" <<  std::endl;
        sleep(2);
    }
}
