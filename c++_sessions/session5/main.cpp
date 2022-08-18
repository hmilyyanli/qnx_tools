#define EXCISE_2
#include "AEmpty.hpp"
#include <iostream>

using namespace std;

class Foo
{
    public:    
    Foo():p(new int(0)){}
    Foo(int v):p(new int(v)){}
    Foo(const Foo& other): p(new int(*other.p)){}
    //move cons
    Foo(const Foo && other): p(new int(*other.p)){}
    //assignment
    Foo& operator=(const Foo& other)
    {
        if(&other != this)
            delete p;
        p = nullptr;
        p = new int(*other.p);
        return *this;
    }
    // move assignment
    Foo& operator=(Foo&& other)
    {
        if(&other != this)
            delete p;
        p = other.p;
        other.p = nullptr;
        return *this;
    }
    int getVal() const &
    {
        return *this->p;
    }
    ~Foo()
    {
        if(p) delete p;
    }
    private:
        int* p = nullptr;
};
#if 0
A operator+(A const& a, A const& b )
{
	return A();
}
#endif
void demoFoo()
{
    Foo m_foo(5);
    Foo ano_foo(m_foo);
    cout << "foo: " << ano_foo.getVal() << endl;
    Foo foo3 = m_foo;
    cout << "foo: " << foo3.getVal() << endl;
}
#if 1
void lifecycle()
{
	cout << "begin lifecycle ..."<< endl;
	{
	cout << "A a1 " << endl;
	A a1;
	cout << "a1.i " << a1.i <<endl;
	a1.i = 32;
	cout << "a1.i " << a1.i <<endl;
	//A a2 = a1;
	//cout << "a2.i " << a2.i <<endl;
	A a3(a1);
	cout << "a3.i " << a3.i <<endl;

	a1.i = 42;
	cout << "a1.i " << a1.i <<endl;
	cout << "a2 = a1" <<endl;
	//a2 = a1;
	//cout << "a2.i " << a2.i <<endl;

	A a4(std::move(a1));
	cout << "a1.i " << a1.i <<endl;
	cout << "a4.i " << a4.i <<endl;

	a4=std::move(a3);
	cout << "a3.i " << a3.i <<endl;
        cout << "a4.i " << a4.i <<endl;
	}
	cout << "end of lifecycle!..."<<endl;
}
#endif
#if 0
void demoAssigment()
{
	int a, b=1,c=2;
	a=b+c;
	//b+c = a;

	A a1,a2;
	A a3= a1+a2;
	(a1+a2) = a3;
}
#endif
int main(int argc, char* argv[])
{
	lifecycle();
	//demoAssigment();
    demoFoo();
	return 0;
}
