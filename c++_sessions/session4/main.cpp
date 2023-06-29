#include "AEmpty.hpp"
#include <iostream>

using namespace std;

A operator+(A const& a, A const& b )
{
	return A();
}

A createA_1(){return A();}
A createA_2(){A a;return a;}
 A createA_3(){return A(42);}
 A createA_4(){return std::move(A());}
A f1(A a)
{
	cout << "A f1(A a) return a" << endl;
	return a;
}

A f2(A& a)
{
         cout << "A f2(A& a) return a" << endl;
         return a;
}

A f3(A& a)
{
        cout << "A f3(A& a) return std::move" << endl;
        return std::move(a);
}

A f4(A const& a)
{
        cout << "A f4(A const& a) return a" << endl;
        return a;
	//return std::move(a);
}
A f5(A&& a)
{
        cout << "A f5(A&& a) return a" << endl;
        return a;
}
A f6(A&& a)
{
        cout << "A f6(A a) return a" << endl;
        return std::move(a);
}

void parameterAndReturn()
{
	cout << "==== start parameterAndReturn...." << endl;
	cout << "call f1(A())..." << endl;
	A a1 = f1(A());
	cout << "call f2(a1)..." << endl;
	A a2 = f2(a1);
	cout << "call f3(a1)..." << endl;
	A a3 = f3(a1);
	cout << "call f4(a1)..." << endl;
	A a4 = f4(a1);
	cout << "call f5(A())..." << endl;
	A a5 = f5(A());
	cout << "call f6(A())..." << endl;
	A a6 = f6(A());
	cout << "==== end parameterAndReturn...." << endl;
}
void lifecycle()
{
	cout << "begin lifecycle ..."<< endl;
	{
	cout << "A a1 " << endl;
	A a1;
	cout << "a1.i " << a1.i <<endl;
	a1.i = 32;
	cout << "a1.i " << a1.i <<endl;
	A a2 = a1;
	cout << "a2.i " << a2.i <<endl;
	A a3(a1);
	cout << "a3.i " << a3.i <<endl;

	a1.i = 42;
	cout << "a1.i " << a1.i <<endl;
	cout << "a2 = a1" <<endl;
	a2 = a1;
	cout << "a2.i " << a2.i <<endl;

	A a4(std::move(a1));
	cout << "a1.i " << a1.i <<endl;
	cout << "a4.i " << a4.i <<endl;

	a4=std::move(a3);
	cout << "a3.i " << a3.i <<endl;
        cout << "a4.i " << a4.i <<endl;
	}
	cout << "end of lifecycle!..."<<endl;
}
void demoAssigment()
{
	int a, b=1,c=2;
	a=b+c;
	//b+c = a; //this statement is incorrect, because variable a is L-Value!

	A a1,a2;
	A a3= a1+a2;
	//(a1+a2) = a3;
}

void demoCopyElision()
{
	A a1 = createA_1();
	cout << "a1.i " << a1.i <<endl;
	A a2 = createA_2();
	cout << "a2.i " << a2.i <<endl;
	A a3 = createA_3();
	cout << "a3.i " << a3.i <<endl;
	A a4 = createA_4();
	cout << "a4.i " << a4.i <<endl;
}

// A class that contains a memory resource.
class MemoryBlock
{
public:
    MemoryBlock():pa(new int){}
    MemoryBlock(MemoryBlock&& block)
    {
        cout << "MemoryBlock(const MemoryBlock&& block)" << endl;
        if(this != &block)
        {
            pa=block.pa;
            block.pa=NULL;
        }
    }
    //move operator=
    MemoryBlock& operator=(const MemoryBlock&& block)
    {
        cout << "MemoryBlock& operator=(const MemoryBlock&& block)" << endl;
        if(this != &block)
        {
            *pa=*block.pa;
             //pa=block.pa;
             //block.pa=NULL;
        }
        return *this;
    }
    ~MemoryBlock(){
        cout << "In ~MemoryBlock()" << endl;
        if(pa != NULL)
        {
            free(pa);
            pa=NULL;
        }
    }
public:
   // TODO: Add resources for the class here.
   int* pa;
};
#if 0
void f(const MemoryBlock&)
{
   cout << "In f(const MemoryBlock&). This version can't modify the parameter." << endl;
}
#endif
//template <typename T>
void f(MemoryBlock&& block)
{
   cout << "In f(MemoryBlock&&). This version can modify the parameter." << endl;
   std::cout << "f val "<<*block.pa<<std::endl;

}

int main(int argc, char* argv[])
{
	//lifecycle();
	//demoAssigment();
	//demoCopyElision();
	//parameterAndReturn();
    MemoryBlock block;
    *block.pa = 10;
    //MemoryBlock&& rb=std::move(block);
    f(std::move(block));
    //f(MemoryBlock());
    std::cout << "val "<<*block.pa<<std::endl;
    return 0;
}
