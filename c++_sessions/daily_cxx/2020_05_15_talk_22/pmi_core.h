#ifndef PMI_CORE_H_INCLUDED
#define PMI_CORE_H_INCLUDED

namespace pmi {

struct Integer {
  int value;
};

class Foo {
  int m_value;

  auto DoDetails(int f_number) const -> int;

public:
  explicit Foo(::pmi::Integer f_value) : m_value{f_value.value} {}

  auto DoSth(::pmi::Integer f_number) const -> ::pmi::Integer;
};

} // namespace pmi

#endif // PMI_CORE_H_INCLUDED
