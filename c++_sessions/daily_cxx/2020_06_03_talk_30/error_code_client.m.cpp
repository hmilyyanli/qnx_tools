#include <iostream>
#include <system_error>

/*
1. compile time errors
   - syntax error
   - type safety errors
   - static_assert
   - -Werror
2. link time errors
   - missing symbols
3. run-time errors (*)
   - assert
   - execution of program
4. logical errors
   - everything else
*/

struct Number {
    double value;
};

auto square(::std::error_code& error_code, Number number)->Number
// Square the specified 'number' and in case of an error load the reason into the specified 'error_code'.
// Precondition: 0 < number < 10
// Postcondition: 0 < number < 100
{
    constexpr double min = 0.;
    constexpr double max = 10.;
    if (min >= number.value) {
        error_code = make_error_code(::std::errc::argument_out_of_domain);
        return { 0. };
    }
    else if (number.value >= max) {
        error_code = make_error_code(::std::errc::argument_out_of_domain);
        return { 0. };
    }
    return { number.value * number.value };
}

auto main() -> int {
    auto ec = ::std::error_code{};
    auto number = Number{ 5. };
    number = ::square(ec, number);
    if (ec)
        ::std::cerr << "unexpected!\n";
    ::std::cout << "number: " << number.value << "\n"
        << ec.category().name() << " " << ec.message() << "\n";
    number = ::square(ec, number);
    if (ec)
        ::std::cout << "ec invalid!\n";
    ::std::cout << "number: " << number.value << "\n"
        << ec.category().name() << " " << ec.message() << "\n";
}
