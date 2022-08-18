#include <iostream>

struct FirstOperantError {};
struct SecondOperantError {};
struct BadExpressionError {};

auto main() -> int try {
  ::std::cout << "Please enter expression (we can handle +, -, * and /)\n"
              << "add an 'x' to end expression (e.g., 1+2*3): ";

  int lval{};
  int rval{};
  ::std::cin >> lval;
  if (!::std::cin) {
    throw FirstOperantError{};
  }

  for (char op; ::std::cin >> op;) {
    if (op != 'x') {
      ::std::cin >> rval;
    }
    if (!::std::cin) {
      throw SecondOperantError{};
    }
    switch (op) {
    case '+':
      lval += rval;
      break;
    case '-':
      lval -= rval;
      break;
    case '*':
      lval *= rval;
      break;
    case '/':
      lval /= rval;
      break;
    default:
      ::std::cout << "Result: " << lval << '\n';
      return 0;
    }
  }
  throw BadExpressionError{};
} catch (...) {
  ::std::cerr << "An error occurred!\n";
}
