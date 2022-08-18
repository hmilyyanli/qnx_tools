#include <cstdlib>
#include <iostream>
#include <sstream>

struct UsageException {};

auto main() -> int try {
  const char *lhsStr = ::std::getenv("LHS");
  const char *rhsStr = ::std::getenv("RHS");

  if (!(lhsStr && rhsStr))
    throw UsageException{};

  ::std::stringstream lhsSs{lhsStr};
  ::std::stringstream rhsSs{rhsStr};
  int lhsValue{};
  int rhsValue{};
  if (!((lhsSs >> lhsValue) && (rhsSs >> rhsValue)))
    throw UsageException{};

  ::std::cout << "LHS + RHS: " << lhsValue + rhsValue << "\n";
} catch (...) {
  ::std::cerr << "Usage: LHS=10 RHS=30 ./env_trick.m.cpp\n";
  return 1;
}
