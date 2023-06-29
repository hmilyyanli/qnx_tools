#include <cassert>
#include <iostream>

namespace {

class BaseInterface {
public:
  // CREATORS
  BaseInterface() = default;
  BaseInterface(const BaseInterface &) = default;
  BaseInterface(BaseInterface &&) noexcept = delete;

  virtual auto operator=(const BaseInterface &other) -> BaseInterface &
  {
      if(this == &other)
      {
          std::cout << "BaseInterface same" << std::endl;
      }
      std::cout << "BaseInterface " << std::endl;
      return *this;
  }
  auto operator=(BaseInterface &&) noexcept -> BaseInterface & = delete;


  virtual ~BaseInterface() = default;

  // MANIPULATORS
  virtual auto Calc() const -> int{return 0;}
};

class Derived final : public BaseInterface {
  // DATA
  int m_value;

public:
  // CREATORS
  explicit Derived(int f_value) : m_value{f_value} {}

  auto Calc() const -> int final { return this->m_value; }
  virtual auto operator=(const BaseInterface &other) -> Derived &
  {
      if (const Derived* d = dynamic_cast<const Derived*>(&other))
      {
            std::cout << "val " << d->m_value << std::endl;
            this->m_value=d->m_value;
            return *this;
      }
      return *this;    
  }
};

struct BaseInterfaceUtil {
  static auto Copy(BaseInterface &f_lhs, BaseInterface &f_rhs) -> void {
     f_lhs = f_rhs;
     //std::cout << "val " << f_rhs.Calc() << std::endl;
  }
};

} // namespace

auto main() -> int {
  Derived d1{10};
  Derived d2{12};
  BaseInterfaceUtil::Copy(d1, d2);
  //d1 = d2;
  assert(d1.Calc() == 12 && "Sth. went error.");
}
