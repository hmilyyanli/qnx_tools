#include <iostream>
#include <array>
//class without strong type
using namespace std;

void dis_1(const int x)
{
    //error! here x means readonly variable
    //array <int,x> m_arr{1,2,3};
    //cout << m_arr[1]<<endl;
} 

void dis_2()
   {
       //OK, here x means const variable.
       const int x=3;
       array <int,x> m_arr{1,2,3};
       cout << m_arr[1]<<endl;
   }

const int sqr1(int arg)
{
    return arg*arg;
}
constexpr int sqr2(int arg)
{
    return arg*arg;
}
int main()
{
    //dis_1(3);
    dis_2();
    //array<int,sqr1(4)> myarr1;//failed, sqr1 is not constexpr
    array<int,sqr2(4)> myarr2;//OK
}
