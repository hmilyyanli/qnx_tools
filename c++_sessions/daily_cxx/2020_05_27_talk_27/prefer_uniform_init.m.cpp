#include <initializer_list>
#include <iostream>
#include <numeric>

//                         =============
//                         struct MyData
//                         =============

struct MyData {
  // DATA
  int m_value;
  double m_number;
};

struct Tag {};

//                         ==============
//                         class MoreData
//                         ==============

class MoreData {
  // DATA
  int m_value{};
  double m_number{};

public:
  // CREATORS
  explicit MoreData(int f_value = 0, double f_number = 0.0) noexcept
      : m_value{f_value}, m_number{f_number} {}

  explicit MoreData(Tag, ::std::initializer_list<int> f_list) noexcept
      : m_value{std::reduce(f_list.begin(), f_list.end())} {}

  // MANIPULATORS
  auto value() & -> int & { return this->m_value; }

  // ACCESSORS
  auto value() const & -> int;
};

auto main() -> int {
  int i3{-2U + 3};
  // MyData md{i3, 3.5};
  MoreData md{i3, 3.5};
  // MoreData md{{}, {1, 2}};
  ::std::cout << md.value() << "\n";
}
