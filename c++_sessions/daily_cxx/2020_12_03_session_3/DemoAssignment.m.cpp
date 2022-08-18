class A {
public:
  auto operator=(A const &) & -> A & = default;
};

A operator+(A const &, A const &) { return A{}; }

void demoAssignment() {
  int a;
  int b = 1;
  int c = 2;
  a = b + c;
  // (b+c) = a;

  A a1;
  A a2;
  A a3 = a1 + a2;
  // (a1 + a2) = a3;
}

auto main() -> int {}
