#include <vont_registrator.hpp>

namespace {

class Mofu final : public ::vont::RegistratorImpl {
public:
  auto getName() const -> const char * final { return "Mofu"; }
};

Mofu g_mofu;

} // namespace

namespace vont {

volatile int g_RegisterMofu = 0;

} // namespace vont
