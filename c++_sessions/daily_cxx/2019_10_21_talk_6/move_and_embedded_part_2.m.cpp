#include <cassert>
#include <iostream>
#include <utility>

template <class T> class Container {
  T m_data;

public:
  template <class... Ts>
  explicit Container(std::in_place_t, Ts &&... f_ts)
      : m_data{std::forward<Ts>(f_ts)...} {}
  Container() = delete;
  Container(const Container &) = delete;
  Container(Container &&) noexcept = default;
  auto operator=(const Container &) -> Container & = delete;
  auto operator=(Container &&) noexcept -> Container & = default;
  auto calc() & -> int { return 1; }
  auto calc() const & -> int { return 2; }
  auto giveUpResource() && -> void;
};

template <class T> auto Container<T>::giveUpResource() && -> void {
  T tmp = std::move(this->m_data);
}

class Printer {
public:
  Printer() { std::cout << "Printer()\n"; }
  Printer(const Printer &) { std::cout << "Printer(const Printer)\n"; }
  Printer(Printer &&) noexcept { std::cout << "Printer(Printer&&)\n"; }
  ~Printer() { std::cout << "~Printer()\n"; }

  auto operator=(const Printer &) -> Printer & {
    std::cout << "operator=(const Printer&)\n";
    return *this;
  }
  auto operator=(Printer &&) noexcept -> Printer & {
    std::cout << "operator=(Printer&&)\n";
    return *this;
  }
};

void callee(Container<Printer> &f_lv, const Container<Printer> &f_clv,
            Container<Printer> &&f_rv) {
  assert(f_lv.calc() == 1);
  assert(f_clv.calc() == 2);
  // f_rv.giveUpResource(); // compile error
  std::move(f_rv).giveUpResource();
}

int main() {
  Container<Printer> c{std::in_place};
  assert(c.calc() == 1);
  callee(c, c, std::move(c));
  std::cout << "Example finished\n";
}
