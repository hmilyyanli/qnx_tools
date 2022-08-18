#include <vont_registrator.hpp>

namespace {

const ::vont::RegistratorImpl *g_first_p{nullptr};

} // namespace

namespace vont {

// CLASS METHODS
auto Registrator::begin() noexcept -> ::vont::RegistratorIterator {
  return ::vont::RegistratorIterator{::g_first_p};
}

// PROTECTED CREATORS
RegistratorImpl::RegistratorImpl() noexcept : m_next_p{::g_first_p} {
  ::g_first_p = this;
}

} // namespace vont
