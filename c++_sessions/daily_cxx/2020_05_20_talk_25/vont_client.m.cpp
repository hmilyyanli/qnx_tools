#include <vont_registrator.hpp>

#include <iostream> // cout

namespace vont {

extern volatile int g_RegisterMofu;
extern volatile int g_RegisterSepa;

} // namespace vont

namespace {

int g_doRegistrationMofu = ::vont::g_RegisterMofu;
int g_doRegistrationSepa = ::vont::g_RegisterSepa;

} // namespace

auto main() -> int {
  auto Registry = ::vont::Registrator::GetRegistry();
  ::std::cout << "size: " << Registry.size() << "\n";

  for (const auto &Entry : Registry)
    ::std::cout << Entry->GetName() << "\n";
}
