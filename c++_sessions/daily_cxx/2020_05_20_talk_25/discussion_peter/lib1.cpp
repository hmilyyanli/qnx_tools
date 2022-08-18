#include <iostream>

auto registerLib1() -> int { return 0; }

void Register(void *p);
void Register(void *p) { std::cout << "Register " << p << std::endl; }
struct A {
  A() { Register(this); }
} a;
