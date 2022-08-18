#include <vont_registrator.hpp>

namespace {

class Sepa final : public ::vont::Registrator {
public:
  // ACCESSORS
  auto GetName() const noexcept -> const char * final { return "Sepa"; }
};

Sepa g_sepa;

} // namespace

namespace vont {

volatile int g_RegisterSepa = 0;

} // namespace vont
