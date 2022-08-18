#include <vont_registrator.hpp>

#include <array>

namespace {

constexpr int MaxSize = 10;

class ArrayWithSize {
  // DATA
  ::std::array<const ::vont::Registrator *, ::MaxSize> m_array{};
  int m_size{0};

public:
  // MANIPULATORS
  auto pushBack(const ::vont::Registrator &f_registrator) noexcept
      -> ArrayWithSize & {
    if (this->m_size != this->m_array.size()) {
      ::gsl::at(this->m_array, this->m_size) = &f_registrator;
      ++this->m_size;
    }
    return *this;
  }

  // ACCESSORS
  auto data() const noexcept { return &::gsl::at(this->m_array, 0); }
  auto size() const noexcept { return this->m_size; }
};

auto g_arrayWithSize = ArrayWithSize{};

} // namespace

namespace vont {

// PROTECTED CREATORS
Registrator::Registrator() noexcept { ::g_arrayWithSize.pushBack(*this); }

// CLASS METHODS
auto Registrator::GetRegistry() noexcept
    -> ::gsl::span<const ::vont::Registrator *const> {
  return {::g_arrayWithSize.data(),
          ::gsl::narrow_cast<::std::size_t>(::g_arrayWithSize.size())};
}

} // namespace vont
