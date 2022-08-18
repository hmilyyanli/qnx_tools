#include <pmi_core.h>

namespace pmi {

inline auto Foo::DoDetails(int f_number) const -> int {
  return this->m_value + f_number;
}

auto Foo::DoSth(::pmi::Integer f_number) const -> ::pmi::Integer {
  return {this->DoDetails(f_number.value)};
}

} // namespace pmi
