#include <dxx_siof_globals.hpp>

#include <iostream>

namespace ds = ::dxx::siof;

auto ::ds::f() -> int {
  ::std::cout << "Using 'y' (which is " << y << " )\n";
  return 3 * y + 7;
}

auto ::ds::g() -> int {
  ::std::cout << "Initializing 'y'\n";
  return 5;
}

auto ::ds::h() -> ::dxx::raii::Object { return ::dxx::raii::Object{&obj2, 1}; }
auto ::ds::i() -> ::dxx::raii::Object {
  return ::dxx::raii::Object{nullptr, 2};
}

auto ::ds::j(int f_v) -> ::dxx::siu::Metre {
  return ::dxx::siu::Metre{static_cast<double>(f_v) / 3.6}; // NOLINT
}
