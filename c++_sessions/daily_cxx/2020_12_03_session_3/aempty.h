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
//   A(A &&original) noexcept : _i{original._i} {
//     ::std::cout << __PRETTY_FUNCTION__ << '\n';
//   }
  ~A() { ::std::cout << __PRETTY_FUNCTION__ << '\n'; }

  auto operator=(const A &original) -> A & {
    if (&original != this)
      this->_i = original._i;
    ::std::cout << __PRETTY_FUNCTION__ << '\n';
    return *this;
  }
//   auto operator=(A &&original) noexcept -> A & {
//     if (&original != this)
//       this->_i = original._i;
//     ::std::cout << __PRETTY_FUNCTION__ << '\n';
//     return *this;
//   }
  auto i() & -> auto & { return this->_i; }

  [[nodiscard]] auto i() const & -> auto & { return this->_i; }
};
