#ifndef DXX_SIU_METRE_INCLUDED
#define DXX_SIU_METRE_INCLUDED

namespace dxx::siu {

//                         ===========
//                         class Metre
//                         ===========

class Metre {
  double m_value;

public:
  explicit constexpr Metre(double f_value) : m_value{f_value} {}

  auto setValue(double f_value) -> Metre & {
    this->m_value = f_value;
    return *this;
  }

  constexpr auto value() const -> double { return this->m_value; }
};

} // namespace dxx::siu

#endif // DXX_SIU_METRE_INCLUDED
