#ifndef CLASSB_HPP
#define CLASSB_HPP
#include <iostream>
class B 
{
public:
	~B(){std::cout<< "dector B..." << std::endl;}
	B():i(0)
	{
	    std::cout<< "default cons B..." << std::endl;
	}
	B(int a):i(a){std::cout<< "ctor B..." << std::endl;}
	//copy .........
	B(B const& a):i(a.i)
	{
		std::cout<< "B::B(B const& a)..." << std::endl;	
	}
	B& operator=(B const& src) & // the last & is l-value qualifer
	{
		i = src.i;
		//std::cout<< "A& operator=(A const& src)..." << std::endl;
		std::cout <<"name: " << __PRETTY_FUNCTION__ << std::endl;
		return *this;
	}
#if 1
	//move
	B(B const && b):i(std::move(b.i))
	{
		std::cout<< "B::B(B const&& b)..." << std::endl;
	}
	B& operator=(B const&& a)
	{
		i = std::move(a.i);
		std::cout<< "A& operator=(A const&& a)..." << std::endl;	
		return *this;
	}
#endif
	int i;
};
#endif
