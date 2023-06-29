#include <algorithm>  // transform
#include <functional> // plus
#include <iostream>

auto main() -> int {
  int first[] = {1, 2, 3, 4, 5};
  int second[] = {10, 20, 30, 40, 50};
  int results[5];
  ::std::transform(first, first + 5, second, results, ::std::plus<int>());
  for (auto x : results)
      ::std::cout << x << ::std::endl; 
}
