#ifndef VONT_REGISTRATOR_HPP_INCLUDED
#define VONT_REGISTRATOR_HPP_INCLUDED

#include <gsl/gsl>

namespace vont {

//                         =================
//                         class Registrator
//                         =================

class Registrator {
protected:
  // PROTECTED CREATORS
  Registrator() noexcept;
  Registrator(const Registrator &) = default;
  Registrator(Registrator &&) noexcept = default;

  // PROTECTED MANIPULATORS
  auto operator=(const Registrator &) -> Registrator & = default;
  auto operator=(Registrator &&) noexcept -> Registrator & = default;

public:
  // CLASS METHODS
  static auto GetRegistry() noexcept
      -> ::gsl::span<const ::vont::Registrator *const>;

  // CREATORS
  virtual ~Registrator() = default;

  // ACCESSORS
  virtual auto GetName() const -> const char * = 0;
};

} // namespace vont

#endif // VONT_REGISTRATOR_HPP_INCLUDED
