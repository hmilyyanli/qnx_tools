#include <iostream>

struct Token {
  char kind;
  double value;
};

auto operator<<(::std::ostream &os, const Token &t) -> ::std::ostream & {
  if (t.kind == '8') {
    os << t.value;
  } else {
    os << t.kind;
  }
  return os;
}


auto main() -> int{
  // (1.5+4)*11
  Token t0{'('};
  Token t1{'8', 1.5};
  Token t2{'+'};
  Token t3{'8', 4.};
  Token t4{')'};
  Token t5{'*'};
  Token t6{'8', 11.};
  ::std::cout << t0 << t1 << t2 << t3 << t4 << t5 << t6 << '\n';
}
