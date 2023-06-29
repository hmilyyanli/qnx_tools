#ifndef AEMPTY_HPP
#define AEMPTY_HPP
#include <iostream>
class A{
public:
	//A()=default;
	A(int a = 1):i(a){std::cout << "cons A"<<std::endl;}
	A& operator=(const A& a)
    {
        std::cout << "operator= A"<<std::endl;
        this->i=a.i;
        return *this;
    }
    int i;
};
class B{
public:
    B(A& a):m_a(a)
    {
        //m_a = a;
    }
    A& m_a;
    
};
#endif
