#include <iostream>
#include <type_traits>
#include <vaddons/vaddons_type_traits.hpp>

namespace {

class Printer {
public:
  template <bool> auto Print() -> void { ::std::cout << "Hello Printer!\n"; }

  template <> auto Print<false>() -> void {
    ::std::cout << "No hello Printer!\n";
  }

  auto operator()() -> void { ::std::cout << "---!\n"; }
};

} // namespace

auto main() -> int {
  Printer printer;
  printer.Print<::std::bool_constant<::std::is_invocable_v<::Printer> ||
                                     ::std::is_base_of_v<::Printer, int>
                                     >::value>();
}
