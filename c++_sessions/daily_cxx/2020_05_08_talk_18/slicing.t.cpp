#include <cassert>

namespace {

class BaseInterface {
public:
  // CREATORS
  BaseInterface() = default;
  BaseInterface(const BaseInterface &) = delete;
  BaseInterface(BaseInterface &&) noexcept = delete;

  auto operator=(const BaseInterface &) -> BaseInterface & = delete;
  auto operator=(BaseInterface &&) noexcept -> BaseInterface & = delete;


  virtual ~BaseInterface() = default;

  // MANIPULATORS
  virtual auto Calc() -> int = 0;
};

class Derived final : public BaseInterface {
  // DATA
  int m_value;

public:
  // CREATORS
  explicit Derived(int f_value) : m_value{f_value} {}

  auto Calc() -> int final { return this->m_value; }
};

struct BaseInterfaceUtil {
  static auto Copy(BaseInterface &f_lhs, const BaseInterface &f_rhs) -> void {
    // f_lhs = f_rhs;
  }
};

} // namespace

auto main() -> int {
  Derived d1{10};
  Derived d2{12};
  BaseInterfaceUtil::Copy(d1, d2);
  // d1 = d2;
  assert(d1.Calc() == 12 && "Sth. went error.");
}
