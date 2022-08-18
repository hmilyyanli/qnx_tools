#include <iostream>
#include <system_error>
#include <cassert>

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
   - valgrind, clang santizers
4. logical errors
   - everything else
*/

// SOURCE

enum class MyEnum : int {
    e_OK = 0,
    e_TOO_LARGE,
    e_TOO_SMALL,
};

template<>
struct std::is_error_code_enum<::MyEnum> : ::std::true_type {};

class MyErrorCategory final : public ::std::error_category {
    MyErrorCategory() = default;
public:
    static auto instance() -> const MyErrorCategory& {
        static const MyErrorCategory g_singelton;
        return g_singelton;
    }

    // ACCESSORS
    auto name() const noexcept -> const char* {
        return "MyEnum";
    }

    auto message(int value) const -> ::std::string {
        switch (static_cast<::MyEnum>(value)) {
        case MyEnum::e_OK:
            return "e_OK";
        case MyEnum::e_TOO_LARGE:
            return "e_TOO_LARGE";
        case MyEnum::e_TOO_SMALL:
            return "e_TOO_SMALL";
        }
        assert(false && "unreachable");
        return "unknown";
    }
};

auto make_error_code(MyEnum f_enum) -> ::std::error_code {
    return ::std::error_code{ static_cast<int>(f_enum),
    ::MyErrorCategory::instance() };
}

// HEADER

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
        error_code = make_error_code(::MyEnum::e_TOO_SMALL);
        return { 0. };
    }
    else if (number.value >= max) {
        error_code = make_error_code(::MyEnum::e_TOO_LARGE);
        return { 0. };
    }
    return { number.value * number.value };
}

// CLIENT CODE

auto evalPolynomial(::std::error_code& error_code, Number number) -> Number
// Precondition: 0 < number < 10
// Postcondition: (x + 3)^2
{
    constexpr double min = 0.;
    constexpr double max = 10.;
    if (!(min < number.value)) {
        error_code = make_error_code(::std::errc::argument_out_of_domain);
        return { 0. };
    }
    else if (!(number.value < max)) {
        error_code = make_error_code(::std::errc::argument_out_of_domain);
        return { 0. };
    }
    constexpr double offset = 3.;
    return ::square(error_code, { number.value + offset });
}

auto main() -> int {
    auto ec = ::std::error_code{};
    auto number = Number{ .1 };
    number = ::evalPolynomial(ec, number);
    if (ec)
        ::std::cerr << "unexpected!\n";
    ::std::cout << "number: " << number.value << "\n"
        << ec.category().name() << " " << ec.message() << "\n";
    number = ::evalPolynomial(ec, number);
    if (ec)
        ::std::cout << "ec invalid!\n";
    ::std::cout << "number: " << number.value << "\n"
        << ec.category().name() << " " << ec.message() << "\n";
    if (ec == make_error_code(::std::errc::argument_out_of_domain))
        ::std::cout << "Handle me!\n";
}
