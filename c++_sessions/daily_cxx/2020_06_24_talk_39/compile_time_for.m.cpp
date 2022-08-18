#include <iostream>

template <class T, class... Ts> struct SumSizesHelper {
  static constexpr int g_size{sizeof(T) + SumSizesHelper<Ts...>::g_size};
};

template <class T> struct SumSizesHelper<T> {
  static constexpr int g_size{sizeof(T)};
};

template <class... Ts> constexpr auto sumSizes() -> int {
  return ::SumSizesHelper<Ts...>::g_size;
  // return (... + sizeof(Ts));
}

auto main() -> int {
  ::std::cout << "Full size: " << sumSizes<int, double, void *, int, char>() << "\n";
}
