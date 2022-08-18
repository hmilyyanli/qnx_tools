#include <aempty.h> // B
#include <utility>  // move

// Exercise 1
//   We expect that the constructors and assignment operators are called in the
//   order of declared members, an that the destructor are called in the reverse
//   order.

// class A {
// ::B<double> c;
// ::B<int> b;
//
// public:
// auto &i() & { return c.i(); }
// };

// Exercise 2
//   I expect the same output as for exercise 1.

// class A : public ::B<double> {
//   ::B<int> b;
// };

// Exercise 3
//   I expect the same output as for exercise 1.

class A : public ::B<double>, public ::B<int> {
public:
  auto &i() & { return this->::B<double>::i(); }
};

void lifecycle() {
  using ::std::cout;
  cout << "=== begin " << __PRETTY_FUNCTION__ << '\n';
  {
    cout << "{\n=== begin Block\n";
    cout << "=== A a1;\n";
    ::A a1;
    cout << "a1.i: " << a1.i() << '\n';
    a1.i() = 42;
    cout << "a1.i=42: " << a1.i() << '\n';
    cout << "=== A a2 = a1;\n";
    A a2 = a1;
    cout << "a2.i: " << a2.i() << '\n';
    cout << "=== A a3(a1);\n";
    A a3(a1);
    cout << "a3.i: " << a3.i() << '\n';
    a1.i() = 43;
    cout << "=== a1.i = 43: " << a1.i() << '\n';

    cout << "=== a2 = a1\n";
    a2 = a1;
    cout << "a2.i: " << a2.i() << '\n';

    cout << "=== A a4(std::move(a1));\n";
    A a4(std::move(a1));
    cout << "a1.i: " << a1.i() << '\n';
    cout << "a4.i: " << a4.i() << '\n';

    cout << "a4.i = std::move(a3);\n";
    a4 = std::move(a3);
    cout << "a3.i: " << a3.i() << '\n';
    cout << "a4.i: " << a4.i() << '\n';

    cout << "=== end Block \n}\n";
  }
  cout << "=== end " << __PRETTY_FUNCTION__ << '\n';
}

auto main() -> int { ::lifecycle(); }
