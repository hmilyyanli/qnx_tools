#include <cctype>
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

auto operator>>(::std::istream &is, Token &t) -> ::std::istream & {
  char c{};
  is >> c;
  if (::std::isdigit(c)) {
    t.kind = '8';
    is.putback(c);
    is >> t.value;
  } else {
    t.kind = c;
  }
  return is;
}

auto main() -> int {
  Token t{};
  while (::std::cin >> t) {
    ::std::cout << t << '\n';
  }
}
