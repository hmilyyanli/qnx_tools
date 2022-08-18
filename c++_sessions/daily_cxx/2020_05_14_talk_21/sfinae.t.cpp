#include <iostream>
#include <vaddons/vaddons_type_traits.hpp>

namespace {

// SFINAE
// substituation failure is not an error.

template <bool, class> struct enable_if{};
template <class T> struct enable_if<true, T> { using type = T; };

template <bool ConditionValue, class T>
using enable_if_t = typename enable_if<ConditionValue, T>::type;

struct Number {
  double m_value;
};

auto operator<<(::std::ostream &f_os, Number f_number) -> ::std::ostream & {
  f_os << f_number.m_value;
  return f_os;
}

template <class T>
auto Calculate(T f_function, Number f_number)
    -> enable_if_t<::vad::is_invocable_r<::Number, T, ::Number>::value,
                          ::Number> {
  return f_function(f_number);
}

template <class T>
auto Calculate(T f_function, Number f_number)
    -> enable_if_t<::vad::is_invocable_r<::Number, T>::value, ::Number> {
  Number rv = f_function();
  rv.m_value += f_number.m_value;
  return rv;
}

} // namespace

auto main() -> int {
  ::std::cout << Calculate(
                     // [](Number f_number) {
                     //   return Number{f_number.m_value * f_number.m_value};
                     // },
                     []() noexcept { return Number{2.3}; }, Number{3.5})
              << "\n";
}
