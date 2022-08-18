#include <algorithm>
#include <array>
#include <iostream>
#include <vfc/linalg/vfc_linalg_all.hpp>

//                         ===========
//                         class Value
//                         ===========

class Value {
  // DATA
  float m_value{0};

public:
  // CREATORS
  explicit Value(float f_value) noexcept : m_value{f_value} {}

  // MANIPULATORS
  auto value() & -> float & { return this->m_value; }

  // ACCESSORS
  auto value() const & -> const float & { return this->m_value; }

  auto createTemp() const & -> ::Value { return ::Value{this->m_value + 10.F}; }
};

auto getValue(float f) -> Value { return Value{f}; }

auto getMatrix() -> ::vfc::linalg::TMatrix22<float> {
  return ::vfc::linalg::TMatrix22<float>{1.F, 0.F, 0.F, 1.F};
}

auto main() -> int {
  auto v = getValue(1.F);
  const auto &dangling = getValue(2.F).createTemp().value();
  ::std::cout << dangling << "\n";
  const auto &dangling2 = getValue(3.F).createTemp().value();
  ::std::cout << dangling2 << "\n";

  const ::vfc::linalg::TVector2<float> a{1.F, 2.F};
  const ::vfc::linalg::TVector2<float> b{-1.F, 3.F};

  const auto& result = ::vfc::linalg::TVector2<float>{::getMatrix() * a + b};
  ::std::cout << result[0] << "\n";

  const ::vfc::linalg::TVector2<float> c{3.F, 0.F};
  ::std::cout << c[0] << "\n";
}
