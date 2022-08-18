#pragma once

#include <iostream> // cout

class A {
  int _i{};

public:
  explicit A(int i) : _i{i} { ::std::cout << __PRETTY_FUNCTION__ << '\n'; }
  A() noexcept { ::std::cout << __PRETTY_FUNCTION__ << '\n'; }
  A(const A &original) : _i{original._i} {
    ::std::cout << __PRETTY_FUNCTION__ << '\n';
  }
  A(A &&original) : _i{original._i} {
    ::std::cout << __PRETTY_FUNCTION__ << '\n';
  }

  auto &i() const & { return this->_i; }
};
