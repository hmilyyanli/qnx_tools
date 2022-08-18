#ifndef VONT_REGISTRATOR_HPP_INCLUDED
#define VONT_REGISTRATOR_HPP_INCLUDED

#include <compare>

namespace vont {

class RegistratorIterator;
class Registrator;
class RegistratorImpl;

//                         =========================
//                         class RegistratorIterator
//                         =========================

class RegistratorIterator {
  // DATA
  const ::vont::RegistratorImpl *m_data_p;

public:
  // CREATORS
  explicit RegistratorIterator(
      const ::vont::RegistratorImpl *f_data_p = nullptr) noexcept
      : m_data_p{f_data_p} {}

  // MANIPULATORS
  auto operator++() & -> ::vont::RegistratorIterator &;

  // ACCESSORS
  auto operator*() const -> const ::vont::Registrator &;
  auto operator-> () const -> const ::vont::Registrator *;
  auto operator<=>(const RegistratorIterator &) const = default;
};

//                         =================
//                         class Registrator
//                         =================

class Registrator {
protected:
  // PROTECTED CREATORS
  Registrator() noexcept = default;
  Registrator(const Registrator &) = default;
  Registrator(Registrator &&) noexcept = default;

  // PROTECTED MANIPULATORS
  auto operator=(const Registrator &) -> Registrator & = default;
  auto operator=(Registrator &&) noexcept -> Registrator & = default;

public:
  // CLASS METHODS
  static auto begin() noexcept -> ::vont::RegistratorIterator;

  // CREATORS
  virtual ~Registrator() = default;

  // ACCESSORS
  virtual auto getName() const -> const char * = 0;
};

//                         =====================
//                         class RegistratorImpl
//                         =====================

class RegistratorImpl : public ::vont::Registrator {
  // DATA
  const ::vont::RegistratorImpl *m_next_p{nullptr};

  // FRIENDS
  friend class ::vont::RegistratorIterator;

protected:
  // PROTECTED CREATORS
  RegistratorImpl() noexcept;
  RegistratorImpl(const RegistratorImpl &) = default;
  RegistratorImpl(RegistratorImpl &&) noexcept = default;
  ~RegistratorImpl() noexcept = default;

  // PROTECTED MANIPULATORS
  auto operator=(const RegistratorImpl &) -> RegistratorImpl & = default;
  auto operator=(RegistratorImpl &&) noexcept -> RegistratorImpl & = default;
};

} // namespace vont

// ============================================================================
//                              INLINE DEFINITIONS
// ============================================================================

namespace vont {

//                         -------------------------
//                         class RegistratorIterator
//                         -------------------------

// MANIPULATORS
inline auto RegistratorIterator::operator++() & -> ::vont::RegistratorIterator & {
  if (this->m_data_p)
    this->m_data_p = this->m_data_p->m_next_p;
  return *this;
}

// ACCESSORS
inline auto RegistratorIterator::operator*() const -> const ::vont::Registrator & {
  return *this->m_data_p;
}
inline auto RegistratorIterator::operator-> () const -> const ::vont::Registrator * {
  return this->m_data_p;
}

} // namespace vont

#endif // VONT_REGISTRATOR_HPP_INCLUDED
