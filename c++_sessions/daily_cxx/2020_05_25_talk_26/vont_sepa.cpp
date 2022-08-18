#include <vont_registrator.hpp>

namespace {

class Sepa final : public ::vont::RegistratorImpl {
public:
  // ACCESSORS
  auto getName() const noexcept -> const char * final { return "Sepa"; }
};

Sepa g_sepa;

} // namespace

namespace vont {

volatile int g_RegisterSepa = 0;

} // namespace vont
