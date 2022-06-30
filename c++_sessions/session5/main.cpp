#define EXCISE_2
#include "AEmpty.hpp"
#include <iostream>

using namespace std;

A operator+(A const& a, A const& b )
{
	return A();
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
	//b+c = a;

	A a1,a2;
	A a3= a1+a2;
	(a1+a2) = a3;
}

int main(int argc, char* argv[])
{
	lifecycle();
	//demoAssigment();
	return 0;
}
