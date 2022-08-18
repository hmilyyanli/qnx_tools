#include <aempty.h> // A
#include <utility>  // move

auto createA1() -> A { return A{}; }

auto createA2() -> A {
  A a;
  return a;
}

auto createA3() -> A { return A{42}; }

auto createA4() -> A { return ::std::move(A{}); }

// Exercise 1
void demoCopyElision() {
  A a = ::createA1();
  static_cast<void>(a);
  // evaluation:
  //   createA1, createA2, createA3: on gcc 10.2 and clang-11 copy ellision.
  //   createA4: on gcc10.2 no copy ellision and on clang-11 copy ellision but
  //   gives warning.
}

auto f1(A a) -> A { // copy elide
  ::std::cout << __PRETTY_FUNCTION__ << " return a\n";
  return a; // copy elide, implicit move
}
auto f2(A &a) -> A {
  ::std::cout << __PRETTY_FUNCTION__ << " return ra\n";
  return a; // no copy elide, copy c'tor
}

auto f3(A &a) -> A {
  ::std::cout << __PRETTY_FUNCTION__ << " return move(a)\n";
  return ::std::move(a); // no copy elide, move c'tor
}

auto f4(A const &rca) -> A {
  ::std::cout << __PRETTY_FUNCTION__ << " return rca\n";
  return rca; // no copy elide, copy c'tor
}

auto f5(A &&ra) -> A {
  ::std::cout << __PRETTY_FUNCTION__ << " return ra\n";
  return ra; // no copy elide , copy c'tor
}

auto f6(A &&ra) -> A {
  ::std::cout << __PRETTY_FUNCTION__ << " return move(ra)\n";
  return ::std::move(ra); // no copy elide, move c'tor
}

// Exercise 2
void parameterAndReturnExpressions() {
  ::std::cout << __PRETTY_FUNCTION__ << '\n';
  A a1 = ::f1(A{}); // elide f1 temporaries
  // A a11 = f1(a1);
  A a2 = ::f2(a1); // no elide
  A a3 = ::f3(a1); // no elide 
  A a4 = ::f4(a1); // no elide
  // A a41 = f4(A{}); // no elide, copy c'tor
  A a5 = ::f5(A{}); // no elide, copy c'tor
  A a6 = ::f6(A{}); // no elide, move c'tor
  // A a61 = ::f6(a1); // does not compile
  A a62 = ::f6(::std::move(a1)); // no elide
}

auto main() -> int { ::parameterAndReturnExpressions(); }
