#ifndef CLASSC_HPP
#define CLASSC_HPP
#include <iostream>
class C
{
public:
	~C(){std::cout<< "dector C..." << std::endl;}
	C():i(0)
	{
	    std::cout<< "default cons C..." << std::endl;
	}
	C(int a):i(a){std::cout<< "ctor C..." << std::endl;}
#if 1
	//copy .........
	C(C const& a):i(a.i)
	{
		std::cout<< "C::C(C const& a)..." << std::endl;	
	}
	C& operator=(C const& src) & // the last & is l-value qualifer
	{
		i = src.i;
		//std::cout<< "A& operator=(A const& src)..." << std::endl;
		std::cout <<"name: " << __PRETTY_FUNCTION__ << std::endl;
		return *this;
	}
#endif
#if 1
	//move
	C(C const && b):i(std::move(b.i))
	{
		std::cout<< "C::C(C const&& b)..." << std::endl;
	}
	C& operator=(C const&& a)
	{
		i = std::move(a.i);
		std::cout<< "A& operator=(A const&& a)..." << std::endl;	
		return *this;
	}
#endif
	int i;
};
#endif
