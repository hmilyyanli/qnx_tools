#ifndef AEMPTY_HPP
#define AEMPTY_HPP
#include <iostream>
class A{
public:
	~A(){std::cout<< "dector..." << std::endl;}
	A():i(0)
	{
	    std::cout<< "default..." << std::endl;
        throw;
	}
	A(int a):i(a){std::cout<< "default ctor..." << std::endl;}
#if 0
	//copy .........
	A(A const& a):i(a.i)
	{
		std::cout<< "A::A(A const& a)..." << std::endl;	
	}
	A& operator=(A const& src) & // the last & is l-value qualifer
	{
		i = src.i;
		//std::cout<< "A& operator=(A const& src)..." << std::endl;
		std::cout <<"name: " << __PRETTY_FUNCTION__ << std::endl;
		return *this;
	}
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

class B{
    public:
    B(int i):ri(i){std::cout << "addr:"<<&ri<<std::endl;}
    int get(){std::cout << "addr:"<<&ri<<std::endl;return ri;}
    private:
    int& ri;
};
#endif
