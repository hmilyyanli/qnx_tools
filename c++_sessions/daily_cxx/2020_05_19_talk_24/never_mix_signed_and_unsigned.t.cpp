#include <iostream>

#include <vector>

namespace {

template <class> class TGetType;

}

auto main() -> int {
  ::std::vector<int> vi{2, 3};

  const auto Diff = -3 + 2F;
  if (Diff < 0)
    ::std::cout << "hello singed unsigned world!\n";
}
