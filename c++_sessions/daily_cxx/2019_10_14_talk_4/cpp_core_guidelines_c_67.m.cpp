#include <cassert>

// Bad example BEGIN
class BaseBad {
public:
  virtual ~BaseBad() = default;
  virtual int calc() const = 0;
};

class Derived1 : public BaseBad {
  int m_data;

public:
  explicit Derived1(int f_data) : m_data{f_data} {}

  int calc() const override { return this->m_data; }
};

void slicing(BaseBad &b) {
  Derived1 d{10};
  b = d; // oops, slicing!
}
// Bad example END

// Example BEGIN
class BaseGood {
protected:
  BaseGood() = default;
  BaseGood(const BaseGood &) = default;
  BaseGood(BaseGood &&) noexcept = default;

  auto operator=(const BaseGood &) & -> BaseGood & = default;
  auto operator=(BaseGood &&) & -> BaseGood & = default;

public:
  virtual ~BaseGood() = default;
  virtual int calc() const = 0;
};

class Derived2 : public BaseGood {
  int m_data;

public:
  explicit Derived2(int f_data) : m_data{f_data} {}

  int calc() const override { return this->m_data; }
};

void slicing(BaseGood &b) {
  Derived2 d{11};
  // b = d; // compile error
}
// Example END

int main() {
  constexpr auto val1 = 100;
  constexpr auto val2 = 200;

  Derived1 d11{val1};
  slicing(d11);
  assert(d11.calc() == val1);
  const Derived1 d12{val2};
  d11 = d12;
  assert(d11.calc() == val2);

  Derived2 d21{val1};
  slicing(d21);
  assert(d21.calc() == val1);
  const Derived2 d22{val2};
  d21 = d22;
  assert(d21.calc() == val2);
}
