#pragma once

#include <iostream> // cout

// IMPLEMENTAION NOTES
//
//   Instead of copying the definition of B twice, as suggested by the
//   exercise, we create a template class with an unused template
//   parameter.

template <class> class B {
  int _i{};

public:
  explicit B(int i) : _i{i} { ::std::cout << __PRETTY_FUNCTION__ << '\n'; }
  B() noexcept { ::std::cout << __PRETTY_FUNCTION__ << '\n'; }
  B(const B &original) : _i{original._i} {
    ::std::cout << __PRETTY_FUNCTION__ << '\n';
  }
  B(B &&original) noexcept : _i{original._i} {
    ::std::cout << __PRETTY_FUNCTION__ << '\n';
  }

  ~B() { ::std::cout << __PRETTY_FUNCTION__ << '\n'; }

  B &operator=(const B &original) {
    this->_i = original._i;
    ::std::cout << __PRETTY_FUNCTION__ << '\n';
    return *this;
  }

  B &operator=(B &&original) noexcept {
    this->_i = original._i;
    ::std::cout << __PRETTY_FUNCTION__ << '\n';
    return *this;
  }

  auto &i() & { return this->_i; }

  auto &i() const & { return this->_i; }
};
