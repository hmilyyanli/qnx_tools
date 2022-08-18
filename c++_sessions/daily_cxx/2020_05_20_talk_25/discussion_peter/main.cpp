#include <iostream>

// extern volatile int g_registerLib1;
auto registerLib1() -> int;
int g_doRegisterLib1 = ::registerLib1();

// void Register( void* p ){ std::cout << "Register " << p << std::endl;}
int main() {return 0;}
