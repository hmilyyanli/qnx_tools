#include <vont_registrator.hpp>

#include <algorithm> // for_each
#include <iostream>  // cout

namespace vont {

extern volatile int g_RegisterMofu;
extern volatile int g_RegisterSepa;

} // namespace vont

namespace {

int g_doRegistrationMofu = ::vont::g_RegisterMofu;
int g_doRegistrationSepa = ::vont::g_RegisterSepa;

} // namespace

auto main() -> int {
  auto first = ::vont::Registrator::begin();
  auto last = ::vont::RegistratorIterator{};

  auto size = 0;
  const auto incrementSizeAndPrintName =
      [&size](const ::vont::Registrator &f_reg) {
        ::std::cout << f_reg.getName() << "\n";
        ++size;
      };

  ::std::for_each(first, last, incrementSizeAndPrintName);
  ::std::cout << "size: " << size << "\n";
}
