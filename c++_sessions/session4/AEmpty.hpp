#ifndef AEMPTY_HPP
#define AEMPTY_HPP
#include <iostream>
class A{
public:
	~A(){std::cout<< "A::~A()..." << std::endl;}
	A():i(0)
	{
	    std::cout<< "A::A()" << std::endl;
	}
	A(int a):i(a){std::cout<< "A::A(i)..." << std::endl;}
	//copy .........
	A(A const& a):i(a.i)
	{
		std::cout<< "A::A(A const& a)..." << std::endl;	
	}
	A& operator=(A const& src) & // the last & is l-value qualifer
	{
		i = src.i;
		std::cout<< "A& operator=(A const& src)..." << std::endl;
		//std::cout <<"name: " << __PRETTY_FUNCTION__ << std::endl;
		return *this;
	}
#if 1
	//move
	A(A const && a):i(std::move(a.i))
	{
		std::cout<< "A::A(A const&& a)..." << std::endl;
	}
	A& operator=(A const&& a)
	{
		i = std::move(a.i);
		std::cout<< "A& operator=(A const&& a)..." << std::endl;	
		return *this;
	}
#endif
	int i;
};
#endif
