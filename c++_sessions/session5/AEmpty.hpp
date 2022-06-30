#ifndef AEMPTY_HPP
#define AEMPTY_HPP
#include "classB.hpp"
#include "classC.hpp"

#ifdef EXCISE_1
class A{
public:
	int i;
private:
	C c;
	B b;
};
#endif
#ifdef EXCISE_2
class A: public C
{
public:
        int i;
        B b;
};	
#endif
#ifdef EXCISE_3
class A: public C, public B
{
public:
        int i;
};
#endif

#endif
